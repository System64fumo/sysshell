#include "clipboard.hpp"
#include <gtk4-layer-shell.h>
#include <gdk/wayland/gdkwayland.h>
#include <gtkmm/eventcontrollerkey.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <glibmm/main.h>
#include <fcntl.h>
#include <fstream>
#include <thread>

static void data_control_offer(void* data, struct zwlr_data_control_offer_v1* offer, const char* mime_type) {
	auto self = static_cast<clipboard*>(data);
	//std::printf("Available mime types: %s\n", mime_type);

	std::string mime = mime_type;
	std::string clipboard_path = std::string(getenv("XDG_RUNTIME_DIR")) + "/sysshell_clipboard.tmp";

	// Skip unsupported mime types
	if (!(mime == "text/plain" || mime == "STRING" || mime == "TEXT" || mime == "x-special/gnome-copied-files"))
		return;

	// Write clipboard data to a temporary file
	FILE *file_ptr = fopen(clipboard_path.c_str(), "w+");
	fclose(file_ptr);
	int fd = open(clipboard_path.c_str(), O_WRONLY);

	// TODO: Not everything is a plain text string, Add support for other mime types
	zwlr_data_control_offer_v1_receive(offer, mime_type, fd);
	zwlr_data_control_offer_v1_destroy(offer);
	close(fd);

	// Slight delay has to happen between writing and reading the file
	// Again this is annoying and i don't want this
	// But a temporary solution is better than no solution
	std::thread([self, clipboard_path]() {
		usleep(100 * 1000);
		std::ifstream file(clipboard_path);
		std::string contents((std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>());
		remove(clipboard_path.c_str());

		Glib::signal_idle().connect([&, self, contents]() {
			self->add_item(contents);
			return false;
		});
	}).detach();
}

struct zwlr_data_control_offer_v1_listener data_control_offer_listener = {
	data_control_offer
};

static void data_control_device_offer(void* data, struct zwlr_data_control_device_v1* device, struct zwlr_data_control_offer_v1* offer) {
	if (!offer)
		return;
	zwlr_data_control_offer_v1_add_listener(offer, &data_control_offer_listener, data);
}

static void data_control_device_selection(void* data, struct zwlr_data_control_device_v1* device, struct zwlr_data_control_offer_v1* offer) {
	if (!offer)
		return;
	zwlr_data_control_offer_v1_destroy(offer);
}

static void data_control_device_primary_selection(void* data, struct zwlr_data_control_device_v1* device, struct zwlr_data_control_offer_v1* offer) {
	if (!offer)
		return;
	zwlr_data_control_offer_v1_destroy(offer);
}

static struct zwlr_data_control_device_v1_listener data_control_device_listener = {
	.data_offer = data_control_device_offer,
	.selection = data_control_device_selection,
	.primary_selection = data_control_device_primary_selection
};

static void registry_handler(void* data, struct wl_registry* registry,
	uint32_t id, const char* interface, uint32_t version) {

	auto self = static_cast<clipboard*>(data);

	if (strcmp(interface, zwlr_data_control_manager_v1_interface.name) == 0) {
		self->control_manager = (zwlr_data_control_manager_v1*)
			wl_registry_bind(registry, id,
				&zwlr_data_control_manager_v1_interface, 1u);
		zwlr_data_control_device_v1* device =
			zwlr_data_control_manager_v1_get_data_device(
			self->control_manager,
			self->seat);
		zwlr_data_control_device_v1_add_listener(device, &data_control_device_listener, self);

		wl_display_roundtrip(self->display);
	}
}

static wl_registry_listener registry_listener = {
	&registry_handler
};

clipboard::clipboard() : gdk_clipboard(get_clipboard()), box_main(Gtk::Orientation::VERTICAL) {
	// TODO: Add positioning control (Ideally place under the cursor or near the text entry field)

	// Layer shell stuff
	gtk_layer_init_for_window(gobj());
	gtk_layer_set_namespace(gobj(), "sysclip");
	gtk_layer_set_layer(gobj(), GTK_LAYER_SHELL_LAYER_OVERLAY);
	gtk_layer_set_keyboard_mode(gobj(), GTK_LAYER_SHELL_KEYBOARD_MODE_ON_DEMAND);

	// UI Setup
	set_name("sysclip");
	set_hide_on_close(true);
	set_default_size(300, 400);

	set_child(box_main);
	//box_main.append(entry_search); // TODO: Work on this later
	box_main.append(flowbox_main);
	flowbox_main.set_max_children_per_line(1);
	flowbox_main.set_selection_mode(Gtk::SelectionMode::NONE);

	flowbox_main.signal_child_activated().connect([&](Gtk::FlowBoxChild* child) {
		auto box_hist = dynamic_cast<Gtk::Box*>(child->get_child());
		auto label_hist = dynamic_cast<Gtk::Label*>(box_hist->get_children()[0]);
		gdk_clipboard->set_text(label_hist->get_text());
	});

	auto controller = Gtk::EventControllerKey::create();
	controller->signal_key_pressed().connect([&](const guint &keyval, const guint &keycode, const Gdk::ModifierType &state) {
		if (keyval == 65307) // Escape key
			hide();

		return false;
	}, true);
	add_controller(controller);

	// Clipboard monitor setup
	gdk_display = gdk_display_get_default();
	gdk_seat = gdk_display_get_default_seat(gdk_display);
	seat = gdk_wayland_seat_get_wl_seat(gdk_seat);
	auto g_display = gdk_wayland_display_get_wl_display(gdk_display);
	display = wl_display_connect(NULL);
	auto registry = wl_display_get_registry(g_display);
	wl_registry_add_listener(registry, &registry_listener, this);
}

void clipboard::add_item(const std::string& value) {
	auto flowbox_child_hist = Gtk::make_managed<Gtk::FlowBoxChild>();
	auto box_hist = Gtk::make_managed<Gtk::Box>();
	auto label_hist = Gtk::make_managed<Gtk::Label>(value);
	auto button_hist = Gtk::make_managed<Gtk::Button>("x");

	label_hist->set_hexpand(true);
	label_hist->set_xalign(0);

	button_hist->signal_clicked().connect([&, flowbox_child_hist]() {
		flowbox_main.remove(*flowbox_child_hist);
	});

	flowbox_child_hist->set_child(*box_hist);
	box_hist->append(*label_hist);
	box_hist->append(*button_hist);

	// TODO: This is terrible, Maybe re-sort instead of re-create?

	// Remove existing item
	for (const auto& child : flowbox_main.get_children()) {
		auto fbox_child = dynamic_cast<Gtk::FlowBoxChild*>(child);
		auto fbc_box_hist = dynamic_cast<Gtk::Box*>(fbox_child->get_child());
		auto fbc_label_hist = dynamic_cast<Gtk::Label*>(fbc_box_hist->get_children()[0]);
		if (fbc_label_hist->get_text() == label_hist->get_text()) {
			flowbox_main.remove(*fbox_child);
		}
	}

	flowbox_main.prepend(*flowbox_child_hist);

	// TODO: Add config option to set this
	if (flowbox_main.get_children().size() > 10)
		flowbox_main.remove(*flowbox_main.get_children()[0]);
}

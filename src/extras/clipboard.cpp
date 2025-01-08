#include "clipboard.hpp"
#include <gtk4-layer-shell.h>
#include <gdk/wayland/gdkwayland.h>
#include <fcntl.h>

static void registry_handler(void* data, struct wl_registry* registry,
	uint32_t id, const char* interface, uint32_t version) {

	auto self = static_cast<clipboard*>(data);

	if (strcmp(interface, zwlr_data_control_manager_v1_interface.name) == 0) {
		self->control_manager = (zwlr_data_control_manager_v1*)
			wl_registry_bind(registry, id,
				&zwlr_data_control_manager_v1_interface, 1u);
		self->setup_clipboard_monitor();
	}
}

static wl_registry_listener registry_listener = {
	&registry_handler
};

static void data_control_offer(void* data, struct zwlr_data_control_offer_v1* zwlr_data_control_offer_v1, const char* mime_type) {
	//std::printf("Available mime types: %s\n", mime_type);
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
	//auto self = static_cast<clipboard*>(data);

	if (!offer)
		return;

	// Temporarily disable this since it's a security risk
	return;

	// Write clipboard data to a temporary file
	// This is horrible but i really can't think of any non blocking way to do this
	FILE *file = fopen("/tmp/test", "a");
	fclose(file);
	int fd = open("/tmp/test", O_WRONLY);

	// TODO: Not everything is a plain text string, Add support for other mime types
	zwlr_data_control_offer_v1_receive(offer, "text/plain", fd);

	close(fd);

	zwlr_data_control_offer_v1_destroy(offer);
}

static void data_control_device_finished(void* data, struct zwlr_data_control_device_v1* device) {
	zwlr_data_control_device_v1_destroy(device);
}

static void data_control_device_primary_selection(void* data, struct zwlr_data_control_device_v1* device, struct zwlr_data_control_offer_v1* offer) {
	//zwlr_data_control_offer_v1_destroy(offer);
}

static struct zwlr_data_control_device_v1_listener data_control_device_listener = {
	.data_offer = data_control_device_offer,
	.selection = data_control_device_selection,
	.finished = data_control_device_finished,
	.primary_selection = data_control_device_primary_selection
};

clipboard::clipboard() {
	// TODO: Actually add the UI for this
	std::printf("Clipboard loaded\n");
	set_hide_on_close(true);

	// Layer shell stuff
	gtk_layer_init_for_window(gobj());
	gtk_layer_set_namespace(gobj(), "clipboard");
	gtk_layer_set_layer(gobj(), GTK_LAYER_SHELL_LAYER_OVERLAY);
	gtk_layer_auto_exclusive_zone_enable(gobj());

	// Initial setup
	gdk_display = gdk_display_get_default();
	gdk_seat = gdk_display_get_default_seat(gdk_display);
	seat = gdk_wayland_seat_get_wl_seat(gdk_seat);
	auto g_display = gdk_wayland_display_get_wl_display(gdk_display);
	display = wl_display_connect(NULL);
	auto registry = wl_display_get_registry(g_display);
	wl_registry_add_listener(registry, &registry_listener, this);
}

void clipboard::setup_clipboard_monitor() {
	zwlr_data_control_device_v1* device = zwlr_data_control_manager_v1_get_data_device(control_manager, seat);
	zwlr_data_control_device_v1_add_listener(device, &data_control_device_listener, this);

	wl_display_roundtrip(display);
}

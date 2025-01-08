#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <gtkmm/flowbox.h>
#include "../wlr-data-control-unstable-v1.h"

class clipboard : public Gtk::Window {
	public:
		clipboard();

		zwlr_data_control_manager_v1* control_manager;

		GdkDisplay* gdk_display;
		GdkSeat* gdk_seat;
		wl_seat* seat;
		wl_display* display;

	private:
		Gtk::Box box_main;
		Gtk::Entry entry_search;
		Gtk::FlowBox flowbox_main;
};

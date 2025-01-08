#include <gtkmm/window.h>
#include "../wlr-data-control-unstable-v1.h"

class clipboard : public Gtk::Window {
	public:
		clipboard();

		zwlr_data_control_manager_v1* control_manager;

		GdkDisplay* gdk_display;
		GdkSeat* gdk_seat;
		wl_seat* seat;
		wl_display* display;
};

EXEC = sysshell
PKGS = gtkmm-4.0 gtk4-layer-shell-0 wireplumber-0.5
DESTDIR = $(HOME)/.local

CXXFLAGS = -march=native -mtune=native -Os -s -Wall -flto=auto -fno-exceptions
CXXFLAGS += $(shell pkg-config --cflags $(PKGS))
LDFLAGS += $(shell pkg-config --libs $(PKGS))

all: $(EXEC)

install: $(EXEC)
	mkdir -p $(DESTDIR)/bin
	install $(EXEC) $(DESTDIR)/bin/$(EXEC)

clean:
	rm $(EXEC)

$(EXEC): src/main.cpp src/config_parser.cpp
	$(CXX) -o $(EXEC) \
	src/main.cpp \
	src/config_parser.cpp \
	$(LDFLAGS) \
	$(CXXFLAGS) \
	-I include

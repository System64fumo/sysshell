EXEC = sysshell
PKGS = gtkmm-4.0 gtk4-layer-shell-0 wireplumber-0.5 dbus-1 libcurl pam
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)
DESTDIR = $(HOME)/.local

CXXFLAGS = -march=native -mtune=native -Os -s -Wall -flto=auto -fno-exceptions
CXXFLAGS += $(shell pkg-config --cflags $(PKGS))
LDFLAGS = $(shell pkg-config --libs $(PKGS))

all: $(EXEC)

install: $(EXEC)
	mkdir -p $(DESTDIR)/bin
	install $(EXEC) $(DESTDIR)/bin/$(EXEC)

clean:
	rm $(EXEC) $(OBJS)

$(EXEC): $(OBJS)
	$(CXX) -o $(EXEC) \
	$(OBJS) \
	$(LDFLAGS) \
	$(CXXFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ \
	$(CXXFLAGS) \
	-I include

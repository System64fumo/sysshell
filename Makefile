EXEC = sysshell
PKGS = gtkmm-4.0 gtk4-layer-shell-0
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)
DESTDIR = $(HOME)/.local

CXXFLAGS += -Os -s -Wall -flto=auto -fno-exceptions
LDFLAGS += -Wl,-O1,--as-needed,-z,now,-z,pack-relative-relocs

CXXFLAGS += $(shell pkg-config --cflags $(PKGS))
LDFLAGS += $(shell pkg-config --libs $(PKGS))

all: $(EXEC)

install: $(EXEC)
	mkdir -p $(DESTDIR)/bin
	install $(EXEC) $(DESTDIR)/bin/$(EXEC)

clean:
	rm $(EXEC) $(OBJS)

$(EXEC): $(OBJS)
	$(CXX) -o $(EXEC) \
	$(OBJS) \
	$(CXXFLAGS) \
	$(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ \
	$(CXXFLAGS) \
	-I include

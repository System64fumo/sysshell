BINS = sysshell
PKGS = gtkmm-4.0 gtk4-layer-shell-0
SRCS = $(wildcard src/*.cpp src/libs/*.cpp)
OBJS = $(SRCS:.cpp=.o)

PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin
DATADIR ?= $(PREFIX)/share

CXXFLAGS += -Os -s -Wall -flto=auto -fno-exceptions
LDFLAGS += -Wl,-O1,--as-needed,-z,now,-z,pack-relative-relocs

CXXFLAGS += $(shell pkg-config --cflags $(PKGS))
LDFLAGS += $(shell pkg-config --libs $(PKGS))

JOB_COUNT := $(BINS) $(OBJS)
JOBS_DONE := $(shell ls -l $(JOB_COUNT) 2> /dev/null | wc -l)

define progress
	$(eval JOBS_DONE := $(shell echo $$(($(JOBS_DONE) + 1))))
	@printf "[$(JOBS_DONE)/$(shell echo $(JOB_COUNT) | wc -w)] %s %s\n" $(1) $(2)
endef

all: $(BINS)

install: $(BINS)
	@echo "Installing..."
	@install -D -t $(DESTDIR)$(BINDIR) $(BINS)
	@install -D -t $(DESTDIR)$(DATADIR)/sys64/shell config.conf

clean:
	@echo "Cleaning up"
	@rm $(BINS) $(OBJS)

$(BINS): $(OBJS)
	$(call progress, Linking $@)
	@$(CXX) -o $(BINS) \
	$(OBJS) \
	$(CXXFLAGS) \
	$(LDFLAGS)

%.o: %.cpp
	$(call progress, Compiling $@)
	@$(CXX) -c $< -o $@ \
	$(CXXFLAGS) \
	-I include

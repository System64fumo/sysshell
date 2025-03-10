BINS = sysshell
PKGS = gtkmm-4.0 gtk4-layer-shell-0
SRCS = $(wildcard src/*.cpp src/libs/*.cpp src/extras/*.cpp)

PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin
DATADIR ?= $(PREFIX)/share
BUILDDIR = build

CXXFLAGS += -Os -s -Wall -flto=auto -fno-exceptions
LDFLAGS += -Wl,-O1,--no-as-needed,-z,now,-z,pack-relative-relocs

CXXFLAGS += $(shell pkg-config --cflags $(PKGS))
LDFLAGS += $(shell pkg-config --libs $(PKGS))

OBJS = $(patsubst src/%.cpp, $(BUILDDIR)/%.o, $(SRCS))

PROTOS = $(wildcard proto/*.xml)
PROTO_HDRS = $(patsubst proto/%.xml, src/%.h, $(PROTOS))
PROTO_SRCS = $(patsubst proto/%.xml, src/%.c, $(PROTOS))
PROTO_OBJS = $(patsubst src/%.c, $(BUILDDIR)/%.o, $(PROTO_SRCS))

JOB_COUNT := $(BINS) $(OBJS) $(PROTO_HDRS) $(PROTO_SRCS) $(PROTO_OBJS)
JOBS_DONE := $(shell ls -l $(JOB_COUNT) 2> /dev/null | wc -l)

define progress
	$(eval JOBS_DONE := $(shell echo $$(($(JOBS_DONE) + 1))))
	@printf "[$(JOBS_DONE)/$(shell echo $(JOB_COUNT) | wc -w)] %s %s\n" $(1) $(2)
endef

all: $(BINS)

install: $(BINS)
	@echo "Installing..."
	@install -D -t $(DESTDIR)$(BINDIR) $(BUILDDIR)/$(BINS)
	@install -D -t $(DESTDIR)$(DATADIR)/sys64/shell config.conf

clean:
	@echo "Cleaning up"
	@rm -rf $(BUILDDIR) $(PROTO_HDRS) $(PROTO_SRCS)

$(BINS): $(PROTO_HDRS) $(PROTO_SRCS) $(PROTO_OBJS) $(OBJS)
	$(call progress, Linking $@)
	@$(CXX) -o $(BUILDDIR)/$@ \
	$(OBJS) \
	$(PROTO_OBJS) \
	$(CXXFLAGS) \
	$(LDFLAGS) -lwayland-client

$(BUILDDIR)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(call progress, Compiling $@)
	@$(CXX) -c $< -o $@ \
	$(CXXFLAGS) \
	-I include

$(BUILDDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(call progress, Compiling $@)
	@$(CC) -c $< -o $@ $(CFLAGS)

$(PROTO_HDRS): src/%.h : proto/%.xml
	$(call progress, Creating $@)
	@wayland-scanner client-header $< $@

$(PROTO_SRCS): src/%.c : proto/%.xml
	$(call progress, Creating $@)
	@wayland-scanner public-code $< $@

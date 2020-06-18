#
#     make help: gives some help
#

# basic configuration
executables     := exo1 exo2 exo3 exo4
modules         :=
others          := out

ifdef PROF
distfiles       := Makefile pokemon.h pokedex.dat $(addsuffix .c,$(executables))
executables     := $(executables) $(addsuffix -soluce,$(executables)) generate
dist            := ../csc4103-cf1.tar.xz
else
distfiles       := .
dist            := ../csc4103-cf1-rendu.tar.xz
endif

# exo1 is created from objects-exo1, which is itself created from exo1.c
$(foreach cur,$(executables),$(eval objects-$(cur) := $(addsuffix .o,$(cur))))

#   advanced configuration
srcdir          ?= 
dstdir          ?= 
objdir          ?= 

_CFLAGS   += -g -O0 -Wall -Wextra -Wno-unused-variable -Wno-deprecated-declarations -fPIC
CFLAGS    += -std=gnu11 $(_CFLAGS)
CXXFLAGS  += -std=gnu++17 $(_CFLAGS)
LDFLAGS   += -std=gnu++17
LIBS      += -lpthread

CC  = gcc
CXX = g++
LD  = $(CXX)

#   That's all folk :)

.PHONY: all dist $(dist) clean cleanall help   # these targets are not files
.SUFFIXES:                                     # remove all the implicit rules
.SECONDARY:                                    # all files are intermediate (keep them)
.SECONDEXPANSION:                              # usefull to automatically build obj directories
all:                                           # ensures that all is the main target

ifeq ($(filter clean cleanall dist help print-%, $(MAKECMDGOALS)),)
mode    := build
else
mode    := no-build
endif

VERBOSE ?= 1
V       ?= $(VERBOSE)
COLOR   ?= 1

ifneq ($(COLOR),0)
red     := \e[0;91m
green   := \e[0;92m
yellow  := \e[0;93m
blue    := \e[0;94m
magenta := \e[0;95m
cyan    := \e[0;96m
black   := \e[0m
endif

print   = @printf "$(value $1)%14s    $(black) %s\n" "$(2)" "$(3)" || exit 0

ifneq ($(filter 1 3,$(V)),)
log     = $(call print,$(1),$(2),$(3))
endif

ifneq ($(filter 0 1,$(V)),)
Q       := @
endif

ifneq ($(filter 4,$(V)),)
mode:=no-build
print-info=$(info $(1))
endif

rootdir :=$(realpath $(dir $(realpath $(MAKEFILE_LIST))))
curdir  :=$(PWD)

do-dir  =$(addsuffix /,$(abspath $(1)/$(2)))

srcdir  :=$(call do-dir,$(rootdir),$(srcdir))
objdir  :=$(call do-dir,$(curdir),$(objdir))
dstdir  :=$(call do-dir,$(curdir),$(dstdir))

modules := $(modules) $(executables)

define check-if-module
$(call print-info,::      check element: $(1) [modules='$(modules)' gen-modules='$(gen-modules)'])
$(if $(filter-out $(modules) $(gen-modules),$(filter-out %.o,$(1))),gen-modules+=$(1) $(eval $(call process-module,$(1))))
endef

define process-module
$(call print-info,::    process module: $(1) [modules='$(modules)' gen-modules='$(gen-modules)'])
$(eval objects-$(notdir $(1)):=$(addprefix $(objdir),$(objects-$(notdir $(1)))))
$(foreach cur,$(objects-$(notdir $(1))),$(if $(filter %.o,$(cur)),$(eval objects+=$(cur))))
$(foreach cur,$(objects-$(notdir $(1))),$(eval $(call check-if-module,$(cur))))
endef

$(foreach cur,$(modules),$(eval $(call process-module,$(cur))))

objects      :=$(sort $(objects))
gen-modules  :=$(sort $(gen-modules))
modules      :=$(addprefix $(dstdir),$(modules))
dependencies :=$(objdir).dependencies

ifeq ($(mode),build)
all: $(modules)
endif

# generate rules
define gen-rule
$(call print-info,$(1))
$(1)
endef

define gen-module-rule
$(call gen-rule,$(1): | $$$$(@D)/.
$(1): $(objects-$(notdir $(1)))

$(if $(filter $(notdir $(1)),$(executables)),
$(1): 
	$$(call log,magenta,linking,$$(notdir $$@))
	$$(Q)$$(LD) $$(LDFLAGS) -o $$@ $$^ $$(LIBS),))
endef

$(foreach cur,$(modules) $(gen-modules),$(eval $(call gen-module-rule,$(cur))))

%.so:
	$(call log,yellow,linking,$(notdir $@))
	$(Q)$(LD) -shared $(LDFLAGS) -o $@ $^ $(LIBS)

%.a: 
	$(call log,yellow,archiving,$(notdir $@))
	$(Q)ar cr $@ $^

define _single-gcc-rule
$(call gen-rule,$(1): $(2)
	$$(call log,cyan,compiling,$$(notdir $$<))
	$$(Q)$(3) -MMD -MP -MT "$$@" -MT "$$(@D)/.$$(*F).d" -MF "$$(@D)/.$$(*F).d" -c "$$<" -o "$$@")
endef

define gcc-rule
$(eval $(call _single-gcc-rule,$(objdir)%.o,$(objdir)$(1) $(objdir).%.d,$(2)))
$(eval $(call _single-gcc-rule,$(objdir)%.o,$(srcdir)$(1) $(objdir).%.d,$(2)))
endef

$(eval $(call gcc-rule,%.cc,$(CXX) $$(CXXFLAGS)))
$(eval $(call gcc-rule,%.c,$(CC) $$(CFLAGS)))
$(eval $(call gcc-rule,%.S,$(CC) $$(CFLAGS)))

.%.d: | $$(@D)/.
#	$(file >> $<,-include $@) why this does not work???
	$(Q)echo "-include $@" >> $(dependencies)
	$(Q)touch $@

-include $(dependencies)

%/.:
	$(Q)mkdir -p $@

print-%:
	$(call print,green,$*,[$($*)])

help:
	@echo "usage: make target"
	@echo
	@echo "Main targets:"
	$(call print,yellow,all,generate the root modules ($(notdir $(modules))))
	$(call print,yellow,dist,generate the archive ($(dist)))
	$(call print,yellow,print-[var],print the variable var (e.g., print-gen-modules))
	@echo
	@echo "Main variables:"
	$(call print,green,PROF,generate the executables for the professors [$(PROF)])
	$(call print,green,V,verbose level (0 nothing, 1 abstract, 2 full command, 3 1+2, 4 auto debug) [$(V)])
	$(call print,green,COLOR,use colors [$(COLOR)])
	$(call print,green,modules,root modules [$(modules)])
	$(call print,green,gen-modules,sub modules generated for the root modules [$(gen-modules)])
	$(call print,green,objects,objects used to build the modules [$(objects)])

tidy:
	$(Q)rm -f *~ \#*

clean:
	$(call print,yellow,$@,remove temporary generated files)
	$(Q)rm -rf $(objects) $(addprefix $(objdir),$(patsubst %.o,.%.d,$(notdir $(objects)))) $(filter-out $(modules),$(gen-modules)) $(dependencies)

cleanall: clean
	$(call print,yellow,$@,cleaning all)
	$(Q)rm -rf $(modules) $(others)

dist: $(dist)

$(dist): cleanall
	$(call log,cyan,generating,$@)
	$(Q)case "$$(uname -s)" in \
		Darwin) tar -f $(dist) -s '|^|$(basename $(basename $(notdir $(dist))))/|' -cJ $(distfiles);; \
		Linux) tar -f $(dist) --transform 's|^|$(basename $(basename $(notdir $(dist))))/|' -cJ $(distfiles);; \
		*) echo "Sorry, unsopported OS, generate your distribution manually";; \
	esac

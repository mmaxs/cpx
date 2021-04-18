

#CC += -v
CC += -std=c11
CPPFLAGS += -D_DEFAULT_SOURCE

ifdef PX_DEBUG
CPPFLAGS += -DPX_DEBUG
endif

# Note: '-pedantic-errors' is not equivalent to '-Werror=pedantic'.
CFLAGS += -Wpedantic -pedantic-errors -Wall -Wextra

# https://nullprogram.com/blog/2016/01/31/
#CFLAGS += -fno-stack-check -fno-stack-protector -mno-stack-arg-probe

cpx%: CPPFLAGS += -iquote ../src
cpx%: CPX_SRCS += ../src/px.c

BUILD_DIR = ./build


ifdef E
$(MAKECMDGOALS): .phony
	$(CC) -E $(CFLAGS) $(CPPFLAGS) $@ -o "$@.pp"

else ifdef S
$(MAKECMDGOALS): .phony
	$(CC) -S $(CFLAGS) $(CPPFLAGS) $@ -o "$@.s"
	
else ifdef dM
$(MAKECMDGOALS): .phony
	$(CC) -E -dM $(CFLAGS) $(CPPFLAGS) $@ | sort > "$@.dm"

else

%: %.c .phony  | $(BUILD_DIR)
	$(LINK.c) $< $(CPX_SRCS) $(LDLIBS) -o $(BUILD_DIR)/$@

cpx-test-tail-recursion: cpx-test-tail-recursion.c .phony  | $(BUILD_DIR)
	$(LINK.c) $< $(CPX_SRCS) $(LDLIBS) -O0 -o $(BUILD_DIR)/$@-0
	$(LINK.c) $< $(CPX_SRCS) $(LDLIBS) -O2 -foptimize-sibling-calls -o $(BUILD_DIR)/$@-2

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

endif

#.DEFAULT_GOAL = $()
#.PHONY: $(MAKECMDGOALS)
.PHONY: .phony


# Summary of the predefined implicit rules:
#
# LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)
# COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
# %.c:
# %: %.c
#         $(LINK.c) $^ $(LOADLIBES) $(LDLIBS) -o $@
# %.o: %.c
#         $(COMPILE.c) $(OUTPUT_OPTION) $<
# .c:
#         $(LINK.c) $^ $(LOADLIBES) $(LDLIBS) -o $@
# .c.o:
#         $(COMPILE.c) $(OUTPUT_OPTION) $<
#
#
# LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)
# COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
# %.cc:
# %: %.cc
#         $(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@
# %.o: %.cc
#         $(COMPILE.cc) $(OUTPUT_OPTION) $<
# .cc:
#         $(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@
# .cc.o:
#         $(COMPILE.cc) $(OUTPUT_OPTION) $<
#
# LINK.cpp = $(LINK.cc)
# COMPILE.cpp = $(COMPILE.cc)
# %.cpp:
# %: %.cpp
#         $(LINK.cpp) $^ $(LOADLIBES) $(LDLIBS) -o $@
# %.o: %.cpp
#         $(COMPILE.cpp) $(OUTPUT_OPTION) $<
# .cpp:
#         $(LINK.cpp) $^ $(LOADLIBES) $(LDLIBS) -o $@
# .cpp.o:
#         $(COMPILE.cpp) $(OUTPUT_OPTION) $<
#


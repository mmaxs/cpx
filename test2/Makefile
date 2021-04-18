

SOURCES = main.c ../src/px.c
CFLAGS += -iquote "../src"

CC += -std=c18

# https://sourceforge.net/p/mingw-w64/wiki2/gnu printf/
# https://sourceforge.net/p/mingw-w64/wiki2/printf and scanf family/
CPPFLAGS += -D__USE_MINGW_ANSI_STDIO

# Note: '-pedantic-errors' is not equivalent to '-Werror=pedantic'.
CFLAGS += -Wall -Wpedantic -pedantic-errors

BUILD_DIR = ./build


.PHONY: $(MAKECMDGOALS)

$(SOURCES):
	$(CC) -E $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH) $@ -o "$@.pp"

main: $(SOURCES)  | $(BUILD_DIR)
	$(LINK.c) $^ $(LOADLIBES) $(LDLIBS) -o $(BUILD_DIR)/$@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)


# The summary of the predefined implicit rules:
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


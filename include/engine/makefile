#
# Compiler flags
#
CXX = g++
CXXFLAGS = -std=c++1z -I ..
_LIBS = sfml-graphics sfml-window sfml-system sfml-network
LIBS = $(addprefix -l, $(_LIBS))

#
# Project files
#
SRCDIR = src
SRCS = $(wildcard $(SRCDIR)/*)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=build/%.o)
EXE  = libengine

#
# Debug build settings
#
DBGEXE = $(EXE)-debug
DBGCXXFLAGS = -g -O0 -DDEBUG

#
# Release build settings
#
RELEXE = $(EXE)
RELCXXFLAGS = -O3 -DNDEBUG

.PHONY: all clean prep debug release remake

# Default build
all: prep release

#
# Debug rules
#
debug: $(DBGEXE)

$(DBGEXE): $(OBJS)
	$(CXX) -shared $(CXXFLAGS) $(DBGCXXFLAGS) $(LIBS) -o $(DBGEXE).so $^

build/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c $(CXXFLAGS) $(DBGCXXFLAGS) $(LIBS) -o $@ $<

#
# Release rules
#
release: $(RELEXE)

$(RELEXE): $(OBJS)
	$(CXX) -shared $(CXXFLAGS) $(RELCXXFLAGS) $(LIBS) -o $(RELEXE).so $^

build/%.o: $(SRCDIR)/%.cpp
	$(CXX) -fpic -c $(CXXFLAGS) $(RELCXXFLAGS) $(LIBS) -o $@ $<

#
# Other rules
#
prep:
	mkdir -p build

remake: clean all

clean:
	rm -f $(RELEXE) $(DBGEXE) build/*
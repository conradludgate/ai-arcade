#
# Compiler flags
#
CXX = g++
CXXFLAGS = -std=c++1z -I include -L include/engine
_LIBS = sfml-graphics sfml-window sfml-system sfml-network
LIBS = $(addprefix -l, $(_LIBS))

#
# Project files
#
SRCDIR = src
SRCS = $(wildcard $(SRCDIR)/*)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=%.o)
EXE  = ai-arcade

#
# Debug build settings
#
DBGDIR = debug
DBGEXE = $(DBGDIR)/$(EXE)
DBGOBJS = $(addprefix $(DBGDIR)/, $(OBJS))
DBGCXXFLAGS = -g -O0 -DDEBUG -lengine-debug

#
# Release build settings
#
RELDIR = release
RELEXE = $(RELDIR)/$(EXE)
RELOBJS = $(addprefix $(RELDIR)/, $(OBJS))
RELCXXFLAGS = -O3 -DNDEBUG -lengine

#
# Engine Source
#
# ENGDIR = include/engine/src
# ENGSRC = $(wildcard $(EXTDIR)/*)
# ENGOBJ = $(EXTSRC:$(EXTDIR)/%.cpp=%.o)

# DBGOBJS += $(addprefix $(DBGDIR)/engine/, $(ENGOBJ))
# RELOBJS += $(addprefix $(RELDIR)/engine/, $(ENGOBJ))

.PHONY: all clean debug prep release remake

# Default build
all: prep release

#
# Debug rules
#
debug: $(DBGEXE)

$(DBGEXE): $(DBGOBJS)
	$(CXX) $(CXXFLAGS) $(DBGCXXFLAGS) $(LIBS) -o $(DBGEXE) $^

$(DBGDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c $(CXXFLAGS) $(DBGCXXFLAGS) $(LIBS) -o $@ $<

#
# Release rules
#
release: $(RELEXE)

$(RELEXE): $(RELOBJS)
	$(CXX) $(CXXFLAGS) $(RELCXXFLAGS) $(LIBS) -o $(RELEXE) $^

$(RELDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c $(CXXFLAGS) $(RELCXXFLAGS) $(LIBS) -o $@ $<

#
# Other rules
#
prep:
	@mkdir -p $(DBGDIR) $(RELDIR)

remake: clean all

clean:
	rm -f $(RELEXE) $(RELOBJS) $(DBGEXE) $(DBGOBJS)
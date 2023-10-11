TARGET:=tbgj

# Compiler stuff
CC:=gcc
CFLAGS=-Wall $(INCLFLAGS) $(DBGFLAGS)
DBGFLAGS:=-g -Wextra
RLSFLAGS:=-O2
INCLFLAGS:=-lncursesw

# Dir
SRCDIR:=src
OBJDIR:=build
SRCDIRS:=$(patsubst %/,%,$(dir $(wildcard $(SRCDIR)/*/ $(SRCDIR)/*/*/))) $(SRCDIR)

# Compile Input/Output
SRCS := $(wildcard *.c $(foreach fd, $(SRCDIRS), $(fd)/*.c))
INCS := $(wildcard *.h $(foreach fd, $(SRCDIRS), $(fd)/*.h))
OBJS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
INC_DIRS = $(addprefix -I , $(SRCDIRS))

.PHONY: all echo clean remake
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCS)
	mkdir -p $(@D)
	$(CC) -o $@ -c $< $(CFLAGS) $(INC_DIRS)

clean:
	rm -rf $(OBJDIR) $(TARGET)

remake: clean all

echo: 
	@echo "Source Dirs: $(SRCDIRS)"
	@echo "Includes: $(INCS)"
	@echo "Sources: $(SRCS)"
	@echo "Objects: $(OBJS)"


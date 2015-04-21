CC := gcc

LIB_SRCDIR := src
LIB_OBJDIR := obj
LIBDIR := lib
BINDIR := bin

INCL := -Iinclude/
CFLAGS :=
DEFINES:=
LIB_SRCS := $(wildcard src/*.c)
LIB_OBJS := $(subst src, obj, $(LIB_SRCS))
LIB_OBJS := $(patsubst %.c, %.o, $(LIB_OBJS))

LIB := libthreadpool.a 

lib : $(LIB_OBJS)
	ar rcs $(LIBDIR)/$(LIB) $^
 
$(LIB_OBJDIR)/%.o : $(LIB_SRCDIR)/%.c
	$(CC) $(CFLAGS) $(DEFINES) $(INCL) -c $< -o $@  

clean : 
	rm -rf bin/* obj/* lib/* a.out *.o

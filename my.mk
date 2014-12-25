CC := gcc

SRCDIR := src
OBJDIR := obj
LIBDIR := lib
BINDIR := bin

INCL := -Iinclude/
CFLAGS := -g

LIB_SRCS := $(wildcard src/*.c)
LIB_OBJS := $(subst src, obj, $(LIB_SRCS))
LIB_OBJS := $(patsubst %.c, %.o, $(LIB_OBJS))

LIB := libthreadpool.a 

lib : $(LIB_OBJS)
	ar rcs $(LIBDIR)/$(LIB) $^
 
$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCL) -c $< -o $@  

clean : 
	rm -rf bin/* obj/* lib/* a.out *.o

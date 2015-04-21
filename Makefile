# regular variables, overridable from the command line. Add -DDEBUG to get debug information. By default, debug info is printed to stdout. Redirect if needed.

CC:=clang
CFLAGS:= -c
LD_FLAGS= -Llib/ -lpthread -lthreadpool
INCL:=-Iinclude/
DEFINES:=


# use these to build library / library + test cases.
lib : lib/libthreadpool.a 

tst : bin/imm_shutdown bin/graceful_shutdown bin/heavy_comp bin/pt_heavy_comp


# command for creating library.    

lib/libthreadpool.a : obj/threadpool.o obj/queue.o obj/task.o
	ar rcs $@ $^


# commands to create library dependencies.

obj/threadpool.o : src/threadpool.c 
	$(CC) $(INCL) $(DEFINES) $(CFLAGS) -c $< -o $@

obj/queue.o : src/queue.c
	$(CC) $(INCL) $(DEFINES) $(CFLAGS) -c $< -o $@

obj/task.o : src/task.c
	$(CC) $(INCL) $(DEFINES) $(CFLAGS) -c $< -o $@


# commands for the tst files(cases). Any new test cases must be added below.

bin/imm_shutdown : obj/imm_shutdown.o lib/libthreadpool.a
	$(CC) $< -o $@ $(LD_FLAGS) 

obj/imm_shutdown.o : tst/imm_shutdown.c
	$(CC) $(INCL) $(DEFINES) $(CFLAGS) -c $< -o $@

bin/graceful_shutdown : obj/graceful_shutdown.o lib/libthreadpool.a
	$(CC) $< -o $@ $(LD_FLAGS)

obj/graceful_shutdown.o : tst/graceful_shutdown.c
	$(CC) $(INCL) $(DEFINES) $(CFLAGS) -c $< -o $@

bin/heavy_comp : obj/heavy_comp.o lib/libthreadpool.a
	$(CC) $< -o $@ $(LD_FLAGS)

obj/heavy_comp.o : tst/heavy_comp.c
	$(CC) $(INCL) $(DEFINES) $(CFLAGS) -c $< -o $@

bin/pt_heavy_comp : obj/pt_heavy_comp.o 
	$(CC) $< -o $@ $(LD_FLAGS)

obj/pt_heavy_comp.o : tst/pt_heavy_comp.c
	$(CC) $(INCL) $(DEFINES) $(CFLAGS) -c $< -o $@


# command to clean the project    

clean : 
	rm -rf lib/* obj/* bin/* */a.out a.out

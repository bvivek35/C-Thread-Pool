all_bin : bin/imm_shutdown bin/graceful_shutdown bin/heavy_comp bin/pt_heavy_comp

bin/imm_shutdown : obj/imm_shutdown.o lib/libthreadpool.a
	gcc obj/imm_shutdown.o -L lib -lthreadpool -lpthread -o bin/imm_shutdown

obj/imm_shutdown.o : tst/imm_shutdown.c
	gcc -c tst/imm_shutdown.c -Iinclude -o obj/imm_shutdown.o

bin/graceful_shutdown : obj/graceful_shutdown.o lib/libthreadpool.a
	gcc obj/graceful_shutdown.o -L lib -lthreadpool -lpthread -o bin/graceful_shutdown

obj/graceful_shutdown.o : tst/graceful_shutdown.c
	gcc -c tst/graceful_shutdown.c -Iinclude -o obj/graceful_shutdown.o

bin/heavy_comp : obj/heavy_comp.o lib/libthreadpool.a
	gcc obj/heavy_comp.o -L lib -lthreadpool -lpthread -o bin/heavy_comp

obj/heavy_comp.o : tst/heavy_comp.c
	gcc -c tst/heavy_comp.c -Iinclude -o obj/heavy_comp.o

bin/pt_heavy_comp : obj/pt_heavy_comp.o 
	gcc obj/pt_heavy_comp.o -lpthread -o bin/pt_heavy_comp

obj/pt_heavy_comp.o : tst/pt_heavy_comp.c
	gcc -c tst/pt_heavy_comp.c -o obj/pt_heavy_comp.o

lib/libthreadpool.a : obj/threadpool.o obj/queue.o obj/task.o
	ar rcs lib/libthreadpool.a obj/threadpool.o obj/queue.o obj/task.o

obj/threadpool.o : src/threadpool.c 
	gcc -c src/threadpool.c -Iinclude -o obj/threadpool.o

obj/queue.o : src/queue.c
	gcc -c src/queue.c -Iinclude -o obj/queue.o

obj/task.o : src/task.c
	gcc -c src/task.c -Iinclude -o obj/task.o

clean : 
	rm -rf lib/* obj/* */a.out a.out




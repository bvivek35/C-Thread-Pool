lib/libthreadpool.a : obj/threadpool.o obj/queue.o obj/task.o
	ar rcs lib/libthreadpool.a obj/threadpool.o obj/queue.o obj/task.o

obj/threadpool.o : src/threadpool.c 
	gcc -c src/threadpool.c -Iinclude -o obj/threadpool.o

obj/queue.o : src/queue.c
	gcc -c src/queue.c -Iinclude -o obj/queue.o

obj/task.o : src/task.c
	gcc -c src/task.c -Iinclude -o obj/task.o

obj/test_pool_2.o : tst/test_pool_2.c
	gcc -c tst/test_pool_2.c -Iinclude -o obj/test_pool_2.o

bin/t2 : obj/test_pool_2.o lib/libthreadpool.a
	gcc obj/test_pool_2.o -L lib -lthreadpool -lpthread -o bin/t2

clean : 
	rm -rf lib/* obj/* */a.out a.out




all:	./compile/obj/driver.o		\
		./compile/obj/ioctl.o		\
		./compile/obj/rw.o			\
		./compile/obj/buffer_test.o	\
		./compile/obj/stream_test.o	\
		./compile/obj/ioctl_test.o	\
		
		$(CC) $(LDFLAGS)	./compile/obj/driver.o		\
							./compile/obj/ioctl.o		\
							./compile/obj/rw.o			\
							./compile/obj/buffer_test.o	\
							./compile/obj/stream_test.o	\
							./compile/obj/ioctl_test.o	\
		\
		-o	\
		\
		./compile/bin/driver

		
./compile/obj/driver.o:				./driver.c
	$(CC) $(CCFLAGS) -c				./driver.c				-o ./compile/obj/driver.o
	
./compile/obj/ioctl.o:				./ioctl/ioctl.c
	$(CC) $(CCFLAGS) -c				./ioctl/ioctl.c			-o ./compile/obj/ioctl.o
	
./compile/obj/rw.o:					./rw/rw.c
	$(CC) $(CCFLAGS) -c				./rw/rw.c				-o ./compile/obj/rw.o
	
./compile/obj/buffer_test.o:		./tests/buffer_test.c
	$(CC) $(CCFLAGS) -c				./tests/buffer_test.c	-o ./compile/obj/buffer_test.o
	
./compile/obj/stream_test.o:		./tests/stream_test.c
	$(CC) $(CCFLAGS) -c				./tests/stream_test.c	-o ./compile/obj/stream_test.o
	
./compile/obj/ioctl_test.o:			./tests/ioctl_test.c
	$(CC) $(CCFLAGS) -c				./tests/ioctl_test.c	-o ./compile/obj/ioctl_test.o

	
clean:
	rm -f ./compile/obj/*
	rm -f ./compile/bin/*
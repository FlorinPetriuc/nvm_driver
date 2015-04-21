all:	./compile/obj/driver.o	\
		./compile/obj/ioctl.o	\
		./compile/obj/rw.o		\
		
		$(CC) $(LDFLAGS)	./compile/obj/driver.o	\
							./compile/obj/ioctl.o	\
							./compile/obj/rw.o		\
		\
		-o	\
		\
		./compile/bin/driver

		
./compile/obj/driver.o:				./driver.c
	$(CC) $(CCFLAGS) -c				./driver.c		-o ./compile/obj/driver.o
	
./compile/obj/ioctl.o:				./ioctl/ioctl.c
	$(CC) $(CCFLAGS) -c				./ioctl/ioctl.c	-o ./compile/obj/ioctl.o
	
./compile/obj/rw.o:					./rw/rw.c
	$(CC) $(CCFLAGS) -c				./rw/rw.c		-o ./compile/obj/rw.o

	
clean:
	rm -f ./compile/obj/*
	rm -f ./compile/bin/*
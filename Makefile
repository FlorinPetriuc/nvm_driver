all:	./compile/obj/lightnvm_driver.o	\
		
		$(CC) $(LDFLAGS)	./compile/obj/lightnvm_driver.o\
		\
		-o	\
		\
		./compile/bin/driver

		
./compile/obj/lightnvm_driver.o:	./lightnvm_driver.c
	$(CC) $(CCFLAGS) -c				./lightnvm_driver.c		-o ./compile/obj/lightnvm_driver.o

	
clean:
	rm -f ./compile/obj/*
	rm -f ./compile/bin/*
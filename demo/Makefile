# NURNware Ray kernel module demo
# (For use with Cold iGnition operating system)
# Copyright (C) 2007 - NURNware Technologies


CC=i686-pc-ray-g++
C_ARGS=-g3 -I../ray/include -O0 -c -Wall -Wswitch-enum -Werror
LD=i686-pc-ray-ld


all: demo


clean:
	@echo -e "Deleting all object files..."
	@-rm `find . -iname '*.o'`>/dev/null


rebuild: clean demo


demo.o: demo.cpp ../ray/include/raykernel.h ../ray/include/ray/typedefs.h \
 ../ray/include/standard.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/exception \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/i686-pc-ray/bits/c++config.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/i686-pc-ray/bits/os_defines.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/i686-pc-ray/bits/cpu_defines.h \
 ../ray/include/video/VideoStream.h
	@echo -e "	 SUBPART OF MODULE [demo.cpp]"
	@$(CC) $(C_ARGS) demo.cpp -o demo.o


demo:  demo.o
	@echo -e "Building module demo"
	@$(CC) -o demo  demo.o  ../ray/raylib/video.o ../ray/raylib/standard.o

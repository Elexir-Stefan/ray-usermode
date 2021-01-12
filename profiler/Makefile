# NURNware Ray kernel module profiler
# (For use with Cold iGnition operating system)
# Copyright (C) 2007 - NURNware Technologies


CC=i686-pc-ray-g++
C_ARGS=-g3 -I../ray/include -O0 -c -Wall -Wswitch-enum -Werror -fdata-sections -ffunction-sections -fstack-protector-all
LD=i686-pc-ray-ld
LD_ARGS=-Wl,--gc-sections
RAYIMAGEPATH=../../RayKernel/rayimage
RAYDRIVERCMD=insertdriver


all: profiler


install: profiler-install


clean:
	@echo -e "Deleting all object files..."
	@-rm `find . -iname '*.o'`>/dev/null


rebuild: clean profiler


profiler.o: profiler.cpp ../ray/include/raykernel.h \
 ../ray/include/ray/typedefs.h ../ray/include/rayexception.h \
 ../ray/include/standard.h ../ray/include/keyboard/keyboard.h \
 ../ray/include/ipc/ipc_int.h ../ray/include/processes/privileges.h \
 ../ray/include/processes/arguments.h ../ray/include/ipc/methodtemplate.h \
 ../ray/include/processes/processes.h ../ray/include/ipc/ipc.h \
 ../ray/include/ipc/ipc_int.h ../ray/include/debug.h \
 ../ray/include/video/VideoStream.h
	@echo -e "	 SUBPART OF MODULE [profiler.cpp]"
	@$(CC) $(C_ARGS) profiler.cpp -o profiler.o


profiler:  profiler.o
	@echo -e "Building module profiler"
	@$(CC) $(LD_ARGS) -o profiler  profiler.o  ../ray/raylib/video.o ../ray/raylib/keyboard/keyboard.o ../ray/raylib/ipc/ipc.o ../ray/raylib/processes/processes.o ../ray/raylib/standard.o
profiler-install: profiler  profiler.o
	@echo Installing module...
	@cd $(RAYIMAGEPATH); ./$(RAYDRIVERCMD) $(CURDIR)/profiler profiler

.PHONY: install
.PHONY: profiler-install
.PHONY: all

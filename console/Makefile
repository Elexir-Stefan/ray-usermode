# NURNware Ray kernel module console
# (For use with Cold iGnition operating system)
# Copyright (C) 2007 - NURNware Technologies


CC=i686-pc-ray-g++
C_ARGS=-g3 -I../ray/include -O0 -c -Wall -Wswitch-enum -Werror -fdata-sections -ffunction-sections -fstack-protector-all
LD=i686-pc-ray-ld
LD_ARGS=-Wl,--gc-sections
RAYIMAGEPATH=../../RayKernel/rayimage
RAYDRIVERCMD=insertdriver


all: console


install: console-install


clean:
	@echo -e "Deleting all object files..."
	@-rm `find . -iname '*.o'`>/dev/null


rebuild: clean console


benchmark.o: benchmark.cpp ../ray/include/raykernel.h \
 ../ray/include/ray/typedefs.h ../ray/include/rayexception.h \
 ../ray/include/standard.h ../ray/include/video/VideoStream.h \
 ../ray/include/video/KernelVideo.h benchmark.h sha1.h
	@echo -e "	 SUBPART OF MODULE [benchmark.cpp]"
	@$(CC) $(C_ARGS) benchmark.cpp -o benchmark.o


Command.o: Command.cpp ../ray/include/raykernel.h \
 ../ray/include/ray/typedefs.h ../ray/include/rayexception.h \
 ../ray/include/standard.h ../ray/include/video/VideoStream.h \
 ../ray/include/video/KernelVideo.h ../ray/include/processes/processes.h \
 ../ray/include/processes/privileges.h \
 ../ray/include/processes/arguments.h ../ray/include/ipc/ipc_int.h \
 ../ray/include/ipc/methodtemplate.h ../ray/include/debug.h Command.h \
 benchmark.h ps.h reboot.h stress.h
	@echo -e "	 SUBPART OF MODULE [Command.cpp]"
	@$(CC) $(C_ARGS) Command.cpp -o Command.o


console.o: console.cpp ../ray/include/raykernel.h \
 ../ray/include/ray/typedefs.h ../ray/include/rayexception.h \
 ../ray/include/standard.h ../ray/include/keyboard/keyboard.h \
 ../ray/include/ipc/ipc_int.h ../ray/include/processes/privileges.h \
 ../ray/include/processes/arguments.h ../ray/include/ipc/methodtemplate.h \
 ../ray/include/processes/processes.h ../ray/include/video/VideoStream.h \
 ../ray/include/video/KernelVideo.h Command.h
	@echo -e "	 SUBPART OF MODULE [console.cpp]"
	@$(CC) $(C_ARGS) console.cpp -o console.o


ps.o: ps.cpp ../ray/include/raykernel.h ../ray/include/ray/typedefs.h \
 ../ray/include/rayexception.h ../ray/include/standard.h \
 ../ray/include/video/VideoStream.h ../ray/include/video/KernelVideo.h \
 ../ray/include/processes/processes.h \
 ../ray/include/processes/privileges.h \
 ../ray/include/processes/arguments.h ../ray/include/ipc/ipc_int.h \
 ../ray/include/ipc/methodtemplate.h ps.h
	@echo -e "	 SUBPART OF MODULE [ps.cpp]"
	@$(CC) $(C_ARGS) ps.cpp -o ps.o


reboot.o: reboot.cpp ../ray/include/raykernel.h \
 ../ray/include/ray/typedefs.h ../ray/include/rayexception.h \
 ../ray/include/standard.h ../ray/include/video/VideoStream.h \
 ../ray/include/video/KernelVideo.h ../ray/include/rdm/rdm.h \
 ../ray/include/processes/processes.h \
 ../ray/include/processes/privileges.h \
 ../ray/include/processes/arguments.h ../ray/include/ipc/ipc_int.h \
 ../ray/include/ipc/methodtemplate.h ../ray/include/system.h
	@echo -e "	 SUBPART OF MODULE [reboot.cpp]"
	@$(CC) $(C_ARGS) reboot.cpp -o reboot.o


sha1.o: sha1.cpp sha1.h
	@echo -e "	 SUBPART OF MODULE [sha1.cpp]"
	@$(CC) $(C_ARGS) sha1.cpp -o sha1.o


stress.o: stress.cpp ../ray/include/raykernel.h \
 ../ray/include/ray/typedefs.h ../ray/include/rayexception.h \
 ../ray/include/standard.h ../ray/include/video/VideoStream.h \
 ../ray/include/video/KernelVideo.h ../ray/include/processes/processes.h \
 ../ray/include/processes/privileges.h \
 ../ray/include/processes/arguments.h ../ray/include/ipc/ipc_int.h \
 ../ray/include/ipc/methodtemplate.h stress.h
	@echo -e "	 SUBPART OF MODULE [stress.cpp]"
	@$(CC) $(C_ARGS) stress.cpp -o stress.o


console:  benchmark.o Command.o console.o ps.o reboot.o sha1.o stress.o
	@echo -e "Building module console"
	@$(CC) $(LD_ARGS) -o console  benchmark.o Command.o console.o ps.o reboot.o sha1.o stress.o  ../ray/raylib/video.o ../ray/raylib/keyboard/keyboard.o ../ray/raylib/processes/processes.o ../ray/raylib/ipc/ipc.o ../ray/raylib/standard.o
console-install: console  benchmark.o Command.o console.o ps.o reboot.o sha1.o stress.o
	@echo Installing module...
	@cd $(RAYIMAGEPATH); ./$(RAYDRIVERCMD) $(CURDIR)/console console

.PHONY: install
.PHONY: console-install
.PHONY: all

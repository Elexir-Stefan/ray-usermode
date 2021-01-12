# NURNware Ray kernel module ipc1
# (For use with Cold iGnition operating system)
# Copyright (C) 2007 - NURNware Technologies


CC=i686-pc-ray-g++
C_ARGS=-g3 -I../ray/include -O0 -c -Wall -Wswitch-enum -Werror -fdata-sections -ffunction-sections -fstack-protector-all
LD=i686-pc-ray-ld
LD_ARGS=-Wl,--gc-sections
RAYIMAGEPATH=../../RayKernel/rayimage
RAYDRIVERCMD=insertdriver


all: ipc1


install: ipc1-install


clean:
	@echo -e "Deleting all object files..."
	@-rm `find . -iname '*.o'`>/dev/null


rebuild: clean ipc1


ipc1.o: ipc1.cpp ../ray/include/raykernel.h ../ray/include/ray/typedefs.h \
 ../ray/include/rayexception.h ../ray/include/standard.h \
 ../ray/include/video/VideoStream.h ../ray/include/processes/processes.h \
 ../ray/include/processes/privileges.h \
 ../ray/include/processes/arguments.h ../ray/include/ipc/ipc_int.h \
 ../ray/include/ipc/methodtemplate.h ../ray/include/ipc/ipc.h \
 ../ray/include/ipc/ipc_int.h
	@echo -e "	 SUBPART OF MODULE [ipc1.cpp]"
	@$(CC) $(C_ARGS) ipc1.cpp -o ipc1.o


ipc1:  ipc1.o
	@echo -e "Building module ipc1"
	@$(CC) $(LD_ARGS) -o ipc1  ipc1.o  ../ray/raylib/video.o ../ray/raylib/ipc/ipc.o ../ray/raylib/processes/processes.o ../ray/raylib/standard.o
ipc1-install: ipc1  ipc1.o
	@echo Installing module...
	@cd $(RAYIMAGEPATH); ./$(RAYDRIVERCMD) $(CURDIR)/ipc1 ipc1

.PHONY: install
.PHONY: ipc1-install
.PHONY: all

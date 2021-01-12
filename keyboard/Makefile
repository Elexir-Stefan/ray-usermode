# NURNware Ray kernel module keyboard
# (For use with Cold iGnition operating system)
# Copyright (C) 2007 - NURNware Technologies


CC=i686-pc-ray-g++
C_ARGS=-g3 -I../ray/include -O0 -c -Wall -Wswitch-enum -Werror -fdata-sections -ffunction-sections -fstack-protector-all
LD=i686-pc-ray-ld
LD_ARGS=-Wl,--gc-sections
RAYIMAGEPATH=../../RayKernel/rayimage
RAYDRIVERCMD=insertdriver


all: keyboard


install: keyboard-install


clean:
	@echo -e "Deleting all object files..."
	@-rm `find . -iname '*.o'`>/dev/null


rebuild: clean keyboard


keyboard.o: keyboard.cpp ../ray/include/raykernel.h \
 ../ray/include/ray/typedefs.h ../ray/include/rayexception.h \
 ../ray/include/standard.h ../ray/include/debug.h \
 ../ray/include/rdm/rdm.h ../ray/include/processes/processes.h \
 ../ray/include/processes/privileges.h \
 ../ray/include/processes/arguments.h ../ray/include/ipc/ipc_int.h \
 ../ray/include/ipc/methodtemplate.h ../ray/include/video/VideoStream.h \
 KeyboardHandler.h ../ray/include/ipc/ipc.h ../ray/include/ipc/ipc_int.h \
 ../commondrivers/keyboard/barrier.h
	@echo -e "	 SUBPART OF MODULE [keyboard.cpp]"
	@$(CC) $(C_ARGS) keyboard.cpp -o keyboard.o


KeyboardHandler.o: KeyboardHandler.cpp ../ray/include/raykernel.h \
 ../ray/include/ray/typedefs.h ../ray/include/rayexception.h \
 ../ray/include/standard.h ../ray/include/debug.h KeyboardHandler.h \
 ../ray/include/rdm/rdm.h ../ray/include/processes/processes.h \
 ../ray/include/processes/privileges.h \
 ../ray/include/processes/arguments.h ../ray/include/ipc/ipc_int.h \
 ../ray/include/ipc/methodtemplate.h ../ray/include/ipc/ipc.h \
 ../ray/include/ipc/ipc_int.h ../ray/include/video/VideoStream.h i8042.h \
 i8042io.h keymap_german.h ../commondrivers/keyboard/raykeybind.h \
 ../commondrivers/keyboard/barrier.h
	@echo -e "	 SUBPART OF MODULE [KeyboardHandler.cpp]"
	@$(CC) $(C_ARGS) KeyboardHandler.cpp -o KeyboardHandler.o


keyboard:  keyboard.o KeyboardHandler.o
	@echo -e "Building module keyboard"
	@$(CC) $(LD_ARGS) -o keyboard  keyboard.o KeyboardHandler.o  ../ray/raylib/video.o ../ray/raylib/rdm/rdm.o ../ray/raylib/processes/processes.o ../ray/raylib/ipc/ipc.o ../ray/raylib/standard.o
keyboard-install: keyboard  keyboard.o KeyboardHandler.o
	@echo Installing module...
	@cd $(RAYIMAGEPATH); ./$(RAYDRIVERCMD) $(CURDIR)/keyboard keyboard

.PHONY: install
.PHONY: keyboard-install
.PHONY: all

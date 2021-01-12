# NURNware Ray kernel modules
# (For use with Cold iGnition operating system)
# Copyright (C) 2007 - NURNware Technologies


CC=i686-pc-ray-g++
C_ARGS=-gdwarf-2 -ggdb -I../include -O0 -c -Wall -Werror -fdata-sections -ffunction-sections


all: modules


clean:
	@-rm `find . -iname '*.o'`


rebuild: clean modules


video/KernelVideo.o: video/KernelVideo.cpp ../include/raykernel.h \
 ../include/ray/typedefs.h ../include/rayexception.h \
 ../include/standard.h ../include/video/KernelVideo.h \
 ../include/syscall.h ../include/ray/sct.h
	@echo -e "MODULE [video/KernelVideo.cpp]"
	@$(CC) $(C_ARGS) video/KernelVideo.cpp -o video/KernelVideo.o


video/VideoStream.o: video/VideoStream.cpp ../include/raykernel.h \
 ../include/ray/typedefs.h ../include/rayexception.h \
 ../include/standard.h ../include/video/VideoStream.h \
 ../include/video/KernelVideo.h
	@echo -e "MODULE [video/VideoStream.cpp]"
	@$(CC) $(C_ARGS) video/VideoStream.cpp -o video/VideoStream.o


video.o:  video/KernelVideo.o video/VideoStream.o
	@echo -e "Generating part video"
	@$(LD) -Ur -o video.o  video/KernelVideo.o video/VideoStream.o


standard/debug.o: standard/debug.cpp ../include/raykernel.h \
 ../include/ray/typedefs.h ../include/rayexception.h \
 ../include/standard.h ../include/ray/sct.h ../include/syscall.h \
 ../include/memory.h ../include/debug.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/vector \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_algobase.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/i686-pc-ray/bits/c++config.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/i686-pc-ray/bits/os_defines.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/i686-pc-ray/bits/cpu_defines.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/cstddef \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/include/stddef.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/functexcept.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/exception_defines.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/cpp_type_traits.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/ext/type_traits.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/ext/numeric_traits.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_pair.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/move.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/concept_check.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_iterator_base_types.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_iterator_base_funcs.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_iterator.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/debug/debug.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/allocator.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/i686-pc-ray/bits/c++allocator.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/ext/new_allocator.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/new \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/exception \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_construct.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_uninitialized.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_vector.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/initializer_list \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_bvector.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/vector.tcc \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/string.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/_ansi.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/newlib.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/sys/config.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/machine/ieeefp.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/sys/reent.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/_ansi.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/sys/_types.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/machine/_types.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/machine/_default_types.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/sys/lock.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/sys/string.h
	@echo -e "MODULE [standard/debug.cpp]"
	@$(CC) $(C_ARGS) standard/debug.cpp -o standard/debug.o


standard/exit.o: standard/exit.cpp ../include/raykernel.h \
 ../include/ray/typedefs.h ../include/rayexception.h \
 ../include/standard.h ../include/syscall.h ../include/ray/sct.h
	@echo -e "MODULE [standard/exit.cpp]"
	@$(CC) $(C_ARGS) standard/exit.cpp -o standard/exit.o


standard/memory.o: standard/memory.cpp ../include/raykernel.h \
 ../include/ray/typedefs.h ../include/rayexception.h \
 ../include/standard.h ../include/memory.h ../include/syscall.h \
 ../include/ray/sct.h
	@echo -e "MODULE [standard/memory.cpp]"
	@$(CC) $(C_ARGS) standard/memory.cpp -o standard/memory.o


standard/outofmemory.o: standard/outofmemory.cpp ../include/raykernel.h \
 ../include/ray/typedefs.h ../include/rayexception.h \
 ../include/standard.h
	@echo -e "MODULE [standard/outofmemory.cpp]"
	@$(CC) $(C_ARGS) standard/outofmemory.cpp -o standard/outofmemory.o


standard/system.o: standard/system.cpp ../include/raykernel.h \
 ../include/ray/typedefs.h ../include/rayexception.h \
 ../include/standard.h ../include/syscall.h ../include/system.h \
 ../include/rdm/rdm.h ../include/processes/processes.h \
 ../include/processes/privileges.h ../include/processes/arguments.h \
 ../include/ipc/ipc_int.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/list \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_algobase.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/i686-pc-ray/bits/c++config.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/i686-pc-ray/bits/os_defines.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/i686-pc-ray/bits/cpu_defines.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/cstddef \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/include/stddef.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/functexcept.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/exception_defines.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/cpp_type_traits.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/ext/type_traits.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/ext/numeric_traits.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_pair.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/move.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/concept_check.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_iterator_base_types.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_iterator_base_funcs.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_iterator.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/debug/debug.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/allocator.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/i686-pc-ray/bits/c++allocator.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/ext/new_allocator.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/new \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/exception \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_list.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/initializer_list \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/list.tcc \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/vector \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_construct.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_uninitialized.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_vector.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_bvector.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/vector.tcc \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/typeinfo \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/include/stdarg.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/string.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/_ansi.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/newlib.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/sys/config.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/machine/ieeefp.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/sys/reent.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/_ansi.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/sys/_types.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/machine/_types.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/machine/_default_types.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/sys/lock.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/sys/string.h \
 ../include/ipc/methodtemplate.h ../include/ray/sct.h
	@echo -e "MODULE [standard/system.cpp]"
	@$(CC) $(C_ARGS) standard/system.cpp -o standard/system.o


standard.o:  standard/debug.o standard/exit.o standard/memory.o standard/outofmemory.o standard/system.o
	@echo -e "Generating part standard"
	@$(LD) -Ur -o standard.o  standard/debug.o standard/exit.o standard/memory.o standard/outofmemory.o standard/system.o


processes/processes.o: processes/processes.cpp ../include/raykernel.h \
 ../include/ray/typedefs.h ../include/rayexception.h \
 ../include/standard.h ../include/processes/processes.h \
 ../include/processes/privileges.h ../include/processes/arguments.h \
 ../include/ipc/ipc_int.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/list \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_algobase.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/i686-pc-ray/bits/c++config.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/i686-pc-ray/bits/os_defines.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/i686-pc-ray/bits/cpu_defines.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/cstddef \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/include/stddef.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/functexcept.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/exception_defines.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/cpp_type_traits.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/ext/type_traits.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/ext/numeric_traits.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_pair.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/move.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/concept_check.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_iterator_base_types.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_iterator_base_funcs.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_iterator.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/debug/debug.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/allocator.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/i686-pc-ray/bits/c++allocator.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/ext/new_allocator.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/new \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/exception \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_list.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/initializer_list \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/list.tcc \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/vector \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_construct.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_uninitialized.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_vector.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_bvector.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/vector.tcc \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/typeinfo \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/include/stdarg.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/string.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/_ansi.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/newlib.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/sys/config.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/machine/ieeefp.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/sys/reent.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/_ansi.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/sys/_types.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/machine/_types.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/machine/_default_types.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/sys/lock.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/sys/string.h \
 ../include/ipc/methodtemplate.h ../include/ray/sct.h \
 ../include/syscall.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/cxxabi.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/i686-pc-ray/bits/cxxabi_tweaks.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/cxxabi-forced.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/stdlib.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/machine/stdlib.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/alloca.h \
 ../include/debug.h
	@echo -e "MODULE [processes/processes.cpp]"
	@$(CC) $(C_ARGS) processes/processes.cpp -o processes/processes.o


processes.o:  processes/processes.o
	@echo -e "Generating part processes"
	@$(LD) -Ur -o processes.o  processes/processes.o


rdm/rdm.o: rdm/rdm.cpp ../include/raykernel.h ../include/ray/typedefs.h \
 ../include/rayexception.h ../include/standard.h ../include/rdm/rdm.h \
 ../include/processes/processes.h ../include/processes/privileges.h \
 ../include/processes/arguments.h ../include/ipc/ipc_int.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/list \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_algobase.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/i686-pc-ray/bits/c++config.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/i686-pc-ray/bits/os_defines.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/i686-pc-ray/bits/cpu_defines.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/cstddef \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/include/stddef.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/functexcept.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/exception_defines.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/cpp_type_traits.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/ext/type_traits.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/ext/numeric_traits.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_pair.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/move.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/concept_check.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_iterator_base_types.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_iterator_base_funcs.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_iterator.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/debug/debug.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/allocator.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/i686-pc-ray/bits/c++allocator.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/ext/new_allocator.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/new \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/exception \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_list.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/initializer_list \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/list.tcc \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/vector \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_construct.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_uninitialized.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_vector.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_bvector.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/vector.tcc \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/typeinfo \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/include/stdarg.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/string.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/_ansi.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/newlib.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/sys/config.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/machine/ieeefp.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/sys/reent.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/_ansi.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/sys/_types.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/machine/_types.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/machine/_default_types.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/sys/lock.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/sys/string.h \
 ../include/ipc/methodtemplate.h ../include/syscall.h \
 ../include/ray/sct.h
	@echo -e "MODULE [rdm/rdm.cpp]"
	@$(CC) $(C_ARGS) rdm/rdm.cpp -o rdm/rdm.o


rdm.o:  rdm/rdm.o
	@echo -e "Generating part rdm"
	@$(LD) -Ur -o rdm.o  rdm/rdm.o


ipc/ipc.o: ipc/ipc.cpp ../include/raykernel.h ../include/ray/typedefs.h \
 ../include/rayexception.h ../include/standard.h ../include/ipc/ipc_int.h \
 ../include/processes/privileges.h ../include/processes/arguments.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/list \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_algobase.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/i686-pc-ray/bits/c++config.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/i686-pc-ray/bits/os_defines.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/i686-pc-ray/bits/cpu_defines.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/cstddef \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/include/stddef.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/functexcept.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/exception_defines.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/cpp_type_traits.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/ext/type_traits.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/ext/numeric_traits.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_pair.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/move.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/concept_check.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_iterator_base_types.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_iterator_base_funcs.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_iterator.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/debug/debug.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/allocator.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/i686-pc-ray/bits/c++allocator.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/ext/new_allocator.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/new \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/exception \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_list.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/initializer_list \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/list.tcc \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/vector \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_construct.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_uninitialized.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_vector.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_bvector.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/vector.tcc \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/typeinfo \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/include/stdarg.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/string.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/_ansi.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/newlib.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/sys/config.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/machine/ieeefp.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/sys/reent.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/_ansi.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/sys/_types.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/machine/_types.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/machine/_default_types.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/sys/lock.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/sys/string.h \
 ../include/ipc/methodtemplate.h ../include/syscall.h \
 ../include/ray/sct.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/cstring
	@echo -e "MODULE [ipc/ipc.cpp]"
	@$(CC) $(C_ARGS) ipc/ipc.cpp -o ipc/ipc.o


ipc.o:  ipc/ipc.o
	@echo -e "Generating part ipc"
	@$(LD) -Ur -o ipc.o  ipc/ipc.o


keyboard/keyboard.o: keyboard/keyboard.cpp ../include/raykernel.h \
 ../include/ray/typedefs.h ../include/rayexception.h \
 ../include/standard.h ../include/keyboard/keyboard.h \
 ../include/ipc/ipc_int.h ../include/processes/privileges.h \
 ../include/processes/arguments.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/list \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_algobase.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/i686-pc-ray/bits/c++config.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/i686-pc-ray/bits/os_defines.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/i686-pc-ray/bits/cpu_defines.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/cstddef \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/include/stddef.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/functexcept.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/exception_defines.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/cpp_type_traits.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/ext/type_traits.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/ext/numeric_traits.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_pair.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/move.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/concept_check.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_iterator_base_types.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_iterator_base_funcs.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_iterator.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/debug/debug.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/allocator.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/i686-pc-ray/bits/c++allocator.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/ext/new_allocator.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/new \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/exception \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_list.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/initializer_list \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/list.tcc \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/vector \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_construct.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_uninitialized.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_vector.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/stl_bvector.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/bits/vector.tcc \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/c++/4.4.3/typeinfo \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/include/stdarg.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/string.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/_ansi.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/newlib.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/sys/config.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/machine/ieeefp.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/sys/reent.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/_ansi.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/sys/_types.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/machine/_types.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/machine/_default_types.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/sys/lock.h \
 /usr/raycompiler/lib/gcc/i686-pc-ray/4.4.3/../../../../i686-pc-ray/include/sys/string.h \
 ../include/ipc/methodtemplate.h ../include/processes/processes.h \
 ../include/../../commondrivers/keyboard/barrier.h
	@echo -e "MODULE [keyboard/keyboard.cpp]"
	@$(CC) $(C_ARGS) keyboard/keyboard.cpp -o keyboard/keyboard.o


keyboard.o:  keyboard/keyboard.o
	@echo -e "Generating part keyboard"
	@$(LD) -Ur -o keyboard.o  keyboard/keyboard.o


modules:  video.o standard.o processes.o rdm.o ipc.o keyboard.o
	@echo User library complete

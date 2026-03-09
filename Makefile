.PHONY: cmake lib

cmake:
	cmake -B build/ .
	make -C build

lib: cmake
	@./build/project_lib/ProjectLib

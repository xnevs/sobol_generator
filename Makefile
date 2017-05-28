MPICXX=mpic++
CXX_FLAGS=-std=c++14 -O2 -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused

all: integrate generate

integrate: examples/integrate.cpp sobol_generator/sobol_generator.hpp sobol_generator/type_to_mpi.hpp
	$(MPICXX) $(CXX_FLAGS) -o integrate examples/integrate.cpp
	
generate: examples/generate.cpp sobol_generator/sobol_generator.hpp sobol_generator/type_to_mpi.hpp
	$(MPICXX) $(CXX_FLAGS) -o generate examples/generate.cpp

MPICXX=mpic++
CXX_FLAGS=-std=c++14 -O2 -march=native -pedantic -Wall -Wextra -Wno-unused

all: example

example: example.cpp sobol_generator/sobol_generator.hpp sobol_generator/type_to_mpi.hpp
	$(MPICXX) -o example example.cpp
	

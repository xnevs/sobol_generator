MPICXX=mpic++
CXX_FLAGS=-std=c++14 -O2 -march=native -pedantic -Wall -Wextra -Wno-unused

all: integrate generate evaluate

integrate: examples/integrate.cpp sobol_generator/sobol_generator.hpp sobol_generator/type_to_mpi.hpp
	$(MPICXX) $(CXX_FLAGS) -o integrate examples/integrate.cpp
	
generate: examples/generate.cpp sobol_generator/sobol_generator.hpp sobol_generator/type_to_mpi.hpp
	$(MPICXX) $(CXX_FLAGS) -o generate examples/generate.cpp

evaluate: examples/evaluate.cpp sobol_generator/sobol_generator.hpp sobol_generator/type_to_mpi.hpp
	$(MPICXX) $(CXX_FLAGS) -o evaluate examples/evaluate.cpp

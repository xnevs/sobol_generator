MPICXX=mpic++
CXX_FLAGS=-std=c++14 -O2 -march=native -pedantic -Wall -Wextra -Wno-unused

all: integrate generate evaluate1 evaluate2 evaluate3

integrate: examples/integrate.cpp sobol_generator/sobol_generator.hpp sobol_generator/type_to_mpi.hpp
	$(MPICXX) $(CXX_FLAGS) -o integrate examples/integrate.cpp
	
generate: examples/generate.cpp sobol_generator/sobol_generator.hpp sobol_generator/type_to_mpi.hpp
	$(MPICXX) $(CXX_FLAGS) -o generate examples/generate.cpp

evaluate1: examples/evaluate1.cpp sobol_generator/sobol_generator.hpp sobol_generator/type_to_mpi.hpp
	$(MPICXX) $(CXX_FLAGS) -o evaluate1 examples/evaluate1.cpp

evaluate2: examples/evaluate2.cpp sobol_generator/sobol_generator.hpp sobol_generator/type_to_mpi.hpp
	$(MPICXX) $(CXX_FLAGS) -o evaluate2 examples/evaluate2.cpp

evaluate3: examples/evaluate3.cpp sobol_generator/sobol_generator.hpp sobol_generator/type_to_mpi.hpp
	$(MPICXX) $(CXX_FLAGS) -o evaluate3 examples/evaluate3.cpp

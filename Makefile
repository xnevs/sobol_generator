MPICXX=mpic++
CXX_FLAGS=-std=c++14 -O2 -march=native -pedantic -Wall -Wextra -Wno-unused

all: integrate generate evaluate generate10 generate20 generate30 generate40 generate50

integrate: examples/integrate.cpp sobol_generator/sobol_generator.hpp sobol_generator/type_to_mpi.hpp
	$(MPICXX) $(CXX_FLAGS) -o integrate examples/integrate.cpp
	
generate: examples/generate.cpp sobol_generator/sobol_generator.hpp sobol_generator/type_to_mpi.hpp
	$(MPICXX) $(CXX_FLAGS) -o generate examples/generate.cpp

evaluate: examples/evaluate.cpp sobol_generator/sobol_generator.hpp sobol_generator/type_to_mpi.hpp
	$(MPICXX) $(CXX_FLAGS) -o evaluate examples/evaluate.cpp
	
generate10: examples/generate10.cpp sobol_generator/sobol_generator.hpp sobol_generator/type_to_mpi.hpp
	$(MPICXX) $(CXX_FLAGS) -o generate10 examples/generate10.cpp

generate20: examples/generate20.cpp sobol_generator/sobol_generator.hpp sobol_generator/type_to_mpi.hpp
	$(MPICXX) $(CXX_FLAGS) -o generate20 examples/generate20.cpp

generate30: examples/generate30.cpp sobol_generator/sobol_generator.hpp sobol_generator/type_to_mpi.hpp
	$(MPICXX) $(CXX_FLAGS) -o generate30 examples/generate30.cpp

generate40: examples/generate40.cpp sobol_generator/sobol_generator.hpp sobol_generator/type_to_mpi.hpp
	$(MPICXX) $(CXX_FLAGS) -o generate40 examples/generate40.cpp

generate50: examples/generate50.cpp sobol_generator/sobol_generator.hpp sobol_generator/type_to_mpi.hpp
	$(MPICXX) $(CXX_FLAGS) -o generate50 examples/generate50.cpp

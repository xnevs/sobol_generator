MPICXX=mpic++
CXX_FLAGS=-std=c++14 -O2 -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused

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

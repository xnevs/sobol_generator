CXX=g++
MPICXX=mpic++
CXX_FLAGS=-std=c++14 -O3 -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused

a.out: main.cpp sobol_generator.hpp type_to_mpi.hpp PrimitivePolynomialsModuloTwoUpToDegree27.o
	$(MPICXX) $(CXX_FLAGS)  PrimitivePolynomialsModuloTwoUpToDegree27.o main.cpp

PrimitivePolynomialsModuloTwoUpToDegree27.o: PrimitivePolynomialsModuloTwo/PrimitivePolynomialsModuloTwoUpToDegree27.h PrimitivePolynomialsModuloTwo/PrimitivePolynomialsModuloTwoUpToDegree27.c
	$(CXX) $(CXX_FLAGS) -c PrimitivePolynomialsModuloTwo/PrimitivePolynomialsModuloTwoUpToDegree27.c

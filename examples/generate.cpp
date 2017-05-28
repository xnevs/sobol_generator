#include <cstdio>
#include <cstdlib>
#include <random>
#include <vector>

#include <mpi.h>

#define PPMT_MAX_DIM 30
#include "../sobol_generator/sobol_generator.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    default_random_engine gen(1234);

    sobol::sobol_generator<3> sg(gen, MPI_COMM_WORLD);

    double y[3];
    for(int i=0; i<atoi(argv[1]); ++i) {
        sg.generate(y);
        printf("%02d %02d: %.4lf %.4lf %.4lf\n", i, rank, y[0], y[1], y[2]);
    }

    MPI_Finalize();
}

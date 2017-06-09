#include <cstdio>
#include <cstdlib>

#include <mpi.h>

#include "../sobol_generator/sobol_generator.hpp"

#define n_dimensions 50

using namespace std;

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    sobol::sobol_generator<n_dimensions> sg(argv[2], MPI_COMM_WORLD);

    int n = atoi(argv[1]);
    double y[n_dimensions];
    double sum = 0;
    for(int i=0; i<n; ++i) {
        sg.generate(y);
        for(int k=0; k<n_dimensions; ++k) {
            sum += y[k];
        }
        //printf("%02d %02d: %.12lf %.12lf %.12lf %.12lf\n", i, rank, y[0], y[1], y[2], y[3]);
    }
    printf("%.16lf\n",sum);

    MPI_Finalize();
}

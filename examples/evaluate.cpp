#include <cstdio>
#include <vector>
#include <cmath>
#include <random>

#include <mpi.h>

#include "../sobol_generator/sobol_generator.hpp"

using namespace std;

double f(double x[]) {
    return sin(x[0]+2*x[1]) + 3*pow(x[2],2) + 4*x[3];
}
double int_f = 3 + sin(1)/2 + sin(2)/2 - sin(3)/2;

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    double N = atoi(argv[2]);

    int comm_size;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    int comm_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank);

    sobol::sobol_generator<4> sg(argv[1], MPI_COMM_WORLD);

    double sum = 0;
    double x[4];
    for(int i=0; i<N; ++i) {
        sg.generate(x);
        sum += f(x);
    }

    if(comm_rank == 0) {
        MPI_Reduce(MPI_IN_PLACE,&sum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
        printf("%.16lf\n", int_f);
        printf("%.16lf\n", sum/(comm_size*N));
    } else {
        MPI_Reduce(&sum,&sum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    }

    MPI_Finalize();
}

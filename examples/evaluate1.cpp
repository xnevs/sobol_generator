#include <cstdio>
#include <vector>
#include <cmath>

#include <mpi.h>

#include "../sobol_generator/sobol_generator.hpp"

using namespace std;

double f(double x) {
    return pow(x,2);
}
double int_f = (1.0/3);


int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    double N = atoi(argv[2]);

    int comm_size;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    int comm_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank);

    sobol::sobol_generator<1> sg(argv[1], MPI_COMM_WORLD);

    double sum = 0;
    double y;
    for(int i=0; i<N; ++i) {
        sg.generate(&y);
        sum += f(y);
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

#include <cstdio>
#include <random>
#include <vector>
#include <cmath>

#include <mpi.h>

#define PPMT_MAX_DIM 30
#include "sobol_generator.hpp"

using namespace std;

double f(double x, double y) {
    return sin(x)*pow(y,2);
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int comm_size;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    random_device rd;
    default_random_engine gen(rd());

    sobol_generator<3> sg(gen, MPI_COMM_WORLD);
    uniform_real_distribution<double> dis;

    double sum1 = 0;
    double sum2 = 0;
    double y[3];
    for(int i=0; i<120; ++i) {
        sg.generate(y);
        sum1 += f(y[1],y[2]);
        sum2 += f(dis(gen),dis(gen));
    }
    if(rank == 0) {
        MPI_Reduce(MPI_IN_PLACE,&sum1,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
        MPI_Reduce(MPI_IN_PLACE,&sum2,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
        printf("%lf\n", sum1/(comm_size*120));
        printf("%lf\n", sum2/(comm_size*120));
    } else {
        MPI_Reduce(&sum1,&sum1,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
        MPI_Reduce(&sum2,&sum2,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    }

    MPI_Finalize();
}

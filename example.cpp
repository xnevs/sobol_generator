/*
 * An example of Monte Carlo integration using the
 * sobol_generator quasi-ranodm number generator.
 * 
 * We integrate the function f(x,y) = sin(x) * y^2
 * on the unit square [0,1]x[0,1].
 */

#include <iostream>
#include <vector>
#include <cmath>

#include <mpi.h>

#include "sobol_generator/sobol_generator.hpp"

double f(double x, double y) {
    return std::sin(x) * std::pow(y,2);
}

int main(int argc, char *argv[]) {
    // initialize MPI
    MPI_Init(&argc, &argv);

    int comm_size;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    int comm_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank);

    // create a sobol_generator object
    sobol::sobol_generator<2> sg(argv[1], MPI_COMM_WORLD);

    // prepare an array for the generated vectors
    double y[2];

    // the number of samples
    int n = 2000000;

    // Monte Carlo integration
    double sum = 0;
    for(int i=0; i<n; ++i) {
        sg.generate(y);
        sum += f(y[0],y[1]);
    }

    // accumulate the partial sums of all the
    // processes at the process with rank 0
    // and output the result at process 0
    if(comm_rank == 0) {
        MPI_Reduce(MPI_IN_PLACE,&sum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
        std::cout << sum / (comm_size*n) << std::endl;
    } else {
        MPI_Reduce(&sum,&sum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    }

    MPI_Finalize();
}

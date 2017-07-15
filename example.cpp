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

    const int n_dims = 2; // integrating a function of two arguments
    const int n_samples = 2000000;

    // create a sobol_generator object
    //  * the number of dimensions is a template parameter
    //  * the first constructor arguments is the path to a file
    //      containing the direction integers
    //  * the second constructor argument is an MPI communicator
    sobol::sobol_generator<n_dims> sg(argv[1], MPI_COMM_WORLD);

    // prepare an array for a sample
    double y[n_dims];

    // the number of samples
    int n = 2000000;

    // Monte Carlo integration
    double sum = 0;
    for(int i=0; i<n; ++i) {
        // call sg.generate(y) to fill the array y
        // with the vaules of the next sample
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

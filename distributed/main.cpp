#include <iostream>
#include <sstream>
#include <iomanip>
#include <random>
#include <vector>

#include <mpi.h>

#define PPMT_MAX_DIM 30
#include "sobol_generator.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    random_device rd;
    default_random_engine gen(1234);

    sobol_generator<3> sg(gen, MPI_COMM_WORLD);

    double y[3];
    for(int i=0; i<5; ++i) {
        sg.generate(y);
        ostringstream oss;
        oss << setfill('0') << setw(3) << i << " " << setfill('0') << setw(3) << rank << ": " ;
        oss << y[1] << " " << y[2] << endl;
        cout << oss.str();
    }

    MPI_Finalize();
}

#include <mpi.h>

#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

int main() {
    MPI_Init(nullptr, nullptr);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    auto arr = new int[3][4];
    if(world_rank == 0) {
        for(int i=0; i<3; ++i) {
            for(int j=0; j<4; ++j) {
                arr[i][j] = 4*i + j;
            }
        }
    }
    MPI_Bcast(arr, 3*4, MPI_INT, 0, MPI_COMM_WORLD);

    for(int i=0; i<3; ++i) {
        ostringstream oss;
        oss << world_rank << " :";
        for(int j=0; j<4; ++j) {
            oss << " " << setw(2) << arr[i][j];
        }
        oss << endl;
        cout << oss.str();
    }

    MPI_Finalize();
}

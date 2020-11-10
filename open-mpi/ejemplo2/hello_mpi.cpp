#include <iostream>
#include "mpi.h"

using namespace std;

int main(int argc, char* argv[]) 
{
    int my_id, num_processes;
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

    cout << "Hello, World! I am process " << my_id << ". Total processes: " << num_processes << endl;

    MPI_Finalize();
    return 0;
}
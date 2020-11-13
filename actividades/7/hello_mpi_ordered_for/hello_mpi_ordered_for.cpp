#include <iostream>
#include "mpi.h"

using namespace std;

int main(int argc, char *argv[]) {

    int my_id, num_processes;
    int message_sent = 0;
    int message_received = 0;

    MPI_Init(&argc, &argv);
    
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
    MPI_Status status;

    if(my_id == 0) {
        cout << "Hello. I am process: " << my_id << ". Total processes: " << num_processes << endl;
        for(int i = 1; i < num_processes; ++i)
        {
            message_sent = i;
            MPI_Ssend(&message_sent, 1 /*count*/, MPI_INT, i /*dest*/, 123 /*message id*/, MPI_COMM_WORLD);
            MPI_Recv(&message_received, 1 /* count*/, MPI_INT, i /*source*/, 123 /*message id*/, MPI_COMM_WORLD, &status);
        }
    }
    else {
        MPI_Recv(&message_received, 1 /* count*/, MPI_INT, 0 /*source*/, 123 /*message id*/, MPI_COMM_WORLD, &status);
        cout << "Hello. I am process: " << my_id << ". Total processes: " << num_processes << endl;
        MPI_Ssend(&message_sent, 1 /*count*/, MPI_INT, 0 /*dest*/, 123 /*message id*/, MPI_COMM_WORLD);
    }


    MPI_Finalize();

    return 0;
}
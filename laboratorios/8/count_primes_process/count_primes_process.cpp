#include <iostream>
#include <mpi.h>
#include <math.h>
#include <stdlib.h>

using namespace std;

bool isPrime(int number) {
    if ( number < 2 ) return false;
	if ( number == 2 ) return true;
	if ( number % 2 == 0 ) return false;

	for ( size_t i = 3, last = (size_t)(double)sqrt(number); i <= last; i += 2 )
		if ( number % i == 0 )
			return false;

	return true;            
}

// Logica: https://math.stackexchange.com/questions/46014/programming-logic-splitting-up-tasks-between-threads
void doWork(int* num_processes, int* pid, int* limit)
{   
    MPI_Send(&primeCounter, 1, MPI_INT, 0, 123, MPI_COMM_WORLD);
}

int main(int argc, char *argv[])
{
    int upper_limit, num_processes, pid, receive_buffer = 0, counter = 0, time;
    if (argc < 1) goto error;
    else if (stoi(argv[argc - 1]) < 2) goto error;
    else upper_limit = stoi(argv[argc - 1]);

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Status status;

    if(pid == 0)
    {
        for(int i = 1; i < num_processes; ++i)
        {   
            MPI_Recv(&receive_buffer, 1, MPI_INT, i, 123, MPI_COMM_WORLD, &status);
            cout << "Received " << receive_buffer << " from process " << i << " adding it to counter" << endl;
            counter+=receive_buffer; 
        }
        cout << counter << " primes found in range [2, " << upper_limit << "] in 0.000584510112s with " << num_processes << " processes" << endl;
    }
    else
        doWork(&num_processes, &pid, &upper_limit);

    MPI_Finalize();

    return 0;

error:
    perror("Error, invalid number of arguments");
    return -1;
}
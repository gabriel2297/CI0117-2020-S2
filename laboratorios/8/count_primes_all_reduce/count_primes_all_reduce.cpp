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

int main(int argc, char *argv[])
{
  int my_id, p_interval, numProcesses, lower_limit, upper_limit, message_sent, message_received, primes = 0, counter = 0, segments, temp;
  size_t max_num;
  double start_time = 0.0, end_time = 0.0;
  MPI_Init(&argc, &argv);

  MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
  MPI_Status status;

  if (my_id == 0){
    if (argc > 1){
      max_num = (size_t)strtoul(argv[1], NULL, 10);
      segments = max_num / numProcesses;
    }
    else {
      std::cerr << "Error, invalid number of parameters" << std::endl;
      return 1;
    }
    for (int i = 1; i < numProcesses; ++i){
      MPI_Send(&max_num, 1, MPI_INT, i, 123, MPI_COMM_WORLD);
      MPI_Send(&segments, 1, MPI_INT, i, 123, MPI_COMM_WORLD);
    }

  }

  if (!my_id){
    lower_limit = 0;
    upper_limit = (int)(my_id + 1) * segments;
  }
  else {
    MPI_Recv(&max_num, 1, MPI_INT, 0, 123, MPI_COMM_WORLD, &status);
    MPI_Recv(&segments, 1, MPI_INT, 0, 123, MPI_COMM_WORLD, &status);
    lower_limit = (int)(my_id * segments) + 1;
    upper_limit = (my_id == numProcesses - 1) ? max_num : (int)(my_id + 1) * segments;
  }
  start_time = MPI_Wtime();
  for (int i = lower_limit; i <= upper_limit; ++i){
    if(isPrime(i)){
      ++counter;
    }
  }
  end_time = MPI_Wtime();
  
  MPI_Allreduce(&counter, &primes, 1,MPI_INT, MPI_SUM, MPI_COMM_WORLD);
  std::cout << "process " << my_id << ": " << counter << " out of " << primes <<  " primes found in range [" << lower_limit << ", " << upper_limit << "] in " << std::fixed << (end_time - start_time) << "s with " << numProcesses << " processes" << std::endl;

  MPI_Finalize();

  return 0;
}

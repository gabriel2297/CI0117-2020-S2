#include <iostream>
#include <omp.h>
#include <time.h>
#include <math.h>
#include <string>
#include <unistd.h>
using namespace std;


typedef struct timespec walltime_t;

void walltime_start(walltime_t* start){
    clock_gettime(CLOCK_MONOTONIC, start);
}

double walltime_elapsed(const walltime_t* start){
    walltime_t finish;
    clock_gettime(CLOCK_MONOTONIC, &finish);

    double elapsed = (finish.tv_sec - start->tv_sec);
    elapsed += (finish.tv_nsec - start->tv_nsec) / 1000000000.0;

    return elapsed;
}

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
    walltime_t* walltime = (walltime_t*)calloc(1, sizeof (walltime_t));
    int upper_limit = 0;
    int counter = 0;
 
    if (argc < 1)
    {
        perror("Error, invalid number of arguments");
    
    }else if (stoi(argv[1]) < 2){
        perror("Error, the number must be greater or equal to 2");
    }
    else
    {
        upper_limit = stoi(argv[1]);
    }

    walltime_start(walltime);
    #pragma omp parallel for default(none) shared(upper_limit) reduction(+: counter) schedule(runtime)
    for (int i = 2; i < upper_limit; ++i){
        if(isPrime(i)) ++counter;
    }
    double time_taken = walltime_elapsed(walltime);
    cout << "There are " << counter << " prime numbers between 2 and " << upper_limit << endl;
    cout << "The time taken was: " << fixed << time_taken << "s" << endl;

    free(walltime);

    return 0;

}
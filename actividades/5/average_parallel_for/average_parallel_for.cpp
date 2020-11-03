#include <iostream>
#include <string>
#include <omp.h>

using namespace std;

#define NUM_THREADS 4

int main(int argc, char *argv[])
{
    argc -= 1;
    if (argc <= 0)
    {
        cout << "Invalid number of parameters" << endl;
        return 1;
    }
    else if (argc % NUM_THREADS != 0)
    {
        cout << "Total number of parameters has to be even" << endl;
        return 1;
    }

    double sum = 0.0;

    #pragma omp parallel for num_threads(NUM_THREADS) default(none) shared(sum, argc, argv, cout)
    for(int i = 0; i < argc; ++i)
    {   
        #pragma omp critical(sum)
        cout << "Thread " << omp_get_thread_num() << ": Processing number " << atoi(argv[i + 1]) << endl;
        sum += atoi(argv[i + 1]);
    }

    cout << "Average: " << (sum / argc) << endl;

    return 0;
}
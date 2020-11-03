#include <iostream>
#include <string>
#include <omp.h>

using namespace std;

#define NUM_THREADS 4

static void calculate_sum(char **array, int array_size, double* global_sum)
{
    double local_sum = 0.0;
    int total_indexes_to_process = array_size / NUM_THREADS;
    #pragma omp critical
    // empezamos en omp_get_thread_num + 1 porque argv[0] es ./average
    for(int i = 0, curr = omp_get_thread_num() + 1; i < total_indexes_to_process; ++i, ++curr) {
        local_sum += atoi(array[curr]);
        cout << "Thread " << omp_get_thread_num() << ": Processing number " << atoi(array[curr]) << endl;
    }
    *global_sum += local_sum;
}

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

    #pragma omp parallel num_threads(NUM_THREADS) default(none) shared(sum, argc, argv)
    {
        calculate_sum(argv, argc, &sum);
    }

    cout << "Average: " << (sum / argc) << endl;

    return 0;
}
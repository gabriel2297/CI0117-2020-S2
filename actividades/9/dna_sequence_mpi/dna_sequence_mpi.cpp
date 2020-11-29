#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "mpi.h"

using namespace std;

void initArray(int *array, int size)
{
    for (int i = 0; i < size; ++i)
    {
        array[i] = 0;
    }
}

int main(int argc, char *argv[])
{
    string sequence;
    int sequence_count[26], final_sequence_count[26], total_processes, pid;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &total_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Status status;

    initArray(sequence_count, 26);

    if (argc < 2)
    {
        cout << "Invalid number of params." << endl;
        return 1;
    }

    if (pid == 0)
    {
        ifstream file(argv[1]);
        if (file.is_open())
        {
            getline(file, sequence);
            file.close();
        }
        else
        {
            cout << "Unable to open file" << argv[1] << endl;
            return 1;
        }
    }

    // decirle a los otros hilos cual es el size de la secuencia
    int sequence_size = sequence.length();
    MPI_Bcast(&sequence_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

    bool is_not_divisible = (sequence_size % total_processes) ? true : false;
    int segment_size = sequence_size / total_processes;
    char* segmented_sequence = new char[segment_size];

    if(pid == 0) {
        cout << "Total processes: " << total_processes << ". Each will process " << segment_size << " characters of the " << sequence_size << " chars sequence\n"; 
        is_not_divisible ? (cout << "The sequence is not divisible by the total processes" << endl) : (cout << "The sequence is divisible by the total processes" << endl);
    }

    MPI_Scatter(&sequence[0], segment_size, MPI_CHAR, segmented_sequence, segment_size, MPI_CHAR, 0, MPI_COMM_WORLD);

    double duration = MPI_Wtime();
    int index;
    for (int i = 0; i < segment_size; ++i)
    {
        index = segmented_sequence[i] - 'a';
        if (index < 26 && index >= 0)
        {
            sequence_count[index]++;
        }
        else
        {
            cout << "Invalid char [" << segmented_sequence[i] << "]" << endl;
        }
    }

    if(is_not_divisible && pid == 0)
    {
        int index;
        int missing_segment_indexes = sequence_size - (sequence_size % total_processes);
        cout << "Process 0 to process " << missing_segment_indexes << " missing" << endl;
        for (int i = missing_segment_indexes; i < sequence_size; ++i)
        {
            index = sequence[i] - 'a';
            if (index < 26 && index >= 0)
            {
                sequence_count[index]++;
            }
            else
            {
                cout << "Invalid char [" << sequence[i] << "]" << endl;
            }
        }
    }

    MPI_Reduce(sequence_count, final_sequence_count, 26, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    duration = MPI_Wtime() - duration;

    if(pid == 0)
    {
        cout << "Sequence occurrences:";
        for (int j = 0; j < 26; ++j)
        {
            if (final_sequence_count[j] > 0)
            {
                cout << " " << (char)('a' + j) << "=" << final_sequence_count[j];
            }
        }
        cout << ". Took: " << duration << "s.";
        cout << endl;
    }

    MPI_Finalize();
    delete[] segmented_sequence;

    return 0;
}
#include <iostream>
#include "mpi.h"

using namespace std;

int main(int argc, char* argv[])
{

    MPI_Init(&argc, &argv);

    cout << "Hello MPI!!" << endl;

    MPI_Finalize();

    return 0;

}


#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

using namespace std;

int main(int argc, char *argv[]) 
{

    int my_id, num_processes, cantidad_valores;
    int *arreglo;
    int message_received, message_sent;
    MPI_Status status;
    int minimo = -1, maximo = -1, suma = -1, numero_seleccionado = 0;

    MPI_Init(&argc, &argv);
    
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

    if(my_id == 0)
    {
        cout << "Digite la cantidad de valores a ingresar: ";
        cin >> cantidad_valores;
        arreglo = new int[cantidad_valores];
        for(int i = 0; i < cantidad_valores; ++i) 
        {
            cout << "Ingrese el valor " << i+1 << ": ";
            cin >> arreglo[i];
        }
    }   

    MPI_Bcast(&cantidad_valores, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(my_id != 0)
    {
        arreglo = new int[cantidad_valores];
    }

    MPI_Bcast(arreglo, cantidad_valores, MPI_INT, 0, MPI_COMM_WORLD);

    srand(time(NULL) * my_id * 1000); /* Initialize seed */
    int index = rand() % cantidad_valores;
    numero_seleccionado = arreglo[index];

    MPI_Reduce(&numero_seleccionado, &maximo, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&numero_seleccionado, &minimo, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
    MPI_Reduce(&numero_seleccionado, &suma, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (my_id != 0)
    {
        MPI_Recv(&message_received, 1 /* count*/, MPI_INT, my_id - 1 /*source*/, 123 /*message id*/, MPI_COMM_WORLD, &status);
    }

    cout << "Hola, soy el proceso " << my_id << ". Elegi el numero " << numero_seleccionado << endl;

	if ( my_id < num_processes - 1 ) 
    {
        MPI_Send(&message_sent, 1 /*count*/, MPI_INT, my_id + 1 /*dest*/, 123 /*message id*/, MPI_COMM_WORLD);
    }

    if(my_id == 0) 
    {
        cout << "El maximo es " << maximo << "\nEl minimo es " << minimo << "\nEl promedio es " << (suma/num_processes) << endl; 
    }

    MPI_Finalize();

    return 0;
}
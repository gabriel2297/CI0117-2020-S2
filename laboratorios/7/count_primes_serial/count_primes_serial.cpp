#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        cout << "Debe especificar hasta donde calcular los numeros primos" << endl;
        return 0;
    }
    else if (argc > 2)
    {
        cout << "No puede utilizar mas de 1 argumento" << endl;
        return 0;
    }
    else if (atoi(argv[1]) <= 1)
    {
        cout << "La cantidad de numeros primos a contar no puede ir de 2 a " << atoi(argv[1]) << endl;
        return 0;
    }

    int fin = atoi(argv[1]);
}
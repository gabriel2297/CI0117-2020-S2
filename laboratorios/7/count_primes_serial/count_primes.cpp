#include <iostream>
#include <omp.h>
#include <time.h>
#include <string>
using namespace std;


/* @brief Contar cuantos numeros primeros hay entre dos y el número
    @param limite superior para el conteo de numeros primos
    @return total de numeros primos entre dos y el numero dado */
int count_primes(int upper_limit){
    int counter = 0;
    for (int i = 2; i < upper_limit; ++i){
        for (int j = 2; j <= i; ++j){
            if (!(i % j) && (i !=j)){
                break;
            } else if (i == j){
                counter++;
            }
        }
    }
    return counter;
}

int main(int argc, char *argv[])
{
    int upper_limit = 0;
    int counter = 0;
    clock_t start, end; 
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
    start = clock(); 
    counter = count_primes(upper_limit);
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "There are " << counter << " prime numbers between 2 and " << upper_limit << endl;
    cout << "The time taken was: " << fixed << time_taken << "s" << endl;

    return 0;

}
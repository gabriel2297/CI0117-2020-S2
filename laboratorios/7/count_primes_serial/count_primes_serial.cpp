#include <iostream>
#include <omp.h>
#include <time.h>
#include <math.h>
#include <string>
using namespace std;


/*  @brief Contar cuantos numeros primeros hay entre dos y el número
    @param el numero que queremos saber si es primo
    @return si el numero es primo o no 
*/
bool isPrime(int number){
    if ( number < 2 ) return false;
	if ( number == 2 ) return true;
	if ( number % 2 == 0 ) return false;

	for ( size_t i = 3, last = (size_t)(double)sqrt(number); i <= last; i += 2 )
		if ( number % i == 0 ) return false;

	return true;
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
    
    for(int i = 2; i < upper_limit; ++i) 
        if (isPrime(i)) ++counter;
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "There are " << counter << " prime numbers between 2 and " << upper_limit << endl;
    cout << "The time taken was: " << fixed << time_taken << "s" << endl;

    return 0;

}
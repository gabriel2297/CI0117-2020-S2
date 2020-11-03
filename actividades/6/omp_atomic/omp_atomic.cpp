#include <iostream>
#include <omp.h>
#include <string>
using namespace std;

int array[] = {1,2,3,4,5,6,7,8,9,10};
int copied_array[10];
const int thread_count = 5;
int main(){
    #pragma omp parallel for num_threads(thread_count) schedule(static, 1)
    for (int i = 0; i < 10; ++i){
        #pragma omp atomic read
        copied_array[i] = array[i];
    }

    cout << "Antes de actualizar los valores: " << endl;
    for (int i = 0; i < 10; ++i){
        cout << copied_array[i] << " ";
    }
    #pragma omp parallel for num_threads(thread_count) schedule(static, 1)
    for (int i = 0; i < 10; ++i){
        #pragma omp atomic update
        copied_array[i] *= 2;
    }
    cout << endl;
    cout << "Después de actualizar los valores: " << endl;
    for (int i = 0; i < 10; ++i){
        cout << copied_array[i] << " ";
    }
    cout << endl;
    return 0;
}
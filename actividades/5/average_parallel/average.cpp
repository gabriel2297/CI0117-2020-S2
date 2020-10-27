#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        cout << "Invalid number of parameters.\n";
        return 1;
    }

    double sum = 0.0;

    for (int i = 1; i < argc; i++)
    {
        sum += stoi(argv[i]);
    }

    cout << "Average: " << (sum / (argc - 1)) << endl;

    return 0;
}
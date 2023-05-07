#include <iostream> // Nauman Ali Murad - 2022479
#include <fstream>

using namespace std;

int main()
{
    string filename;
    int row, column;
    ifstream input;
    cout << endl;
    cout << "**********************************************" << endl;
    cout << "*  Welcome to the Polynomial Adding Machine! *" << endl;
    cout << "*                 2022479                    *" << endl;
    cout << "**********************************************" << endl;
    cout << "Are you ready to add some polynomials? Let's get started!" << endl;

    cout << "Please enter the name of the file: ";
    cin >> filename;

    input.open(filename + ".txt");
    if (!input)
    {
        cout << "Uh oh! File \"" << filename << ".txt\" not found! Make sure you entered the correct file name." << endl;
        return 1;
    }

    input >> row >> column;

    int **array = new int *[row];
    for (int i = 0; i < row; i++)
    {
        array[i] = new int[column];
    }

    for (int i = 0; i < row; i++) // for reading file using input
    {
        for (int j = 0; j < column; j++)
        {
            input >> array[i][j];
        }
    }

    int *newArray = new int[column]; // mem allocation for result array
    for (int j = 0; j < column; j++)
    {
        newArray[j] = 0;
    }

    for (int j = 0; j < column; j++) // i,j addition
    {
        for (int i = 0; i < row; i++)
        {
            newArray[j] += array[i][j];
        }
    }
    ofstream outputFile("result_addition.txt");
    if (outputFile.is_open())
    {
        outputFile << "The result for file \"" << filename << "\" is:" << endl;

        cout << "The result of the polynomial addition is: ";
        for (int k = 0; k < column; k++)
        {
            cout << newArray[k] << " ";
            outputFile << newArray[k] << " ";
        }
        cout << endl;
        outputFile.close();
    }
    else
    {
        cout << "Oops! Can't seem to open the output file. Maybe check your file permissions?" << endl;
    }

    for (int i = 0; i < row; i++)
    {
        delete[] array[i];
    }
    delete[] array;
    delete[] newArray;
    return 0;
}

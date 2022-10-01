#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <chrono>

#include "matrix.h"

using std::cout, std::endl, std::cin, std::vector, std::string;

std::vector<int> file_to_vector(char *filename)
{
    std::ifstream f(filename);
    std::vector<int> returnvect;
    int row;
    int col;

    f >> row;
    f >> col;

    returnvect.resize(row);
    for (int i = 0; i < row; i++)
    {
        f >> returnvect[i];
    }
    f.close();
    return returnvect;
}

std::vector<int> vector_to_file(char *filename)
{
    std::ofstream f;
    std::vector<int> returnvect;
    f.open(filename);

    int row = 0;
    int col = 0;

    f << row;
    f << col;

    for (int i = 0; i < row; i++)
    {
        f << returnvect[i];
    }
    f << std::endl;
    f.close();
    return returnvect;
}

int main()
{
    int option;
    cout << "1. matrix-vector multiplication\n2. matrix-matrix multiplication\n3. matrix Kronecker multiplication\n";
    cout << "Enter option: ";
    std::cin >> option;

    if (option == 1)
    {
        char *matrix_a = "";
        char *vector_b = "";
        char *vector_c = "";
        Matrix A;
        std::vector<int> b;
        std::vector<int> c;
        std::string line;
        cout << "matrix A file name: ";
        std::cin >> matrix_a;
        cout << std::endl;

        cout << "vector B file name: ";
        std::cin >> vector_b;
        cout << std::endl;

        A.file_to_matrix(matrix_a);
        file_to_vector(vector_b);

        cout << "vector C file name: ";
        std::cin >> vector_c;
        cout << std::endl;

        auto start = std::chrono::high_resolution_clock::now();
        A.multiply_vector(b);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);

        int num_of_multiplication = A.count_mults(b);
        int num_of_addition = A.count_adds(b);

        vector_to_file(vector_c);
        cout << "# of multiplications: " << num_of_multiplication << std::endl;
        cout << "# of additions: " << num_of_addition << std::endl;
        cout << "Execution time of the multiplication of A and B: " << duration.count() << " seconds(s)";
    }

    else if (option == 2)
    {
        char *matrix_a = "";
        char *matrix_b = "";
        char *matrix_c = "";
        char *matrix_t = "";
        Matrix A;
        Matrix B;
        Matrix C;
        Matrix T;

        cout << "matrix A file name: ";
        std::cin >> matrix_a;
        cout << std::endl;

        cout << "matrix B file name: ";
        std::cin >> matrix_b;
        cout << std::endl;

        A.file_to_matrix(matrix_a);
        B.file_to_matrix(matrix_b);

        if (A.is_multipliable(B)) // checks to see if they are multiplicable
        {
            cout << "matrix C file name: ";
            std::cin >> matrix_c;
            cout << std::endl;

            cout << "matrix T file name: ";
            std::cin >> matrix_t;
            cout << std::endl;

            auto start = std::chrono::high_resolution_clock::now(); // time complexity for mutiply 2 matrices
            C = A.multiply(B);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration_multiply = std::chrono::duration_cast<std::chrono::seconds>(stop - start);

            auto start1 = std::chrono::high_resolution_clock::now(); // time complexity for mutiply 2 matrices
            T = C.transpose();
            auto stop1 = std::chrono::high_resolution_clock::now();
            auto duration_transpose = std::chrono::duration_cast<std::chrono::seconds>(stop1 - start1);

            C.matrix_to_file(matrix_c);
            T.matrix_to_file(matrix_t);

            cout << "# of multiplications: " << A.count_mults(B) << std::endl;
            cout << "# of additions: " << A.count_adds(B) << std::endl;
            cout << "Execution time of the multiplication of A and B: " << duration_multiply.count() << " seconds(s)" << std::endl;
            cout << "Execution time of the transposal of C: " << duration_transpose.count() << " seconds(s)" << std::endl;
        }
        else
        {
            cout << "Invalid operation" << endl;
        }
    }
    else
    {
        char *matrix_a = "";
        char *matrix_b = "";
        char *matrix_c = "";
        char *matrix_t = "";
        Matrix A;
        Matrix B;
        Matrix C;
        Matrix T;

        cout << "matrix A file name: ";
        std::cin >> matrix_a;
        cout << std::endl;

        cout << "matrix B file name: ";
        std::cin >> matrix_b;
        cout << std::endl;

        A.file_to_matrix(matrix_a);
        B.file_to_matrix(matrix_b);

        if (A.is_multipliable(B)) // checks to see if they are multiplicable
        {
            cout << "matrix C file name: ";
            std::cin >> matrix_c;
            cout << std::endl;

            cout << "matrix T file name: ";
            std::cin >> matrix_t;
            cout << std::endl;

            auto start = std::chrono::high_resolution_clock::now(); // time complexity for mutiply 2 matrices
            C = A.kronecker(B);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration_kronecker = std::chrono::duration_cast<std::chrono::seconds>(stop - start);

            auto start1 = std::chrono::high_resolution_clock::now(); // time complexity for mutiply 2 matrices
            T = C.transpose();
            auto stop1 = std::chrono::high_resolution_clock::now();
            auto duration_transpose = std::chrono::duration_cast<std::chrono::seconds>(stop1 - start1);

            cout << "# of multiplications: " << A.count_mults_kron(B) << std::endl;
            cout << "Execution time of the multiplication of A and B: " << duration_kronecker.count() << " seconds(s)" << std::endl;
        }
        else
        {
            cout << "Invalid operation" << endl;
        }
    }
}
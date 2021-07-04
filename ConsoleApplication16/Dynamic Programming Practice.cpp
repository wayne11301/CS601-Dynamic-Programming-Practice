
//
//  Team member:  Yi-Nong Wei, Vijayalaxmi Patil
//

#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
using namespace std;
#define MAX_VALUE 2147483647;

void display_optimal_matrix(vector<vector<int>>& S, int i, int j) {
    // starting with last matrix multiplication value tracing each value in matrix table S(storing optimal value of indices) to print the optimal solution
    if (i == j)
        cout << "M" << i << " ";
    else
    {
        cout << "(" << " ";
        display_optimal_matrix(S, i, S[i][j]);
        cout << "*" << " ";
        display_optimal_matrix(S, S[i][j] + 1, j);
        cout << ")" << " ";
    }

}

void matrix_multiplication_order_finder(vector <int> p) {

    int n = p.size() - 1;  // storing the correct no of matrices

    vector<vector<int>> M(n + 1, vector<int>(n + 1)); // matrix table used for storing the total no of multiplication for each input matrix combination
    vector<vector<int>> S(n + 1, vector<int>(n + 1)); // matrix table used to store the index k value which has the optimal cost of multiplication for each input matrix combination

   //storing 0 in the row and column with same values
    for (int i = 1; i <= n; i++)
        M[i][i] = 0;

    for (int l = 2; l <= n; l++) //staring from the second matrix values of row and column
    {
        for (int i = 1; i <= n - l + 1; i++) // staring  with first matrix and spliting the product Mi * Mi+1.. Mj between Mk and Mk+1 where i <= k < j
        {
            int j = i + l - 1;

            // initially storing default value in each matrix
            M[i][j] = MAX_VALUE;

            for (int k = i; k <= j - 1; k++)
            {
                /* calculating the total no of multiplication using the formula
                 * M[i,j] = 0 if i=j
                 *        = min (M[i,k] + M[k+1,j] + Pi-1 * Pk * Pj where i<=k<j  */
                int q = M[i][k] + M[k + 1][j] + (p[i - 1] * p[k] * p[j]);
                // checking for the minimun value and storing the minimum value index in S table
                if (q < M[i][j])
                {
                    M[i][j] = q;
                    S[i][j] = k;
                }

            }

        }

    }

    //calling display function
    cout << "Optimal Matrices Output is :" << endl;
    display_optimal_matrix(S, 1, n);
    cout << endl;
}


int main(int argc, const char* argv[]) {

    string line, row, col, input;
    vector <int> p;
    vector<pair<string, string>> matrixmul;

    cout << "Enter the matrices, end with # when finished:" << endl;
    getline(cin, line, '#');
    cin.ignore();
    stringstream matrix_input(line);

    // reading the input data
    while (getline(matrix_input, row, '*')) {
        getline(matrix_input, col, '\n');
        matrixmul.push_back(make_pair(row, col));
    }

    // storing all the row and last column values in the vector
    for (int i = 0; i < matrixmul.size(); i++)
    {
        p.push_back(stoi(matrixmul[i].first));

        if (i == matrixmul.size() - 1)
            p.push_back(stoi(matrixmul[i].second));

    }

    //calling matrix order function
    matrix_multiplication_order_finder(p);

    return 0;
}

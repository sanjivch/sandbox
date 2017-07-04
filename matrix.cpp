#include <iostream>
#include <math.h>
#define N 7
using namespace std;

 
// Function to get cofactor of A[p][q] in temp[][]. n is current
// dimension of A[][]
void getCofactor(double A[N][N], double temp[N][N], int p, int q, int n)
{   
   
    int i = 0, j = 0;
 
    // Looping for each element of the matrix
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            //  Copying into temporary matrix only those element
            //  which are not in given row and column
            if (row != p && col != q)
            {
                temp[i][j++] = A[row][col];
 
                // Row is filled, so increase row index and
                // reset col index
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}
 
/* Recursive function for finding determinant of matrix.
   n is current dimension of A[][]. */
double determinant(double A[N][N], int n)
{
    
    
    double D = 0.0; // Initialize result
 
    //  Base case : if matrix contains single element
    if (n == 1)
        return A[0][0];
 
    double temp[N][N]; // To store cofactors
 
    double sign = 1.0;  // To store sign multiplier
 
     // Iterate for each element of first row
    for (int f = 0; f < n; f++)
    {
        // Getting Cofactor of A[0][f]
        getCofactor(A, temp, 0, f, n);
        D += sign * A[0][f] * determinant(temp, n - 1);
        
        // terms are to be added with alternate sign
        sign = -sign;
    }
 
    return D;
}
 
// Function to get adjoint of A[N][N] in adj[N][N].
void adjoint(double A[N][N],double adj[N][N])
{
      
    if (N == 1)
    {
        adj[0][0] = 1.0;
        return;
    }
 
    // temp is used to store cofactors of A[][]
    double sign = 1.0;
    double temp[N][N];
 
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        {
            
            // Get cofactor of A[i][j]
            getCofactor(A, temp, i, j, N);
 
            // sign of adj[j][i] positive if sum of row
            // and column indexes is even.
            sign = ((i+j)%2==0)? 1.0: -1.0;
 
            // Interchanging rows and columns to get the
            // transpose of the cofactor matrix
            adj[j][i] = (sign)*(determinant(temp, N-1));
        }
    }
}
 
// Function to calculate and store inverse, returns false if
// matrix is singular
bool inverse(double A[N][N], double inverse[N][N])
{
    
    // Find determinant of A[][]
    double det = determinant(A, N);
    
    if (det == 0.0)
    {
        cout << "Singular matrix, can't find its inverse";
        return false;
    }
 
    // Find adjoint
    double adj[N][N];
    adjoint(A, adj);
 
    // Find Inverse using formula "inverse(A) = adj(A)/det(A)"
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            inverse[i][j] = adj[i][j]/(det);
 
    return true;
}

void delta(double A[N][N], double F[N], double delH[N]){
    
    for(int i =0; i<N; i++){
      delH[i] = 0.0;
      for(int j =0; j<N; j++){
        delH[i] += A[i][j] * F[j];
      }
     // cout << delH[i] << endl;
    }
}

template<class T>
void display(T A[N][N])
{
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
            cout << A[i][j] << " ";
        cout << endl;
    }
}
template<class S>
void displayC(S H[N]){
  
  for (int j=0; j<N; j++){
    cout << H[j] << endl;
  }
}
 
// Driver program
int main()
{
    
                       
    double F[N] = {0.606,-0.822,-0.330,0.845,2.779,-5.002,-0.372};
    double H[N] = {198.0, 193.0, 195.0, 175.0, 188.0, 190.0, 184.0};
    double A[N][N] = { {8.352, -1.131, 0.0, 0.0, 0.0, -0.911, 0.0},
                       {-1.131, 1.514, -0.036, 0.0, 0.0, 0.0, -0.347},
                       {0.0, -0.036, 0.126, -0.013, 0.0, 0.0, 0.0},
                       {0.0, 0.0, -0.013, 0.216, -0.041, 0.0, -0.163},
                       {0.0, 0.0, 0.0, -0.041, 0.904, -0.863, 0.0},
                       {-0.911, 0.0, 0.0, 0.0, -0.863, 1.802, -0.027},
                       {0.0, -0.347, 0.0, -0.163, 0.0, -0.027, 0.537}};
 
    double news[N][N];  // To store adjoint of A[][]
    double delH[N];
 
    double inv[N][N]; // To store inverse of A[][]
 
    double node[10];
    double k[10] = {0.00584, 0.0645, 0.0645, 0.349, 0.233, 1.416, 55.20, 13.60, 82.79, 82.79};
    
    for(int i=0; i<10; i++){
      if(i==0)
        node[i] = pow((200.0-H[i])/k[i], 0.54);
      else
        node[i] = pow(abs(H[i-1]-H[i])/k[i], 0.54);
    }
    displayC(node);
    
    
    
 
    
    if (inverse(A, inv))
        display(inv);
    delta(inv,F, delH);
    
    return 0;
}

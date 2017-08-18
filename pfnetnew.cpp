/*
Solve the PF Network using Newton- Raphson method. A Jacobian of 'n' nodes and a residual matrix 
are generated based on the network interaction. The resulting equation in matrix form is solved to 
obtain the delP at the nodes. This code is based on "Simultaneous Node adjustment algorithm". 
(Ref: http://www.innovyze.com/bookstore/cwbsa/Chap5.pdf)
*/

#include <iostream>
#include <math.h>
using namespace std;

#define N 2

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



int main(){
  
  double m1, m2, m3, m4;
  double nP1 = 101.325, nP2 = 101.325, soP = 110.0, si1P = 102.0, si2P = 102.3;
  double dP1 = 0.0, dP2 = 0.0;
  double Jn[2][2], delP[2][1], res[2][1], invJ[2][2];
  
  int iter, i, j;
  /*
  **Network schematic**
  soP======|m1|========>nP1=======|m2|=====>nP2=======|m3|=======>si1P
                                            ||
                                             =========|m4|=======>si2P
  
  */
  //TODO: the network equations could be automated
  for(iter=1; iter <50;iter++){
  //Not the exact flow equations. Very generic equations. Need to be replaced with the actual ones.
    m1 = sqrt(abs(soP - nP1));
    m2 = sqrt(abs(nP1 - nP2));
    m3 = 0.5*sqrt(abs(nP2 - si1P));
    m4 = 0.5*sqrt(abs(nP2 - si2P));
    
    Jn[0][0] = m1 + m2;
    Jn[0][1] = -m2;
    Jn[1][0] = -m2;
    Jn[1][1] = m2 + m3 + m4;
    
    res[0][0] = m1 - m2;
    res[1][0] = m2 - m3 - m4;
    
    if (inverse(Jn, invJ))
          display(invJ);
          
    
    delP[0][0] = invJ[0][0] * res[0][0] + invJ[0][1] * res[1][0];
    delP[1][0] = invJ[1][0] * res[0][0] + invJ[1][1] * res[1][0];
      
    nP1 = nP1 + delP[0][0];
    nP2 = nP2 + delP[1][0];
    
    //TODO: Stopping criteria to check the convergence and exit the loop
    
    cout << m1 << " " << m2 << " " << m3 << " " << m4 << " " << nP1 << " " << nP2 << " " << delP[0][0]<<" "<<delP[1][0]<< endl;
  }
  
  
  
}

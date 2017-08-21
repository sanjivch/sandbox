#include <iostream>
#include <math.h>
using namespace std;

#define N 3

class PID{
  public:
    double PV, SP, CO;
    double error, Kc=0.5, Ti=2.0, Td;

    double controlPID(double dt, double pv, double sp, double integral){

      error = pv - sp;
      CO = Kc*error + Kc*integral/Ti;
      return CO/100.0;
    }

    double errorIntegral(double dt, double pv, double sp, double iError){
       return iError+(pv-sp)*dt;
    }
};


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
  
  PID pid1;
  pid1.CO = 0.5;
  pid1.SP = 1.0;
  pid1.Kc = -0.15;
  pid1.Ti = 1.0;
  
  double intError2 = 0.0;
  double deltaT = 0.1;
  
  double m1, m2, m3, m4 = 0.0, m5;
  double nP1 = 101.325, nP2 = 101.325, nP3 = 101.325, soP = 115.0, si1P = 103.0, si2P = 102.3;
  double dP1 = 0.0, dP2 = 0.0, dP3 = 0.0;
  double Jn[3][3], delP[3][1], res[3][1], invJ[3][3];
  
  int iter, i, j;
  /*
  
  soP======|m1|========>nP1=======|m2|=====>nP2=======|m3|=======nP3=======|m5|========>si1P
                                            ||
                                             =========|m4|=======>si2P
  
  */
  for(double t=0.0;t<2200.0;t+=deltaT){
  for(iter=1; iter <25;iter++){
  
    m1 = sqrt(abs(soP - nP1));
    m2 = sqrt(abs(nP1 - nP2));
    m3 = 0.5*sqrt(abs(nP2 - nP3));
    m4 = pid1.controlPID(deltaT,m4, pid1.SP, intError2)*sqrt(abs(nP2 - si2P));
    m5 = 0.5*sqrt(abs(nP3 - si1P));
    
    
    Jn[0][0] = m1 + m2;
    Jn[0][1] = -m2;
    Jn[0][2] = 0.0;
    Jn[1][0] = -m2;
    Jn[1][1] = m2 + m3 + m4;
    Jn[1][2] = -m3;
    Jn[2][0] = 0.0;
    Jn[2][1] = -m3;
    Jn[2][2] = m3 + m5;
    
    res[0][0] = m1 - m2;
    res[1][0] = m2 - m3 - m4;
    res[2][0] = m3 - m5;
    
    if (inverse(Jn, invJ))
         // display(invJ);
          
    
    delP[0][0] = invJ[0][0] * res[0][0] + invJ[0][1] * res[1][0] + invJ[0][2] * res[2][0];
    delP[1][0] = invJ[1][0] * res[0][0] + invJ[1][1] * res[1][0] + invJ[1][2] * res[2][0];
    delP[2][0] = invJ[2][0] * res[0][0] + invJ[2][1] * res[2][0] + invJ[2][2] * res[2][0];
      
    nP1 = nP1 + delP[0][0];
    nP2 = nP2 + delP[1][0];
    nP3 = nP3 + delP[2][0];
    
   // cout << m1 << " " << m2 << " " << m3 << " " << m4 << " " << nP1 << " " << nP2 << " " << delP[0][0]<<" "<<delP[1][0]<< endl;
  }
  
  intError2 = pid1.errorIntegral(deltaT, m4, pid1.SP, intError2);
  
  cout << m1 << " " << m2 << " " << m3 << " " <<m5<< " " << m4 << " " << nP1 << " " << nP2 << " " <<nP3 <<" "<< delP[0][0]<<" "<<delP[1][0]<< " " << delP[2][0] << " "<<endl;
  }
}

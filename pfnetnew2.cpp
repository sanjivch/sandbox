#include <iostream>
#include <cmath>
#include <math.h>
using namespace std;

#define N 3
#define PI 3.1415

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

double fric(double Re, double dia, double eps){
  if(Re > 2100.0)
      return 1.325/pow(log(eps/(3.7*dia) + 5.74/pow(Re,0.9)),2);
  else
      return 16.0/Re;
}


int main(){

  PID pid1;
  pid1.CO = 0.5;
  pid1.SP = 25.0;
  pid1.Kc = -0.65;
  pid1.Ti = 0.20;

  double intError2 = 0.0;
  double deltaT = 0.1;

  double m1, m2, m3, m4 = 0.0, m5;
  double l1 = 20.2, l2 = 20.2, l3 = 25.0, l4 = 21.5, l5 = 20.0;
  double vel1, vel2, vel3, vel4, vel5;
  double NRe1, NRe2, NRe3, NRe4, NRe5;
  double epsilon = 0.000061;
  double f1, f2, f3, f4, f5;
  double diaIn1= 380.0, diaIn2= 360.0, diaIn3 = 200.0, diaIn4 = 200.0, diaIn5 = 200.0;
  double kFit1 = 0.2, kFit2 = 0.3, kFit3 = 0.3, kFit4 = 0.0375, kFit5 = 0.3;
  double area1, area2, area3, area4, area5;
  double nP1 = 101.325, nP2 = 101.325, nP3 = 101.325, soP = 205.0, si1P = 108.0, si2P = 122.3;
  double dP1 = 0.0, dP2 = 0.0, dP3 = 0.0;
  double Jn[3][3], delP[3][1], res[3][1], invJ[3][3];
  double maxCv = 1.0;
  double rho = 997.3, viscosity = 0.000891;

  double open;

  int iter, i, j;
  /*

  soP======|m1|========>nP1=======|m2|=====>nP2=======|m3|=======nP3=======|m5|========>si1P
                                            ||
                                             =========|m4|=======>si2P

  */

  area1 = 0.25*PI*pow(0.001*diaIn1,2);
  area2 = 0.25*PI*pow(0.001*diaIn2,2);
  area3 = 0.25*PI*pow(0.001*diaIn3,2);
  area4 = 0.25*PI*pow(0.001*diaIn4,2);
  area5 = 0.25*PI*pow(0.001*diaIn5,2);

  NRe1 = NRe2 = NRe3 = NRe4 = NRe5 = 2100.0;

  for(double t=0.0;t<3000.0;t+=deltaT){
    f1 = fric(NRe1, diaIn1, epsilon);
    f2 = fric(NRe2, diaIn2, epsilon);
    f3 = fric(NRe3, diaIn3, epsilon);
    f4 = fric(NRe4, diaIn4, epsilon);
    f5 = fric(NRe5, diaIn5, epsilon);


    for(iter=1; iter <30;iter++){

      m1 = area1 * sqrt(2 * rho * abs(soP - nP1)/(f1*l1*1000.0/diaIn1 + kFit1));
      m2 = area2 * sqrt(2 * rho * abs(nP1 - nP2)/(f2*l2*1000.0/diaIn2 + kFit2));
      m3 = area3 * sqrt(2 * rho * abs(nP2 - nP3)/(f3*l3*1000.0/diaIn3 + kFit3));
      open = pid1.controlPID(deltaT,m4, pid1.SP, intError2);
      m4 = open * maxCv * area4 * sqrt(2 * rho * abs(nP2 - si2P)/(f4*l4*1000.0/diaIn4 + kFit4));
      m5 = area5 * sqrt(2 * rho * abs(nP3 - si1P)/(f5*l5*1000.0/diaIn5 + kFit5));


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

      vel1 = m1/(rho * area1);
      vel2 = m2/(rho * area2);
      vel3 = m3/(rho * area3);
      vel4 = m4/(rho * area4);
      vel5 = m5/(rho * area5);

      NRe1 = 0.001*diaIn1 * vel1 * rho/ viscosity;
      NRe2 = 0.001*diaIn2 * vel2 * rho/ viscosity;
      NRe3 = 0.001*diaIn3 * vel3 * rho/ viscosity;
      NRe4 = 0.001*diaIn4 * vel4 * rho/ viscosity;
      NRe5 = 0.001*diaIn5 * vel5 * rho/ viscosity;

  intError2 = pid1.errorIntegral(deltaT, m4, pid1.SP, intError2);
  //cout << m4 << " " << open<<endl;
  //cout << m1 << " " << m2 << " " << m3 << " " <<m5<< " " << m4 << " " << nP1 << " " << nP2 << " " <<nP3 <<" "<< delP[0][0]<<" "<<delP[1][0]<< " " << delP[2][0] << " "<<endl;
  }

  cout << m1 << " " << m2 << " " << m3 << " " <<m5<< " " << m4 << " " << nP1 << " " << nP2 << " " <<nP3 <<" "<< delP[0][0]<<" "<<delP[1][0]<< " " << delP[2][0] << " "<<open <<endl;
}

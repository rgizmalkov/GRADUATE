
/*--------------------------------------------------------------------------*/
/* Блок программ интегрирования дифференциальных уравнений движения КА
   Автор: Погодин А.В., отд. 122-2, тел. 40-42 (с)*/
/*--------------------------------------------------------------------------*/
//#pragma hdrstop
#include "variables.h"
#include "integrator.h"
#include "iostream"
/*--------------------------------------------------------------------------*/
//#pragma package(smart_init)
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/

/* Переход от юлианской даты UTC к юлианской дате TDB */
double UTC_TDB(int K, double jd)
{
double JD_inner,k_dob;
k_dob = K;
/* dUTC - глобальный параметр */
if((K==0)||(K==1))
{JD_inner = jd + pow(-1.,k_dob)*(32.184+dUTC)/86400.0;}
else {JD_inner = 0.0;}
return JD_inner;
}

/* Определение среднего звездного времени (в радианах) на заданный момент UTC */
double GMST1(double jd)
{
 double jd0,Tut,Smean;
 jd0 = floor(jd-0.5) + 0.5;
Tut = (jd0 - 2451545)/36525;
Smean = 1.7533685592 + 628.3319706889*Tut + 6.7707139E-6*Tut*Tut -
			   4.50876E-10*Tut*Tut*Tut + 1.002737909350795*pi_2*(jd-jd0);
 return Smean;
}

/*--------------------------------------------------------------------------*/
/* Вычисление углов поворота для учета прецессии и нутации */
void ELEM(double jd, double &ksi, double &zeta, double &teta, double &psi, double &eps, double &eps0)
/*
 ksi, zeta, teta - углы в радианах для расчета матрицы прецессии
 psi, eps, eps0  - углы в радианах для расчета матрицы нутации
 jd - время UTC
*/
{
double jdTDB, TDB,Ml,Ms,ul,Ds,Uzl;
int i;

jdTDB = UTC_TDB(0,jd);
TDB   = (jdTDB - 2451545.0)/36525.0;

ksi  = 0.011180860*TDB + 1.464E-6*TDB*TDB + 8.70E-8*TDB*TDB*TDB;
zeta = 0.011180860*TDB + 5.308E-6*TDB*TDB + 8.90E-8*TDB*TDB*TDB;
teta = 0.009717173*TDB - 2.068E-6*TDB*TDB - 2.02E-7*TDB*TDB*TDB;

Ml   = 2.355548394 + (1325*pi_2 + 3.470890873)*TDB + 1.517952E-4*TDB*TDB + 3.103E-7*TDB*TDB*TDB;
Ms   = 6.240035940 +   (99*pi_2 + 6.266610600)*TDB - 2.797400E-6*TDB*TDB - 5.820E-8*TDB*TDB*TDB;
ul   = 1.627901934 + (1342*pi_2 + 1.431476084)*TDB - 6.427170E-5*TDB*TDB + 5.340E-8*TDB*TDB*TDB;
Ds   = 5.198469514 + (1236*pi_2 + 5.360106500)*TDB - 3.340860E-5*TDB*TDB + 9.220E-8*TDB*TDB*TDB;
Uzl  = 2.182438624 -    (5*pi_2 + 2.341119397)*TDB + 3.614290E-5*TDB*TDB + 3.880E-8*TDB*TDB*TDB;

eps = 0; psi = 0;
for(i=0;i<=105;i++)
{ psi = psi +  (coef_A[i] + coef_B[i]*TDB)*sin(coef_a1[i]*Ml + coef_a2[i]*Ms +coef_a3[i]*ul +coef_a4[i]*Ds +coef_a5[i]*Uzl);
  eps = eps +  (coef_C[i] + coef_D[i]*TDB)*cos(coef_a1[i]*Ml + coef_a2[i]*Ms +coef_a3[i]*ul +coef_a4[i]*Ds +coef_a5[i]*Uzl);}
psi  = psi*1E-4/3600./180.*M_PI;
eps  = eps*1E-4/3600./180.*M_PI;
eps0 = 0.4090928042 - 0.2269655E-3*TDB - 2.86E-9*TDB*TDB + 8.80E-9*TDB*TDB*TDB;
eps += eps0;

}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Вычисление матрицы перехода из ГЭСК эпохи J2000.0 в эпоху текущего момента времени и обратно */
void J2000_NOW(double jd, Matrix<> &B, Matrix<> &BO)
/*
 ksi, zeta, teta - углы в радианах для расчета матрицы прецессии (должны быть предварительно насчитанны и находиться в общей область памяти)
 psi, eps, eps0  - углы в радианах для расчета матрицы нутации   (должны быть предварительно насчитанны и находиться в общей область памяти)
 jd - время UTC
*/
{
Matrix<> P, N;

P(0,0) =  cos(ksi)*cos(zeta)*cos(teta) - sin(ksi)*sin(zeta);
P(0,1) = -sin(ksi)*cos(zeta)*cos(teta) - cos(ksi)*sin(zeta);
P(0,2) = -cos(zeta)*sin(teta);

P(1,0) =  cos(ksi)*sin(zeta)*cos(teta) + sin(ksi)*cos(zeta);
P(1,1) = -sin(ksi)*sin(zeta)*cos(teta) + cos(ksi)*cos(zeta);
P(1,2) = -sin(zeta)*sin(teta);

P(2,0) =  cos(ksi)*sin(teta);
P(2,1) = -sin(ksi)*sin(teta);
P(2,2) =  cos(teta);

N(0,0) =  cos(psi);
N(0,1) = -sin(psi)*cos(eps0);
N(0,2) = -sin(psi)*sin(eps0);

N(1,0) =  sin(psi)*cos(eps);
N(1,1) =  cos(psi)*cos(eps)*cos(eps0)+sin(eps)*sin(eps0);
N(1,2) =  cos(psi)*cos(eps)*sin(eps0)-sin(eps)*cos(eps0);

N(2,0) =  sin(psi)*sin(eps);
N(2,1) =  cos(psi)*sin(eps)*cos(eps0)-cos(eps)*sin(eps0);
N(2,2) =  cos(psi)*sin(eps)*sin(eps0)+cos(eps)*cos(eps0);

B = N*P;
BO=~B;
}
/*--------------------------------------------------------------------------*/
/* Вычисление матрицы перехода из TEME в ГЭСК J2000 и обратной ей матрицы */
void TEME_GSK(double jd, Matrix<> &A, Matrix<> &AO)
/*
 jd - время UTC
*/
{
Matrix<> R;
Matrix<> B, BO;

double jd_ut,S_mean,K;

S_mean = GMST1(jd);//.....
ELEM     (jd, ksi, zeta, teta, psi, eps, eps0);

K      = psi*cos(eps);

J2000_NOW(jd, B, BO);

R(0,0) = cos(K); R(0,1) = sin(K); R(0,2) = 0;
R(1,0) =-sin(K); R(1,1) = cos(K); R(1,2) = 0;
R(2,0) = 0;      R(2,1) = 0;      R(2,2) = 1;

A = R*B;
AO=~A;
}

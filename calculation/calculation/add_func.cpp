/*--------------------------------------------------------------------------*/
/* Блок программ интегрирования дифференциальных уравнений движения КА
   Автор: Погодин А.В., отд. 122-2, тел. 40-42 (с)*/
/*--------------------------------------------------------------------------*/
//#pragma hdrstop

#include "add_func.h"
#include "constants.h"
/*--------------------------------------------------------------------------*/
//#pragma package(smart_init)

//***************************************************************************
//---------------------------------------------------------------------------
//Расчет радиус-вектора и скорости по элементам
void ElementsToCoords(double a,double e,double i,double Q,double w,double teta,double X[])
/*
a - большая полуось км
e - эксцентриситет н.а.
i - наклонение рад.
Q - долгота восх. узла рад.
w - арг. перицентра рад.
teta - ист. аномалия рад.
X - вектор состояния
*/

{
double u=w+teta;
double R_=a*fabs(1.0-e*e)/(1.0+e*cos(teta));
double rx=cos(u)*cos(Q)-sin(u)*sin(Q)*cos(i);
double ry=cos(u)*sin(Q)+sin(u)*cos(Q)*cos(i);
double rz=sin(u)*sin(i);
X[0]=R_*rx;
X[1]=R_*ry;
X[2]=R_*rz;
double Vr=sqrt(mu3/(a*fabs(1.0-e*e)))*e*sin(teta);
double Vn=sqrt(mu3/(a*fabs(1.0-e*e)))*(1.0+e*cos(teta));
double nx=-sin(u)*cos(Q)-cos(i)*cos(u)*sin(Q);
double ny=-sin(u)*sin(Q)+cos(i)*cos(u)*cos(Q);
double nz=sin(i)*cos(u);
X[3]=Vr*rx+Vn*nx;
X[4]=Vr*ry+Vn*ny;
X[5]=Vr*rz+Vn*nz;
}
//---------------------------------------------------------------------------
//Расчет элементов по радиус-вектору и скорости
void CoordsToElements(double X[], double &a, double &e, double &i, double &Q, double &w, double &teta)
{
double C[3],F[3],R[3],V[3],R_,V_,C_,F_,p,b,u,S,a1;
for(int i=0;i<=2;i++)
{
  R[i] = X[i];
  V[i] = X[i+3];
 }
R_ = Nrm(R);     V_ = Nrm(V);
VMultVector(R,V,C); C_ = Nrm(C);
F[0] = -mu3*R[0]/R_+C[2]*V[1]-C[1]*V[2]; //
F[1] = -mu3*R[1]/R_+C[0]*V[2]-C[2]*V[0]; // интеграл энергии
F[2] = -mu3*R[2]/R_+C[1]*V[0]-C[0]*V[1]; //
F_ = Nrm(F);                            //

i = acos(C[2]/C_);
a1 = mu3/(2.0*mu3/R_-V_*V_);
p = C_*C_/mu3;
e = F_/mu3;
a = fabs(a1);
Q = atan2(C[0]/(C_*sin(i)),-C[1]/(C_*sin(i)));
u = atan2(R[2]/(R_*sin(i)),(R[0]*cos(Q)+R[1]*sin(Q))/R_);
w = atan2((-F[0]*sin(Q)+F[1]*cos(Q))/F_/cos(i),(F[0]*cos(Q)+F[1]*sin(Q))/F_);
teta = u-w;
}
//---------------------------------------------------------------------------
double KeplerSolve(double a,double e, double t0, double t1)
{
double M,E1,E2,teta;
M=sqrt(mu3/pow(a,3))*(t1-t0);
E1=M;
E2=10000.;
while (fabs(E1-E2)>1e-8)
{
E1=E2;
E2=e*sin(E1)+M;
}

teta=2.*atan(tan(E1/2.)*sqrt((1.+e)/(1.-e)));
return teta;
}
//---------------------------------------------------------------------------
double InvKepler(double tau, double a, double e, double teta)
{
double M,E1,t;
M=sqrt(mu3/pow(a,3));
if (e>1)
   {
   E1=sqrt(e*e-1)*sin(teta)/(1-e*cos(teta));
   t=tau+(e*E1-log(E1+sqrt(E1*E1+1)))/M;
   }
   else
   {
   E1=sqrt(1-e*e)*sin(teta)/(1+e*cos(teta));
   t=tau+(atan2(E1,(e+cos(teta))/(1+e*cos(teta)))-e*E1)/M;
   };
return t;
}
//---------------------------------------------------------------------------
double norm(double* R, int size) {
	double result = 0.0;
	for (int i = 0; i < size; i++) {
		result += R[i] * R[i];
	}
	result = sqrt(result);
	return result;
}
int Sign(double S) {
	if (S > 0) return 1;
	if (S < 0) return -1;
	return 0;
}
//Расчет элементов по радиус-вектору и скорости
void RV2El(double X[], double &a, double &e, double &inc, double &LAN, double &w, double &teta)
{
double C[3],R_el[3],V_el[3],S,b,a1,u,p;
for(int i=0;i<=2;i++)
{
  R_el[i] = X[i];
  V_el[i] = X[i+3];
 }
double R_ = norm(R_el, 3);//Norm(R_el,3)
double V_ = Nrm(V_el);
VMultVector(R_el,V_el,C);
double C_ = Nrm(C);
inc = acos(C[2]/C_);
if (sin(inc)==0.0)
   {
   u = atan2(R_el[1]/R_,R_el[0]/R_);
   LAN = 0;
   }
   else
   {
   LAN = atan2(C[0]/(C_*sin(inc)),-C[1]/(C_*sin(inc)));
   u = atan2(R_el[2]/(R_*sin(inc)),(R_el[0]*cos(LAN)+R_el[1]*sin(LAN))/R_);
   }
a1 = mu3/(2.0*mu3/R_-V_*V_);
p = C_*C_/mu3;
e = sqrt(1.0-p/a1);
a = fabs(a1);
if (e==0.0)
   {
   w = 0.0;
   teta = -u;
   }
   else
   {
   b = 1.0/e*(p/R_-1.0);
   S = SMultVector(R_el,V_el)/(R_*V_);
   teta = atan2(sqrt(1.0-b*b)*Sign(S),b);
   
   w = u-teta;
   }
if (LAN<0.0)LAN+=pi_2;
if (w<0.0)w+=pi_2;
if (teta<0.0)teta+=pi_2;
}
//----------------------------------------------------------------------------
double Nrm(double *r)
{
double R = sqrt(r[0]*r[0]+r[1]*r[1]+r[2]*r[2]);
return R;
}
//----------------------------------------------------------------------------
double Sqr(double &a) { return a*a; }
//----------------------------------------------------------------------------
double Cub(double &a) { return a*a*a; }
//------------------------------------------------------------------------------
void VMultVector(const double V1[],const double V2[],double V3[])
{
V3[0]=V1[1]*V2[2]-V1[2]*V2[1];
V3[1]=V1[2]*V2[0]-V1[0]*V2[2];
V3[2]=V1[0]*V2[1]-V1[1]*V2[0];
}
//------------------------------------------------------------------------------
double SMultVector(const double V1[],const double V2[])
{
double R=0;
for (int i=0; i<=2; i++)
   R=R+V1[i]*V2[i];
return R;
}

//===========================================================================

//Определение матрицы поворота вокруг одной из осей СК на заданный угол
Matrix<> RotMat(const int j, const double Alpha)
//
// j - признак оси поворота:    0 - x
//                              1 - y
//                              2 - z
// Alpha - угол поворота (рад)

{
Matrix<> A;
double cA = cos(Alpha), sA = sin(Alpha);

if(j==0)
{
 A[0][0] = 1;  A[0][1] = 0;   A[0][2] = 0;
 A[1][0] = 0;  A[1][1] = cA;  A[1][2] = sA;
 A[2][0] = 0;  A[2][1] =-sA;  A[2][2] = cA;
}
if(j==1)
{
 A[0][0] = cA;  A[0][1] = 0;  A[0][2] =-sA;
 A[1][0] = 0;   A[1][1] = 1;  A[1][2] = 0;
 A[2][0] = sA;  A[2][1] = 0;  A[2][2] = cA;
}
if(j==2)
{
 A[0][0] = cA;  A[0][1] = sA; A[0][2] = 0;
 A[1][0] =-sA;  A[1][1] = cA; A[1][2] = 0;
 A[2][0] = 0;   A[2][1] = 0;  A[2][2] = 1;
}

return A;
}
//===========================================================================

//Получение матрицы перехода от ГрСК в ДМСК и обратно
void DipM(Matrix<> &Aforward,Matrix<> &Areverse)
//
//   Aforward - Матрица перехода от ГрСК к ДМСК (СК геомагнитного диполя)
//   Areverse - Матрица перехода от ДМСК к ГрСК
//
{double LongM = 289.371/180.*M_PI,
        CoLatM=  11.283/180.*M_PI,
        CLong,CLat,SLong,SLat;

  CLong = cos(LongM);
  SLong = sin(LongM);
  CLat  = cos(CoLatM);
  SLat  = sin(CoLatM);

  Aforward[0][0] = CLat*CLong;   Aforward[0][1] = CLat*SLong;   Aforward[0][2] = -SLat;
  Aforward[1][0] = -SLong;       Aforward[1][1] = CLong;        Aforward[1][2] = 0.;
  Aforward[2][0] = SLat*CLong;   Aforward[2][1] = SLat*SLong;   Aforward[2][2] = CLat;

  Areverse[0][0] = CLat*CLong;   Areverse[0][1] = -SLong;   Areverse[0][2] = SLat*CLong;
  Areverse[1][0] = CLat*SLong;   Areverse[1][1] = CLong;    Areverse[1][2] = SLat*SLong;
  Areverse[2][0] = -SLat;        Areverse[2][1] = 0.;       Areverse[2][2] = CLat;

}
//===========================================================================


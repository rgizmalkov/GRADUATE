// Intergration2.cpp: определяет точку входа для консольного приложения.
//
#include "integration.h"
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include "func.h"
#include "efemer1_m.h"
#include "../sgp4v/constants.h"
#pragma warning(disable : 4996)
using namespace std;
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
static const double Rz = 6378.16;
static const double mu = 398600.441;
static const double mu_Sol = 0.13271244e12;
static const double mu_Moon = 4902.799;
static const double		TOLX = 0.01679616*1e-8;
static const double		TOL = 1e-8;
void func_AG(const double r[3], double t, double a_G[3])
{
	double U[10][10] = { 0 }, V[10][10] = { 0 }, mod_r = 0,
		dU[9][9][3] = { 0 }, dV[9][9][3] = { 0 }, r_gr[3] = { 0 }, a_G_gr[3] = { 0 }, s;
	mod_r = ModulVec(r[0], r[1], r[2]);
	U[0][0] = 1 / mod_r;
	V[0][0] = 0;
	//s=GMST(JulianDateToDateTime(t));
	//double dt = JulianDateToDateTime(t);

	// ia?aoia a A?eiae?a
	GEI3toWGS84(r, t, r_gr);
	//GEItoGEO3(r,s,r_gr);

	//Aeaaiiaeuiua yeaiaiou
	for (int i = 0; i<9; i++)
	{
		U[i + 1][i + 1] = (2 * i + 1) / mod_r / mod_r*(r_gr[0] * U[i][i] - r_gr[1] * V[i][i]);
		V[i + 1][i + 1] = (2 * i + 1) / mod_r / mod_r*(r_gr[0] * V[i][i] + r_gr[1] * U[i][i]);
	}
	//Inoaeuiua Yeaiaiou
	for (int i = 0; i<9; i++)
		for (int j = 0; j<9; j++)
		{
			if (j>i)
			{
				U[i][j] = 0;
				V[i][j] = 0;
			}
			else
				if (i == 0)
				{
					U[i + 1][j] = (2 * i + 1)*r_gr[2] * U[i][j] / (i - j + 1) / mod_r / mod_r;
					V[i + 1][j] = (2 * i + 1)*r_gr[2] * V[i][j] / (i - j + 1) / mod_r / mod_r;
				}
				else
				{
					U[i + 1][j] = ((2 * i + 1)*r_gr[2] * U[i][j] - (i + j)*U[i - 1][j]) / (i - j + 1) / mod_r / mod_r;
					V[i + 1][j] = ((2 * i + 1)*r_gr[2] * V[i][j] - (i + j)*V[i - 1][j]) / (i - j + 1) / mod_r / mod_r;
				}

		}
	//I?iecaiaiua
	for (int i = 0; i<9; i++)
		for (int j = 0; j<9; j++)
		{
			//I?iecaiaiay ii O
			if (j == 0)
			{
				dU[i][j][0] = -0.5*U[i + 1][j + 1] - 0.5*U[i + 1][1];
				dV[i][j][0] = -0.5*V[i + 1][j + 1] + 0.5*V[i + 1][1];
			}
			else
			{
				dU[i][j][0] = -0.5*U[i + 1][j + 1] + 0.5*(i - j + 2)*(i - j + 1)*U[i + 1][j - 1];
				dV[i][j][0] = -0.5*V[i + 1][j + 1] + 0.5*(i - j + 2)*(i - j + 1)*V[i + 1][j - 1];
			}
			//I?iecaiaiay ii O
			if (j == 0)
			{
				dU[i][j][1] = -0.5*V[i + 1][j + 1] - 0.5*V[i + 1][1];
				dV[i][j][1] = 0.5*U[i + 1][j + 1] - 0.5*U[i + 1][1];
			}
			else
			{
				dU[i][j][1] = -0.5*V[i + 1][j + 1] - 0.5*(i - j + 2)*(i - j + 1)*V[i + 1][j - 1];
				dV[i][j][1] = 0.5*U[i + 1][j + 1] + 0.5*(i - j + 2)*(i - j + 1)*U[i + 1][j - 1];
			}
			//I?iecaiaiay ii Z
			dU[i][j][2] = -(i - j + 1)*U[i + 1][j];
			dV[i][j][2] = -(i - j + 1)*V[i + 1][j];
		}
	//onei?aiea
	for (int k = 0; k<3; k++)
		for (int i = 0; i<9; i++)
			for (int j = 0; j<9; j++)
				a_G_gr[k] += mu3*pow(Rz, i)*(Cnn[i][j] * dU[i][j][k] + Snn[i][j] * dV[i][j][k]);

	WGS84toGEI3(a_G_gr, t, a_G);

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void func(const double r[], double t, double funkc[])
//передаём вектор состояния и время | получаем вектор [скорости|ускорения]
{
	double SM[12] = { 0 }, a_G[3] = { 0 }, a_Moon[3] = { 0 }, a_Sol[3] = { 0 };
	int k3 = 0;
	efemerides(t, SM);

	double mod = ModulVec(r[0],r[1],r[2]);
	double mod_3 = mod*mod*mod;
	double R_Moon = ModulVec(&SM[3]);
	double R_Sun = ModulVec(SM);
	double R_Moon_3 = R_Moon*R_Moon*R_Moon;
	double R_Sun_3 = R_Sun*R_Sun*R_Sun;
	double r_M_r = ModulVec(SM[3] - r[0], SM[4] - r[1], SM[5] - r[2]);
	double r_S_r = ModulVec(SM[0] - r[0], SM[1] - r[1], SM[2] - r[2]);
	double r_M_r_3 = r_M_r*r_M_r*r_M_r;
	double r_S_r_3 = r_S_r*r_S_r*r_S_r;

	func_AG(r, t, a_G);
	//func_AG_C20(r,a_G);
	for (int k = 0; k<3; k++) {
		k3 = k + 3;
		a_Moon[k] = mu_Moon*((SM[k3] - r[k]) / r_M_r_3 - SM[k3] / R_Moon_3);
		a_Sol[k] = mu_Sol *((SM[k] - r[k]) / r_S_r_3 - SM[k] / R_Sun_3);


		funkc[k + 3] = -mu3*r[k] / mod_3
			+ a_Moon[k]
			+ a_Sol[k]
			+ a_G[k];
		funkc[k] = r[k3];
	}
}
//---------------------------------------------------------------------------
//r_0 - начальный вектор положения в J2000
//V_0 - начальный вектор скорости в J2000
//interval - интервал интегрирования в секундах
//dt - начальный шаг интегрирования(можно принять 1 сек)
//t_0 - время
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void iteracii(double r_0[3], double V_0[3], double interval, double dt, double &t_0)
{
	// ----------> JD incoming!
	if (interval>0)
	{
		double vect_pre[6] = { 0 }, vect_next[6] = { 0 }, mod[6] = { 0 },
			vect_next_cap[6] = { 0 }, sost[6] = { 0 }, f[13][6] = { 0 },
			sum = 0, TE = 0, TEmax = 0;
		double t, dt_ = 0, interval_, t_0_, tk;
		bool end = false;
		double step = dt;
		for (int i = 0;i<3;i++)
		{
			vect_pre[i] = r_0[i];
			vect_pre[i + 3] = V_0[i];
		}

		interval_ = interval;      // интервал в сек -> интервал в JulianDate
		//t_0_ = DateTimeToJulianDate(t_0);   //время начала в JulianDate
		t = t_0;                         //текущее время в JulianDate

		tk = t + interval_;                  //конечное время в JulianDate

		while (t + dt_ <= tk)
		{
			dt_ = dt / 86400.;

			//считаем по 12 штук f[13][6] для x y z Vx Vy Vz
			func(vect_pre, t, sost); //начальное значение f[0][]
			for (int i = 0; i<6; i++)
			{
				f[0][i] = sost[i];
			}

			for (int i = 1; i <= 12; i++)
			{
				for (int j = 0; j<6; j++)
				{
					sum = 0;
					for (int m = 0; m <= i - 1; m++)
						sum += (beta[i][m] * f[m][j]);
					mod[j] = vect_pre[j] + dt*sum;
				}

				func(mod, t + alpha[i] * dt_, sost);
				for (int j = 0; j<6; j++)
					f[i][j] = sost[j];
			}
			//Находим x y z Vx Vy Vz на след шаге и их же с шапкой
			for (int i = 0; i<6; i++)
			{
				sum = 0;
				for (int j = 0; j <= 10; j++)
					sum += (ce[j] * f[j][i]);
				vect_next[i] = vect_pre[i] + dt*sum;
			}

			for (int i = 0; i<6; i++)
			{
				sum = 0;
				for (int j = 0; j <= 12; j++)
					sum += (ce_cap[j] * f[j][i]);
				vect_next_cap[i] = vect_pre[i] + dt*sum;
			}

			//определяем контрольный член - главный член погрешности на одном шаге
			TEmax = -99999999.999;
			for (int i = 0; i<3; i++)
			{
				TE = fabs(vect_next_cap[i] - vect_next[i]);
				if (TE>TEmax)
					TEmax = TE;
			}

			//если эта погрешность выходит за интервал, то меняем размер шага, иначе шагаем дальше
			if (TEmax<TOLX && !end)
				dt *= 1.4;
			else if (TEmax>TOL && !end)
				dt *= 0.7;
			else
			{
				for (int i = 0;i<6;i++)  vect_pre[i] = vect_next[i];
				t += dt_; //шагаем по времени
				//std::cout << vect_next[0] << " " << vect_next[1] << " " << vect_next[2] << std::endl;
				//std::cout << vect_next[3] << " " << vect_next[4] << " " << vect_next[5] << std::endl;
				//std::cout << "t= " << "=" << std::to_string(t) << "	dt_=" << std::to_string(dt_) << std::endl;
			}
			//если при след. шаге выйдем за интервал, то посл. шаг делаем ровно до tk
			dt_ = dt / 86400.;
			if ((t + dt_>tk) && !end)
			{
				dt_ = tk - t;
				//		  if(!dt_) dt_=1;//для случаев когда шаг подходит и сразу выходит в конец интервала
				dt = dt_*86400.;
				end = true; //флаг окончания интегрирования
			}
		}
		for (int i = 0;i<3;i++)
		{
			r_0[i] = vect_pre[i];
			V_0[i] = vect_pre[i + 3];
		}
		//t_0 = JulianDateToDateTime(long(t));
		dt = step;
		t_0 = t;


	}
}


void iteraciiTestTime(double r_0[3], double V_0[3], double interval, double dt, double &t_0)
{
	// ----------> JD incoming!
	if (interval>0)
	{
		double vect_pre[6] = { 0 }, vect_next[6] = { 0 }, mod[6] = { 0 },
			vect_next_cap[6] = { 0 }, sost[6] = { 0 }, f[13][6] = { 0 },
			sum = 0, TE = 0, TEmax = 0;
		double t, dt_ = 0, interval_, t_0_, tk;
		bool end = false;
		double step = dt;
		for (int i = 0;i<3;i++)
		{
			vect_pre[i] = r_0[i];
			vect_pre[i + 3] = V_0[i];
		}

		interval_ = interval / 86400.;      // интервал в сек -> интервал в JulianDate
								   //t_0_ = DateTimeToJulianDate(t_0);   //время начала в JulianDate
		t = t_0;                         //текущее время в JulianDate

		tk = t + interval_;                  //конечное время в JulianDate

		while (t + dt_ <= tk)
		{
			dt_ = dt / 86400.;

			//считаем по 12 штук f[13][6] для x y z Vx Vy Vz
			func(vect_pre, t, sost); //начальное значение f[0][]
			for (int i = 0; i<6; i++)
			{
				f[0][i] = sost[i];
			}

			for (int i = 1; i <= 12; i++)
			{
				for (int j = 0; j<6; j++)
				{
					sum = 0;
					for (int m = 0; m <= i - 1; m++)
						sum += (beta[i][m] * f[m][j]);
					mod[j] = vect_pre[j] + dt*sum;
				}

				func(mod, t + alpha[i] * dt_, sost);
				for (int j = 0; j<6; j++)
					f[i][j] = sost[j];
			}
			//Находим x y z Vx Vy Vz на след шаге и их же с шапкой
			for (int i = 0; i<6; i++)
			{
				sum = 0;
				for (int j = 0; j <= 10; j++)
					sum += (ce[j] * f[j][i]);
				vect_next[i] = vect_pre[i] + dt*sum;
			}

			for (int i = 0; i<6; i++)
			{
				sum = 0;
				for (int j = 0; j <= 12; j++)
					sum += (ce_cap[j] * f[j][i]);
				vect_next_cap[i] = vect_pre[i] + dt*sum;
			}

			//определяем контрольный член - главный член погрешности на одном шаге
			TEmax = -99999999.999;
			for (int i = 0; i<3; i++)
			{
				TE = fabs(vect_next_cap[i] - vect_next[i]);
				if (TE>TEmax)
					TEmax = TE;
			}

			//если эта погрешность выходит за интервал, то меняем размер шага, иначе шагаем дальше
			if (TEmax<TOLX && !end)
				dt *= 1.4;
			else if (TEmax>TOL && !end)
				dt *= 0.7;
			else
			{
				for (int i = 0;i<6;i++)  vect_pre[i] = vect_next[i];
				t += dt_; //шагаем по времени
				std::cout << vect_next[0] << " " << vect_next[1] << " " << vect_next[2] << std::endl;
				std::cout << vect_next[3] << " " << vect_next[4] << " " << vect_next[5] << std::endl;
				std::cout << "t= " << "=" << std::to_string(t) << "	dt_=" << std::to_string(dt_) << std::endl;
			}
			//если при след. шаге выйдем за интервал, то посл. шаг делаем ровно до tk
			dt_ = dt / 86400.;
			if ((t + dt_>tk) && !end)
			{
				dt_ = tk - t;
				//		  if(!dt_) dt_=1;//для случаев когда шаг подходит и сразу выходит в конец интервала
				dt = dt_*86400.;
				end = true; //флаг окончания интегрирования
			}
		}
		for (int i = 0;i<3;i++)
		{
			r_0[i] = vect_pre[i];
			V_0[i] = vect_pre[i + 3];
		}
		//t_0 = JulianDateToDateTime(long(t));
		dt = step;
		t_0 = t;


	}
}

void iteraciiGetCoord(double r_0[3], double V_0[3], double interval, double dt, double &t_0)
{
	FILE* fset = fopen("orb2.txt", "ab");
	if (interval>0)
	{
		double vect_pre[6] = { 0 }, vect_next[6] = { 0 }, mod[6] = { 0 },
			vect_next_cap[6] = { 0 }, sost[6] = { 0 }, f[13][6] = { 0 },
			sum = 0, TE = 0, TEmax = 0;
		double t, dt_ = 0, interval_, t_0_, tk;
		bool end = false;
		double step = dt;
		for (int i = 0;i<3;i++)
		{
			vect_pre[i] = r_0[i];
			vect_pre[i + 3] = V_0[i];
		}

		interval_ = interval / 86400.;      // интервал в сек -> интервал в JulianDate
											//t_0_ = DateTimeToJulianDate(t_0);   //время начала в JulianDate
		t = t_0;                         //текущее время в JulianDate

		tk = t + interval_;                  //конечное время в JulianDate

		while (t + dt_ <= tk)
		{
			dt_ = dt / 86400.;

			//считаем по 12 штук f[13][6] для x y z Vx Vy Vz
			func(vect_pre, t, sost); //начальное значение f[0][]
			for (int i = 0; i<6; i++)
			{
				f[0][i] = sost[i];
			}

			for (int i = 1; i <= 12; i++)
			{
				for (int j = 0; j<6; j++)
				{
					sum = 0;
					for (int m = 0; m <= i - 1; m++)
						sum += (beta[i][m] * f[m][j]);
					mod[j] = vect_pre[j] + dt*sum;
				}

				func(mod, t + alpha[i] * dt_, sost);
				for (int j = 0; j<6; j++)
					f[i][j] = sost[j];
			}
			//Находим x y z Vx Vy Vz на след шаге и их же с шапкой
			for (int i = 0; i<6; i++)
			{
				sum = 0;
				for (int j = 0; j <= 10; j++)
					sum += (ce[j] * f[j][i]);
				vect_next[i] = vect_pre[i] + dt*sum;
			}

			for (int i = 0; i<6; i++)
			{
				sum = 0;
				for (int j = 0; j <= 12; j++)
					sum += (ce_cap[j] * f[j][i]);
				vect_next_cap[i] = vect_pre[i] + dt*sum;
			}

			//определяем контрольный член - главный член погрешности на одном шаге
			TEmax = -99999999.999;
			for (int i = 0; i<3; i++)
			{
				TE = fabs(vect_next_cap[i] - vect_next[i]);
				if (TE>TEmax)
					TEmax = TE;
			}

			//если эта погрешность выходит за интервал, то меняем размер шага, иначе шагаем дальше
			if (TEmax<TOLX && !end)
				dt *= 1.4;
			else if (TEmax>TOL && !end)
				dt *= 0.7;
			else
			{
				for (int i = 0;i<6;i++)  vect_pre[i] = vect_next[i];
				t += dt_; //шагаем по времени
				std::cout << vect_next[0] << " " << vect_next[1] << " " << vect_next[2] << std::endl;
				std::cout << vect_next[3] << " " << vect_next[4] << " " << vect_next[5] << std::endl;
				std::cout << "t= " << "=" << std::to_string(t) << "	dt_=" << std::to_string(dt_) << std::endl;
				std::string str = "";
				str +=std::to_string(vect_next[0]) + "	  " + std::to_string(vect_next[1]) + "	  " + std::to_string(vect_next[2]) + "\n";
				char const *chString = str.c_str();
				fwrite(chString, strlen(chString), 1, fset);
			}
			//если при след. шаге выйдем за интервал, то посл. шаг делаем ровно до tk
			dt_ = dt / 86400.;
			if ((t + dt_>tk) && !end)
			{
				dt_ = tk - t;
				//		  if(!dt_) dt_=1;//для случаев когда шаг подходит и сразу выходит в конец интервала
				dt = dt_*86400.;
				end = true; //флаг окончания интегрирования
			}
		}
		for (int i = 0;i<3;i++)
		{
			r_0[i] = vect_pre[i];
			V_0[i] = vect_pre[i + 3];
		}
		//t_0 = JulianDateToDateTime(long(t));
		dt = step;
		t_0 = t;
		fclose(fset);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


double iteracii2(double r_0[3], double V_0[3], double r_02[3], double V_02[3], double interval, double dt, double &t_0, double &maxDist, vector<string> &col) {
	
	long count = 0;
	if (interval>0)
	{
		double vect_pre[6] = { 0 }, vect_next[6] = { 0 }, mod[6] = { 0 },
			vect_next_cap[6] = { 0 }, sost[6] = { 0 }, f[13][6] = { 0 },
			sum = 0, TE = 0, TEmax = 0;
		double vect_preTest[6] = { 0 }, vect_nextTest[6] = { 0 }, modTest[6] = { 0 },
			vect_next_capTest[6] = { 0 }, sostTest[6] = { 0 }, fTest[13][6] = { 0 },
			sumTest = 0;
		/////////////////////////////////////////////////////////////////////////////////////////
		double t, dt_ = 0, dt1_ = 0, interval_, t_0_, tk;
		double dt1 = dt;
		double julsec = 1 / (86400 * 60);
		bool end = false;
		//////////////////////////////////////////////////////////////////////////////////////////
		for (int i = 0;i<3;i++)
		{
			vect_pre[i] = r_0[i];
			vect_pre[i + 3] = V_0[i];
		}
		for (int i = 0;i<3;i++)
		{
			vect_preTest[i] = r_02[i];
			vect_preTest[i + 3] = V_02[i];
		}
		//////////////////////////////////////////////////////////////////////////////////////////
		interval_ = interval / 86400.;      // интервал в сек -> интервал в JulianDate
		//t_0_ = DateTimeToJulianDate(t_0);   //время начала в JulianDate
		t = t_0;                         //текущее время в JulianDate

		tk = t + interval_;                  //конечное время в JulianDate
		//////////////////////////////////////////////////////////////////////////////////////////
		double distance = 999999999;
		while (t + dt_ <= tk)
		{
			//if(distance >= 150){
			dt_ = dt / 86400.;

			//считаем по 12 штук f[13][6] для x y z Vx Vy Vz
			func(vect_pre, t, sost);			//начальное значение f[0][]
			func(vect_preTest, t, sostTest);	//начальное значение fTest[0][]
			//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//
			// calculation for "1st" catalog satellite
			for (int i = 0; i<6; i++)
			{
				f[0][i] = sost[i];
			}

			for (int i = 1; i <= 12; i++)
			{
				for (int j = 0; j<6; j++)
				{
					sum = 0;
					for (int m = 0; m <= i - 1; m++)
						sum += (beta[i][m] * f[m][j]);
					mod[j] = vect_pre[j] + dt*sum;
				}

				func(mod, t + alpha[i] * dt_, sost);
				for (int j = 0; j<6; j++)
					f[i][j] = sost[j];
			}
			//Находим x y z Vx Vy Vz на след шаге и их же с шапкой
			for (int i = 0; i<6; i++)
			{
				sum = 0;
				for (int j = 0; j <= 10; j++)
					sum += (ce[j] * f[j][i]);
				vect_next[i] = vect_pre[i] + dt*sum;
			}

			for (int i = 0; i<6; i++)
			{
				sum = 0;
				for (int j = 0; j <= 12; j++)
					sum += (ce_cap[j] * f[j][i]);
				vect_next_cap[i] = vect_pre[i] + dt*sum;
			}
			//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//
			//calculation for "2nd" testing satellite
			for (int i = 0; i<6; i++)
			{
				fTest[0][i] = sostTest[i];
			}

			for (int i = 1; i <= 12; i++)
			{
				for (int j = 0; j<6; j++)
				{
					sumTest = 0;
					for (int m = 0; m <= i - 1; m++)
						sumTest += (beta[i][m] * fTest[m][j]);
					modTest[j] = vect_preTest[j] + dt*sumTest;
				}

				func(modTest, t + alpha[i] * dt_, sostTest);
				for (int j = 0; j<6; j++)
					fTest[i][j] = sostTest[j];
			}
			//Находим x y z Vx Vy Vz на след шаге и их же с шапкой
			for (int i = 0; i<6; i++)
			{
				sumTest = 0;
				for (int j = 0; j <= 10; j++)
					sumTest += (ce[j] * fTest[j][i]);
				vect_nextTest[i] = vect_preTest[i] + dt*sumTest;
			}

			for (int i = 0; i<6; i++)
			{
				sumTest = 0;
				for (int j = 0; j <= 12; j++)
					sumTest += (ce_cap[j] * fTest[j][i]);
				vect_next_capTest[i] = vect_preTest[i] + dt*sumTest;
			}
			//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//
			//определяем контрольный член - главный член погрешности на одном шаге
			TEmax = -99999999.999;
			//firstly, for catalog satellite elements
			for (int i = 0; i<3; i++)
			{
				TE = fabs(vect_next_cap[i] - vect_next[i]);
				if (TE>TEmax)
					TEmax = TE;
			}
			// now - testing element
			for (int i = 0; i<3; i++)
			{
				TE = fabs(vect_next_capTest[i] - vect_nextTest[i]);
				if (TE>TEmax)
					TEmax = TE;
			}
			
				//если эта погрешность выходит за интервал, то меняем размер шага, иначе шагаем дальше
				if (TEmax<TOLX && !end)
					dt *= 1.4;
				else if (TEmax>TOL && !end)
					dt *= 0.7;
				else
				{
					//if (distance >= 150 && dt > julsec) dt = julsec;
					for (int i = 0;i < 6;i++)  vect_pre[i] = vect_next[i];
					for (int i = 0;i < 6;i++)  vect_preTest[i] = vect_nextTest[i];

					//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//
					distance = distanceCollision(vect_pre, vect_preTest);
					if (distance < maxDist) maxDist = distance;
					if (distance <= 10.0) {
						/*std::cout << "\\\-\\\-\\\-COLLISION-//-//-//" << std::endl;
						std::cout << "Catalog Satellite is:" << std::endl;
						std::cout << vect_next[0] << " " << vect_next[1] << " " << vect_next[2] << std::endl;
						std::cout << vect_next[3] << " " << vect_next[4] << " " << vect_next[5] << std::endl;
						std::cout << "Testing Satellite is:" << std::endl;
						std::cout << vect_nextTest[0] << " " << vect_nextTest[1] << " " << vect_nextTest[2] << std::endl;
						std::cout << vect_nextTest[3] << " " << vect_nextTest[4] << " " << vect_nextTest[5] << std::endl;
						std::cout << "distance is: " << distance << std::endl;
						std::cout << std::endl;*/
						//write(vect_next, vect_nextTest, distance,t, fset);
						col.push_back(stringResult(vect_next, vect_nextTest, distance, t));
					}
					//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//

					t += dt_; //шагаем по времени


					std::cout << "Catalog Satellite is:" << std::endl;
					std::cout << vect_next[0] << " " << vect_next[1] << " " << vect_next[2] << std::endl;
					std::cout << vect_next[3] << " " << vect_next[4] << " " << vect_next[5] << std::endl;
					std::cout << "Testing Satellite is:" << std::endl;
					std::cout << vect_nextTest[0] << " " << vect_nextTest[1] << " " << vect_nextTest[2] << std::endl;
					std::cout << vect_nextTest[3] << " " << vect_nextTest[4] << " " << vect_nextTest[5] << std::endl;
					std::cout << "distance is: " << distance << std::endl;
					std::cout << "t= " << "=" << std::to_string(t) << "	dt_=" << std::to_string(dt_) << std::endl;
					std::cout << std::endl;
				}
				//если при след. шаге выйдем за интервал, то посл. шаг делаем ровно до tk
				dt_ = dt / 86400.;
				if ((t + dt_>tk) && !end)
				{
					dt_ = tk - t;
					//		  if(!dt_) dt_=1;//для случаев когда шаг подходит и сразу выходит в конец интервала
					dt = dt_*86400.;
					end = true; //флаг окончания интегрирования
				}
			}/////////////////////////////////////////////distance < 150 STEP <<<< 1 sek//////////////////////////////////////////////////////////////////////////////////

			//else {

			//	dt1_ = dt1 / 86400.;

			//	//считаем по 12 штук f[13][6] для x y z Vx Vy Vz
			//	func(vect_pre, t, sost);			//начальное значение f[0][]
			//	func(vect_preTest, t, sostTest);	//начальное значение fTest[0][]
			//										//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//
			//										// calculation for "1st" catalog satellite
			//	for (int i = 0; i<6; i++)
			//	{
			//		f[0][i] = sost[i];
			//	}

			//	for (int i = 1; i <= 12; i++)
			//	{
			//		for (int j = 0; j<6; j++)
			//		{
			//			sum = 0;
			//			for (int m = 0; m <= i - 1; m++)
			//				sum += (beta[i][m] * f[m][j]);
			//			mod[j] = vect_pre[j] + dt1*sum;
			//		}

			//		func(mod, t + alpha[i] * dt1_, sost);
			//		for (int j = 0; j<6; j++)
			//			f[i][j] = sost[j];
			//	}
			//	//Находим x y z Vx Vy Vz на след шаге и их же с шапкой
			//	for (int i = 0; i<6; i++)
			//	{
			//		sum = 0;
			//		for (int j = 0; j <= 10; j++)
			//			sum += (ce[j] * f[j][i]);
			//		vect_next[i] = vect_pre[i] + dt1*sum;
			//	}

			//	for (int i = 0; i<6; i++)
			//	{
			//		sum = 0;
			//		for (int j = 0; j <= 12; j++)
			//			sum += (ce_cap[j] * f[j][i]);
			//		vect_next_cap[i] = vect_pre[i] + dt1*sum;
			//	}
			//	//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//
			//	//calculation for "2nd" testing satellite
			//	for (int i = 0; i<6; i++)
			//	{
			//		fTest[0][i] = sostTest[i];
			//	}

			//	for (int i = 1; i <= 12; i++)
			//	{
			//		for (int j = 0; j<6; j++)
			//		{
			//			sumTest = 0;
			//			for (int m = 0; m <= i - 1; m++)
			//				sumTest += (beta[i][m] * fTest[m][j]);
			//			modTest[j] = vect_preTest[j] + dt1*sumTest;
			//		}

			//		func(modTest, t + alpha[i] * dt1_, sostTest);
			//		for (int j = 0; j<6; j++)
			//			fTest[i][j] = sostTest[j];
			//	}
			//	//Находим x y z Vx Vy Vz на след шаге и их же с шапкой
			//	for (int i = 0; i<6; i++)
			//	{
			//		sumTest = 0;
			//		for (int j = 0; j <= 10; j++)
			//			sumTest += (ce[j] * fTest[j][i]);
			//		vect_nextTest[i] = vect_preTest[i] + dt1*sumTest;
			//	}

			//	for (int i = 0; i<6; i++)
			//	{
			//		sumTest = 0;
			//		for (int j = 0; j <= 12; j++)
			//			sumTest += (ce_cap[j] * fTest[j][i]);
			//		vect_next_capTest[i] = vect_preTest[i] + dt1*sumTest;
			//	}
			//	//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//
			//	//определяем контрольный член - главный член погрешности на одном шаге
			//	TEmax = -99999999.999;
			//	//firstly, for catalog satellite elements
			//	for (int i = 0; i<3; i++)
			//	{
			//		TE = fabs(vect_next_cap[i] - vect_next[i]);
			//		if (TE>TEmax)
			//			TEmax = TE;
			//	}
			//	// now - testing element
			//	for (int i = 0; i<3; i++)
			//	{
			//		TE = fabs(vect_next_capTest[i] - vect_nextTest[i]);
			//		if (TE>TEmax)
			//			TEmax = TE;
			//	}


			//	
			//	//если эта погрешность выходит за интервал, то меняем размер шага, иначе шагаем дальше
			//	if (TEmax < TOLX && !end) {
			//		if (dt1 < 0.0011) dt1 *= 1.4;
			//		for (int i = 0;i < 6;i++)  vect_pre[i] = vect_next[i];
			//		for (int i = 0;i < 6;i++)  vect_preTest[i] = vect_nextTest[i];

			//		//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//
			//		distance = distanceCollision(vect_pre, vect_preTest);
			//		if (distance < maxDist) maxDist = distance;
			//		if (distance <= 10.0) {
			//			std::cout << "\\-\\-\\-COLLISION-//-//-//" << std::endl;
			//			std::cout << "Catalog Satellite is:" << std::endl;
			//			std::cout << vect_next[0] << " " << vect_next[1] << " " << vect_next[2] << std::endl;
			//			std::cout << vect_next[3] << " " << vect_next[4] << " " << vect_next[5] << std::endl;
			//			std::cout << "Testing Satellite is:" << std::endl;
			//			std::cout << vect_nextTest[0] << " " << vect_nextTest[1] << " " << vect_nextTest[2] << std::endl;
			//			std::cout << vect_nextTest[3] << " " << vect_nextTest[4] << " " << vect_nextTest[5] << std::endl;
			//			std::cout << "distance is: " << distance << std::endl;
			//			std::cout << std::endl;
			//			write(vect_next, vect_nextTest, distance,t, fset);
			//		}
			//		else if (TEmax>TOL && !end)
			//			dt1 *= 0.7;
			//		//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//

			//		t += dt1_; //шагаем по времени


			//		//std::cout << "Catalog Satellite is:" << std::endl;
			//		//std::cout << vect_next[0] << " " << vect_next[1] << " " << vect_next[2] << std::endl;
			//		//std::cout << vect_next[3] << " " << vect_next[4] << " " << vect_next[5] << std::endl;
			//		//std::cout << "Testing Satellite is:" << std::endl;
			//		//std::cout << vect_nextTest[0] << " " << vect_nextTest[1] << " " << vect_nextTest[2] << std::endl;
			//		//std::cout << vect_nextTest[3] << " " << vect_nextTest[4] << " " << vect_nextTest[5] << std::endl;
			//		//std::cout << "distance is: " << distance << std::endl;
			//		//std::cout << "t= " << "=" << std::to_string(t) << "	dt1_=" << std::to_string(dt1_) << std::endl;
			//		//std::cout << std::endl;
			//	}
			//	//если при след. шаге выйдем за интервал, то посл. шаг делаем ровно до tk
			//	dt1_ = dt1 / 86400.;
			//	if ((t + dt1_>tk) && !end)
			//	{
			//		dt1_ = tk - t;
			//		//		  if(!dt_) dt_=1;//для случаев когда шаг подходит и сразу выходит в конец интервала
			//		dt1 = dt1_*86400.;
			//		end = true; //флаг окончания интегрирования
			//	}
			//}
			//
			//
		//}
		for (int i = 0;i<3;i++)
		{
			r_0[i] = vect_pre[i];
			V_0[i] = vect_pre[i + 3];
			r_02[i] = vect_preTest[i];
			V_02[i] = vect_preTest[i + 3];
		}
		//t_0 = JulianDateToDateTime(long(t));
		t_0 = t;
		return 0;
	}
}





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main1()
{
	//10 - 12 - 14 00 : 00 : 00
	//	X : 5275.738649
	//	Y : 4113.778417
	//	Z : -2578.482494
	//	Vx : 2.732180
	//	Vy : 0.655926
	//	Vz : 6.868442
	//double X[6] = { 0 };
	//ElementsToCoords(8625.995544, 0.185348, 0.599401, 1.933275, 0.025489, -0.024422, X);
	double X[6] = { -2497.6936276390561 , 6568.6708278446367, 4.2301814397030295, -6.3158665350207217, -2.4380423064761634, 4.6256410305641635 };
	double r[] = { X[0], X[1], X[2] };
	double v[] = { X[3], X[4], X[5] };

	std::cout << r[0] << " " << r[1] << " " << r[2] << std::endl;
	std::cout << v[0] << " " << v[1] << " " << v[2] << std::endl;
	int Year = 2016; int Month = 02; int Day = 01; int Hour = 05; int Min = 12; double Sec = 30;
	//double jd = DateTimeToJulDate(Year, Month, Day, Hour, Min, Sec);
	//double r[] = { 5275.738649 , 4113.778417, -2578.482494 };
	//double v[] = { 2.732180 , 0.655926, 6.868442 };
	//std::cout << r[0] << " " << r[1] << " " << r[2] << std::endl;
	//std::cout << v[0] << " " << v[1] << " " << v[2] << std::endl;
	const time_t timer = time(NULL);
	double time = timer;
	double a[] = { 0, 0, 0 };

	iteracii(r, v, 86400.0, 1.0, time);
	//std::cout << res << std::endl;
	std::cout << r[0] << " " << r[1] << " " << r[2] << std::endl;
	std::cout << v[0] << " " << v[1] << " " << v[2] << std::endl;
	system("pause");
	return 0;
}


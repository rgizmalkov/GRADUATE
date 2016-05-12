// ---------------------------------------------------------------------------
#include "efemer1_m.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#pragma hdrstop
#pragma warning (disable : 4996)
static const double	ccc1 = 1.,
					e0 = 2451545.,
					thj = 36525.,
					cc1 = 1.,
					cc0 = 0.,
					ae = 149597.8667;

// ---------------------------------------------------------------------------
//#pragma package(smart_init)

/* Мусор какой-то
double ccc1 = 1.;
double e0 = 2451545.;
double thj = 36525.;
double cc1 = 1.;
double cc0 = 0.;
double ae = 149597.8667;
*/

/* Вычисление координат Луны или Солнца с использованием подготовленных таблиц
Ajd	юлианская дата
Time	время от этой даты
Npl	условный номер Луны или Солнца
R	результат - координаты Луны или Солнца
 */
void r405(double &ajd, double &time, int &npl, double *r);

double cheb(double x, int degree, double *coeff);
/* ----------------------------------------------------- */
/* Chebyshev value calculation */
/* x      - argument value */
/* degree - degree of polynom */
/* coeff  - coefficients of polynom */
/* w      - result */
/* ----------------------------------------------------- */

double d_sign(double*, double*);

// double d_int(double *);
double d_nint(double *x);
int i_dnnt(double *x);

void planet(double &ajd, int &npl, double *r);
/*
Расчет координат планет относительно Земли (модификация r405)
1 - Меркурий относительно Солнца
2 - Венера относительно Солнца
3 - Барицентр системы Земля-Луна  отн. Солнца
4 - Марс относительно Солнца
5 - Юпитер относительно Солнца
6 - Сатурн относительно Солнца
...
10 - Луна относительно Земли
 */

void efemerides(double &ajd, double *SM);
// Расчет координат планет и ортов направлений на них

/* -----------------------------------------------------------------------------
/* -----------------------------------------------------------------------------
/* -----------------------------------------------------------------------------

/* Вычисление координат Луны или Солнца с использованием подготовленных таблиц
r405(ajd,time,npl,r)
ajd     - jd-date
time    - time from ajd
npl     - number of planet
r       - result
 */
void r405(double &ajd, double &time, int &npl, double *r) {
	static double* de405 = NULL; // Место под кэш de405
	if (de405 == NULL) { // Если процедура запущена первый раз то загружаем de405 в кэш
		FILE *stream;
		if ((stream = fopen("de405", "rb")) == NULL) { //Открываем
			printf("error of open de405\n");
			return;
		}
		fseek(stream, 0, SEEK_END);
		size_t de405_size = ftell(stream);  // определяем размер файла в байтах
		rewind(stream);

		//Выделяем место под Кеш (хорошо-бы придумать как эту память потом удалять)
		if ((de405 = (double*)calloc(de405_size, sizeof(char))) == NULL) return;
        //Загружаем файл в Кэш
		if (fread(de405, sizeof(char), de405_size, stream) != de405_size) return;

		fclose(stream);
	}

	// FILE *stream;
	static const int ic[11] = {
		12, 12, 15, 10, 9, 8, 8, 6, 6, 12, 15
	};
	static const int ip[11] = {
		3, 147, 183, 273, 303, 330, 354, 378, 396, 414, 702
	};
	// double buf[746] = { 0. };
	double* buf;
	static const double dintp[11] = {
		8., 32., 16., 32., 32., 32., 32., 32., 32., 4., 32.
	};
	static const double daybeg = -54770.;
	static const double dayend = 59726.;
	static const double dj50 = 2433282.5;
	static const double dint = 32.;

	double d1;
	double daymod, xx, dif;
	double dnl;
	double dtt;
	int irecbeg = 1;
	int ideg, idif, irec;
	int i, j;
	int ncc;
	int nii;

	if (npl < 1 || npl > 11)
		return;
	d1 = (ajd - dj50) * 2.;
	daymod = d_nint(&d1) / 2. + time / 86.4;
	if (daymod < daybeg)
		return;
	if (daymod >= dayend)
		return;
	idif = (int)((daymod - daybeg) / dint);
	irec = idif + irecbeg;

	/* if (irec != i_dnnt(buf)) {
	//----------------//
	//   OPEN         //
	//----------------//
	if ((stream=fopen("de405","rb")) == NULL) {
	printf ("error of open de405\n");
	return;
	}
	//------------------------------//
	//  FILE-stream-pointer setting //
	//------------------------------//
	if (fseek(stream,idif*5968,SEEK_SET) != 0) {
	printf ("error of fseek\n");
	return;
	}
	//----------------//
	//  READ          //
	//----------------//
	if (fread(buf,sizeof(buf),1,stream) == 0) return;
	fclose(stream);
	}
	 */
	buf = de405 + (idif * 746); // Устанавливаем указатель на нужное место в de405

	if (irec != i_dnnt(buf)) {
		printf("error of irec number\n");
		printf("irec=%10d", irec);
		printf("buf=%10.3f\n", buf);
		return;
	}
	d1 = (ajd - dj50 - buf[1]) * 2.;
	dif = d_nint(&d1) / 2. + time / 86.4;
	ncc = ic[npl - 1];
	ideg = ncc - 1;
	dtt = dintp[npl - 1];
	nii = (int)(dif / dtt);
	xx = (dif / dtt - nii) * 2. - 1.;
	j = ip[npl - 1] + (nii * 3 - 1) * ncc;
	for (i = 0; i <= 2; ++i) {
		j += ncc;
		r[i] = cheb(xx, ideg, &buf[j - 1]);
		r[i] *= 0.001;
	}
	return;

}

/* ----------------------------------------------------- */
/* Chebyshev value calculation */
/* x      - argument value */
/* degree - degree of polynom */
/* coeff  - coefficients of polynom */
/* w      - result */
/* ----------------------------------------------------- */
double cheb(double x, int degree, double *coeff) {
	int i;
	double bk, bk1, bk2, w;
	bk1 = 0.;
	bk2 = 0.;
	for (i = degree; i >= 1; --i) {
		bk = coeff[i] - bk2 + bk1 * 2. * x;
		bk2 = bk1;
		bk1 = bk;
	}
	w = coeff[0] - bk2 + bk1 * x;
	return w;
}
// ----------------------------------------------------------------------------

double d_nint(double *x) {
	return((*x) >= 0 ? floor(*x + 0.5) : -floor(0.5 - *x));
}

// ----------------------------------------------------------------------------
int i_dnnt(double *x) {
	return((*x) >= 0 ? (int)floor(*x + 0.5) : -(int)floor(0.5 - *x));
}

// ----------------------------------------------------------------------------
/*
Расчет координат планет относительно Земли (модификация r405)
1 - Меркурий
2 - Венера
3 - Солнце
4 - Марс
...
10 - Луна
 */
void planet(double &ajd, int &npl, double *r) {
	double ajd0 = floor(ajd) + 0.5;
	double days = ajd - ajd0;
	double tt = days * 86.4;
	r405(ajd0, tt, npl, r);
}
// ----------------------------------------------------------------------------

void efemerides(double &ajd, double *SM)
// Расчет координат планет и ортов направлений на них относительно КА
// ajd      - всемирное координированное время (UTC)
// SM       - вектор размерности 12 содержащий (по порядку) следующие вектора: [RS,RM,RSort,RMort]
// RS[3]    - Радиус вектор Солнца
// RM[3]    - Радиус вектор Луны
// RSort[3] - Орт Солнца
// RMort[3] - Орт Луны
{
	double RS[3] = {0.},
	RM[3] = {0.},
	RSort[3] = {0.},
	RMort[3] = {0.};

	double k = 4902.800582 / (398600.448 + 4902.800582);
	double jd_tdb = ajd + 67.184 / 86400.;
	int sun = 3, moon = 10;

	planet(jd_tdb, sun, RS); // Получение координат Солнца
	planet(jd_tdb, moon, RM); // Получение координат Луны

	double RSort_ = 0;
	double RMort_ = 0;

	for (int i = 0; i <= 2; i++)
		RS[i] = -RS[i] + k * RM[i];

	for (int i = 0; i <= 2; i++) {
		RS[i] = RS[i] * 1000.;
		RM[i] = RM[i] * 1000.;
		RSort_ += RS[i] * RS[i];
		RMort_ += RM[i] * RM[i];
	}

	RSort_ = sqrt(RSort_);
	RMort_ = sqrt(RMort_);
	for (int i = 0; i <= 2; i++) {
		RSort[i] = RS[i] / RSort_;
		/* TODO : Добавить проверку деления на 0 (при невозможности прочитать файл de405 */
		RMort[i] = RM[i] / RMort_;
	}

	for (int i = 0; i <= 2; i++) {
		SM[i] = RS[i];
		SM[i + 3] = RM[i];
		SM[i + 6] = RSort[i];
		SM[i + 9] = RMort[i];
	}
}

//---------------------------------------------------------------------------

#ifndef integratorH
#define integratorH
#include "math.h"
#include "classes.h"
#include "constants.h"
#include "variables.h"
//---------------------------------------------------------------------------
/* Переход от юлианской даты UTC к юлианской дате TDB */
double UTC_TDB(int, double );

/* Определение среднего звездного времени (в радианах) на заданный момент UTC */
double GMST1(double );

/* Вычисление углов поворота для учета прецессии и нутации */
void ELEM(double ,double&,double&,double&,double&,double&, double&);

/* Вычисление матрицы перехода из ГЭСК эпохи J2000.0 в эпоху текущего момента времени и обратно */
void J2000_NOW(double , Matrix<> &, Matrix<> &);

/* Вычисление матрицы перехода из ГЭСК в ГрСК и обратной ей матрицы */
void GSK_GRIN(double , Matrix<> &, Matrix<> &);

/* Вычисление матрицы перехода из TEME в ГЭСК J2000 и обратной ей матрицы */
void TEME_GSK(double , Matrix<> &, Matrix<> &);
#endif

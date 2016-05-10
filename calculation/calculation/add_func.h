#include "classes.h"
#include "constants.h"

/*--------------------------------------------------------------------------*/
//Расчет радиус-вектора и скорости по координатам
void ElementsToCoords(double , double , double , double , double , double, double[]);

//Расчет элементов по радиус-вектору и скорости
void CoordsToElements(double X[], double &a, double &e, double &i, double &Q, double &w, double &teta);

//Расчет элементов по радиус-вектору и скорости
void RV2El(const double X[], double &a, double &e, double &inc, double &LAN, double &w, double &teta);

//Решение уравнения Кеплера (t->teta)
double KeplerSolve(double, double, double, double);

//Решение обратного уравнения Кеплера (teta->t)
double InvKepler(double, double, double, double);

//Модуль 3-мерного вектора
double Nrm(double *r);

//Возведение числа в квадрат
double Sqr(double &a);

//Возведение числа в куб
double Cub(double &a);

//Векторное умножение двух векторов
void VMultVector(const double [],const double [],double []);

//Скалярное умножение двух векторов
double SMultVector(const double [],const double []);

//Определение матрицы поворота вокруг одной из осей СК на заданный угол
Matrix<> RotMat(const int, const double);

//Получение матрицы перехода от ГрСК в ДМСК и обратно
void DipM(Matrix<> &,Matrix<> &);

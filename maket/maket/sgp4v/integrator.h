//---------------------------------------------------------------------------

#ifndef integratorH
#define integratorH
#include "math.h"
#include "classes.h"
#include "constants.h"
#include "variables.h"
//---------------------------------------------------------------------------
/* ������� �� ��������� ���� UTC � ��������� ���� TDB */
double UTC_TDB(int, double );

/* ����������� �������� ��������� ������� (� ��������) �� �������� ������ UTC */
double GMST1(double );

/* ���������� ����� �������� ��� ����� ��������� � ������� */
void ELEM(double ,double&,double&,double&,double&,double&, double&);

/* ���������� ������� �������� �� ���� ����� J2000.0 � ����� �������� ������� ������� � ������� */
void J2000_NOW(double , Matrix<> &, Matrix<> &);

/* ���������� ������� �������� �� ���� � ���� � �������� �� ������� */
void GSK_GRIN(double , Matrix<> &, Matrix<> &);

/* ���������� ������� �������� �� TEME � ���� J2000 � �������� �� ������� */
void TEME_GSK(double , Matrix<> &, Matrix<> &);
#endif

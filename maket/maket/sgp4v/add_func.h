#include "classes.h"
#include "constants.h"

/*--------------------------------------------------------------------------*/
//������ ������-������� � �������� �� �����������
void ElementsToCoords(double , double , double , double , double , double, double[]);

//������ ��������� �� ������-������� � ��������
void CoordsToElements(double X[], double &a, double &e, double &i, double &Q, double &w, double &teta);

//������ ��������� �� ������-������� � ��������
void RV2El(const double X[], double &a, double &e, double &inc, double &LAN, double &w, double &teta);

//������� ��������� ������� (t->teta)
double KeplerSolve(double, double, double, double);

//������� ��������� ��������� ������� (teta->t)
double InvKepler(double, double, double, double);

//������ 3-������� �������
double Nrm(double *r);

//���������� ����� � �������
double Sqr(double &a);

//���������� ����� � ���
double Cub(double &a);

//��������� ��������� ���� ��������
void VMultVector(const double [],const double [],double []);

//��������� ��������� ���� ��������
double SMultVector(const double [],const double []);

//����������� ������� �������� ������ ����� �� ���� �� �� �������� ����
Matrix<> RotMat(const int, const double);

//��������� ������� �������� �� ���� � ���� � �������
void DipM(Matrix<> &,Matrix<> &);

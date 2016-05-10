/*--------------------------------------------------------------------------*/
/* ���������� �������
������: Beta 1.18.08.08
�����: ������� �.�., ���. 122-2, ���. 40-42 (�)
/*--------------------------------------------------------------------------*/


#ifndef classesH
#define classesH

#include "math.h"
//#include "SysUtils.hpp"


// ����� ��������
template <class T=double>
class Vector
{
public:
  Vector()
  {
   for (int x=0;x<3;x++)
				v[x]=0.;
  }
  // �������� �������� ��������
  Vector<> operator+(Vector<> a) const
  { Vector<> result;
	for (int i=0; i<3; i++)
			result[i]=v[i]+a[i];
		return result;
	}

  // �������� ��������� ��������
  Vector<> operator-(Vector<> a) const
  { Vector<> result;
	for (int i=0; i<3; i++)
			result[i]=v[i]-a[i];
		return result;
	}

  // �������� ���������� ��������� ��������
  Vector<> operator-() const
  { Vector<> result;
	for (int i=0; i<3; i++)
			result[i]=-v[i];
		return result;
	}

  // �������� ��������� ������� �� ����� ���� double
  Vector<> operator*(double a) const
  { Vector<> result;
	for (int i=0; i<3; i++)
			result[i]=v[i]*a;
		return result;
	}
  // �������� ��������� ������� �� ����� ���� int
  Vector<> operator*(int a) const
  { Vector<> result;
	for (int i=0; i<3; i++)
			result[i]=v[i]*a;
		return result;
	}

  // �������� ������� ������� �� ����� ���� double
  Vector<> operator/(double a) const
  { Vector<> result;
	for (int i=0; i<3; i++)
			result[i]=v[i]/a;
		return result;
	}
  // �������� ������� ������� �� ����� ���� int
  Vector<> operator/(int a) const
  { Vector<> result;
	for (int i=0; i<3; i++)
			result[i]=v[i]/a;
		return result;
	}

  // �������� ���������� ������������ ��������
  T operator*(Vector<> a)
  { T result = 0;
	for (int i=0;i<3;i++) result += v[i]*a[i];
	return result;
  }

  // �������� ���������� ������������ ��������
  const T operator*(Vector<> a) const
  { T result = 0;
	for (int i=0;i<3;i++) result += v[i]*a[i];
	return result;
  }

  // �������� ���������� ������������ ��������
  Vector<> operator ^(Vector<> a)
  { Vector result;
	for (int x=0;x<3;x++)
	{int y,z;
	 y=x+1;
	 z=x+2;
	 if(y>2)y-=3;
	 if(z>2)z-=3;
	 result [x] = v[y]*a[z]-v[z]*a[y];}
	 return result;
	}

  // �������� ���������� ������������ ��������
  const Vector<> operator ^(Vector<> a) const
  { Vector result;
	for (int x=0;x<3;x++)
	{int y,z;
	 y=x+1;
	 z=x+2;
	 if(y>2)y-=3;
	 if(z>2)z-=3;
	 result [x] = v[y]*a[z]-v[z]*a[y];}
	 return result;
	}

  // �������� ��������� � ��������� �������
  T &operator[](int id)
  { return v[id];
	}

  // �������� ��������� � ��������� ������� ��� ���������� ��� const
  const T &operator[](int id) const
  { return v[id];
  }

private:
  T v[3];
};


// ����� ������

template <int W=3, int H=3, class T=double>
class Matrix
{
public:
  Matrix()
  {
   for (int x=0;x<W;x++)
		for (int y=0;y<H;y++)
				m[x][y]=0.;
  }

  // �������� ��������� ������� �� ����� ���� double
  Matrix operator*(double a)
  { Matrix result;
	for (int i=0; i<W; i++)
		for (int j=0; j<H; j++)
			result(i,j)=m[i][j]*a;
		return result;
	}

  // �������� ��������� ������� �� ����� ���� int
  Matrix operator*(int a)
  { Matrix<> result;
	for (int i=0; i<W; i++)
		for (int j=0; j<H; j++)
			result(i,j)=m[i][j]*a;
		return result;
	}

 // �������� ��������� ������� �� ������
 Vector<> operator*(Vector<> a)
  {Vector<> result;
   for (int x=0;x<W;x++)
			   result[x] = m[x][0]*a[0]+m[x][1]*a[1]+m[x][2]*a[2];
		return result;
  }

 // �������� ��������� ������
 Matrix<> operator*(Matrix<> a)
  {Matrix<> result;
   for (int x=0;x<W;x++)
		for (int y=0;y<H;y++)
			   result(x,y) = m[x][0]*a(0,y)+m[x][1]*a(1,y)+m[x][2]*a(2,y);
		return result;
  }

 // �������� �������� ������
 Matrix<> operator+(Matrix<> a)
  {Matrix<> result;
   for (int x=0;x<W;x++)
		for (int y=0;y<H;y++)
			   result(x,y) = m[x][y]+a(x,y);
		return result;
  }

 // �������� ��������� ������
 Matrix<> operator-(Matrix<> a)
  {Matrix<> result;
   for (int x=0;x<W;x++)
		for (int y=0;y<H;y++)
			   result(x,y) = m[x][y]-a(x,y);
		return result;
  }

 // �������� ���������������� ������
 Matrix<H,W,T> operator~()
  {Matrix<H,W,T> result;
   for (int x=0;x<W;x++)
		for (int y=0;y<H;y++)
			   result[x][y] = m[y][x];
		return result;
  }


  T *operator[](int w)  // ��������� � ������� � ����� �++
  {
	 return ((T*)m)+w*H;
	 }

  T &operator()(int w, int h) // ��������� � ������� � ����� ������� (�� � ������������ �++)
  {
	 return m[w][h];
	 }

private:
  T m[W][H];
};

# endif

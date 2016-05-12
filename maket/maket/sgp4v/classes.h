/*--------------------------------------------------------------------------*/
/* Библиотека классов
Версия: Beta 1.18.08.08
Автор: Погодин А.В., отд. 122-2, тел. 40-42 (с)
/*--------------------------------------------------------------------------*/


#ifndef classesH
#define classesH

#include "math.h"
//#include "SysUtils.hpp"


// класс векторов
template <class T=double>
class Vector
{
public:
  Vector()
  {
   for (int x=0;x<3;x++)
				v[x]=0.;
  }
  // операция сложения векторов
  Vector<> operator+(Vector<> a) const
  { Vector<> result;
	for (int i=0; i<3; i++)
			result[i]=v[i]+a[i];
		return result;
	}

  // операция вычитания векторов
  Vector<> operator-(Vector<> a) const
  { Vector<> result;
	for (int i=0; i<3; i++)
			result[i]=v[i]-a[i];
		return result;
	}

  // операция присвоения обратного значения
  Vector<> operator-() const
  { Vector<> result;
	for (int i=0; i<3; i++)
			result[i]=-v[i];
		return result;
	}

  // операция умножения вектора на число типа double
  Vector<> operator*(double a) const
  { Vector<> result;
	for (int i=0; i<3; i++)
			result[i]=v[i]*a;
		return result;
	}
  // операция умножения вектора на число типа int
  Vector<> operator*(int a) const
  { Vector<> result;
	for (int i=0; i<3; i++)
			result[i]=v[i]*a;
		return result;
	}

  // операция деления вектора на число типа double
  Vector<> operator/(double a) const
  { Vector<> result;
	for (int i=0; i<3; i++)
			result[i]=v[i]/a;
		return result;
	}
  // операция деления вектора на число типа int
  Vector<> operator/(int a) const
  { Vector<> result;
	for (int i=0; i<3; i++)
			result[i]=v[i]/a;
		return result;
	}

  // операция скалярного произведения векторов
  T operator*(Vector<> a)
  { T result = 0;
	for (int i=0;i<3;i++) result += v[i]*a[i];
	return result;
  }

  // операция скалярного произведения векторов
  const T operator*(Vector<> a) const
  { T result = 0;
	for (int i=0;i<3;i++) result += v[i]*a[i];
	return result;
  }

  // операция векторного произведения векторов
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

  // операция векторного произведения векторов
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

  // операция обращения к элементам вектора
  T &operator[](int id)
  { return v[id];
	}

  // операция обращения к элементам вектора при объявлении как const
  const T &operator[](int id) const
  { return v[id];
  }

private:
  T v[3];
};


// класс матриц

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

  // операция умножения матрицы на число типа double
  Matrix operator*(double a)
  { Matrix result;
	for (int i=0; i<W; i++)
		for (int j=0; j<H; j++)
			result(i,j)=m[i][j]*a;
		return result;
	}

  // операция умножения матрицы на число типа int
  Matrix operator*(int a)
  { Matrix<> result;
	for (int i=0; i<W; i++)
		for (int j=0; j<H; j++)
			result(i,j)=m[i][j]*a;
		return result;
	}

 // операция умножения матрицы на вектор
 Vector<> operator*(Vector<> a)
  {Vector<> result;
   for (int x=0;x<W;x++)
			   result[x] = m[x][0]*a[0]+m[x][1]*a[1]+m[x][2]*a[2];
		return result;
  }

 // операция умножения матриц
 Matrix<> operator*(Matrix<> a)
  {Matrix<> result;
   for (int x=0;x<W;x++)
		for (int y=0;y<H;y++)
			   result(x,y) = m[x][0]*a(0,y)+m[x][1]*a(1,y)+m[x][2]*a(2,y);
		return result;
  }

 // операция сложения матриц
 Matrix<> operator+(Matrix<> a)
  {Matrix<> result;
   for (int x=0;x<W;x++)
		for (int y=0;y<H;y++)
			   result(x,y) = m[x][y]+a(x,y);
		return result;
  }

 // операция вычитания матриц
 Matrix<> operator-(Matrix<> a)
  {Matrix<> result;
   for (int x=0;x<W;x++)
		for (int y=0;y<H;y++)
			   result(x,y) = m[x][y]-a(x,y);
		return result;
  }

 // операция транспонирования матриц
 Matrix<H,W,T> operator~()
  {Matrix<H,W,T> result;
   for (int x=0;x<W;x++)
		for (int y=0;y<H;y++)
			   result[x][y] = m[y][x];
		return result;
  }


  T *operator[](int w)  // обращение к матрице в стиле С++
  {
	 return ((T*)m)+w*H;
	 }

  T &operator()(int w, int h) // обращение к матрице в стиле Фортран (но с размерностью С++)
  {
	 return m[w][h];
	 }

private:
  T m[W][H];
};

# endif

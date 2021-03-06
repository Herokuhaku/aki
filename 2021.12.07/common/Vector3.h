#pragma once
#include <DxLib.h>

template <class T>
class Vector3Template
{
public:
	Vector3Template();
	~Vector3Template();
	Vector3Template(T x_, T y_,T z_);
	Vector3Template(VECTOR v);
	T x;
	T y;
	T z;

	// γόZq
	Vector3Template& operator = (const Vector3Template& vec);
	Vector3Template& operator = (const VECTOR& vec);

	// PZq
	Vector3Template& operator += (const Vector3Template& vec);
	Vector3Template& operator -= (const Vector3Template& vec);
	Vector3Template& operator *= (const Vector3Template& vec);
	Vector3Template& operator /= (const Vector3Template& vec);

	// 2Zq
	Vector3Template operator +(const Vector3Template& vec)const;
	Vector3Template operator -(const Vector3Template& vec)const;
	Vector3Template operator *(const Vector3Template& vec)const;
	Vector3Template operator /(const Vector3Template& vec)const;
	Vector3Template operator %(const Vector3Template& vec)const;

	Vector3Template operator +()const;
	Vector3Template operator -()const;
	
	bool operator <  (const Vector3Template& vec)const;

	VECTOR toVECTOR();


	///xNgΜε«³
	float Magnitude()const;
	void Normalize(void);
	Vector3Template Normalized(void);
};

///ΰΟπΤ·
template <class T>
float Dot(const Vector3Template<T>& va, const Vector3Template<T>& vb);

///OΟπΤ·
template <class T>
Vector3Template<T> Cross(const Vector3Template<T>& va, const Vector3Template<T>& vb);

// Vector3 Ζ intΜl₯Z
template <class T>
Vector3Template<T> operator +(const Vector3Template<T>& vec, const int& num);
template <class T>
Vector3Template<T> operator -(const Vector3Template<T>& vec, const int& num);
template <class T>
Vector3Template<T> operator *(const Vector3Template<T>& vec, const int& num);
template <class T>
Vector3Template<T> operator /(const Vector3Template<T>& vec, const int& num);

// int Ζ Vector3Μl₯Z
template <class T>
Vector3Template<T> operator +(const int& num, const Vector3Template<T>& vec);
template <class T>
Vector3Template<T> operator -(const int& num, const Vector3Template<T>& vec);
template <class T>
Vector3Template<T> operator *(const int& num, const Vector3Template<T>& vec);
template <class T>
Vector3Template<T> operator /(const int& num, const Vector3Template<T>& vec);

// Vector3 Ζ floatΜl₯Z
template <class T>
Vector3Template<T> operator + (const Vector3Template<T>& vec, const float& num);

template <class T>
Vector3Template<T> operator - (const Vector3Template<T>& vec, const float& num);

template <class T>
Vector3Template<T> operator * (const Vector3Template<T>& vec, const float& num);

template <class T>
Vector3Template<T> operator / (const Vector3Template<T>& vec, const float& num);

using Int3 = Vector3Template<int>;
using Float3 = Vector3Template<float>;
using Double3 = Vector3Template<double>;

#include "./detailes/Vector3.h"
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

	// 代入演算子
	Vector3Template& operator = (const Vector3Template& vec);
	Vector3Template& operator = (const VECTOR& vec);

	// 単項演算子
	Vector3Template& operator += (const Vector3Template& vec);
	Vector3Template& operator -= (const Vector3Template& vec);
	Vector3Template& operator *= (const Vector3Template& vec);
	Vector3Template& operator /= (const Vector3Template& vec);

	// 2項演算子
	Vector3Template operator +(const Vector3Template& vec)const;
	Vector3Template operator -(const Vector3Template& vec)const;
	Vector3Template operator *(const Vector3Template& vec)const;
	Vector3Template operator /(const Vector3Template& vec)const;
	Vector3Template operator %(const Vector3Template& vec)const;

	Vector3Template operator +()const;
	Vector3Template operator -()const;
	
	bool operator <  (const Vector3Template& vec)const;

	VECTOR toVECTOR();


	///ベクトルの大きさ
	float Magnitude()const;
	void Normalize(void);
	Vector3Template Normalized(void);
};

///内積を返す
template <class T>
float Dot(const Vector3Template<T>& va, const Vector3Template<T>& vb);

///外積を返す
template <class T>
Vector3Template<T> Cross(const Vector3Template<T>& va, const Vector3Template<T>& vb);

// Vector3 と intの四則演算
template <class T>
Vector3Template<T> operator +(const Vector3Template<T>& vec, const int& num);
template <class T>
Vector3Template<T> operator -(const Vector3Template<T>& vec, const int& num);
template <class T>
Vector3Template<T> operator *(const Vector3Template<T>& vec, const int& num);
template <class T>
Vector3Template<T> operator /(const Vector3Template<T>& vec, const int& num);

// int と Vector3の四則演算
template <class T>
Vector3Template<T> operator +(const int& num, const Vector3Template<T>& vec);
template <class T>
Vector3Template<T> operator -(const int& num, const Vector3Template<T>& vec);
template <class T>
Vector3Template<T> operator *(const int& num, const Vector3Template<T>& vec);
template <class T>
Vector3Template<T> operator /(const int& num, const Vector3Template<T>& vec);

// Vector3 と floatの四則演算
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
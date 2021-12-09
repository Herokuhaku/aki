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

	// ������Z�q
	Vector3Template& operator = (const Vector3Template& vec);
	Vector3Template& operator = (const VECTOR& vec);

	// �P�����Z�q
	Vector3Template& operator += (const Vector3Template& vec);
	Vector3Template& operator -= (const Vector3Template& vec);
	Vector3Template& operator *= (const Vector3Template& vec);
	Vector3Template& operator /= (const Vector3Template& vec);

	// 2�����Z�q
	Vector3Template operator +(const Vector3Template& vec)const;
	Vector3Template operator -(const Vector3Template& vec)const;
	Vector3Template operator *(const Vector3Template& vec)const;
	Vector3Template operator /(const Vector3Template& vec)const;
	Vector3Template operator %(const Vector3Template& vec)const;

	Vector3Template operator +()const;
	Vector3Template operator -()const;
	
	bool operator <  (const Vector3Template& vec)const;

	VECTOR toVECTOR();


	///�x�N�g���̑傫��
	float Magnitude()const;
	void Normalize(void);
	Vector3Template Normalized(void);
};

///���ς�Ԃ�
template <class T>
float Dot(const Vector3Template<T>& va, const Vector3Template<T>& vb);

///�O�ς�Ԃ�
template <class T>
Vector3Template<T> Cross(const Vector3Template<T>& va, const Vector3Template<T>& vb);

// Vector3 �� int�̎l�����Z
template <class T>
Vector3Template<T> operator +(const Vector3Template<T>& vec, const int& num);
template <class T>
Vector3Template<T> operator -(const Vector3Template<T>& vec, const int& num);
template <class T>
Vector3Template<T> operator *(const Vector3Template<T>& vec, const int& num);
template <class T>
Vector3Template<T> operator /(const Vector3Template<T>& vec, const int& num);

// int �� Vector3�̎l�����Z
template <class T>
Vector3Template<T> operator +(const int& num, const Vector3Template<T>& vec);
template <class T>
Vector3Template<T> operator -(const int& num, const Vector3Template<T>& vec);
template <class T>
Vector3Template<T> operator *(const int& num, const Vector3Template<T>& vec);
template <class T>
Vector3Template<T> operator /(const int& num, const Vector3Template<T>& vec);

// Vector3 �� float�̎l�����Z
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
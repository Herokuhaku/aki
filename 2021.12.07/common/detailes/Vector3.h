#include "../Vector3.h"
#include <tuple>

template<class T>
Vector3Template<T>::Vector3Template()
{
	x = 0;
	y = 0;
	z = 0;
}

template<class T>
Vector3Template<T>::~Vector3Template()
{
}

template<class T>
Vector3Template<T>::Vector3Template(T x_, T y_, T z_)
{
	x = x_;
	y = y_;
	z = z_;
}

template<class T>
Vector3Template<T>::Vector3Template(VECTOR v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

template<class T>
Vector3Template<T>& Vector3Template<T>::operator=(const Vector3Template<T>& vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
	return *this;
	// TODO: return ステートメントをここに挿入します
}

template<class T>
Vector3Template<T>& Vector3Template<T>::operator=(const VECTOR& vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
	return *this;
}

template<class T>
Vector3Template<T>& Vector3Template<T>::operator+=(const Vector3Template<T>& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
	return *this;
	// TODO: return ステートメントをここに挿入します
}

template<class T>
Vector3Template<T>& Vector3Template<T>::operator-=(const Vector3Template<T>& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
	// TODO: return ステートメントをここに挿入します
}

template<class T>
Vector3Template<T>& Vector3Template<T>::operator*=(const Vector3Template<T>& vec)
{
	x *= vec.x;
	y *= vec.y;
	z *= vec.z;
	return *this;
	// TODO: return ステートメントをここに挿入します
}

template<class T>
Vector3Template<T>& Vector3Template<T>::operator/=(const Vector3Template<T>& vec)
{
	!vec.x ? x = 1000000000 : x /= vec.x;
	!vec.y ? y = 1000000000 : y /= vec.y;
	!vec.z ? z = 1000000000 : z /= vec.z;
	return *this;
	// TODO: return ステートメントをここに挿入します
}

template<class T>
Vector3Template<T> Vector3Template<T>::operator+(const Vector3Template<T>& vec) const
{
	return Vector3Template(x + vec.x, y + vec.y,z + vec.z);
}

template<class T>
Vector3Template<T> Vector3Template<T>::operator-(const Vector3Template<T>& vec) const
{
	return Vector3Template(x - vec.x, y - vec.y, z - vec.z);
}

template<class T>
 Vector3Template<T> Vector3Template<T>::operator*(const Vector3Template<T>& vec) const
{
	return Vector3Template(x * vec.x, y * vec.y,z * vec.z);
}

template<class T>
Vector3Template<T> Vector3Template<T>::operator/(const Vector3Template<T>& vec) const
{
	Vector3Template<T> tmp();
	!vec.x ? tmp.x = 1000000000 : x / vec.x;
	!vec.y ? tmp.y = 1000000000 : y / vec.y;
	!vec.z ? tmp.z = 1000000000 : z / vec.z;

	return tmp;
}

template<class T>
Vector3Template<T> Vector3Template<T>::operator%(const Vector3Template<T>& vec) const
{
	Vector3Template<T> tmp();
	!vec.x ? tmp.x = 1000000000 : x % vec.x;
	!vec.y ? tmp.y = 1000000000 : y % vec.y;
	!vec.z ? tmp.z = 1000000000 : z % vec.z;
	return tmp;
}

template<class T>
Vector3Template<T> Vector3Template<T>::operator+() const
{
	return Vector3Template<T>(x, y,z);
}

template<class T>
Vector3Template<T> Vector3Template<T>::operator-() const
{
	return Vector3Template<T>(-x,-y,-z);
}

template<class T>
inline bool Vector3Template<T>::operator<(const Vector3Template& vec) const
{
	return std::tie(x, y, z) < std::tie(vec.x, vec.y, vec.z);
	return (x < vec.x&& y < vec.y&& z < vec.z);
}

template<class T>
VECTOR Vector3Template<T>::toVECTOR()
{
	VECTOR tmp;
	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return tmp;
}

template<class T>
float Vector3Template<T>::Magnitude() const
{
	return sqrt(x * x + y * y + z * z);
}

template<class T>
void Vector3Template<T>::Normalize(void)
{
	float mag = Magnitude();
	x /= mag;
	y /= mag;
	z /= mag;
}

template<class T>
Vector3Template<T> Vector3Template<T>::Normalized(void)
{
	float mag = Magnitude();
	return Vector3Template<T>(x / mag,	y / mag,z / mag);
}

template<class T>
float Dot(const Vector3Template<T>& va, const Vector3Template<T>& vb)
{
	return va.x * vb.x + va.y * vb.y + va.z * vb.z;
}

template<class T>
Vector3Template<T> Cross(const Vector3Template<T>& va, const Vector3Template<T>& vb)
{
	return Vector3Template<T>(va.z * vb.y - va.y * vb.z, va.z * vb.x - va.x * vb.z, va.x * vb.y - vb.x * va.y);
}

template<class T>
Vector3Template<T> operator+(const Vector3Template<T>& vec, const int& num)
{
	return Vector3Template<T>(vec.x + num, vec.y + num,vec.z + num);
}

template<class T>
Vector3Template<T> operator-(const Vector3Template<T>& vec, const int& num)
{
	return Vector3Template<T>(vec.x - num, vec.y - num,vec.z - num);
}

template<class T>
Vector3Template<T> operator*(const Vector3Template<T>& vec, const int& num)
{
	return Vector3Template<T>(vec.x * num, vec.y * num,vec.z * num);
}

template<class T>
Vector3Template<T> operator/(const Vector3Template<T>& vec, const int& num)
{
	if (!num)
	{
		return Vector3Template<T>(1000000000, 1000000000, 1000000000);
	}
	return Vector3Template<T>(vec.x / num, vec.y / num,vec.z / num);
}

template<class T>
Vector3Template<T> operator+(const int& num, const Vector3Template<T>& vec)
{
	return Vector3Template<T>(num + vec.x, num + vec.y,num + vec.z);
}

template<class T>
Vector3Template<T> operator-(const int& num, const Vector3Template<T>& vec)
{
	return Vector3Template<T>(num - vec.x, num - vec.y, num - vec.z);
}

template<class T>
Vector3Template<T> operator*(const int& num, const Vector3Template<T>& vec)
{
	return Vector3Template<T>(num * vec.x, num * vec.y, num * vec.z);
}

template<class T>
Vector3Template<T> operator/(const int& num, const Vector3Template<T>& vec)
{
	return Vector3Template<T>(num / vec.x, num / vec.y, num / vec.z);
}

template<class T>
Vector3Template<T> operator+(const Vector3Template<T>& vec, const float& num)
{
	return Vector3Template<T>(vec.x + num, vec.y + num,vec.z + num);
}

template<class T>
Vector3Template<T> operator-(const Vector3Template<T>& vec, const float& num)
{
	return Vector3Template<T>(vec.x + num, vec.y + num, vec.z + num);
}

template<class T>
Vector3Template<T> operator*(const Vector3Template<T>& vec, const float& num)
{
	return Vector3Template<T>(vec.x * num, vec.y * num,vec.z * num);
}

template<class T>
Vector3Template<T> operator/(const Vector3Template<T>& vec, const float& num)
{
	if (!num)
	{
		return Vector3Template<T>(1000000000, 1000000000, 1000000000);
	}
	return Vector3Template<T>(vec.x / num, vec.y / num,vec.z / num);
}

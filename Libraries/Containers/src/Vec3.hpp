#ifndef VEC3_HPP
#define VEC3_HPP

#include <stdint.h>

template <typename T>
class Vec3 {
	public:
	    T x, y, z;
	    Vec3 operator+(const Vec3& other) const { return Vec3(x + other.x, y + other.y, z + other.z); }
	    Vec3 operator-(const Vec3& other) const { return Vec3(x - other.x, y - other.y, z - other.z); }
	    Vec3 operator*(const Vec3& other) const { return Vec3(x * other.x, y * other.y, z * other.z); }
	    Vec3 operator/(const Vec3& other) const { return Vec3(x / other.x, y / other.y, z / other.z); }
	    bool operator==(const Vec3& other) const { return (x == other.x && y == other.y && z == other.z); }
	    bool operator!=(const Vec3& other) const { return (x != other.x || y != other.y || z != other.z); }
	    Vec3();
	    Vec3(T x, T y, T z);
		Vec3(const Vec3 &other);
	    ~Vec3();
};

template <typename T>
Vec3<T>::Vec3(T x, T y, T z)
    : x(x)
    , y(y)
    , z(z)
{
}

template <typename T>
Vec3<T>::Vec3()
{
    x = 0;
    y = 0;
    z = 0;
}
template <typename T>
Vec3<T>::Vec3(const Vec3 &other)
{
	*this = other;
}

template <typename T>
Vec3<T>::~Vec3()
{
}

#endif

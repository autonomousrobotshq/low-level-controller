#ifndef VEC3_hpp
# define VEC3_HPP

#include <stdint.h>

class Vec3 {
	public:
		int16_t x, y, z;
		Vec3 operator+ (const Vec3 &other) const { return Vec3(x + other.x, y + other.y, z + other.z); }
		Vec3 operator- (const Vec3 &other) const { return Vec3(x - other.x, y - other.y, z - other.z); }
		Vec3 operator* (const Vec3 &other) const { return Vec3(x * other.x, y * other.y, z * other.z); }
		Vec3 operator/ (const Vec3 &other) const { return Vec3(x / other.x, y / other.y, z / other.z); }
		bool operator== (const Vec3 &other) const { return (x == other.x && y == other.y && z == other.z); }
		bool operator!= (const Vec3 &other) const { return (x != other.x || y != other.y || z != other.z); }
		Vec3();
		Vec3(int16_t x, int16_t y, int16_t z);
		~Vec3();
};

#endif

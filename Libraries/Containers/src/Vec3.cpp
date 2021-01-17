#include <Vec3.hpp>

Vec3::Vec3(int16_t x, int16_t y, int16_t z)
    : x(x)
    , y(y)
    , z(z)
{
}

Vec3::Vec3()
{
    x = 0;
    y = 0;
    z = 0;
}

Vec3::~Vec3()
{
}

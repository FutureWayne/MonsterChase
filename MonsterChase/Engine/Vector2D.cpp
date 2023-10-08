#include "Vector2D.h"
#include <cmath>

Vector2D::Vector2D() : x(0), y(0) {}

Vector2D::Vector2D(int x, int y) : x(x), y(y) {}

Vector2D& Vector2D::operator+=(const Vector2D& vec) {
    x += vec.x;
    y += vec.y;
    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& vec) {
    x -= vec.x;
    y -= vec.y;
    return *this;
}

Vector2D Vector2D::operator+(const Vector2D& vec) const {
    return Vector2D(x + vec.x, y + vec.y);
}

Vector2D Vector2D::operator-(const Vector2D& vec) const {
    return Vector2D(x - vec.x, y - vec.y);
}

Vector2D Vector2D::operator-() const
{
	return Vector2D(-x, -y);
}

Vector2D& Vector2D::operator*=(int scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

Vector2D& Vector2D::operator/=(int scalar)
{
	x /= scalar;
	y /= scalar;
	return *this;
}

Vector2D Vector2D::operator*(int scalar) const {
    return Vector2D(x * scalar, y * scalar);
}

Vector2D Vector2D::operator/(int scalar) const {
    return Vector2D(x / scalar, y / scalar);
}


bool Vector2D::operator==(const Vector2D& other) const {
    return x == other.x && y == other.y;
}

bool Vector2D::operator!=(const Vector2D& other) const {
    return !(*this == other);
}

void Vector2D::normalize() {
    float length = std::sqrt(x * x + y * y);
    if (length != 0) {
        x /= length;
        y /= length;
    }
}

Vector2D Vector2D::getNormalized() const {
    float length = std::sqrt(x * x + y * y);
    return (length != 0) ? Vector2D(x / length, y / length) : Vector2D();
}

Vector2D operator*(int scalar, const Vector2D& vec)
{
	return vec * scalar;
}

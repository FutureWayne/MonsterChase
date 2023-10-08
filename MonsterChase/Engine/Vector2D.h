#pragma once

class Vector2D {
public:
    int x, y;

    Vector2D();
    Vector2D(int x, int y);

    // Operator overloads for vector arithmetic
    Vector2D& operator+=(const Vector2D& vec);
    Vector2D& operator-=(const Vector2D& vec);
    Vector2D operator+(const Vector2D& vec) const;
    Vector2D operator-(const Vector2D& vec) const;

    // Negation
    Vector2D operator-() const;

    // Scalar multiplication and division
    Vector2D& operator*=(int scalar);
    Vector2D& operator/=(int scalar);
    Vector2D operator*(int scalar) const;
    Vector2D operator/(int scalar) const;

    friend Vector2D operator*(int scalar, const Vector2D& vec);

    // Equality and inequality
    bool operator==(const Vector2D& other) const;
    bool operator!=(const Vector2D& other) const;

    // Normalization
    void normalize();
    Vector2D getNormalized() const;
};

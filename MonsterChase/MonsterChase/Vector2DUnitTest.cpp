#include <assert.h>
#include "Vector2D.h"
#include "Vector2DUnitTest.h"

void Vector2DUnitTest()
{
    Vector2D A(0, 1);
    Vector2D B(2, 3);

    // equality
    bool bEqual = A == B;
    assert(bEqual == false);

    bEqual = B == Vector2D(2, 3);
    assert(bEqual == true);

    // Inequality
    bool bNotEqual = A != B;
    assert(bNotEqual == true);

    bool bNotEqual2 = B != Vector2D(2, 3);
    assert(bNotEqual2 == false);

    // Vector2D + Vector2D
    Vector2D C = A + B;
    assert(C == Vector2D(2, 4));

    // Vector2D - Vector2D
    C = B - A;
    assert(C == Vector2D(2, 2));

    // Vector2D * int
    C = A * 2;
    assert(C == Vector2D(0, 2));

    // Vector2D / int
    C = Vector2D(6, 4) / 2;
    assert(C == Vector2D(3, 2));

    // int * Vector2D
    C = 2 * B;
    assert(C == Vector2D(4, 6));

    // negate
    C = -B;
    assert(C == Vector2D(-2, -3));

    // Vector2D += Vector2D
    B += Vector2D(2, 1);
    assert(B == Vector2D(4, 4));

    // Vector2D -= Vector2D
    B -= Vector2D(2, 1);
    assert(B == Vector2D(2, 3));

    // Vector2D *= int
    B *= 2;
    assert(B == Vector2D(4, 6));

    // Vector2D /= int
    B /= 2;
    assert(B == Vector2D(2, 3));
}
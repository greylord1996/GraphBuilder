#pragma once
#include <iostream>
struct Vector2f
{
  float x, y;

  Vector2f();

  Vector2f(float x, float y);
  Vector2f(float ang);

  Vector2f operator *=(float d);
  Vector2f operator +=(Vector2f right);
  Vector2f operator -=(Vector2f right);
  float SquareLength();
  float Length();
  Vector2f GetPerpendicular();
  Vector2f GetNorm();
  void Print();
};

Vector2f operator +(Vector2f left, Vector2f right);
Vector2f operator -(Vector2f left, Vector2f right);
Vector2f operator *(Vector2f v, float d);
Vector2f operator *(float d, Vector2f v);
float operator ^(Vector2f v0, Vector2f v1);
float operator *(Vector2f v1, Vector2f v2);

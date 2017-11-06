#include "Coords.h"

Coords2f::Coords2f()
{
	
	xVector = Vector2f(1.0f, 0.0f);
	yVector = Vector2f(0.0f, 1.0f);
	
}

Coords2f::Coords2f(Vector2f pos, float ang)
{
	float pi = 3.1415926535897932384626f;
	this->pos = pos;
	this->xVector = Vector2f(cosf(ang), -sinf(ang));
	this->yVector = Vector2f(sinf(ang), cosf(ang));
}

void Coords2f::SetPos(Vector2f pos)
{
	this->pos = pos;
}

void Coords2f::SetAng(float ang)
{
	this->ang = ang;
}
Vector2f Coords2f:: GetPos()
{
	return this->pos;
}

Vector2f Coords2f:: GetXVector()
{
	return this->xVector;
}
Vector2f Coords2f:: GetYVector()
{
	return this->yVector;
}



void Coords2f::SetVector(Vector2f xVector)
{
	this->xVector = xVector;
	this->yVector = Vector2f(-xVector.y, xVector.x);
	
}

Vector2f Coords2f::GetWorldPoint(Vector2f localPoint)//give us world coords
{
	return this->pos + this->xVector * localPoint.x + this->yVector * localPoint.y;
}

Vector2f Coords2f::GetLocalPoint(Vector2f worldPoint)//give us camera coords
{
	Vector2f deltaVec = worldPoint - this->pos;
	return Vector2f(deltaVec * xVector, deltaVec * yVector);
}

Vector2f Coords2f::GetWorldVector(Vector2f localVector)
{
	return xVector * localVector.x + yVector * localVector.y;
}

Vector2f Coords2f::GetLocalVector(Vector2f worldVector)
{
	return Vector2f(worldVector * xVector, worldVector * yVector);
}


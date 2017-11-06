#pragma once
#include <SFML/Graphics.hpp>
#include "vector2f.h"
#include "Coords.h"



class Camera
{
public:
	Camera() {};
	Camera(sf::Window* window, float currFov, float dstFov, float currAng, float dstAng, Vector2f currPos, Vector2f dstPos);
	void Update(float deltaTime);
	void ShiftCamera(float deltaTime, float constAlpha);
	void RotateCamera(float deltaTime, float constAlpha);
	void ManageScale(float deltaTime, float constAlpha);
	void ManageButton();
	Vector2f GetWorldPoint(Vector2f screenPoint, Vector2f areaSize);
	Vector2f GetScreenPoint(Vector2f worldPoint);
	Vector2f GetScreenVector(Vector2f worldVector);
	Vector2f GetWorldVector(Vector2f screenVector);
	


	

private:
	float currFovCamera;
	float dstFovCamera;
	float dstAngCamera;
	float currAngCamera;
	Coords2f currPosCamera;
	Coords2f dstPosCamera;
	sf::Window* window;
	Vector2f fovVec;
	Vector2f windowSize;
	Vector2f center;
};
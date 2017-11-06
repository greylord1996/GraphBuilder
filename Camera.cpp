#pragma once
#include "Camera.h"

Camera::Camera(sf::Window* window, float currFov, float dstFov, float currAng, float dstAng, Vector2f currPos, Vector2f dstPos)
{

	this->currPosCamera = Coords2f(currPos, currAng);
	this->dstPosCamera = Coords2f(dstPos, dstAng);

	this->currFovCamera = currFov;
	this->dstFovCamera = dstFov;

	this->currAngCamera = currAng;
	this->dstAngCamera = dstAng;
	this->window = window;

	float xSize = (float)this->window->getSize().x;
	float ySize = (float)this->window->getSize().y;
	this->windowSize = Vector2f(xSize, ySize);


	float fovX = currFovCamera;
	float fovY = fovX * (windowSize.y / windowSize.x);
	this->fovVec = Vector2f(fovX, fovY);

}



void Camera:: Update(float deltaTime)
{
	const float constAlpha = 5.0f;



	ManageButton();
	ShiftCamera(deltaTime, constAlpha);
	RotateCamera(deltaTime, constAlpha);
	ManageScale(deltaTime, constAlpha);
}

void Camera:: ShiftCamera(float deltaTime, float constAlpha)
{
	Vector2f offsetVec = dstPosCamera.GetPos() - currPosCamera.GetPos();
	this->currPosCamera.SetPos(dstPosCamera.GetPos() - offsetVec * exp(-constAlpha * deltaTime));
}

void Camera:: RotateCamera(float deltaTime, float constAlpha)
{
	Vector2f rotVec = dstPosCamera.GetXVector() - currPosCamera.GetXVector();
	this->currPosCamera.SetVector((dstPosCamera.GetXVector() - rotVec * exp(-constAlpha * deltaTime)).GetNorm());
}

void Camera:: ManageScale(float deltaTime, float constAlpha)
{
	float differScales = this->dstFovCamera - this->currFovCamera;
	currFovCamera = dstFovCamera - differScales * exp(-deltaTime * constAlpha);
}


void Camera:: ManageButton()
{
	const float deltaControlMotion = 10.0f;
	const float deltaControlScale = 10.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		this->dstPosCamera.SetPos(Vector2f(dstPosCamera.GetPos().x, dstPosCamera.GetPos().y - deltaControlMotion));
		std::cout << "Up is pressed" << std::endl;
		std::cout << "currPosition" << currPosCamera.GetPos().y << std::endl;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->dstPosCamera.SetPos(Vector2f(dstPosCamera.GetPos().x, dstPosCamera.GetPos().y + deltaControlMotion));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->dstPosCamera.SetPos(Vector2f(dstPosCamera.GetPos().x + deltaControlMotion, dstPosCamera.GetPos().y));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->dstPosCamera.SetPos(Vector2f(dstPosCamera.GetPos().x - deltaControlMotion, dstPosCamera.GetPos().y));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
	{
		this->dstFovCamera -= deltaControlScale;
		std::cout << "currFovCamera " << currFovCamera << std::endl;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
	{
		this->dstFovCamera += deltaControlScale;
	}

}

Vector2f Camera:: GetWorldPoint(Vector2f screenPoint, Vector2f areaSize)
{
	Vector2f currPos = currPosCamera.GetWorldPoint(screenPoint);
	float fovX = currFovCamera;
	float fovY = fovX * (areaSize.y / areaSize.x);
	this->fovVec = Vector2f(fovX, fovY);
	Vector2f cameraWorldPos;
	cameraWorldPos.x = (currPos.x / areaSize.x) * fovVec.x;
	cameraWorldPos.y = -(currPos.y / areaSize.y) * fovVec.y;
	
	Vector2f screenCenter = areaSize * 0.5f;
	screenCenter.x = screenCenter.x;
	screenCenter.y = -screenCenter.y;

	Vector2f centerInWorld = currPosCamera.GetWorldPoint(screenCenter);
	centerInWorld.x = (screenCenter.x / areaSize.x) * fovVec.x;
	centerInWorld.y = (screenCenter.y / areaSize.y) * fovVec.y;

	Vector2f debugVec = (currPos);

	return (cameraWorldPos - centerInWorld);

}


Vector2f Camera:: GetScreenPoint(Vector2f worldPoint)
{
	Vector2f t = currPosCamera.GetLocalPoint(worldPoint);
}

Vector2f Camera:: GetScreenVector(Vector2f worldVector)
{
	return currPosCamera.GetLocalVector(worldVector);
}

Vector2f Camera:: GetWorldVector(Vector2f screenVector)
{
	return currPosCamera.GetWorldVector(screenVector);
}
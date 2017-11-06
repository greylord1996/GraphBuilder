#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "RPN.h"
#include "vector2f.h"
#include "Coords.h"
#include "Camera.h"
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFGUI\Entry.hpp>
#include <SFGUI\Box.hpp>


#define $ std::cout << "!!!!!!!!!!!!!!!!!!!" << std::endl;

struct UnarySubFunctor : public Ñalculator
{
	float Evaluate(float value)
	{
		return (0-value);
	}
};

struct SumFunctor : public Functor
{
	float Evaluate(float left, float right)
	{
		return left + right;
	}
};

struct SubFunctor : public Functor
{
	float Evaluate(float left, float right)
	{
		return left - right;
	}
};

struct MulFunctor : public Functor
{
	float Evaluate(float left, float right)
	{
		return left * right;
	}
};

struct DivFunctor : public Functor
{
	float Evaluate(float left, float right)
	{
		return left / right;
	}
};

struct PowFunctor : public Functor
{
	float Evaluate(float left, float right)
	{
		return powf(left, right);
	}
};

struct SinFunctor : public Ñalculator
{
	float Evaluate(float variable)
	{
		return sinf(variable);
	}
};

struct CosFunctor : public Ñalculator
{
	float Evaluate(float variable)
	{
		return cosf(variable);
	}
};

struct TanFunctor : public Ñalculator
{
	float Evaluate(float variable)
	{
		return tanf(variable);
	}
};

struct ExpFunctor : public Ñalculator
{
	float Evaluate(float variable)
	{
		return expf(variable);
	}
};

struct SqrtFunctor : public Ñalculator
{
	float Evaluate(float variable)
	{
		return sqrtf(variable);
	}
};

struct LogFunctor : public Ñalculator
{
	float Evaluate(float variable)
	{
		return log(variable);
	}
};

struct Log_10_Functor : public Ñalculator
{
	float Evaluate(float variable)
	{
		return log10(variable);
	}
};

struct ArcSinFunctor : public Ñalculator
{
	float Evaluate(float variable)
	{
		return asinf(variable);
	}
};

struct CtgFunctor : public Ñalculator
{
	float Evaluate(float variable)
	{
		return (1.0f / (tanf(variable)));
	}
};

struct DebugFunctor : public Ñalculator
{
	float Evaluate(float var)
	{
		return 0.0f;
	}
};




void RenderFullScreenQuad(sf::RenderWindow* window, sf::Texture* tex)
{
	sf::Vertex vertices[4];

	float w = float(window->getSize().x);
	float h = float(window->getSize().y);

	vertices[0].position = sf::Vector2f(0.0f, 0.0f);
	vertices[1].position = sf::Vector2f(w, 0.0f);
	vertices[2].position = sf::Vector2f(w, h);
	vertices[3].position = sf::Vector2f(0.0f, h);

	float hTex = float(tex->getSize().y);
	float wTex = float(tex->getSize().x);
	

	vertices[0].texCoords = sf::Vector2f(0.0f, 0.0f);
	vertices[1].texCoords = sf::Vector2f(wTex, 0.0f);
	vertices[2].texCoords = sf::Vector2f(wTex, hTex);
	vertices[3].texCoords = sf::Vector2f(0.0f, hTex);
	vertices[0].color = sf::Color::White;
	vertices[1].color = sf::Color::White;
	vertices[2].color = sf::Color::White;
	vertices[3].color = sf::Color::White;
	window->draw(vertices, 4, sf::Quads, tex);

}


int main()
{
	setlocale(LC_ALL, "Russian");


	std::string in_str;


	TanFunctor tanFunctor;
	SumFunctor sumFunctor;
	SubFunctor subFunctor;
	SinFunctor sinFunctor;
	MulFunctor mulFunctor;
	DivFunctor divFunctor;
	PowFunctor powFunctor;
	UnarySubFunctor unarySubFunctor;
	CosFunctor cosFunctor;
	ExpFunctor expFunctor;
	SqrtFunctor sqrtFunctor;
	LogFunctor logFunctor;
	Log_10_Functor log_10_Functor;
	ArcSinFunctor arcsinFunctor;
	DebugFunctor debugFunctor;
	CtgFunctor ctgFunctor;
	
	

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Graphics builder");
	sf::Color color1;
	sf::Color color2;
	color1.r = 201;
	color1.g = 251;
	color1.b = 182;

	color2.r = 180;
	color2.g = 243;
	color2.a = 116;

	window.resetGLStates();
	sfg::SFGUI sFgui;

	sfg::Window::Ptr guiWindow = sfg::Window::Create();
	guiWindow->SetTitle("Menu");
	auto m_label = sfg::Label::Create();
	

	sfg::Box::Ptr box1 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5);
	

	sfg::Button::Ptr button = sfg::Button::Create("Build function");
	sfg::Entry::Ptr entry = sfg::Entry::Create();


	RPN parser;
	parser.AddUnaryOperator('-', 4.0, &unarySubFunctor);
	parser.AddBinaryOperator('+', 2.0, &sumFunctor);
	parser.AddBinaryOperator('-', 2.0, &subFunctor);
	parser.AddBinaryOperator('*', 3.0, &mulFunctor);
	parser.AddBinaryOperator('/', 3.0, &divFunctor);
	parser.AddBinaryOperator('^', 4.0, &powFunctor);


	parser.AddFunction("sin", &sinFunctor);
	parser.AddFunction("cos", &cosFunctor);
	parser.AddFunction("exp", &expFunctor);
	parser.AddFunction("tan", &tanFunctor);
	parser.AddFunction("sqrt", &sqrtFunctor);
	parser.AddFunction("log", &logFunctor);
	parser.AddFunction("log10", &log_10_Functor);
	parser.AddFunction("arcsin", &arcsinFunctor);
	parser.AddFunction("ctg", &ctgFunctor);

	parser.AddVariable('x');
	parser.AddVariable('y');
	parser.AddVariable('z');

	parser.AddOpenBracket('(');
	parser.AddCloseBracket(')');

	
	int flagToTo = 0;
	auto func = [&]()
	{
	
		std::string vault;
		sf::String pi  = (entry->GetText());		
		std::string piDouble = pi.toAnsiString();

		std::cout << "pi " << piDouble << std::endl;

		parser.LoadFunction(piDouble);
		parser.ParseString();
		//parser.PrintDebug();
		parser.ReverseToPolishNotation();
		//parser.PrintNotation();
		flagToTo = 1;
		pi.clear();
		piDouble.clear();

	};
	
	button->GetSignal(sfg::Widget::OnLeftClick).Connect(func);
	
	
	entry->SetRequisition(sf::Vector2f(100.0f, 0.0f));
	box1->Pack(entry, true);
	box1->Pack(button, false);
	guiWindow->Add(box1);
	
	sf::Image image;
	image.create(1920.0f * 0.6f, 1080.0f * 0.6f, sf::Color::Black);
	Vector2f imageSize = Vector2f(float(image.getSize().x), float(image.getSize().y));
	std::cout << "imageSize.x " << imageSize.x << std::endl;
	std::cout << "imageSize.y " << imageSize.y << std::endl;

	Camera camera(&window, 100.0f, 100.0f, 0.0f, 0.0f, Vector2f(0.0f, 0.0f), Vector2f(0.0f, 0.0f));

	sf::Clock clock;
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			
			guiWindow->HandleEvent(event);
			
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		float deltaTime = clock.getElapsedTime().asSeconds();


		if (flagToTo == 1)
		{
			camera.Update(deltaTime);

			for (size_t x = 0; x < image.getSize().x; x++)
			{
				for (size_t y = 0; y < image.getSize().y; y++)
				{
					Vector2f screenPoint = Vector2f((float)x, (float)y);

					Vector2f worldPoint = camera.GetWorldPoint(screenPoint, imageSize);
					float worldPointX = worldPoint.x;
					float worldPointY = worldPoint.y;


					if (parser.CalcNotation(worldPointX, worldPointY, 0) > 0)
					{

						image.setPixel(x, y, color1);
					}
					else
					{
						image.setPixel(x, y, color2);
					}
				}
			}
			sf::Texture tex;
			tex.create(float(imageSize.x), float(imageSize.y));
			tex.loadFromImage(image);

			RenderFullScreenQuad(&window, &tex);
			
			
		}
		

		guiWindow->Update(deltaTime);
		sFgui.Display(window);
		
		
		window.display();
	}
	
	system("pause");
	return 0;

}

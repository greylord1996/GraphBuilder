#pragma once
#include <string>
#include <iostream>
#include <cctype>
#include <vector>
#define TABLESIZE 10
#define FUNCLENGTH 10
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFGUI\Entry.hpp>
#include <SFGUI\Box.hpp>

//virtual methods

struct Functor
{
public:
	virtual float Evaluate(float left, float right) = 0;
};

struct Ñalculator
{
public:
	virtual float Evaluate(float variable) = 0;
};


//Functor* pahom;
//Ñalculator* epifan;





class lexem
{
public:
	enum type
	{
		binary = 0,
		oper = 1,
		funct = 2,
		var = 3,
		num = 4, 
		openBrack = 5,
		closeBrack = 6,
		signal = 7,
		unary = 8
	};
	virtual type GetType() = 0;
	virtual float TakeValue(float val)
	{
		return 0.0f;
	}
	virtual float GetPriority()
	{
		return 100.0f;
	}
	virtual float GetNumber()
	{
		return 0.0f;
	}
	virtual char GetChar()
	{
		return '#';
	}
	virtual std::string GetString()
	{
		return "str";
	}
	virtual Functor* GetOpPtr()
	{
		return NULL;
	}

	virtual Ñalculator* GetFuncPtr()
	{
		return NULL;
	}
	
};
//descriptions of lexems

class UnaryOperatorDesc : public lexem
{
public:
	char symbol;
	float priority;
	Ñalculator* func;
	virtual type GetType()
	{
		return unary;
	}
	virtual char GetChar()
	{
		return this->symbol;
	}
	virtual float GetPriority()
	{
		return priority;
	}
	virtual Ñalculator* GetFuncPtr()
	{
		return func;
	}

};

class  BinaryOperatorDesc: public lexem
{
public:
	char symbol; //'+' '-"
	float priority;
	Functor* func;
	virtual type GetType()
	{
		return binary;
	}
	virtual char GetChar()
	{
		return this->symbol;
	}
	virtual float GetPriority()
	{
		return priority;
	}
	virtual Functor* GetOpPtr()
	{
		return func;
	}


};

class FunctionDesc: public lexem
{
public:
	std::string nameFunction;
	Ñalculator* func;
	FunctionDesc() {};
	FunctionDesc(std::string nameFunction, Ñalculator* func)
	{
		this->nameFunction = nameFunction;
		this->func = func;
	}
	virtual type GetType()
	{
		return funct;
	}
	virtual std::string GetString()
	{
		return this->nameFunction;
	}
	virtual float GetPriority()
	{
		return -1.0f;
	}
	virtual Ñalculator* GetFuncPtr()
	{
		return func;
	}
};

class OpenBracketsDesc: public lexem
{
public:
	char openBracket;
	//float priority;
	virtual type GetType()
	{
		return openBrack;
	}
	virtual char GetChar()
	{
		return this->openBracket;
	}
	virtual float GetPriority()
	{
		return 1.0f;
	}

};

class CloseBracketsDesc : public lexem
{
public:
	char closeBracket;
	//float priority;
	virtual type GetType()
	{
		return closeBrack;
	}
	virtual char GetChar()
	{
		return this->closeBracket;
	}
	virtual float GetPriority()
	{
		return -1.0f;
	}

};

class VariableDesc: public lexem
{
public:
	char varSymbol;
	float value;
	virtual type GetType()
	{
		return var;
	}
	virtual char GetChar()
	{
		return this->varSymbol;
	}
	virtual float GetPriority()
	{
		return -1.0f;
	}
	virtual float TakeValue(float val)
	{
		value = val;
		return value;
	}
};

class NumberDesc: public lexem
{
public:
	float number;
	virtual type GetType()
	{
		return num;
	}
	virtual float GetNumber()
	{
		return this->number;
	}
	virtual float GetPriority()
	{
		return -1.0f;
	}
	NumberDesc(float num)
	{
		this->number = num;
	}
	NumberDesc(){}
};

class SignalEnd : public lexem
{
public:
	//int signalEnd;
	virtual type GetType()
	{
		return signal;
	}
	virtual float GetPriority()
	{
		return -1.0f;
	}
};



/*
class Object
{
public:
	enum type
	{
		variable = 0,
		function = 1,
		number = 2,
		operation = 3,
		open_bracket = 4,
		close_bracket = 5,
		unary_op = 6
	};
	type type_id;
	std::string str;
	int priority;
	int signalEnd;
};*/
/*
class BinaryFunc
{
	virtual float GetValue(float a, float b) = 0;
};*/

class RPN
{
public:
	RPN() {};
	//RPN(std::string str, int length);
	void LoadFunction(std::string str);
	void ParseString();
	//void PrintObjects();
	void ReverseToPolishNotation();
	//void PrintNotation();
	//void CalcNotaion();

	

	void RPN::AddUnaryOperator(char operatorName, float priority, Ñalculator * func);
	void AddBinaryOperator(char operatorName, float priority, Functor* func);
	void AddFunction(std::string nameFunction, Ñalculator* func);
	void AddVariable(char varSymbol);
	void AddNumber(std::string strVar);
	void AddOpenBracket(char openBracket);
	void AddCloseBracket(char closeBracket);
	void PrintDebug();
	void PrintNotation();
	float CalcNotation(float x, float y, float z);
	

	

//public:
	double result = 0.0f;
	double value = 0.0f;
	double vault1 = 0.0f;
	double vault2 = 0.0f;
	double val = 0.0f;
	double value1 = 0.0f;
	double value2 = 0.0f;


	std::vector<double> stack;
	std::vector<UnaryOperatorDesc> unaryOperators;
	std::vector<BinaryOperatorDesc> binaryOperators;
	std::vector<FunctionDesc> functions;
	std::vector<VariableDesc> variables;
	std::vector<OpenBracketsDesc> openBrackets;
	std::vector<CloseBracketsDesc> closeBrackets;
	std::vector<NumberDesc> numbers;
	std::vector<SignalEnd> signals;
	std::vector< lexem* > lexems;
	//std::vector<lexem> lexems;
	std::vector<lexem*> XLexems;
	std::vector<lexem*> YLexems;
	std::string str;
	int length;
	//std::vector<Object> structVec;
};




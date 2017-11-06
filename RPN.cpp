#pragma once
#include "RPN.h"
#include <string>
#include <iostream>
#include <cctype>
#include <vector>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFGUI\Entry.hpp>
#include <SFGUI\Box.hpp>



void RPN::LoadFunction(std::string str)
{
	
	
	this->length = str.size();
	for (int i = 0; i < length; i++)
	{
		this->str.push_back(str[i]);
	}
	this->str.push_back('!');

}

void RPN::ParseString()
{
	int flag = 1;//unary
	int galf = 2;//unary
	int cond = 0; //for numbers it's amazing
	int condFunc = 0;//for funcs it's amazing
	int condVar = 0;
	bool gotComma = false;
	std::string charVault = {};
	charVault.clear();

	for (int i = 0; i < length + 1; ++i)
	{
		
		//We try find number
		if (isdigit(str[i]) && cond != 1)
		{
			cond = 1;
		}

		if (cond == 1)
		{
			if (isdigit(str[i]))
			{
				charVault.push_back(str[i]);
			}
			else {

				if ((str[i] == ',') && (gotComma) == false)
				{
					charVault.push_back(str[i]);
					gotComma = true;
				}

				else
					if ((str[i] == ',') && (gotComma) == true)
					{
						std::cout << "Comma_error:" << str[i] << " i = " << i << std::endl;
					}
					else

						if (!(isdigit(str[i])) && (str[i] != ',') || (str[i] != '!'))
						{
							cond = 0;
							AddNumber(charVault.data());
							lexems.push_back(static_cast<lexem*>(new NumberDesc(numbers.back().GetNumber())));
							numbers.clear();
							//	std::cout << "numbers.number debug  " << numbers.data()->GetNumber() << std::endl;
							charVault.clear();
							gotComma = false;
						}
			}
			//We have found 
		}
		
		

		for (size_t openBracketIndex = 0; openBracketIndex < openBrackets.size(); openBracketIndex++)
		{
			if (str[i] == openBrackets[openBracketIndex].openBracket)
			{
				lexems.push_back((lexem*)((&openBrackets[openBracketIndex])));
			}
		}

		
		for (size_t closeBracketIndex = 0; closeBracketIndex < closeBrackets.size(); closeBracketIndex++)
		{
			if (str[i] == closeBrackets[closeBracketIndex].closeBracket)
			{
				lexems.push_back((lexem*)((&closeBrackets[closeBracketIndex])));
			}
		}

		
		
			if (isalpha(str[i]) && condFunc == 0 && (str[i] != 'x') && (str[i] != 'y') && (str[i] != 'z'))
			{
				condFunc = 1;
			}

			if (condFunc == 1)
			{
				if (isalpha(str[i]))
				{

					charVault.push_back(str[i]);
				}
				if (!isalpha(str[i + 1]))
				{

					bool iGotIt = false;
					condFunc = 0;
					for (size_t functionsIndex = 0; functionsIndex < functions.size(); functionsIndex++)
					{
						if (strcmp(charVault.data(), functions[functionsIndex].nameFunction.data()) == 0)
						{
							lexems.push_back((lexem*)((&functions[functionsIndex])));
							charVault.clear();

							iGotIt = true;
						}
					}
				}
				//std::cout << "condFunc = " << condFunc << std::endl;

			}
			else 
			{
				for (size_t variableIndex = 0; variableIndex < variables.size(); variableIndex++)
				{
					if (str[i] == variables[variableIndex].varSymbol)
					{
						lexems.push_back((lexem*)((&variables[variableIndex])));
					}
				}
			}
			

			flag = 1;
			if ((i == 0 && str[i] == '-') || (i != 0 && str[i - 1] == '('  && str[i] == '-'))
			{

				for (size_t operatorsIndex = 0; operatorsIndex < unaryOperators.size(); operatorsIndex++)
				{
					//	std::cout << " binaryOperators.size() " << binaryOperators.size() << std::endl;
					if (str[i] == unaryOperators[operatorsIndex].symbol)
					{
						lexems.push_back((lexem*)((&unaryOperators[operatorsIndex])));
						flag = 0;
					}
				}
			}
			else {
				if (flag == 1) {
					for (size_t operatorsIndex = 0; operatorsIndex < binaryOperators.size(); operatorsIndex++)
					{
						//	std::cout << " binaryOperators.size() " << binaryOperators.size() << std::endl;
						if (str[i] == binaryOperators[operatorsIndex].symbol)
						{
							lexems.push_back((lexem*)((&binaryOperators[operatorsIndex])));
						}
					}
				}
			}


			
		}

			
		SignalEnd* signalEnd = new SignalEnd;
		signals.push_back(*signalEnd);
		//lexems.push_back(signalEnd);
		lexems.push_back(signals.data());
		signals.pop_back();
		str.clear();
	//	std::cout << "sigsize = " << signals.size() << std::endl;
}


void RPN::ReverseToPolishNotation()
{
	SignalEnd signalEnd;
	XLexems.clear();
	YLexems.clear();
	signals.push_back(signalEnd);
	YLexems.push_back((lexem*)(signals.data()));

	for (size_t i = 0; i < this->lexems.size(); ++i)
	{
		//std::cout << lexems[i] << std::endl;
		if ((lexems[i]->GetType() == lexems[i]->num) || (lexems[i]->GetType() == lexems[i]->var))
		{
			XLexems.push_back(lexems[i]);
		}
		else
		{
			if (lexems[i]->GetType() == lexems[i]->openBrack || lexems[i]->GetType() == lexems[i]->funct)
			{
				//std::cout << "I am in Y\n";
				YLexems.push_back(lexems[i]);
				//std::cout << "Y.back().str " << Y.back().str << std::endl;
			}
			else
			
				if (lexems[i]->GetType() == lexems[i]->closeBrack)
				{
					while (!YLexems.empty() && YLexems.back()->GetType() != YLexems.back()->openBrack)
					{

						XLexems.push_back(YLexems.back());
						YLexems.pop_back();
					}

					if (!YLexems.empty() && YLexems.back()->GetType() == YLexems.back()->openBrack)
					{
						YLexems.pop_back();
					}

					if (!YLexems.empty() && YLexems.back()->GetType() == YLexems.back()->funct)
					{
						XLexems.push_back(YLexems.back());
						YLexems.pop_back();
					}

					
				}
			
		}

		if (lexems[i]->GetType() == lexems[i]->binary || lexems[i]->GetType() == lexems[i]->unary)
		{
			while (!YLexems.empty() && (lexems[i]->GetPriority() <= YLexems.back()->GetPriority()))
			{
				XLexems.push_back(YLexems.back());
				YLexems.pop_back();
			}

			YLexems.push_back(lexems[i]);
			//std::cout << "numer " << i << " operator " << YLexems.data() << std::endl;
		}
		else
		{
			if (lexems[i]->GetType() == lexems[i]->signal)
			{
				while (!YLexems.empty())
				{
					XLexems.push_back(YLexems.back());
					YLexems.pop_back();
				}
			}
		}
	}
}



	void RPN::AddUnaryOperator(char operatorName, float priority, Ñalculator * func)
	{
		class UnaryOperatorDesc unaryOperator;
		unaryOperator.symbol = operatorName;
		unaryOperator.priority = priority;
		unaryOperator.func = func;
		unaryOperators.push_back(unaryOperator);

	}


		void RPN::AddBinaryOperator(char operatorName, float priority, Functor * func)
		{
			class BinaryOperatorDesc binaryOperator;
			binaryOperator.symbol = operatorName;
			binaryOperator.priority = priority;
			binaryOperator.func = func;
			binaryOperators.push_back(binaryOperator);

		}

		void RPN::AddFunction(std::string nameFunction, Ñalculator * func)
		{
			class FunctionDesc function(nameFunction, func);
			functions.push_back(function);
		}

		void RPN::AddVariable(char varSymbol)
		{
			class VariableDesc variable;
			variable.varSymbol = varSymbol;
			variables.push_back(variable);
		}

		void RPN::AddNumber(std::string strVar)
		{
			float var = (float)atof(strVar.data());
			class NumberDesc number;
			number.number = var;
			numbers.push_back(number);

		}

		
		void RPN::AddOpenBracket(char openBracket)
		{
			class OpenBracketsDesc openBrack;
			openBrack.openBracket = openBracket;
			openBrackets.push_back(openBrack);
		}

		void RPN::AddCloseBracket(char closeBracket)
		{
			class CloseBracketsDesc closeBrack;
			closeBrack.closeBracket = closeBracket;
			closeBrackets.push_back(closeBrack);
		}

		void RPN::PrintDebug()
		{
			for (size_t i = 0; i < this->lexems.size(); ++i)
			{
				//std::cout << lexems[0]->GetType() << std::endl;
				if (this->lexems[i]->GetType() == this->lexems[i]->var)
				{
					//std::cout << "numer " << i << " variable " << this->lexems[i]->GetType() << std::endl;
					std::cout << "numer " << i << " variable " << this->lexems[i]->GetChar() << std::endl;
				}else
				if (lexems[i]->GetType() == lexems[i]->num)
				{
					//std::cout << "numer " << i << " number " << this->lexems[i]->GetType()<< std::endl;
					std::cout << "numer " << i << " number " << this->lexems[i]->GetNumber() << std::endl;
				}
				if (lexems[i]->GetType() == lexems[i]->funct)
				{
					//std::cout << "numer " << i << " funct " << this->lexems[i]->GetType() << std::endl;
					std::cout << "numer " << i << " funct " << this->lexems[i]->GetString() << std::endl;
				}
				if (lexems[i]->GetType() == lexems[i]->openBrack)
				{
					//std::cout << "numer " << i << " openBrack " << this->lexems[i]->GetType() << std::endl;
					std::cout << "numer " << i << " openBrack " << this->lexems[i]->GetChar() << std::endl;
				}
				if (lexems[i]->GetType() == lexems[i]->closeBrack)
				{
					//std::cout << "numer " << i << " closeBrack " << this->lexems[i]->GetType() << std::endl;
					std::cout << "numer " << i << " closeBrack " << this->lexems[i]->GetChar() << std::endl;
				}
				if (lexems[i]->GetType() == lexems[i]->binary)
				{
					//std::cout << "numer " << i << " operator " << this->lexems[i]->GetType() << std::endl;
					std::cout << "numer " << i << " operator " << this->lexems[i]->GetChar() << std::endl;
				}

				if (lexems[i]->GetType() == lexems[i]->unary)
				{
					//std::cout << "numer " << i << " operator " << this->lexems[i]->GetType() << std::endl;
					std::cout << "numer " << i << " unary operator " << this->lexems[i]->GetChar() << std::endl;
				}
			}
		}

		void RPN::PrintNotation()
		{
			for (size_t i = 0; i < XLexems.size(); ++i)
			{
				if (this->XLexems[i]->GetType() == this->XLexems[i]->var)
				{
					std::cout << "numer " << i << " variable " << this->XLexems[i]->GetChar() << std::endl;
				}

				if (XLexems[i]->GetType() == XLexems[i]->num)
				{
					std::cout << "numer " << i << " number " << this->XLexems[i]->GetNumber() << std::endl;
				}
				if (XLexems[i]->GetType() == XLexems[i]->funct)
				{
					std::cout << "numer " << i << " funct " << this->XLexems[i]->GetString() << std::endl;
				}
				if (XLexems[i]->GetType() == XLexems[i]->openBrack)
				{
					std::cout << "numer " << i << " openBrack " << this->XLexems[i]->GetChar() << std::endl;
				}
				if (XLexems[i]->GetType() == XLexems[i]->closeBrack)
				{
					std::cout << "numer " << i << " closeBrack " << this->XLexems[i]->GetChar() << std::endl;
				}
				if (XLexems[i]->GetType() == XLexems[i]->binary)
				{
					std::cout << "numer " << i << " operator " << this->XLexems[i]->GetChar() << std::endl;
				}
			}
		}
		

		float RPN::CalcNotation(float x, float y, float z)
		{
				double result = 0.0f;
				std::vector<double> stack;


				for (int i = 0; i < this->XLexems.size(); i++)
				{
					if (this->XLexems[i]->GetType() == XLexems[i]->num)
					{
						stack.push_back(XLexems[i]->GetNumber());
					}

					if (this->XLexems[i]->GetType() == XLexems[i]->var)
					{
						if (XLexems[i]->GetChar() == 'x')
						{
							stack.push_back(XLexems[i]->TakeValue(x));
						}

						if (XLexems[i]->GetChar() == 'y')
						{
							stack.push_back(XLexems[i]->TakeValue(y));
						}

						if (XLexems[i]->GetChar() == 'z')
						{
							stack.push_back(XLexems[i]->TakeValue(z));
						}


					}

					if (this->XLexems[i]->GetType() == XLexems[i]->funct || this->XLexems[i]->GetType() == XLexems[i]->unary)
					{
						double value = XLexems[i]->GetFuncPtr()->Evaluate(stack.back());
						stack.pop_back();
						stack.push_back(value);
					}

					if (XLexems[i]->GetType() == XLexems[i]->binary)
					{
						double value1 = stack.back();
						stack.pop_back();
						double value2 = stack.back();
						stack.pop_back();
						stack.push_back(XLexems[i]->GetOpPtr()->Evaluate(value2, value1));
					}

				}
				
				//std::cout << "HERE IZ ZE ANZWER: " << stack.back() << std::endl;
				result = stack.back();
			
				lexems.clear();
				return result;
		}
	
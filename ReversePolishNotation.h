
#include <string>
#include <iostream>
#include <cctype>
#define TABLESIZE 10
#define FUNCLENGTH 10

char  functions[TABLESIZE][FUNCLENGTH] = { "cos", "sin", "log", "arcsin", "arccos", "tan", "arctan", "ctg", "arcctg", "exp" };

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
};

class RPN
{
public:
	RPN() {};
	RPN(std::string str, int length)
	{
		this->length = length;
		for (int i = 0; i < length; i++)
		{
			this->str.push_back(str[i]);
		}
		this->str.push_back('!');
	}
	void ParseString()
	{
		int cond = 0; //for numbers it's amazing
		int condFunc = 0;//for funcs it's amazing
		bool gotComma = false;
		std::string charVault;
				
		for (int i = 0; i < length + 1; ++i)
		{
			//We try find number
			if (isdigit(str[i]) && cond != 1)
			{
				//		std::cout << "Num_1:" << str[i] << " i = " << i << std::endl;
				//	charVault.push_back(str[i]);
				cond = 1;
			}
			
				if (cond == 1)
				{
					if (isdigit(str[i]))
					{
						//			std::cout << "Num_2: " << str[i] << " i = " << i << std::endl;
						charVault.push_back(str[i]);
					}
					else
						if ((str[i] == ',') && (gotComma) == false)
						{
							//			std::cout << "Comma_1:" << str[i] << " i = " << i << std::endl;
							charVault.push_back(str[i]);
							gotComma = true;
						}
						else
							if ((str[i] == ',') && (gotComma) == true)
							{
							//	std::cout << "Comma_error:" << str[i] << " i = " << i << std::endl;
								//break;
								//return 1488;//get out of the programm
							}
							else

								if (!(isdigit(str[i])) && (str[i] != ',') || (str[i] != '!'))
								{
							//		std::cout << "we enter\n";
									cond = 0;
									Object object = {};
									object.type_id = object.number;
									object.str = charVault.data();

									structVec.push_back(object);
							//		std::cout << "numsize = " << charVault.size() << "\n";
							//		std::cout << "str: " << structVec.back().str << std::endl;
									charVault.clear();
									gotComma = false;
								}

					//We have found 

				}
				else
					//std::cout << "We enter" << std::endl;
					if (charVault.size() == 0 && (str[i] != '!'))
					{
						bool variableGot = false;
						if (str[i] == 'y')
						{
							//std::cout << "We enter who y" << std::endl;
							charVault.push_back(str[i]);
							//std::cout << "we enter\n";
							Object object = {};
							object.type_id = object.variable;
							object.str = charVault.data();

							structVec.push_back(object);
							//std::cout << "varsize = " << charVault.size() << "\n";
							//std::cout << "str: " << structVec.back().str << std::endl;
							charVault.clear();
							variableGot = true;
						}

						if (str[i] == 'x')

						{
							charVault.push_back(str[i]);
							//std::cout << "we enter\n";
							Object object = {};
							object.type_id = object.variable;
							object.str = charVault.data();

							structVec.push_back(object);
							//std::cout << "varsize = " << charVault.size() << "\n";
							//std::cout << "str: " << structVec.back().str << std::endl;
							charVault.clear();
							variableGot = true;
						}

						if (str[i] == 'z')
						{
							charVault.push_back(str[i]);
							//std::cout << "we enter\n";
							Object object = {};
							object.type_id = object.variable;
							object.str = charVault.data();

							structVec.push_back(object);
							//std::cout << "varsize = " << charVault.size() << "\n";
							//std::cout << "str: " << structVec.back().str << std::endl;
							charVault.clear();
							variableGot = true;
						}
						if (str[i+1] != '!' &&  variableGot && str[i+1] != '+'&& str[i + 1] != '-' && str[i + 1] != '*' && str[i + 1] != '/' && str[i + 1] != '^' && str[i + 1] != ')')
						{
						//	std::cout << "wrong enter. after variable have to be operation or closing bracket\n";
						}
					}
					//else//
					
			if (charVault.size() == 0 && (str[i] != '!'))
			{
				if (str[i] == ')')
				{
					//std::cout << ")))\n" << std::endl;
					charVault.push_back(str[i]);
					//std::cout << "we enter\n";
					Object object = {};
					object.type_id = object.close_bracket;
					object.str = charVault.data();

					//std::cout << "(((\n";
					structVec.push_back(object);
					//std::cout << "varsize = " << charVault.size() << "\n";
					//std::cout << "str: " << structVec.back().str << std::endl;
					charVault.clear();
				}

				if (str[i] == '(')

				{
					//std::cout << "???\n";
					charVault.push_back(str[i]);
					//std::cout << "we enter!!!\n";
					Object object = {};
					object.type_id = object.open_bracket;
					object.str = charVault.data();
					object.priority = 1;

					structVec.push_back(object);
					//std::cout << "varsize = " << charVault.size() << "\n";
					//std::cout << "str: " << structVec.back().str << std::endl;
					charVault.clear();
				}

			}

			if (charVault.size() == 0 && (str[i] != '!'))
			{
				if (str[i] == '+')
				{
					//std::cout << "We enter" << std::endl;
					charVault.push_back(str[i]);
					//std::cout << "we enter\n";
					Object object = {};
					object.type_id = object.operation;
					object.str = charVault.data();
					object.priority = 2;
					

					structVec.push_back(object);
					//std::cout << "varsize = " << charVault.size() << "\n";
					//std::cout << "str: " << structVec.back().str << std::endl;
					charVault.clear();
				}

				if ((i == 0 && str[i] == '-') || (i != 0 && str[i - 1] == '(' && str[i] == '-'))
				{
					charVault.push_back(str[i]);
					Object object = {};
					object.type_id = object.unary_op;
					object.priority = 4;

					object.str = charVault.data();

					structVec.push_back(object);
					//std::cout << "funcsize = " << charVault.size() << "\n";
					//	std::cout << "str: " << structVec.back().str << std::endl;
					charVault.clear();


				}else


				if (str[i] == '-')

				{
					charVault.push_back(str[i]);
					//	std::cout << "we enter\n";
					Object object = {};
					object.type_id = object.operation;
					object.str = charVault.data();
					object.priority = 2;


					structVec.push_back(object);
					//std::cout << "varsize = " << charVault.size() << "\n";
					//std::cout << "str: " << structVec.back().str << std::endl;
					charVault.clear();

				}

				if (str[i] == '*')

				{
					charVault.push_back(str[i]);
					//std::cout << "we enter\n";
					Object object = {};
					object.type_id = object.operation;
					object.str = charVault.data();
					object.priority = 3;

					structVec.push_back(object);
					//std::cout << "varsize = " << charVault.size() << "\n";
					//std::cout << "str: " << structVec.back().str << std::endl;
					charVault.clear();

				}

				if (str[i] == '/')

				{
					charVault.push_back(str[i]);
					//std::cout << "we enter\n";
					Object object = {};
					object.type_id = object.operation;
					object.str = charVault.data();
					object.priority = 3;

					structVec.push_back(object);
					//std::cout << "varsize = " << charVault.size() << "\n";
					//std::cout << "str: " << structVec.back().str << std::endl;
					charVault.clear();

				}
				if (str[i] == '^')

				{
					charVault.push_back(str[i]);
					//std::cout << "we enter\n";
					Object object = {};
					object.type_id = object.operation;
					object.str = charVault.data();
					object.priority = 4;

					structVec.push_back(object);
					//std::cout << "varsize = " << charVault.size() << "\n";
					//std::cout << "str: " << structVec.back().str << std::endl;
					charVault.clear();

				}
			}

			if (isalpha(str[i]) && condFunc == 0 && (str[i] != 'x') && (str[i] != 'y') && (str[i] != 'z'))
			{
				//std::cout << "oi\n" << std::endl;
				//std::cout << "Symbol " << str[i] << std::endl;
			//	charVault.push_back(str[i]);
				condFunc = 1;
			}//else
			if (condFunc == 1)
			{
				if (isalpha(str[i]))
				{
					//std::cout << "Symbol " << str[i] << std::endl;
					charVault.push_back(str[i]);
				}
				if (!isalpha(str[i + 1]))
				{
					//std::cout << "currstr =  " << charVault.data() << std::endl;
					bool iGotIt = false;
					condFunc = 0;
					for (int j = 0; j < TABLESIZE; j++)
					{
						if (strcmp(charVault.data(), functions[j]) == 0)
						{
							Object object = {};
							object.type_id = object.function;
							object.str = charVault.data();

							structVec.push_back(object);
							//std::cout << "funcsize = " << charVault.size() << "\n";
						//	std::cout << "str: " << structVec.back().str << std::endl;
							charVault.clear();

							iGotIt = true;
						}	
					}
					if (iGotIt == true && str[i + 1] != '(')
					//	std::cout << "worng enter\n";
					if (iGotIt == false)
					{
						//std::cout << "!!!\n";
					}
				}
				//std::cout << "condFunc = " << condFunc << std::endl;
				
			}

			
			
		}
		
		Object obj = {};
		obj.signalEnd = 1;
		structVec.push_back(obj);	
	}

	void PrintObjects()
	{
		for (int i = 0; i < this->structVec.size(); i++)
		{
			std::cout << "Object " << i << "  " << "Str is " <<  this->structVec[i].str << std::endl;
			std::cout << "Object " << i << "  " << "Type_id is " << this->structVec[i].type_id << std::endl;
			std::cout << "Object " << i << "  " << "Priority is " <<  this->structVec[i].priority << std::endl;
		}
	}

	void ReverseToPolishNotation()
	{
		Object obj;
		obj.signalEnd = 1;
		Y.push_back(obj);
		
		for (int i = 0; i < this->structVec.size(); ++i)
		{
			if (structVec[i].type_id == structVec[i].number || structVec[i].type_id == structVec[i].variable)
			{
				X.push_back(structVec[i]);
			}else

			if (structVec[i].type_id == structVec[i].open_bracket || structVec[i].type_id == structVec[i].function)
			{
				std::cout << "I am in Y\n";
				Y.push_back(structVec[i]);
				//std::cout << "Y.back().str " << Y.back().str << std::endl;
			}else

				if (structVec[i].type_id == structVec[i].close_bracket)
				{
					while (!Y.empty() && Y.back().type_id != Y.back().open_bracket)
					{
						
						X.push_back(Y.back());
						Y.pop_back();
					}

					if (!Y.empty() && Y.back().type_id == Y.back().open_bracket)
					{
						Y.pop_back();
					}

					if (!Y.empty() && Y.back().type_id == Y.back().function)//528528
					{
						X.push_back(Y.back());
						Y.pop_back();
					}
				}

			if (structVec[i].type_id == structVec[i].operation || structVec[i].type_id == structVec[i].unary_op)
			{
				

				while (!Y.empty() && (structVec[i].priority <= Y.back().priority))
				{
					
						X.push_back(Y.back());
						Y.pop_back();
				}

				
				Y.push_back(structVec[i]);

				
			} else
				if (structVec[i].signalEnd == 1)
				{
					while (!Y.empty())
					{
						X.push_back(Y.back());
						Y.pop_back();
					}
				}

		}
	}

	void PrintNotation()
	{
		for (int i = 0; i < this->X.size(); i++)
		{
			std::cout << "I am X_stack\n";
			std::cout << "Object X " << i << "  " << "Str is " << this->X[i].str << std::endl;
			std::cout << "Object X signal " << i << "  " << "Str is " << this->X[i].signalEnd << std::endl;
			//std::cout << "Object " << i << "  " << "Type_id is " << this->structVec[i].type_id << std::endl;
			//std::cout << "Object " << i << "  " << "Priority is " << this->structVec[i].priority << std::endl;
		}

		for (int i = 0; i < this->Y.size(); i++)
		{
			//std::cout << "I am Y_stack\n";
			std::cout << "Object Y " << i << "  " << "Str is " << this->Y[i].str << std::endl;
			//std::cout << "Object " << i << "  " << "Type_id is " << this->structVec[i].type_id << std::endl;
			//std::cout << "Object " << i << "  " << "Priority is " << this->structVec[i].priority << std::endl;
		}

	}
	
	void CalcNotaion()
	{
		std::vector<double> stack;
		
		for (int i = 0; i < this->X.size(); i++)
		{
			if (this->X[i].type_id == X[i].number)
			{
				stack.push_back(atof(X[i].str.data()));
			}


			if (this->X[i].type_id == X[i].variable)
			{
				if (strcmp(X[i].str.data(), "x") == 0)
				{
					stack.push_back(1488.0f);
				}
				if (strcmp(X[i].str.data(), "y") == 0)
				{
					stack.push_back(1588.0f);
				}
				if (strcmp(X[i].str.data(), "z") == 0)
				{
					stack.push_back(1688.0f);
				}
			}

			if (this->X[i].type_id == X[i].function || this->X[i].type_id == X[i].unary_op)
			{
						

				if (strcmp(X[i].str.data(), "sin") == 0)
				{
					double value = sinf(stack.back());
					stack.pop_back();
					stack.push_back(value);
				}
				if (strcmp(X[i].str.data(), "cos") == 0)
				{
					double value = cosf(stack.back());
					stack.pop_back();
					stack.push_back(value);
				}
				if (strcmp(X[i].str.data(), "exp") == 0)
				{
					double value = expf(stack.back());
					stack.pop_back();
					stack.push_back(value);
				}
				if (strcmp(X[i].str.data(), "log") == 0)
				{
					double value = logf(stack.back());
					stack.pop_back();
					stack.push_back(value);
				}
				if (strcmp(X[i].str.data(), "tan") == 0)
				{
					double value = tanf(stack.back());
					stack.pop_back();
					stack.push_back(value);
				}
				if (strcmp(X[i].str.data(), "arctan") == 0)
				{
					double value = atanf(stack.back());
					stack.pop_back();
					stack.push_back(value);
				}
				if (strcmp(X[i].str.data(), "ctg") == 0)
				{
					double value = 1/tanf(stack.back());
					stack.pop_back();
					stack.push_back(value);
				}
				if (strcmp(X[i].str.data(), "arcctg") == 0)
				{
					double pi = 3.14159265358979323846;
					double value = (pi/2) - atanf(stack.back());
					stack.pop_back();
					stack.push_back(value);
				}
				if (strcmp(X[i].str.data(), "arcsin") == 0)
				{
					double value = asinf(stack.back());
					stack.pop_back();
					stack.push_back(value);
				}
				if (strcmp(X[i].str.data(), "arccos") == 0)
				{
					
					double value = acosf(stack.back());
					stack.pop_back();
					stack.push_back(value);
				}
				if (strcmp(X[i].str.data(), "-") == 0)
				{

					double value = -stack.back();
					stack.pop_back();
					stack.push_back(value);
					
				}

			}else
			if (X[i].type_id == X[i].operation)
			{
				double value1 = stack.back();
			//	std::cout << "value1 " << value1 << std::endl;
				//std::cout << "blablablablablablabla" << std::endl;
				stack.pop_back();
				double value2 = stack.back();
				//std::cout << "value2 " << value2 << std::endl;
				stack.pop_back();

				
				if (strcmp(X[i].str.data(),"+") == 0)
				{
					std::cout << "value1 " << value1 << std::endl;
					std::cout << "value2 " << value2 << std::endl;
					stack.push_back(value1 + value2);
				}
				if (strcmp(X[i].str.data(), "-") == 0)
				{
					stack.push_back(value2 - value1);
				}
				if (strcmp(X[i].str.data(), "*") == 0)
				{
					stack.push_back(value2 * value1);
				}
				if (strcmp(X[i].str.data(), "/") == 0)
				{
					stack.push_back(value2 / value1);
				}
				if (strcmp(X[i].str.data(), "^") == 0)
				{
					stack.push_back(powf(value2, value1));
				}
			}

		}
		std::cout << "HERE IZ ZE ANZWER: " << stack.back() << std::endl;
	}
	
	

public:
	std::vector<Object> X;
	std::vector<Object> Y;
	std::string str;
	int length;
	std::vector<Object> structVec;
};

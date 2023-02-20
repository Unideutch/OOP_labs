// ConsoleApplication12.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cmath>
#include <string>

int CharToInt(char letter)
{
	//Предполагается, что здесь будет перевод буковок в числа
	std::string symbols = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	return (int)symbols.find(letter);
}

char IntToChar(int mod)
{
	std::string symbols = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	return symbols[mod];
}

std::string Reverse(std::string str) 
{
	char ch;
	for (int i = 0; i < (str.length() / 2); i++)
	{
		ch = str[i];
		str[i] = str[str.length() - i - 1];
		str[str.length() - i - 1] = ch;
	}

	return str;
}

std::string IntToStr(int n, int radix, bool& wasError)
{
	int mod;
	std::string result = "";
	char ch;

	while (n != 0) 
	{
		mod = n % radix;
		ch = IntToChar(mod);
		result.push_back(ch);
		n = n / radix;
	}

	if (result == "")
		result = "0";

	result = Reverse(result);
	return result;
}


void CheckInput(bool& wasError, int startBase, int endBase, std::string number)
{
	if (startBase > 36 || startBase < 2) 
		wasError = true;
	if (endBase > 36 || endBase < 2)
		wasError = true;
	if (number == "")
		wasError = true;
}

int StrToInt(const std::string& str, int radix, bool& wasError)
{
	int i, result = 0;
	int charValue;
	char symbol;
	for (i = 0; i < str.length(); i++)
	{
		symbol = str[i];
		charValue = CharToInt(symbol);
		if (charValue >= radix)
		{
			wasError = true;
			std::cout << "Symbol out of notation\n";
			break;
		}

		if (result > (INT_MAX - charValue) / radix)
		{
			wasError = true;
			std::cout << "Out of integer borders\n";
			break;
		}

		result = result * radix + charValue;
	}

	return result;
}

int main()
{
	std::cout << "Start\n";
	int startSystem = 0;
	int endSystem = 0;
	std::string number = "";
	std::cin >> startSystem >> endSystem >> number;
	bool wasError = false;
	//Проверяем системы счисления
	CheckInput(wasError, startSystem, endSystem, number);
	if (wasError) 
	{
		std::cout << "Wrong input\n";
	}
	else
	{
		//Get absolute value of number
		bool underZero = number[0] == '-';
		if (underZero) 
		{
			number = number.substr(1, number.length() - 1);
		}

		int interim = StrToInt(number, startSystem, wasError);

		if (!wasError)
		{
			std::string resultString = IntToStr(interim, endSystem, wasError);

			if (underZero) {
				std::cout << '-' << resultString << "\n";
			}
			else
			{
				std::cout << resultString << "\n";
			}
		}
	}
}



// ConsoleApplication12.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cmath>
#include <string>
#include <fstream>

bool CheckingArgs(int argc)
{
	return (argc == 4);
}

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

bool IsValidRadix(const std::string& radix)
{
	if (radix.length() == 0)
	{
		return false;
	}

	for (size_t i = 0; i < radix.length(); ++i)
	{
		if (radix[i] > '9' || radix[i] < '0')
		{
			return false;
		}
	}

	if (stoi(radix) < 2 || stoi(radix) > 36)
	{
		return false;
	}

	return true;
}

int main(int argc, char* argv[])
{
	std::cout << "Start\n";

	std::ofstream output("output.txt");

	if (!CheckingArgs(argc))
	{
		std::cout << "invalid count of input parameters\n"
			<< "Expected model: replace.exe <input_file> <output_file> <search string> <replace string>\n";
		return 0;
	}

	bool wasError = false;

	if (!IsValidRadix(argv[1]) || !IsValidRadix(argv[2]))
	{
		std::cout << "Wrong input\n";
		return 0;
	}

	int startSystem = std::stoi(argv[1]);
	int endSystem = std::stoi(argv[2]);
	
	std::string number = argv[3];

	//Проверяем системы счисления

	//Get absolute value of number
	bool underZero = number[0] == '-';
	if (underZero)
	{
		number = number.substr(1, number.length() - 1);
	}

	int interim = StrToInt(number, startSystem, wasError);

	if (wasError)
	{
		return 0;
	}

	std::string resultString = IntToStr(interim, endSystem, wasError);

	if (underZero) {
		std::cout << '-' << resultString << "\n";
	}
	else
	{
		std::cout << resultString << "\n";
	}

	output << resultString << "\n";

	return 0;
}



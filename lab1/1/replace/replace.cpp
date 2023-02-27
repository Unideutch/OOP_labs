
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>

//Check input

bool CheckingArgs(int argc)
{
	return (argc == 5);
}

//Inicialize files

bool FileInicialization(std::ifstream& inputFile, std::ofstream& outputFile, std::string inputPath, std::string outputPath)
{
	inputFile.open(inputPath);
	outputFile.open(outputPath);

	if (!inputFile.is_open())
	{
		std::cout << "Wrong input path\n";
		return false;
	}

	if (!outputFile.is_open())
	{
		std::cout << "Wrong output path\n";
		return false;
	}

	return true;
}

//Actually replacing

std::string Replacing(const std::string& str, const std::string& search, const std::string& replacer)
{
	std::string result = "";

	size_t positionInStr = 0;
	size_t positionFind = 0;

	if (search == "" || str.find(search) == std::string::npos)
	{
		return str;
	}

	while (positionInStr < str.length())
	{
		positionFind = str.find(search, positionInStr);

		if (positionFind == std::string::npos)
		{
			result.append(str, positionInStr, str.length() - positionInStr);
			break;
		}

		result.append(str, positionFind, positionFind - positionInStr);
		result.append(replacer);

		positionInStr = positionFind + search.length();
	}

	return result;
}

//Replace proc

void WriteReplaced(std::ifstream& inputFile, std::ofstream& outputFile, std::string search, std::string replacer)
{
	std::string str;
	while (std::getline(inputFile, str))
	{
		outputFile << Replacing(str, search, replacer) << "\n";
	}
}

int main(int argc, char* argv[])
{
	std::cout << "start\n" << argv[1] << std::endl << argv[2] << std::endl;

	clock_t startTime = clock();

	if (!CheckingArgs(argc))
	{
		std::cout << "invalid count of input parameters\n"
			<< "Expected model: replace.exe <input_file> <output_file> <search string> <replace string>\n";
		return 0;
	}

	std::ifstream inputFile;
	std::ofstream outputFile;

	if (!FileInicialization(inputFile, outputFile, argv[1], argv[2]))
	{
		return 1;
	}

	WriteReplaced(inputFile, outputFile, argv[3], argv[4]);

	std::cout << "Time execution is " << float(clock() - startTime) / 1000 << " sec\n";
	return 0;
}
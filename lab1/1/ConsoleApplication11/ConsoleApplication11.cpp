#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

//1. Getting input and output files, and two lines - string to replace and replacement
//2. Checking and associating files
//3. Starting to read and writing one string in time

std::string Replacer(std::string origin, std::string toReplace, std::string replacement) {
	if (origin.find(toReplace) != std::string::npos && toReplace != "") 
	{
		int toReplacePos = origin.find(toReplace);
		origin.replace(toReplacePos, toReplace.length(), replacement);

		int postPartLen = origin.length() - toReplacePos - replacement.length();

		std::string postPart = origin.substr(toReplacePos + replacement.length(), postPartLen);
		postPart = Replacer(postPart, toReplace, replacement);
		origin.replace(toReplacePos + replacement.length(), postPartLen, postPart);
	}

	return origin;
}

void ReadAndWrite(std::string inputFile, std::string outputFile, std::string search, std::string replace) {
	std::ifstream inFile(inputFile);
	if (!inFile)
	{
		std::cout << "Wrong input file";
	}
	std::ofstream outFile(outputFile);

	if (!outFile)
	{
		std::cout << "Wrong output file";
	}
	std::string origin = "";

	while (std::getline(inFile, origin))
	{
		std::string changed = "";
		if (search == "") {
			outFile << origin << "\n";
		}
		else
		{
			changed = Replacer(origin, search, replace);
			outFile << changed << "\n";
		}
	}
}

int main(int argc, char* argv[])
{
	if (argc != 5) {
		std::cout << "Wrong number of input values\n"
			<< "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
	}
	else
	{
		ReadAndWrite(argv[1], argv[2], argv[3], argv[4]);
	}
}

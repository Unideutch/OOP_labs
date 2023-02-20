
#include <iostream>
#include <string>
#include <fstream>

//1. Getting input and output files, and two lines - string to replace and replacement
//2. Checking and associating files
//3. Starting to read and writing one string in time

std::string Replacer(std::string origin, std::string toReplace, std::string replacement) {
    if (origin.find(toReplace) != std::string::npos) {
        origin.replace(origin.find(toReplace), toReplace.length(), replacement);
    }
    return origin;
}

void ReadAndWrite(std::string input, std::string output, std::string orig, std::string rep) {
    std::ifstream inFile(input);
    std::ofstream outFile(output);
    std::string origin = "";
    std::getline(inFile, origin);
    std::string changed = "";
    changed = Replacer(origin, orig, rep);

    outFile << changed;
}

int main()
{
    std::string inputFile = "d:\\temp\\input.txt";
    std::string outputFile = "d:\\temp\\output.txt";
    std::string changingStr = "";
    std::string replacement = "";

    //std::cin >> inputFile;
    //std::cin >> outputFile;
    std::cin >> changingStr;
    std::cin >> replacement;

    ReadAndWrite(inputFile, outputFile, changingStr, replacement);
}


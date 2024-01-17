#include "WareHouse.h";
#include <iostream>
#include <fstream>
#include <string>

WareHouse::WareHouse(const string &configFilePath) :
{
    // Open the text file
    std::ifstream inputFile("example.txt");

    // Check if the file is open
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    // Read the file line by line
    std::string line;
    while (std::getline(inputFile, line))
    {
        // Process each line
        std::cout << "Line: " << line << std::endl;

        // You can add your parsing logic here based on the content of each line
    }

    // Close the file
    inputFile.close();

    return 0;
}
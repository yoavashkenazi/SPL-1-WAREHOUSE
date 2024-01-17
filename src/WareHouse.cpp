#include "../include/WareHouse.h"
#include <iostream>
#include <fstream>
#include <string>

WareHouse::WareHouse(const string &configFilePath)
{
    // Open the text file
    std::ifstream inputFile(configFilePath);

    // Check if the file is open
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    // Read the file line by line
    std::string line;
    while (std::getline(inputFile, line))
    {
        // Process each line
        std::cout << "Line: " << line << std::endl;
    }

    // Close the file
    inputFile.close();
}
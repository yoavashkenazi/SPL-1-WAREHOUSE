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
        char delimiter = '#';
        std::vector<std::string> result;
        size_t start = 0;
        size_t end = line.find(delimiter);

        while (end != std::string::npos)
        {
            result.push_back(line.substr(start, end - start));
            start = end + 1;
            end = line.find(delimiter, start);
        }

        // Add the last substring after the last delimiter
        result.push_back(line.substr(start));

        // Process each line
        if (!result[0].empty())
        {
            std::cout << result[0] << std::endl;
        }
    }

    // Close the file
    inputFile.close();
}
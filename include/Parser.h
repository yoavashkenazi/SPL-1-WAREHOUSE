#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "../include/BaseAction.h"
#include "../include/Volunteer.h"
#include "../include/WareHouse.h"

//צריך לחשוב אם רלוונטי פה, כי זה צריך לבצע פעולות עם הוורהאוס
//class for parsing 
class Parser{
    public:
        string input;
        Parser (string input);
        void InputToAction(string input);
};

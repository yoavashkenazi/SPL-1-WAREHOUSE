#include "../include/WareHouse.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "../include/BaseAction.h"
#include "../include/Volunteer.h"

void InputToAction(string input){
    std::istringstream iss(input);
    std::string firstWord;
    iss >> firstWord;
    if (firstWord == "step"){
        int numOfSteps;
        iss >> numOfSteps;
        SimulateStep action(numOfSteps);
    } else if (firstWord == "order"){
        int costumerId;
        iss >> costumerId;
        AddOrder action(costumerId);
    } else if (firstWord == "customer"){
        string name, cType;
        int distance, maxOrders;
        iss >> name >> cType >> distance >> maxOrders;
        AddCustomer action(name, cType, distance, maxOrders);
    } else if (firstWord == "orderStatus"){
        int id;
        iss >> id;
        PrintOrderStatus action(id);
    } else if (firstWord == "customerStatus"){
        int costumerId;
        iss >> costumerId;
        PrintCustomerStatus action(costumerId);
    } else if (firstWord == "volunteerStatus"){
        int volunteerId;
        iss >> volunteerId;
        PrintVolunteerStatus action(volunteerId);
    } else if (firstWord == "log"){
        PrintActionsLog action();
    } else if (firstWord == "close"){
        Close action();
    } else if (firstWord == "backup"){
        BackupWareHouse action();
    } else if (firstWord == "restore"){
        RestoreWareHouse action();
    }
}



///////צריך להעביר למחלקה שבה יש את הקאונטר של הת.ז של האנשים
///////וצריך להחליט על המיקום בזיכרון של הלקוחות והמתנדבים הראשונים
void StringToCreate (string input){
    std::istringstream iss(input);
    std::string firstWord;
    iss >> firstWord;
    if (firstWord == "costumer"){ //creating a costumer
        string name, cType;
        int distance, maxOrders;
        iss >> name >> cType >> distance >> maxOrders;
        if (cType == "soldier"){
            SoldierCustomer* SC = new SoldierCustomer(id, name, distance, maxOrders); ///////////////////////////////////////////////////////////new
        } else{
            CivilianCustomer* CC = new CivilianCustomer(id, name, distance, maxOrders); ///////////////////////////////////////////////////////////new
        }
    }
    else{ //creating a volunteer
        string name, role;
        int numberOfWords (CountWords(input));
        iss >> name >> role;
        if(role == "collector"){ //collector
            if (numberOfWords == 3){ //regular collector
                int coolDown;
                iss >> coolDown;
                CollectorVolunteer* CV = new CollectorVolunteer(id, name, coolDown); ///////////////////////////////////////////////////////////new
            } else{ //limited collector
                int coolDown, volunteerMaxOrders;
                iss >> coolDown >> volunteerMaxOrders;
                LimitedCollectorVolunteer* LCV = new LimitedCollectorVolunteer(id, name, coolDown, volunteerMaxOrders); ///////////////////////////////////////////////////////////new
            }
        } else{ //driver
            if (numberOfWords == 4){ //regular driver
                int maxDistance, distancePerStep;
                iss >> maxDistance >> distancePerStep;
                DriverVolunteer* DV = new DriverVolunteer(id, name, maxDistance, distancePerStep); ///////////////////////////////////////////////////////////new
            } else{ //limited driver
                int maxDistance, distancePerStep, volunteerMaxOrders;
                iss >> maxDistance >> distancePerStep >> volunteerMaxOrders;
                LimitedDriverVolunteer* DV = new LimitedDriverVolunteer(id, name, maxDistance, distancePerStep, volunteerMaxOrders); ///////////////////////////////////////////////////////////new
            }
        }
    }
}

int CountWords(const std::string& input) { //counts the number of words in input
    std::istringstream iss(input);
    std::string word;
    int wordCount = 0;

    while (iss >> word) {
        wordCount++;
    }

    return wordCount;
}
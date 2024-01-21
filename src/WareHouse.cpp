#include "../include/WareHouse.h"
#include "../include/Volunteer.h"
#include "../include/BaseAction.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

WareHouse::WareHouse(const string &configFilePath) : isOpen(false), customerCounter(0), volunteerCounter(0), ordersCounter(0)
{
    this->configFileProccessing(configFilePath);
}

void WareHouse::start()
{
    std::cerr << "Warehouse is open!" << std::endl;
    this->open();
    while (this->isOpen)
    {
        break;
    }
}

const vector<BaseAction *> &WareHouse::getActionsLog() const
{
    return this->actionsLog;
}
void WareHouse::addOrder(Order *order)
{
    this->pendingOrders.insert(pendingOrders.begin(), order);
    this->orderCounter = this->orderCounter + 1;
}
void WareHouse::addAction(BaseAction *action)
{
    actionsLog.push_back(action);
}
void WareHouse::printActionsLogs()
{
    for (BaseAction *action : this->actionsLog)
    {
        std::cout << action->toString() << std::endl;
    }
}
Customer &WareHouse::getCustomer(int customerId) const
{
    for (Customer *c : this->customers)
    {
        if (c->getId() == customerId)
        {
            return (*c);
        }
    }
}
Volunteer &WareHouse::getVolunteer(int volunteerId) const
{
    for (Volunteer *v : this->volunteers)
    {
        if (v->getId() == volunteerId)
        {
            return (*v);
        }
    }
}
Order &WareHouse ::getOrder(int orderId) const
{
    for (Order *o : this->pendingOrders)
    {
        if (o->getId() == orderId)
        {
            return (*o);
        }
    }
    for (Order *o : this->inProcessOrders)
    {
        if (o->getId() == orderId)
        {
            return (*o);
        }
    }
    for (Order *o : this->completedOrders)
    {
        if (o->getId() == orderId)
        {
            return (*o);
        }
    }
}

void WareHouse::close()
{
    this->isOpen = false;
}

void WareHouse::open()
{
    this->isOpen = true;
}

void WareHouse::AddCustomer(Customer *customer)
{
    customers.push_back(customer);
    this->customerCounter = this->customerCounter + 1;
}

void WareHouse::configFileProccessing(const string &configFilePath)
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

int WareHouse::getCustomerCounter() const
{
    return this->customerCounter;
}
int WareHouse::getVolunteerCounter() const
{
    return this->volunteerCounter;
}
int WareHouse::getOrderCounter() const
{
    return this->orderCounter;
}

void WareHouse::InputToAction(string input)
{
    std::istringstream iss(input);
    std::string firstWord;
    iss >> firstWord;
    if (firstWord == "step")
    {
        int numOfSteps;
        iss >> numOfSteps;
        SimulateStep action(numOfSteps);
    }
    else if (firstWord == "order")
    {
        int customerId;
        iss >> customerId;
        AddOrder action(customerId);
    }
    else if (firstWord == "customer")
    {
        string name, cType;
        int distance, maxOrders;
        iss >> name >> cType >> distance >> maxOrders;
        AddCustomer action(name, cType, distance, maxOrders);
    }
    else if (firstWord == "orderStatus")
    {
        int id;
        iss >> id;
        PrintOrderStatus action(id);
    }
    else if (firstWord == "customerStatus")
    {
        int customerId;
        iss >> customerId;
        PrintCustomerStatus action(customerId);
    }
    else if (firstWord == "volunteerStatus")
    {
        int volunteerId;
        iss >> volunteerId;
        PrintVolunteerStatus action(volunteerId);
    }
    else if (firstWord == "log")
    {
        PrintActionsLog action();
    }
    else if (firstWord == "close")
    {
        Close action();
    }
    else if (firstWord == "backup")
    {
        BackupWareHouse action();
    }
    else if (firstWord == "restore")
    {
        RestoreWareHouse action();
    }
}

///////צריך להעביר למחלקה שבה יש את הקאונטר של הת.ז של האנשים
///////וצריך להחליט על המיקום בזיכרון של הלקוחות והמתנדבים הראשונים
void WareHouse::ConfigLineProccess(string input)
{
    std::istringstream iss(input);
    std::string firstWord;
    iss >> firstWord;
    if (firstWord == "customer")
    { // creating a customer
        string name, cType;
        int distance, maxOrders;
        iss >> name >> cType >> distance >> maxOrders;
        if (cType == "soldier")
        {
            SoldierCustomer *SC = new SoldierCustomer(id, name, distance, maxOrders); ///////////////////////////////////////////////////////////new
        }
        else
        {
            CivilianCustomer *CC = new CivilianCustomer(id, name, distance, maxOrders); ///////////////////////////////////////////////////////////new
        }
    }
    else
    { // creating a volunteer
        string name, role;
        int numberOfWords(CountWords(input));
        iss >> name >> role;
        if (role == "collector")
        { // collector
            if (numberOfWords == 4)
            { // regular collector
                int coolDown;
                iss >> coolDown;
                CollectorVolunteer *CV = new CollectorVolunteer(id, name, coolDown); ///////////////////////////////////////////////////////////new
            }
            else
            { // limited collector
                int coolDown, volunteerMaxOrders;
                iss >> coolDown >> volunteerMaxOrders;
                LimitedCollectorVolunteer *LCV = new LimitedCollectorVolunteer(id, name, coolDown, volunteerMaxOrders); ///////////////////////////////////////////////////////////new
            }
        }
        else
        { // driver
            if (numberOfWords == 5)
            { // regular driver
                int maxDistance, distancePerStep;
                iss >> maxDistance >> distancePerStep;
                DriverVolunteer *DV = new DriverVolunteer(id, name, maxDistance, distancePerStep); ///////////////////////////////////////////////////////////new
            }
            else
            { // limited driver
                int maxDistance, distancePerStep, volunteerMaxOrders;
                iss >> maxDistance >> distancePerStep >> volunteerMaxOrders;
                LimitedDriverVolunteer *DV = new LimitedDriverVolunteer(id, name, maxDistance, distancePerStep, volunteerMaxOrders); ///////////////////////////////////////////////////////////new
            }
        }
    }
}

int WareHouse::CountWords(const std::string &input)
{ // counts the number of words in input
    std::istringstream iss(input);
    std::string word;
    int wordCount = 0;

    while (iss >> word)
    {
        wordCount++;
    }

    return wordCount;
}
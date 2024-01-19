#include "../include/WareHouse.h"
#include "../include/Volunteer.h"
#include <iostream>
#include <fstream>
#include <string>

WareHouse::WareHouse(const string &configFilePath) : isOpen(false), customerCounter(0), volunteerCounter(0)
{
    this->configFileProccessing(configFilePath);
}

void WareHouse::start()
{
    std::cerr << "Warehouse is open!" << std::endl;
    this->open();
}

const vector<BaseAction *> &WareHouse::getActionsLog() const
{
    return this->actionsLog;
}
void WareHouse::addOrder(Order *order)
{
    pendingOrders.insert(pendingOrders.begin(), order);
}
void WareHouse::addAction(BaseAction *action)
{
    actionsLog.push_back(action);
}
void WareHouse::printActionsLogs()
{
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
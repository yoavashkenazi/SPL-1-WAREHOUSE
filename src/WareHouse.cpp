#include "../include/WareHouse.h"
#include "../include/Volunteer.h"
#include "../include/Action.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

WareHouse::WareHouse(const string &configFilePath) : isOpen(false), customerCounter(0), volunteerCounter(0), orderCounter(0)
{
    this->configFileProccessing(configFilePath);
}

WareHouse::WareHouse(const WareHouse &other) : isOpen(other.isOpen), customerCounter(other.customerCounter), volunteerCounter(other.volunteerCounter), orderCounter(other.orderCounter)
{
    for (const BaseAction *originalAction : other.actionsLog)
    {
        this->actionsLog.push_back(originalAction->clone());
    }
    for (const Volunteer *originalVolunteer : other.volunteers)
    {
        this->volunteers.push_back(originalVolunteer->clone());
    }
    for (const Order *originalOrder : other.pendingOrders)
    {
        this->pendingOrders.push_back(new Order(*originalOrder));
    }
    for (const Order *originalOrder : other.inProcessOrders)
    {
        this->inProcessOrders.push_back(new Order(*originalOrder));
    }
    for (const Order *originalOrder : other.completedOrders)
    {
        this->completedOrders.push_back(new Order(*originalOrder));
    }
    for (const Customer *originalCustomer : other.customers)
    {
        this->customers.push_back(originalCustomer->clone());
    }
}

WareHouse::WareHouse(const WareHouse &&other) noexcept : isOpen(other.isOpen), customerCounter(other.customerCounter), volunteerCounter(other.volunteerCounter), orderCounter(other.orderCounter)
{
    for (const BaseAction *originalAction : other.actionsLog)
    {
        this->actionsLog.push_back(originalAction->clone());
    }
    for (const Volunteer *originalVolunteer : other.volunteers)
    {
        this->volunteers.push_back(originalVolunteer->clone());
    }
    for (const Order *originalOrder : other.pendingOrders)
    {
        this->pendingOrders.push_back(new Order(*originalOrder));
    }
    for (const Order *originalOrder : other.inProcessOrders)
    {
        this->inProcessOrders.push_back(new Order(*originalOrder));
    }
    for (const Order *originalOrder : other.completedOrders)
    {
        this->completedOrders.push_back(new Order(*originalOrder));
    }
    for (const Customer *originalCustomer : other.customers)
    {
        this->customers.push_back(originalCustomer->clone());
    }
}

WareHouse::~WareHouse()
{
    this->clearWarehouse();
}
WareHouse &WareHouse::operator=(const WareHouse &other)
{
    if (&other != this)
    {
        // delete all the values in all vectors first
        this->clearWarehouse();

        this->isOpen = other.isOpen;
        this->customerCounter = other.customerCounter;
        this->volunteerCounter = other.volunteerCounter;
        this->orderCounter = other.orderCounter;
        for (const BaseAction *originalAction : other.actionsLog)
        {
            this->actionsLog.push_back(originalAction->clone());
        }
        for (const Volunteer *originalVolunteer : other.volunteers)
        {
            this->volunteers.push_back(originalVolunteer->clone());
        }
        for (const Order *originalOrder : other.pendingOrders)
        {
            this->pendingOrders.push_back(new Order(*originalOrder));
        }
        for (const Order *originalOrder : other.inProcessOrders)
        {
            this->inProcessOrders.push_back(new Order(*originalOrder));
        }
        for (const Order *originalOrder : other.completedOrders)
        {
            this->completedOrders.push_back(new Order(*originalOrder));
        }
        for (const Customer *originalCustomer : other.customers)
        {
            this->customers.push_back(originalCustomer->clone());
        }
    }
}
WareHouse &WareHouse::operator=(const WareHouse &&other) noexcept
{
    // delete all the values in all vectors first
    this->clearWarehouse();

    this->isOpen = other.isOpen;
    this->customerCounter = other.customerCounter;
    this->volunteerCounter = other.volunteerCounter;
    this->orderCounter = other.orderCounter;
    for (const BaseAction *originalAction : other.actionsLog)
    {
        this->actionsLog.push_back(originalAction->clone());
    }
    for (const Volunteer *originalVolunteer : other.volunteers)
    {
        this->volunteers.push_back(originalVolunteer->clone());
    }
    for (const Order *originalOrder : other.pendingOrders)
    {
        this->pendingOrders.push_back(new Order(*originalOrder));
    }
    for (const Order *originalOrder : other.inProcessOrders)
    {
        this->inProcessOrders.push_back(new Order(*originalOrder));
    }
    for (const Order *originalOrder : other.completedOrders)
    {
        this->completedOrders.push_back(new Order(*originalOrder));
    }
    for (const Customer *originalCustomer : other.customers)
    {
        this->customers.push_back(originalCustomer->clone());
    }
}

void WareHouse::start()
{
    std::cerr << "Warehouse is open!" << std::endl;
    this->open();
    while (this->isOpen)
    {
        cout << " \n Enter command: \n"
             << endl;
        string input;
        std::getline(std::cin, input);
        this->InputToAction(input);
    }
}
const vector<BaseAction *> &WareHouse::getActions() const
{
    return this->actionsLog;
}
void WareHouse::addOrder(Order *order)
{
    this->pendingOrders.push_back(order);
    this->orderCounter = this->orderCounter + 1;
    this->getCustomer(order->getCustomerId()).addOrder(order->getId());
}
void WareHouse::addAction(BaseAction *action)
{
    actionsLog.push_back(action);
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
void WareHouse::addCustomer(Customer *customer)
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
            this->ConfigLineProccessing(result[0]);
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
bool WareHouse::customerExist(int id) const
{
    return id < this->customerCounter;
}
bool WareHouse::volunteerExist(int id) const
{
    for (Volunteer *v : this->volunteers)
    {
        if (v->getId() == id)
        {
            return true;
        }
    }
    return false;
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
        SimulateStep *action = new SimulateStep(numOfSteps);
        action->act(*this);
        actionsLog.push_back(action);
    }
    else if (firstWord == "order")
    {
        int customerId;
        iss >> customerId;
        AddOrder *action = new AddOrder(customerId);
        action->act(*this);
        actionsLog.push_back(action);
    }
    else if (firstWord == "customer")
    {
        string name, cType;
        int distance, maxOrders;
        iss >> name >> cType >> distance >> maxOrders;
        AddCustomer *action = new AddCustomer(name, cType, distance, maxOrders);
        action->act(*this);
        actionsLog.push_back(action);
    }
    else if (firstWord == "orderStatus")
    {
        int id;
        iss >> id;
        PrintOrderStatus *action = new PrintOrderStatus(id);
        action->act(*this);
        actionsLog.push_back(action);
    }
    else if (firstWord == "customerStatus")
    {
        int customerId;
        iss >> customerId;
        PrintCustomerStatus *action = new PrintCustomerStatus(customerId);
        action->act(*this);
        actionsLog.push_back(action);
    }
    else if (firstWord == "volunteerStatus")
    {
        int volunteerId;
        iss >> volunteerId;
        PrintVolunteerStatus *action = new PrintVolunteerStatus(volunteerId);
        action->act(*this);
        actionsLog.push_back(action);
    }
    else if (firstWord == "log")
    {
        PrintActionsLog *action = new PrintActionsLog();
        action->act(*this);
        actionsLog.push_back(action);
    }
    else if (firstWord == "close")
    {
        Close *action = new Close();
        action->act(*this);
        actionsLog.push_back(action);
    }
    else if (firstWord == "backup")
    {
        BackupWareHouse *action = new BackupWareHouse();
        action->act(*this);
        actionsLog.push_back(action);
    }
    else if (firstWord == "restore")
    {
        RestoreWareHouse *action = new RestoreWareHouse();
        action->act(*this);
        actionsLog.push_back(action);
    }
    else
    {
        cout << "The Program did nothing, check the input or the code :)" << endl;
    }
}
void WareHouse::ConfigLineProccessing(string input)
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
            SoldierCustomer *sc = new SoldierCustomer(getCustomerCounter(), name, distance, maxOrders); ///////////////////////////////////////////////////////////new
            this->addCustomer(sc);
        }
        else
        {
            CivilianCustomer *cc = new CivilianCustomer(getCustomerCounter(), name, distance, maxOrders); ///////////////////////////////////////////////////////////new
            this->addCustomer(cc);
        }
    }
    else
    { // creating a volunteer
        string name, role;
        int numberOfWords(CountWords(input));
        iss >> name >> role;
        if (role == "collector")
        { // collector
            int coolDown;
            iss >> coolDown;
            CollectorVolunteer *cv = new CollectorVolunteer(getVolunteerCounter(), name, coolDown); ///////////////////////////////////////////////////////////new
            volunteers.push_back(cv);
        }
        else if (role == "limited_collector")
        { // limited collector
            int coolDown, volunteerMaxOrders;
            iss >> coolDown >> volunteerMaxOrders;
            LimitedCollectorVolunteer *lcv = new LimitedCollectorVolunteer(getVolunteerCounter(), name, coolDown, volunteerMaxOrders); ///////////////////////////////////////////////////////////new
            volunteers.push_back(lcv);
        }
        else if (role == "driver")
        { // regular driver
            int maxDistance, distancePerStep;
            iss >> maxDistance >> distancePerStep;
            DriverVolunteer *dv = new DriverVolunteer(getVolunteerCounter(), name, maxDistance, distancePerStep); ///////////////////////////////////////////////////////////new
            volunteers.push_back(dv);
        }
        else
        { // limited driver
            int maxDistance, distancePerStep, volunteerMaxOrders;
            iss >> maxDistance >> distancePerStep >> volunteerMaxOrders;
            LimitedDriverVolunteer *ldv = new LimitedDriverVolunteer(getVolunteerCounter(), name, maxDistance, distancePerStep, volunteerMaxOrders); ///////////////////////////////////////////////////////////new
            volunteers.push_back(ldv);
        }
        this->volunteerCounter++;
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
vector<Order *> &WareHouse::getOrders(int i)
{ // returns the Orders vector
    if (i == 0)
    {
        return this->pendingOrders;
    }
    else if (i == 1)
    {
        return this->inProcessOrders;
    }
    else if (i == 2)
    {
        return this->completedOrders;
    }
}
bool WareHouse::moveOrderBetweenVectors(int orderId, vector<Order *> &fromVector, vector<Order *> &toVector)
{
    // move the orders between orders vectors
    for (int i = 0; i < fromVector.size(); ++i)
    {
        if (fromVector[i]->getId() == orderId)
        {
            // Element found, move to "toVector" and remove from "fromVector"
            toVector.push_back(std::move(fromVector[i]));
            fromVector.erase(fromVector.begin() + i);
            return true;
        }
    }
    return false;
}
const vector<Volunteer *> &WareHouse::getVolunteers()
{
    return this->volunteers;
}
bool WareHouse::deleteLimitedVolunteer(int id)
{
    // delete volunteer by id
    for (int i = 0; i < this->volunteers.size(); ++i)
    {
        if (volunteers[i]->getId() == id)
        {
            // delete the volunteer
            delete volunteers[i];
            // delete the pointer from the vector
            this->volunteers.erase(this->volunteers.begin() + i);
            return true;
        }
    }
    // return false if not found
    return false;
}
void WareHouse::clearWarehouse()
{
    // delete all the values in all vectors
    for (const BaseAction *action : this->actionsLog)
    {
        delete action;
        action = nullptr;
    }
    for (const Volunteer *volunteer : this->volunteers)
    {
        delete volunteer;
        volunteer = nullptr;
    }
    for (const Order *order : this->pendingOrders)
    {
        delete order;
        order = nullptr;
    }
    for (const Order *order : this->inProcessOrders)
    {
        delete order;
        order = nullptr;
    }
    for (const Order *order : this->completedOrders)
    {
        delete order;
        order = nullptr;
    }
    for (const Customer *customer : this->customers)
    {
        delete customer;
        customer = nullptr;
    }
}
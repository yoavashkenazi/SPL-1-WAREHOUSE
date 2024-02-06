#include "../include/WareHouse.h"
#include "../include/Volunteer.h"
#include "../include/Action.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

WareHouse::WareHouse(const string &configFilePath) : isOpen(false), actionsLog(), volunteers(), pendingOrders(), inProcessOrders(), completedOrders(), customers(), customerCounter(0), volunteerCounter(0), orderCounter(0), fakeVolunteer(new CollectorVolunteer(-1, "fakeVolunteer", -1)), fakeOrder(new Order(-1, -1, -1)), fakeCustomer(new SoldierCustomer(-1, "fakeCustomer", -1, -1))
{
    this->configFileProccessing(configFilePath);
}

WareHouse::WareHouse(const WareHouse &other) : isOpen(other.isOpen), actionsLog(), volunteers(), pendingOrders(), inProcessOrders(), completedOrders(), customers(), customerCounter(other.customerCounter), volunteerCounter(other.volunteerCounter), orderCounter(other.orderCounter), fakeVolunteer(other.fakeVolunteer->clone()), fakeOrder(new Order(*(other.fakeOrder))), fakeCustomer(other.fakeCustomer->clone())
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

WareHouse::WareHouse(const WareHouse &&other) noexcept : isOpen(other.isOpen), actionsLog(), volunteers(), pendingOrders(), inProcessOrders(), completedOrders(), customers(), customerCounter(other.customerCounter), volunteerCounter(other.volunteerCounter), orderCounter(other.orderCounter), fakeVolunteer(other.fakeVolunteer->clone()), fakeOrder(new Order(*(other.fakeOrder))), fakeCustomer(other.fakeCustomer->clone())
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
        this->fakeVolunteer = new CollectorVolunteer(-1, "fakeVolunteer", -1);
        this->fakeOrder = new Order(-1, -1, -1);
        this->fakeCustomer = new SoldierCustomer(-1, "fakeCustomer", -1, -1);
    }
    return *this;
}
WareHouse &WareHouse::operator=(const WareHouse &&other) noexcept
{
    if (&other != this)
    {
        // delete all the pointers first
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
        this->fakeVolunteer = new CollectorVolunteer(-1, "fakeVolunteer", -1);
        this->fakeOrder = new Order(-1, -1, -1);
        this->fakeCustomer = new SoldierCustomer(-1, "fakeCustomer", -1, -1);
    }
    return *this;
}

void WareHouse::start()
{
    std::cerr << "Warehouse is open!" << std::endl;
    this->open();
    while (this->isOpen)
    {
        cout << "Enter command:"
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
    return *(this->fakeCustomer);
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
    return *(this->fakeVolunteer);
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
    return *(this->fakeOrder);
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
    //parses each word out of the input given by the user.
    //according to the first word of the input, it is possible to infer how many words the input contains, and the meaning of each word.
    //the words than are used to create the appropriate action.
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
    //parses each word out of the input given in the configFile.
    //according to the first word of the input, it is possible to infer how many words the input contains, and the meaning of each word.
    //the words than are used to create the appropriate object.
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
vector<Order *> &WareHouse::getPendingOrders()
{ // returns the pending Orders vector
    return this->pendingOrders;
}
vector<Order *> &WareHouse::getInProcessOrders()
{ // returns the in process Orders vector
    return this->inProcessOrders;
}
vector<Order *> &WareHouse::getCompletedOrders()
{ // returns the completed Orders vector
    return this->completedOrders;
}
bool WareHouse::moveOrderBetweenVectors(int orderId, vector<Order *> &fromVector, vector<Order *> &toVector)
{
    // move the orders between orders vectors
    for (std::vector<Order *>::size_type i = 0; i < fromVector.size(); ++i)
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
    for (std::vector<Volunteer *>::size_type i = 0; i < this->volunteers.size(); ++i)
    {
        if (volunteers[i] != nullptr && volunteers[i]->getId() == id)
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
    // delete all pointers
    for (const BaseAction *action : this->actionsLog)
    {
        if (action != nullptr)
            delete action;
        action = nullptr;
    }
    this->actionsLog.clear();
    for (const Volunteer *volunteer : this->volunteers)
    {
        if (volunteer != nullptr)
            delete volunteer;
        volunteer = nullptr;
    }
    this->volunteers.clear();
    for (const Order *order : this->pendingOrders)
    {
        if (order != nullptr)
            delete order;
        order = nullptr;
    }
    this->pendingOrders.clear();
    for (const Order *order : this->inProcessOrders)
    {
        if (order != nullptr)
            delete order;
        order = nullptr;
    }
    this->inProcessOrders.clear();
    for (const Order *order : this->completedOrders)
    {
        if (order != nullptr)
            delete order;
        order = nullptr;
    }
    this->completedOrders.clear();
    for (const Customer *customer : this->customers)
    {
        if (customer != nullptr)
            delete customer;
        customer = nullptr;
    }
    this->customers.clear();

    if (this->fakeVolunteer != nullptr)
    {
        delete this->fakeVolunteer;
        this->fakeVolunteer = nullptr;
    }
    if (this->fakeOrder != nullptr)
    {
        delete this->fakeOrder;
        this->fakeOrder = nullptr;
    }
    if (this->fakeCustomer != nullptr)
    {
        delete this->fakeCustomer;
        this->fakeCustomer = nullptr;
    }
}
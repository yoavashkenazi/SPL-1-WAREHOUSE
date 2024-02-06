#pragma once
#include <string>
#include <vector>
using namespace std;

#include "Order.h"
#include "Customer.h"

class BaseAction;
class Volunteer;

// Warehouse responsible for Volunteers, Customers Actions, and Orders.

class WareHouse
{

public:
    WareHouse(const string &configFilePath);
    WareHouse(const WareHouse &other); //copy constructor
    WareHouse(const WareHouse &&other) noexcept; //move constructor
    ~WareHouse(); //destructor
    WareHouse &operator=(const WareHouse &other); //copy assignment operator
    WareHouse &operator=(const WareHouse &&other) noexcept; //move assignment operator
    void start();
    const vector<BaseAction *> &getActions() const; //returns actionsLog vector
    void addOrder(Order *order);
    void addAction(BaseAction *action);
    Customer &getCustomer(int customerId) const;
    Volunteer &getVolunteer(int volunteerId) const;
    Order &getOrder(int orderId) const;
    void close();
    void open();
    void addCustomer(Customer *customer); //** add customer to the warehouse
    int getCustomerCounter() const; //returns customerCounter
    int getVolunteerCounter() const; //returns VolunteerCounter
    int getOrderCounter() const; //returns orderCounter
    bool customerExist(int id) const; //returns true iff customer exists according to id
    bool volunteerExist(int id) const; //returns true iff volunteer exists according to id
    vector<Order *> &getPendingOrders();   // returns the Pending Orders vector
    vector<Order *> &getInProcessOrders(); // returns the in process Orders vector
    vector<Order *> &getCompletedOrders(); // returns the in completed Orders vector

    bool moveOrderBetweenVectors(int orderId, vector<Order *> &fromVector, vector<Order *> &toVector); //moves order orderId from fromVector to toVector
    const vector<Volunteer *> &getVolunteers(); // returns the Volunteers vector
    bool deleteLimitedVolunteer(int id); // removes the limited volunteer from the volunteersVector after they have reached their limit. 

private:
    bool isOpen;
    vector<BaseAction *> actionsLog;
    vector<Volunteer *> volunteers;
    vector<Order *> pendingOrders;
    vector<Order *> inProcessOrders;
    vector<Order *> completedOrders;
    vector<Customer *> customers;
    int customerCounter;  // For assigning unique customer IDs
    int volunteerCounter; // For assigning unique volunteer IDs
    void configFileProccessing(const string &configFilePath); //pareses the configFile
    int orderCounter; // ** for assigning unique order IDs 
    void InputToAction(string input); //parses input and executes the according action.
    void ConfigLineProccessing(string input); //parses a single line from configFile and executes the according action.  
    void clearWarehouse(); //deletes all pointers and clears thier vectors.
    Volunteer *fakeVolunteer;
    Order *fakeOrder;
    Customer *fakeCustomer;
};

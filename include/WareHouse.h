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
    void start();
    const vector<BaseAction *> &getActions() const;
    void addOrder(Order *order);
    void addAction(BaseAction *action);
    Customer &getCustomer(int customerId) const;
    Volunteer &getVolunteer(int volunteerId) const;
    Order &getOrder(int orderId) const;
    void close();
    void open();
    void addCustomer(Customer *customer); //** add customer to the warehouse
    int getCustomerCounter() const;
    int getVolunteerCounter() const;
    int getOrderCounter() const;
    bool customerExist(int id) const;
    bool volunteerExist(int id) const;

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
    void configFileProccessing(const string &configFilePath);
    int orderCounter; // ** for assigning unique order IDs
    void InputToAction(string input);
    void ConfigLineProccessing(string input);
    int CountWords(const std::string &input);
};

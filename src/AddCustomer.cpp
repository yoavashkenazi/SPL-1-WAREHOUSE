#include "../include/Action.h"
#include "../include/Order.h"
#include "../include/Customer.h"
#include <iostream>
#include <string>


CustomerType stringToCustomerType(string input) //returns the CustomerType of input
{
    if (input == "soldier")
    {
        return CustomerType::Soldier;
    }
    else
    {
        return CustomerType::Civilian;
    }
}
string CustomerTypeToString(CustomerType input) //returns the string of input
{
    if (input == CustomerType::Soldier)
    {
        return "soldier";
    }
    else
    {
        return "civilian";
    }
}

AddCustomer::AddCustomer(const string &customerName, const string &customerType, int distance, int maxOrders) : BaseAction(), customerName(customerName), customerType(stringToCustomerType(customerType)), distance(distance), maxOrders(maxOrders) {}

void AddCustomer::act(WareHouse &wareHouse)
{
    if (customerType == CustomerType::Soldier)
    {
        SoldierCustomer *newCustomer = new SoldierCustomer(wareHouse.getCustomerCounter(), customerName, distance, maxOrders);
        wareHouse.addCustomer(newCustomer);
    }
    else
    {
        CivilianCustomer *newCustomer = new CivilianCustomer(wareHouse.getCustomerCounter(), customerName, distance, maxOrders);
        wareHouse.addCustomer(newCustomer);
    }
    complete();
}

string AddCustomer::toString() const
{
    string output("customer " + customerName + " " + CustomerTypeToString(customerType) + " " + std::to_string(distance) + " " + std::to_string(maxOrders) + " COMPLETED");
    return output;
}

AddCustomer *AddCustomer::clone() const
{
    AddCustomer *cloneAddCustomer = new AddCustomer(customerName, CustomerTypeToString(customerType), distance, maxOrders);
    cloneAddCustomer->complete();
    return cloneAddCustomer;
}

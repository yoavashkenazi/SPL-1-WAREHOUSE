#include "../include/Action.h"
#include "../include/Order.h"
#include <iostream>
#include <string>



AddOrder::AddOrder(int id) : BaseAction(), customerId(id) {}

void AddOrder::act(WareHouse &wareHouse)
{
    //checks if the customer doesn`t exists or he exceeded his limit.
    if (!wareHouse.customerExist(customerId) || !(wareHouse.getCustomer(customerId).canMakeOrder())) 
    {
        this->error("Cannot place this order");
    }
    else
    {
        Order *order = new Order(wareHouse.getOrderCounter(), customerId, (wareHouse.getCustomer(customerId)).getCustomerDistance());
        wareHouse.addOrder(order);
        complete();
    }
}

string AddOrder::toString() const
{
    string output;
    if (this->getStatus() == ActionStatus::COMPLETED)
    {
        output = "order " + std::to_string(customerId) + " COMPLETED";
    }
    else
    {
        output = "order " + std::to_string(customerId) + " ERROR";
    }
    return output;
}

AddOrder *AddOrder::clone() const
{
    return new AddOrder(*this);
}

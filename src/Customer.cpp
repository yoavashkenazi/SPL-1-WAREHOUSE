#include "../include/Customer.h"

Customer::Customer(int id, const string &name, int locationDistance, int maxOrders) : id(id), name(name), locationDistance(locationDistance), maxOrders(maxOrders), ordersId(), orderCounter(0)
{
}
const string &Customer::getName() const
{
    return this->name;
}
int Customer::getId() const
{
    return this->id;
}
int Customer::getCustomerDistance() const
{
    return this->locationDistance;
}
int Customer::getMaxOrders() const // Returns maxOrders
{
    return this->maxOrders;
}
int Customer::getNumOrders() const // Returns num of orders the customer has made so far
{
    return this->orderCounter;
}
bool Customer::canMakeOrder() const // Returns true if the customer didn't reach max orders
{
    return (this->getNumOrders() < this->getMaxOrders());
}
const vector<int> &Customer::getOrdersIds() const
{
    return this->ordersId;
}
int Customer::addOrder(int orderId) // return OrderId if order was added successfully, -1 otherwise
{
    // assumes that the customer can make an order
    // check if id exists
    for (int id : this->ordersId)
    {
        if (id == orderId)
            return -1;
    }
    this->orderCounter = this->orderCounter + 1;
    this->ordersId.push_back(orderId);
    return orderId;
}

SoldierCustomer::SoldierCustomer(int id, const string &name, int locationDistance, int maxOrders) : Customer(id, name, locationDistance, maxOrders)
{
}
SoldierCustomer *SoldierCustomer::clone() const
{
    return new SoldierCustomer(*this);
}
CivilianCustomer ::CivilianCustomer(int id, const string &name, int locationDistance, int maxOrders) : Customer(id, name, locationDistance, maxOrders)
{
}
CivilianCustomer *CivilianCustomer::clone() const
{
    return new CivilianCustomer(*this);
}
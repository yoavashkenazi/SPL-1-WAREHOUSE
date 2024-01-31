#include "../include/Action.h"
#include "../include/Order.h"
#include "../include/Customer.h"
#include <iostream>
#include <string>

string Close::orderStatusToString(OrderStatus status)
{
    switch (status)
    {
    case OrderStatus::PENDING:
        return "Pending";
    case OrderStatus::COLLECTING:
        return "Collecting";
    case OrderStatus::DELIVERING:
        return "Delivering";
    case OrderStatus::COMPLETED:
        return "Completed";
    default:
        return "Unknown";
    }
}

Close::Close() : BaseAction() {}
void Close::act(WareHouse &wareHouse)
{
    vector<Order *> pendingOrderVector = wareHouse.getPendingOrders();
    for (Order *o : pendingOrderVector)
    {
        cout << "OrderID: " + std::to_string(o->getId()) + " , CustomerID: " + std::to_string(o->getCustomerId()) + " , OrderStatus: " + Close::orderStatusToString(o->getStatus()) << endl;
    }
    vector<Order *> inProccessOrderVector = wareHouse.getInProcessOrders();
    for (Order *o : inProccessOrderVector)
    {
        cout << "OrderID: " + std::to_string(o->getId()) + " , CustomerID: " + std::to_string(o->getCustomerId()) + " , OrderStatus: " + Close::orderStatusToString(o->getStatus()) << endl;
    }
    vector<Order *> completedOrderVector = wareHouse.getCompletedOrders();
    for (Order *o : completedOrderVector)
    {
        cout << "OrderID: " + std::to_string(o->getId()) + " , CustomerID: " + std::to_string(o->getCustomerId()) + " , OrderStatus: " + Close::orderStatusToString(o->getStatus()) << endl;
    }

    wareHouse.close();
    this->complete();
}
Close *Close::clone() const
{
    return new Close(*this);
}
string Close::toString() const
{
    string output;
    output = "Close COMPLETED";
    return output;
}
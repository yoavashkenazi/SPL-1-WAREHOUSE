#include "../include/Action.h"
#include "../include/Order.h"
#include <iostream>
#include <string>

PrintOrderStatus::PrintOrderStatus(int id) : BaseAction(), orderId(id) {}

void PrintOrderStatus::act(WareHouse &wareHouse)
{
    if (orderId > wareHouse.getOrderCounter())
    { // if the order doesnt exist (the id is higher than the counter)
        this->error("Order doesn't exist");
    }
    else
    {
        Order o = wareHouse.getOrder(orderId);
        cout << o.toString();
        this->complete();
    }
}

string PrintOrderStatus::toString() const
{
    string output;
    if (this->getStatus() == ActionStatus::COMPLETED)
    {
        output = "orderStatus " + std::to_string(orderId) + " COMPLETED";
    }
    else
    {
        output = "orderStatus " + std::to_string(orderId) + " ERROR";
    }
    return output;
}

PrintOrderStatus *PrintOrderStatus::clone() const
{
    PrintOrderStatus *clonePrintOrderStatus = new PrintOrderStatus(orderId);
    if (this->getStatus() == ActionStatus::COMPLETED)
    {
        clonePrintOrderStatus->complete();
    }
    else
    {
        clonePrintOrderStatus->error(this->getErrorMsg());
    }
    return clonePrintOrderStatus;
}

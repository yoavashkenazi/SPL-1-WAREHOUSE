#include "../include/Action.h"
#include "../include/Order.h"
#include "../include/Customer.h"
#include <iostream>
#include <string>

//returns the string of status
string PrintCustomerStatus::orderStatusToString(OrderStatus status)
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

PrintCustomerStatus::PrintCustomerStatus(int customerId) : BaseAction(), customerId(customerId) {}

void PrintCustomerStatus::act(WareHouse &wareHouse)
{
    if (!wareHouse.customerExist(customerId))
    { // if the customer doesnt exist
        this->error("Customer doesn't exist");
    }
    else
    {
        Customer *c = &(wareHouse.getCustomer(customerId));
        cout << "CustomerID: " + std::to_string(customerId) << endl;
        vector<int> ordersId = c->getOrdersIds();
        for (int i : ordersId)
        {
            cout << "OrderID: " + std::to_string(i) << endl;
            cout << "OrderStatus: " + orderStatusToString((wareHouse.getOrder(i)).getStatus()) << endl;
        }
        cout << "numOrdersLeft: " + std::to_string(c->getMaxOrders() - c->getNumOrders()) << endl;
        this->complete();
    }
}

string PrintCustomerStatus::toString() const
{
    string output;
    if (this->getStatus() == ActionStatus::COMPLETED)
    {
        output = "customerStatus " + std::to_string(customerId) + " COMPLETED";
    }
    else
    {
        output = "customerStatus " + std::to_string(customerId) + " ERROR";
    }
    return output;
}

PrintCustomerStatus *PrintCustomerStatus::clone() const
{
    return new PrintCustomerStatus(*this);
}

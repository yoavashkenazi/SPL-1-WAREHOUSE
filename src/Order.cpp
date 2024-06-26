#include "../include/Order.h"
#include <iostream>
#include <sstream>

Order::Order(int id, int customerId, int distance) : id(id), customerId(customerId), distance(distance), status(OrderStatus::PENDING), collectorId(NO_VOLUNTEER), driverId(NO_VOLUNTEER)
{
}
int Order::getId() const
{
    return this->id;
}
int Order::getCustomerId() const
{
    return this->customerId;
}
void Order::setStatus(OrderStatus status)
{
    this->status = status;
}
void Order::setCollectorId(int collectorId)
{
    this->collectorId = collectorId;
}
void Order::setDriverId(int driverId)
{
    this->driverId = driverId;
}
int Order::getCollectorId() const
{
    return this->collectorId;
}
int Order::getDriverId() const
{
    return this->driverId;
}
OrderStatus Order::getStatus() const
{
    return this->status;
}
const string Order::toString() const
{
    string statusStr = "Completed";
    switch (this->getStatus())
    {
    case OrderStatus::PENDING:
        statusStr = "Pending";
        break;
    case OrderStatus::COLLECTING:
        statusStr = "Collecting";
        break;
    case OrderStatus::DELIVERING:
        statusStr = "Delivering";
        break;
    case OrderStatus::COMPLETED:
        statusStr = "Completed";
        break;
    }

    string collectorIdStr = "None";
    if (this->getCollectorId() != NO_VOLUNTEER)
    {
        collectorIdStr = std::to_string(this->getCollectorId());
    }
    string driverIdStr = "None";
    if (this->getDriverId() != NO_VOLUNTEER)
    {
        driverIdStr = std::to_string(this->getDriverId());
    }

    std::ostringstream oss;
    oss << "OrderID: " << std::to_string(this->getId()) << "\n"
        << "OrderStatus: " << statusStr << "\n"
        << "CustomerID: " << std::to_string(this->getCustomerId()) << "\n"
        << "Collector: " << collectorIdStr << "\n"
        << "Driver: " << driverIdStr << "\n";
    return oss.str();
}
const int Order::getDistance() const
{
    return this->distance;
}

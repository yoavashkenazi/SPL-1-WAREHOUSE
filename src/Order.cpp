#include "../include/Order.h"

Order::Order(int id, int customerId, int distance) : id(id), customerId(customerId), distance(distance)
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
const string Order::toString() const {}
#include "../include/Volunteer.h"
#include "../include/WareHouse.h"
#include <iostream>
#include <sstream>

Volunteer ::Volunteer(int id, const string &name) : completedOrderId(NO_ORDER), activeOrderId(NO_ORDER), id(id), name(name)
{
}
int Volunteer ::getId() const
{
    return this->id;
}
const string &Volunteer ::getName() const
{
    return this->name;
}
int Volunteer ::getActiveOrderId() const
{
    return this->activeOrderId;
}
int Volunteer ::getCompletedOrderId() const
{
    return this->completedOrderId;
}
bool Volunteer ::isBusy() const
{
    return (activeOrderId != NO_ORDER);
}

CollectorVolunteer ::CollectorVolunteer(int id, const string &name, int coolDown) : Volunteer(id, name), coolDown(coolDown), timeLeft(coolDown)
{
}
CollectorVolunteer *CollectorVolunteer ::clone() const
{
    return new CollectorVolunteer(getId(), getName(), getCoolDown());
}
void CollectorVolunteer ::step()
{
    if (decreaseCoolDown())
    {
        this->completedOrderId = this->activeOrderId;
        this->activeOrderId = NO_ORDER;
    }
}
int CollectorVolunteer ::getCoolDown() const
{
    return this->coolDown;
}
int CollectorVolunteer ::getTimeLeft() const
{
    return this->timeLeft;
}
bool CollectorVolunteer ::decreaseCoolDown() // Decrease timeLeft by 1,return true if timeLeft=0,false otherwise
{
    this->timeLeft = this->timeLeft - 1;
    return (this->timeLeft == 0);
}
bool CollectorVolunteer ::hasOrdersLeft() const
{
    return true;
}
bool CollectorVolunteer ::canTakeOrder(const Order &order) const
{
    return (!isBusy());
}
void CollectorVolunteer ::acceptOrder(const Order &order)
{
    // assumes that the volunteer can take order
    this->activeOrderId = order.getId();
    this->timeLeft = this->coolDown;
}
string CollectorVolunteer ::toString() const
{
    string orderIdStr = "None";
    string timeLeftStr = "None";
    if (this->isBusy())
    {
        orderIdStr = std::to_string(this->getActiveOrderId());
        timeLeftStr = std::to_string(this->getTimeLeft());
    }
    std::ostringstream oss;
    oss << "VolunteerID: " << std::to_string(this->getId()) << "\n"
        << "isBusy: " << std::to_string(this->isBusy()) << "\n"
        << "OrderID: " << orderIdStr << "\n"
        << "TimeLeft: " << timeLeftStr << "\n"
        << "OrdersLeft: NO LIMIT"<< "\n";
    return oss.str();
}

LimitedCollectorVolunteer ::LimitedCollectorVolunteer(int id, const string &name, int coolDown, int maxOrders) : CollectorVolunteer(id, name, coolDown), maxOrders(maxOrders), ordersLeft(maxOrders)
{
}
LimitedCollectorVolunteer *LimitedCollectorVolunteer::clone() const
{
    return new LimitedCollectorVolunteer(this->getId(), this->getName(), this->getCoolDown(), this->getMaxOrders());
}
bool LimitedCollectorVolunteer::hasOrdersLeft() const
{
    return (this->ordersLeft > 0);
}
bool LimitedCollectorVolunteer::canTakeOrder(const Order &order) const
{
    return (!isBusy() && hasOrdersLeft());
}
void LimitedCollectorVolunteer::acceptOrder(const Order &order)
{
    // assumes that the volunteer can take order
    CollectorVolunteer::acceptOrder(order);
    this->ordersLeft = this->ordersLeft - 1;
}

int LimitedCollectorVolunteer::getMaxOrders() const
{
    return this->maxOrders;
}
int LimitedCollectorVolunteer::getNumOrdersLeft() const
{
    return this->ordersLeft;
}
string LimitedCollectorVolunteer::toString() const
{
    string orderIdStr = "None";
    string timeLeftStr = "None";
    if (this->isBusy())
    {
        orderIdStr = std::to_string(this->getActiveOrderId());
        timeLeftStr = std::to_string(this->getTimeLeft());
    }
    std::ostringstream oss;
    oss << "VolunteerID: " << std::to_string(this->getId()) << "\n"
        << "isBusy: " << std::to_string(this->isBusy()) << "\n"
        << "OrderID: " << orderIdStr << "\n"
        << "TimeLeft: " << timeLeftStr << "\n"
        << "OrdersLeft: " << std::to_string(this->getNumOrdersLeft())<< "\n";
    return oss.str();
}

DriverVolunteer::DriverVolunteer(int id, const string &name, int maxDistance, int distancePerStep) : Volunteer(id, name), maxDistance(maxDistance), distancePerStep(distancePerStep) {}
DriverVolunteer *DriverVolunteer::clone() const
{
    return new DriverVolunteer(this->getId(), this->getName(), this->getMaxDistance(), this->getDistancePerStep());
}
int DriverVolunteer::getDistanceLeft() const
{
    return this->distanceLeft;
}
int DriverVolunteer::getMaxDistance() const
{
    return this->maxDistance;
}
int DriverVolunteer::getDistancePerStep() const
{
    return this->distancePerStep;
}
bool DriverVolunteer::decreaseDistanceLeft() // Decrease distanceLeft by distancePerStep,return true if distanceLeft<=0,false otherwise
{
    this->distanceLeft = this->distanceLeft - distancePerStep;
    return this->distanceLeft <= 0;
}
bool DriverVolunteer::hasOrdersLeft() const
{
    return true;
}
bool DriverVolunteer::canTakeOrder(const Order &order) const // Signal if the volunteer is not busy and the order is within the maxDistance
{
    return (!isBusy() && order.getDistance() <= this->getMaxDistance());
}
void DriverVolunteer::acceptOrder(const Order &order) // 
{
    // assumes that the volunteer can take order
    this->activeOrderId = order.getId();
    this->distanceLeft = order.getDistance();
}
void DriverVolunteer::step() // Decrease distanceLeft by distancePerStep
{
    if (decreaseDistanceLeft())
    {
        this->completedOrderId = this->activeOrderId;
        this->activeOrderId = NO_ORDER;
    }
}
string DriverVolunteer::toString() const
{
    string orderIdStr = "None";
    string distanceLeftStr = "None";
    if (this->isBusy())
    {
        orderIdStr = std::to_string(this->getActiveOrderId());
        distanceLeftStr = std::to_string(this->getDistanceLeft());
    }
    std::ostringstream oss;
    oss << "VolunteerID: " << std::to_string(this->getId()) << "\n"
        << "isBusy: " << std::to_string(this->isBusy()) << "\n"
        << "OrderID: " << orderIdStr << "\n"
        << "DistanceLeft: " << distanceLeftStr << "\n"
        << "OrdersLeft: NO LIMIT"<< "\n";
    return oss.str();
}

LimitedDriverVolunteer ::LimitedDriverVolunteer(int id, const string &name, int maxDistance, int distancePerStep, int maxOrders) : DriverVolunteer(id, name, maxDistance, distancePerStep), maxOrders(maxOrders), ordersLeft(maxOrders) {}
LimitedDriverVolunteer *LimitedDriverVolunteer ::clone() const
{
    return new LimitedDriverVolunteer(this->getId(), this->getName(), this->getMaxDistance(), this->getDistancePerStep(), this->getMaxOrders());
}
int LimitedDriverVolunteer ::getMaxOrders() const
{
    return this->maxOrders;
}
int LimitedDriverVolunteer ::getNumOrdersLeft() const
{
    return this->ordersLeft;
}
bool LimitedDriverVolunteer ::hasOrdersLeft() const
{
    return (this->ordersLeft > 0);
}
bool LimitedDriverVolunteer ::canTakeOrder(const Order &order) const // Signal if the volunteer is not busy, the order is within the maxDistance and have orders left
{
    (!isBusy() && order.getDistance() <= this->getMaxDistance() && hasOrdersLeft());
}
void LimitedDriverVolunteer ::acceptOrder(const Order &order) // Assign distanceLeft to order's distance and decrease ordersLeft
{
    // assumes that the volunteer can take order
    DriverVolunteer::acceptOrder(order);
    this->ordersLeft = this->ordersLeft - 1;
}
string LimitedDriverVolunteer ::toString() const
{
    string orderIdStr = "None";
    string distanceLeftStr = "None";
    if (this->isBusy())
    {
        orderIdStr = std::to_string(this->getActiveOrderId());
        distanceLeftStr = std::to_string(this->getDistanceLeft());
    }
    std::ostringstream oss;
    oss << "VolunteerID: " << std::to_string(this->getId()) << "\n"
        << "isBusy: " << std::to_string(this->isBusy()) << "\n"
        << "OrderID: " << orderIdStr << "\n"
        << "DistanceLeft: " << distanceLeftStr << "\n"
        << "OrdersLeft: " << std::to_string(this->getNumOrdersLeft())<< "\n";
    return oss.str();
}
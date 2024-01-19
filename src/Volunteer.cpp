#include "../include/Volunteer.h"

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

CollectorVolunteer ::CollectorVolunteer(int id, string name, int coolDown) : Volunteer(id, name), coolDown(coolDown), timeLeft(coolDown)
{
}
CollectorVolunteer *CollectorVolunteer ::clone() const
{
    return new CollectorVolunteer(getId(), getName(), getCoolDown());
}
void CollectorVolunteer ::step() {}
int CollectorVolunteer ::getCoolDown() const
{
    return this->coolDown;
}
int CollectorVolunteer ::getTimeLeft() const
{
    return this->timeLeft;
}
bool CollectorVolunteer ::decreaseCoolDown()
{
    this->timeLeft = this->timeLeft - 1;
    return (this->timeLeft == 0);
} // Decrease timeLeft by 1,return true if timeLeft=0,false otherwise
bool CollectorVolunteer ::hasOrdersLeft() const
{
    return true;
}
bool CollectorVolunteer ::canTakeOrder(const Order &order) const {}
void CollectorVolunteer ::acceptOrder(const Order &order) {}
string CollectorVolunteer ::toString() const {}

LimitedCollectorVolunteer ::LimitedCollectorVolunteer(int id, string name, int coolDown, int maxOrders) : CollectorVolunteer(id, name, coolDown), maxOrders(maxOrders)
{
}

LimitedCollectorVolunteer *LimitedCollectorVolunteer::clone() const
{
}
bool LimitedCollectorVolunteer::hasOrdersLeft() const
{
}
bool LimitedCollectorVolunteer::canTakeOrder(const Order &order) const
{
}
void LimitedCollectorVolunteer::acceptOrder(const Order &order) {}

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
}

DriverVolunteer::DriverVolunteer(int id, string name, int maxDistance, int distancePerStep) : Volunteer(id, name), maxDistance(maxDistance), distancePerStep(distancePerStep) {}
DriverVolunteer *DriverVolunteer::clone() const {}

int DriverVolunteer::getDistanceLeft() const {}
int DriverVolunteer::getMaxDistance() const {}
int DriverVolunteer::getDistancePerStep() const {}
bool DriverVolunteer::decreaseDistanceLeft() {} // Decrease distanceLeft by distancePerStep,return true if distanceLeft<=0,false otherwise
bool DriverVolunteer::hasOrdersLeft() const {}
bool DriverVolunteer::canTakeOrder(const Order &order) const {} // Signal if the volunteer is not busy and the order is within the maxDistance
void DriverVolunteer::acceptOrder(const Order &order) {}        // Reset distanceLeft to maxDistance
void DriverVolunteer::step() {}                                 // Decrease distanceLeft by distancePerStep
string DriverVolunteer::toString() const {}

LimitedDriverVolunteer ::LimitedDriverVolunteer(int id, const string &name, int maxDistance, int distancePerStep, int maxOrders) : DriverVolunteer(id, name, maxDistance, distancePerStep), maxOrders(maxOrders) {}
LimitedDriverVolunteer *LimitedDriverVolunteer ::clone() const {}
int LimitedDriverVolunteer ::getMaxOrders() const {}
int LimitedDriverVolunteer ::getNumOrdersLeft() const {}
bool LimitedDriverVolunteer ::hasOrdersLeft() const {}
bool LimitedDriverVolunteer ::canTakeOrder(const Order &order) const {} // Signal if the volunteer is not busy, the order is within the maxDistance and have orders left
void LimitedDriverVolunteer ::acceptOrder(const Order &order) {}        // Reset distanceLeft to maxDistance and decrease ordersLeft
string LimitedDriverVolunteer ::toString() const {}
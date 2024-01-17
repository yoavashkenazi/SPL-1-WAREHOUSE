#include "../include/Volunteer.h"

Volunteer ::Volunteer(int id, const string &name) : id(id), name(name)
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
bool Volunteer ::isBusy() const {
    return activeOrderId}

CollectorVolunteer ::CollectorVolunteer(int id, string name, int coolDown) : Volunteer(id, name), coolDown(coolDown), timeLeft(coolDown)
{
}
CollectorVolunteer *CollectorVolunteer ::clone() const {}
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
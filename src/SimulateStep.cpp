#include "../include/Action.h"
#include "../include/Volunteer.h"
#include <iostream>

SimulateStep::SimulateStep(int numOfSteps) : BaseAction(), numOfSteps(numOfSteps)
{
}
void SimulateStep::act(WareHouse &wareHouse)
{
    for (int i = 0; i < numOfSteps; i++)
    {
        // part 1 - assigning pending orders to volunteers
        vector<Order *> pendingOrdersVector = wareHouse.getPendingOrders();
        vector<int> toInProcess;
        for (Order *o : pendingOrdersVector)
        { // each order in pendingOrders
            if (o->getStatus() == OrderStatus::PENDING)
            { // if the order status is PENDING, hand it to collector
                vector<Volunteer *> volunteerVector = wareHouse.getVolunteers();
                for (Volunteer *v : volunteerVector)
                {                                                                                            // searching for an available collector
                    if ((v->getVolunteerType() == 0 || v->getVolunteerType() == 1) && (v->canTakeOrder(*o))) // if the volunteer is a collector and available.
                    {
                        v->acceptOrder(*o);
                        o->setCollectorId(v->getId());
                        o->setStatus(OrderStatus::COLLECTING);
                        toInProcess.push_back(o->getId());
                        break; // break because volunteer is associated
                    }
                }
            }
            else
            { // if the order status is COLLECTING, hand it to a Driver
                vector<Volunteer *> volunteerVector = wareHouse.getVolunteers();
                for (Volunteer *v : volunteerVector)
                {                                                                                            // searching for an available driver
                    if ((v->getVolunteerType() == 2 || v->getVolunteerType() == 3) && (v->canTakeOrder(*o))) // if the volunteer is a driver and available.
                    {
                        v->acceptOrder(*o);
                        o->setDriverId(v->getId());
                        o->setStatus(OrderStatus::DELIVERING);
                        toInProcess.push_back(o->getId());
                        break; // break because driver is associated
                    }
                }
            }
        }

        for (int id : toInProcess)
        {
            wareHouse.moveOrderBetweenVectors(id, wareHouse.getPendingOrders(), wareHouse.getInProcessOrders()); // move from Pending to inProcess
        }
        // part 2 - Decreasing timeLeft and DistanceLeft
        vector<Volunteer *> volunteerVector = wareHouse.getVolunteers();
        for (Volunteer *v : volunteerVector)
        {
            if (v->isBusy())
            {
                v->step();
            }
        }
        // part 3 - checking each inProcess order if it was completed and moving it to pending/completed
        vector<Order *> inProccessOrdersVector = wareHouse.getInProcessOrders();
        // vectors of order ids which will move from inProcess to other vectors in warehouse
        vector<int> toPending;
        vector<int> toCompleted;
        for (Order *o : inProccessOrdersVector)
        {
            if (o->getStatus() == OrderStatus::DELIVERING && (wareHouse.getVolunteer(o->getDriverId())).getCompletedOrderId() != NO_ORDER)
            {
                toCompleted.push_back(o->getId());
                o->setStatus(OrderStatus::COMPLETED);
            }
            else if (o->getStatus() == OrderStatus::COLLECTING && (wareHouse.getVolunteer(o->getCollectorId())).getCompletedOrderId() != NO_ORDER)
            {
                toPending.push_back(o->getId());
            }
        }

        for (int id : toPending)
        {
            wareHouse.moveOrderBetweenVectors(id, wareHouse.getInProcessOrders(), wareHouse.getPendingOrders()); // move from inProcess to Pending
        }
        for (int id : toCompleted)
        {
            wareHouse.moveOrderBetweenVectors(id, wareHouse.getInProcessOrders(), wareHouse.getCompletedOrders()); // move from inProcess to Completed
        }

        // part 4 - deleting each limited volunteer that reached his maxOrders
        for (Volunteer *v : volunteerVector)
        {
            if ((!(v->hasOrdersLeft())) && v->getActiveOrderId() == NO_ORDER)
            {
                wareHouse.deleteLimitedVolunteer(v->getId());
            }
        }
    }
}
std::string SimulateStep::toString() const
{
    string output;
    output = "step " + std::to_string(numOfSteps) + " COMPLETED";
    return output;
}
SimulateStep *SimulateStep::clone() const
{
    SimulateStep *cloneSimulateStep = new SimulateStep(numOfSteps);
    if (this->getStatus() == ActionStatus::COMPLETED)
    {
        cloneSimulateStep->complete();
    }
    return cloneSimulateStep;
}
#include "../include/Action.h"
#include "../include/Volunteer.h"
#include <iostream>

SimulateStep::SimulateStep(int numOfSteps): BaseAction(), numOfSteps(numOfSteps) {
}
void SimulateStep::act(WareHouse &wareHouse){
    for (int i = 0; i < numOfSteps ; i++){ 
        //part 1 - assigning pending orders to volunteers
        vector<Order *> pendingOrdersVector = wareHouse.getOrders(0);
        for (Order* o : pendingOrdersVector){//each order in pendingOrders
            if (o->getStatus() == OrderStatus::PENDING){ //if the order status is pending, hand it to collector
                vector<Volunteer *> volunteerVector = wareHouse.getVolunteers();
                for (Volunteer* v : volunteerVector){ //searching for an available collector
                    if ((CollectorVolunteer* collector = dynamic_cast<CollectorVolunteer*>(v)) && (v->canTakeOrder(*o))){
                        v->acceptOrder(*o);
                        wareHouse.moveOrderBetweenVectors(o->getId());
                        o->setCollectorId(v->getId());
                        o->setStatus(OrderStatus::COLLECTING);
                    }
                }
            }
            else{//if the order status is collecting, hand it to a Driver
                vector<Volunteer *> volunteerVector = wareHouse.getVolunteers();
                for (Volunteer* v : volunteerVector){ //searching for an available driver
                    if ((DriverVolunteer* driver = dynamic_cast<DriverVolunteer*>(v)) && (v->canTakeOrder(*o))){
                        v->acceptOrder(*o);
                        wareHouse.moveOrderBetweenVectors(o->getId());
                        o->setDriverId(v->getId());
                        o->setStatus(OrderStatus::DELIVERING);
                    }
                }
            }
        }
        //part 2 - Decreasing timeLeft and DistanceLeft
        vector<Volunteer *> volunteerVector = wareHouse.getVolunteers();
        for (Volunteer* v : volunteerVector){
            if (v->isBusy()){
                v->step();
            }
        }
        //part 3 - checking each inProccess order if it was completed and moving it to pending/completed
        vector<Order *> inProccessOrdersVector = wareHouse.getOrders(1);
        for (Order* o : inProccessOrdersVector){
            if ((wareHouse.getVolunteer(o->getCollectorId())).getCompletedOrderId()!=NO_ORDER){ //if the order proccessing is completed
                if (o->getStatus() == OrderStatus::COLLECTING){
                    wareHouse.moveOrderBetweenVectors(o->getId()); //move from inProcces to Pending
                }
                else{
                    wareHouse.moveOrderBetweenVectors(o->getId()); //move from inProccess to Completed
                    o->setStatus(OrderStatus::COMPLETED);
                }
            }
        }
        //part 4 - deleting each limited volunteer that reached his maxOrders
        vector<Volunteer *> volunteerVector = wareHouse.getVolunteers();
        for (Volunteer* v : volunteerVector){
            if (!(v->hasOrdersLeft) && v->getActiveOrderId()==NO_ORDER){
                wareHouse.deleteLimitedVolunteer(v->getId());
            }
        }
    }
}
std::string SimulateStep::toString() const {
    string output;
    output = "step " + std::to_string(numOfSteps) + " COMPLETED";
    return output;
}
SimulateStep *SimulateStep::clone() const {
    SimulateStep *cloneSimulateStep = new SimulateStep(numOfSteps);
    if (this->getStatus() == ActionStatus::COMPLETED)
    {
        cloneSimulateStep->complete();
    }
    return cloneSimulateStep;
}
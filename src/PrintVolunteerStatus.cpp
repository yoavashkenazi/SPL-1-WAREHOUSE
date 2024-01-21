#include "../include/Action.h"
#include "../include/Order.h"
#include "../include/Customer.h"
#include <iostream>
#include <string>

//needed to be added: wareHouse.VolunteerExist(int id)

string orderStatusToString(OrderStatus status) {
    switch (status) {
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

PrintVolunteerStatus::PrintVolunteerStatus(int id): BaseAction(), volunteerId(id){}

void PrintVolunteerStatus::act(WareHouse &wareHouse){
    if ((!wareHouse.VolunteerExist(volunteerId)){ //if the volunteer doesnt exist
        this->error("Volunteer doesn't exist"); 
    }
    else{
        Volunteer v = wareHouse.getVolunteer(volunteerId);
        // cout << "volunteerId" + std::to_string(volunteerId) << endl;
        // if (v.isBusy()) {
        //     cout << "isBusy: True" << endl;
        //     cout << "OrderID: " + std:to_string(v.getActiveOrderId()) << endl;
        //     if (v)
        //     cout << "TimeLeft: " + 
        // }
        // else {
        //     cout << "isBusy: False" << endl;
        //     cout << "OrderID: None" << endl;
        //     cout << "TimeLeft: None" << endl;
        // }
        cout << v.toString();
        this->complete();
    }
}

string PrintVolunteerStatus::toString() const {
    string output;
    if (this->getStatus() == ActionStatus::COMPLETED){
        output = "volunteerStatus " + std::to_string(volunteerId) + " COMPLETED";}
    else{
        output = "volunteerStatus " + std::to_string(volunteerId) + " ERROR";}
    return output;
}

PrintVolunteerStatus *PrintVolunteerStatus::clone() const {
    PrintVolunteerStatus* clonePrintVolunteerStatus = new PrintVolunteerStatus(volunteerId);
    if(this->getStatus() == ActionStatus::COMPLETED){
        clonePrintVolunteerStatus->complete();}
    else{
        clonePrintVolunteerStatus->error(this->getErrorMsg());
    }
    return clonePrintVolunteerStatus;
}

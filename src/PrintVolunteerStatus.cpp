#include "../include/Action.h"
#include "../include/Order.h"
#include "../include/Customer.h"
#include "../include/Volunteer.h"
#include <iostream>
#include <string>

PrintVolunteerStatus::PrintVolunteerStatus(int id) : BaseAction(), volunteerId(id) {}

void PrintVolunteerStatus::act(WareHouse &wareHouse)
{
    if (!wareHouse.volunteerExist(volunteerId))
    { // if the volunteer doesnt exist
        this->error("Volunteer doesn't exist");
    }
    else
    {
        Volunteer *v = &(wareHouse.getVolunteer(volunteerId));
        cout << v->toString();
        this->complete();
    }
}

string PrintVolunteerStatus::toString() const
{
    string output;
    if (this->getStatus() == ActionStatus::COMPLETED)
    {
        output = "volunteerStatus " + std::to_string(volunteerId) + " COMPLETED";
    }
    else
    {
        output = "volunteerStatus " + std::to_string(volunteerId) + " ERROR";
    }
    return output;
}

PrintVolunteerStatus *PrintVolunteerStatus::clone() const
{
    return new PrintVolunteerStatus(*this);
}

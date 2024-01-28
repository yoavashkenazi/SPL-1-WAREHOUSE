#include "../include/Action.h"
#include "../include/Order.h"
#include "../include/Customer.h"
#include <iostream>
#include <string>

PrintActionsLog::PrintActionsLog() : BaseAction() {}
void PrintActionsLog::act(WareHouse &wareHouse)
{
    vector<BaseAction *> actionsVector = wareHouse.getActions();
    for (BaseAction *ba : actionsVector)
    {
        cout << ba->toString() << endl;
    }
    this->complete();
}
PrintActionsLog *PrintActionsLog::clone() const
{
    return new PrintActionsLog(*this);
}
string PrintActionsLog::toString() const
{
    string output;
    output = "log COMPLETED";
    return output;
}
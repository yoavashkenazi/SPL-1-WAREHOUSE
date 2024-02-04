#include "../include/Action.h"
#include "../include/Order.h"
#include "../include/Customer.h"
#include <iostream>
#include <string>
extern WareHouse *backup;

BackupWareHouse::BackupWareHouse() : BaseAction() {}
void BackupWareHouse::act(WareHouse &wareHouse)
{
    if (backup != nullptr)
        delete backup;
    backup = new WareHouse(wareHouse);
    this->complete();
}
BackupWareHouse *BackupWareHouse::clone() const
{
    return new BackupWareHouse(*this);
}
string BackupWareHouse::toString() const
{
    string output;
    if (this->getStatus() == ActionStatus::COMPLETED)
    {
        output = "backup COMPLETED";
    }
    else
    {
        output = "backup ERROR";
    }
    return output;
}
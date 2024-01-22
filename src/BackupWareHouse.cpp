#include "../include/Action.h"
#include "../include/Order.h"
#include "../include/Customer.h"
#include <iostream>
#include <string>
extern WareHouse* backup;

BackupWareHouse::BackupWareHouse(): BaseAction(){}
void BackupWareHouse::act(WareHouse &wareHouse) {
    delete backup;
    backup = new WareHouse(wareHouse);
    this->complete();
}
BackupWareHouse *BackupWareHouse::clone() const {
    BackupWareHouse *cloneBackupWareHouse = new BackupWareHouse();
    if (this->getStatus() == ActionStatus::COMPLETED)
    {
        cloneBackupWareHouse->complete();
    }
    return cloneBackupWareHouse;
}
string BackupWareHouse::toString() const {
    string output;
    output = "backup COMPLETED";
    return output;
}
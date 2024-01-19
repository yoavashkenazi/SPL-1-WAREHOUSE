#include "../include/BaseAction.h"
#include <iostream>


BaseAction::BaseAction(){}
ActionStatus BaseAction::getStatus() const{
    return status;
}
void BaseAction::complete(){
    status = ActionStatus::COMPLETED;
}
void BaseAction::error(string errorMsg){
    status = ActionStatus::ERROR;
    this->errorMsg = errorMsg;
    cout << "ERROR:"+ errorMsg << endl; 
}
string getErrorMsg(){
    string output = BaseAction::errorMsg;
    return output;
}
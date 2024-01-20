#include "../include/BaseAction.h"
#include "../include/Order.h"
//test
//needed to be added: wareHouse.getCustomerCounter(), wareHouse.CustomerExist()

AddOrder::AddOrder(int id): customerId(id), BaseAction() {
    
}
void AddOrder::act(WareHouse &wareHouse) {
    if ((!wareHouse.CustomerExist() || !(wareHouse.getCustomer(customerId).canMakeOrder())){
       this->error("Cannot place this order"); 
    } else{
        Order* order = new Order(wareHouse.getCustomerCounter(), customerId, (wareHouse.getCustomer(customerId)).getCustomerDistance());
        WareHouse.addOrder(order);
        complete();
    }
    

}
string toString() {
    string output;
    if (this->getStatus == ActionStatus::COMPLETED){
        output = "order " + customerId + " COMPLETED"; }
    else{
        output = "order " + this->customerId + " ERROR"; }
    return output;
}
AddOrder *clone() {

}
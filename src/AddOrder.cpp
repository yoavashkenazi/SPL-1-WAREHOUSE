#include "../include/BaseAction.h";

//needed to be added: wareHouse.getCustomerCounter(), wareHouse.CustomerExist()

AddOrder::AddOrder(int id): customerId(id), errorMsg(""), status(ERROR) {
    
}
void AddOrder::act(WareHouse &wareHouse) {
    if ((!wareHouse.CustomerExist() || !(wareHouse.getCustomer(customerId).canMakeOrder())){
       error("Cannot place this order"); 
    } else{
        Order* order = new Order(wareHouse.getCustomerCounter(), customerId, (wareHouse.getCustomer(customerId)).getCustomerDistance());
        WareHouse.addOrder(order);
        complete();
    }
    

}
string toString() {}
AddOrder *clone() {}
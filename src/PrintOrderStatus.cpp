#include "../include/Action.h"
#include "../include/Order.h"
#include <iostream>
#include <string>

//needed to be added: wareHouse.getOrderCounter()

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

PrintOrderStatus::PrintOrderStatus(int id): BaseAction(), orderId(id){}

void PrintOrderStatus::act(WareHouse &wareHouse){
    if (orderId > wareHouse.getOrderCounter()){ //if the order doesnt exist (the id is higher than the counter)
        this->error("Order doesn't exist"); 
    }
    else{
        Order o = wareHouse.getOrder(orderId);
        cout << "OrderId: " + orderId << endl;  
        cout << "OrderStatus: " + orderStatusToString(o.getStatus()) << endl;
        cout << "CustomerID: " + std::to_string(o.getCustomerId()) << endl;
        if (o.getCollectorId() == -1){ cout << "Collector: None" << endl;} //if there is no collector
        else {cout << "Collector: " + std::to_string(o.getCollectorId()) << endl;}
        if (o.getDriverId() == -1){ cout << "Driver: None" << endl;} 
        else {cout << "Driver: " + std::to_string(o.getDriverId()) << endl;} //if there is no driver
        this->complete();
    }
}

string PrintOrderStatus::toString() const {
    string output;
    if (this->getStatus() == ActionStatus::COMPLETED){
        output = "orderStatus " + std::to_string(orderId) + " COMPLETED";}
    else{
        output = "orderStatus " + std::to_string(orderId) + " ERROR";}
    return output;
}

PrintOrderStatus *PrintOrderStatus::clone() const {
    PrintOrderStatus* clonePrintOrderStatus = new PrintOrderStatus(orderId);
    if(this->getStatus() == ActionStatus::COMPLETED){
        clonePrintOrderStatus->complete();}
    else{
        clonePrintOrderStatus->error(this->getErrorMsg());
    }
    return clonePrintOrderStatus;
}

#include "../include/Action.h"
#include "../include/Order.h"
#include "../include/Customer.h"
#include <iostream>
#include <string>

Close::Close(){}
void Close::act(WareHouse &wareHouse){}
Close *Close::clone() const {}
string Close::toString() const{}
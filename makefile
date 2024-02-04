all: clean compile link

link:
	g++ -o bin/warehouse bin/main.o bin/WareHouse.o bin/AddOrder.o bin/Volunteer.o bin/Order.o bin/Customer.o bin/PrintCustomerStatus.o bin/PrintOrderStatus.o bin/SimulateStep.o bin/BaseAction.o bin/PrintVolunteerStatus.o bin/AddCustomer.o bin/PrintActionsLog.o bin/Close.o bin/BackupWareHouse.o bin/RestoreWareHouse.o

compile:
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/main.o src/main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/AddOrder.o src/AddOrder.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/WareHouse.o src/WareHouse.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Volunteer.o src/Volunteer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Order.o src/Order.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Customer.o src/Customer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/PrintCustomerStatus.o src/PrintCustomerStatus.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/PrintOrderStatus.o src/PrintOrderStatus.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/SimulateStep.o src/SimulateStep.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/BaseAction.o src/BaseAction.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/PrintVolunteerStatus.o src/PrintVolunteerStatus.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/AddCustomer.o src/AddCustomer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/PrintActionsLog.o src/PrintActionsLog.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Close.o src/Close.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/BackupWareHouse.o src/BackupWareHouse.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/RestoreWareHouse.o src/RestoreWareHouse.cpp

clean:
	rm -f bin/warehouse bin/*.o


all: clean compile link

valgrind: compile
	valgrind --leak-check=full --show-reachable=yes ./bin/hello ./configFile.txt

link:
	g++ -o bin/hello bin/main.o bin/WareHouse.o bin/AddOrder.o bin/Volunteer.o bin/Order.o bin/Customer.o bin/PrintCustomerStatus.o bin/PrintOrderStatus.o bin/SimulateStep.o bin/BaseAction.o bin/PrintVolunteerStatus.o bin/AddCustomer.o bin/PrintActionsLog.o bin/Close.o bin/BackupWareHouse.o bin/RestoreWareHouse.o

compile:
	g++ -g -Wall -Weffc++ -c -o bin/main.o src/main.cpp
	g++ -g -Wall -Weffc++ -c -o bin/AddOrder.o src/AddOrder.cpp
	g++ -g -Wall -Weffc++ -c -o bin/WareHouse.o src/WareHouse.cpp
	g++ -g -Wall -Weffc++ -c -o bin/Volunteer.o src/Volunteer.cpp
	g++ -g -Wall -Weffc++ -c -o bin/Order.o src/Order.cpp
	g++ -g -Wall -Weffc++ -c -o bin/Customer.o src/Customer.cpp
	g++ -g -Wall -Weffc++ -c -o bin/PrintCustomerStatus.o src/PrintCustomerStatus.cpp
	g++ -g -Wall -Weffc++ -c -o bin/PrintOrderStatus.o src/PrintOrderStatus.cpp
	g++ -g -Wall -Weffc++ -c -o bin/SimulateStep.o src/SimulateStep.cpp
	g++ -g -Wall -Weffc++ -c -o bin/BaseAction.o src/BaseAction.cpp
	g++ -g -Wall -Weffc++ -c -o bin/PrintVolunteerStatus.o src/PrintVolunteerStatus.cpp
	g++ -g -Wall -Weffc++ -c -o bin/AddCustomer.o src/AddCustomer.cpp
	g++ -g -Wall -Weffc++ -c -o bin/PrintActionsLog.o src/PrintActionsLog.cpp
	g++ -g -Wall -Weffc++ -c -o bin/Close.o src/Close.cpp
	g++ -g -Wall -Weffc++ -c -o bin/BackupWareHouse.o src/BackupWareHouse.cpp
	g++ -g -Wall -Weffc++ -c -o bin/RestoreWareHouse.o src/RestoreWareHouse.cpp

clean:
	rm -f bin/*

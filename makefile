
all: clean compile link

link:
	g++ -o bin/hello bin/main.o bin/WareHouse.o bin/AddOrder.o bin/Volunteer.o bin/Order.o bin/Customer.o bin/PrintCustomerStatus.o bin/PrintOrderStatus.o bin/SimulateStep.o bin/BaseAction.o bin/SoldierCustomer.o

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
	g++ -g -Wall -Weffc++ -c -o bin/SoldierCustomer.o src/SoldierCustomer.cpp
	g++ -g -Wall -Weffc++ -c -o bin/PrintVolunteerStatus.o src/PrintVolunteerStatus.cpp

clean:
	rm -f bin/*

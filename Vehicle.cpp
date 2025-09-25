#include "Vehicle.h"
#include <sstream>

// ===== Base Vehicle =====
Vehicle::Vehicle(string id, string brand, double rate, bool rented)
    : id(id), brand(brand), rentalRate(rate), rented(rented) {}// 

    void Vehicle::display() const {
    cout << id  << brand<< rentalRate<< (rented ? "Rented" : "Available") << endl;
}

void Vehicle::rent() { rented = true; }
void Vehicle::returnVehicle() { rented = false; }

//======Bicycle===========
Bicycle::Bicycle(string id, string brand, double rate, int seats, bool rented)
    : Vehicle(id, brand, rate, rented), seats(seats) {}

void  Bicycle::display() const {
    Vehicle::display();
    cout << " Bicycle Seat: " << seats << endl;
}
double Bicycle::calculateFee(int days) const { return rentalRate * days; }
string Bicycle::toFileString() const {
    return "Bicycle " + id + " " + brand + " " + to_string(rentalRate) + " " +
           to_string(seats) + " " + (rented ? "1" : "0");
}


// ===== Car =====
Car::Car(string id, string brand, double rate, int numDoors, bool rented)
    : Vehicle(id, brand, rate, rented), numDoors(numDoors) {}

void Car::display() const {
    Vehicle::display();
    cout << "Car doors: " << numDoors << endl;
}
double Car::calculateFee(int days) const { return rentalRate * days; }
string Car::toFileString() const {
    return "Car " + id + " " + brand + " " + to_string(rentalRate) + " " +
           to_string(numDoors) + " " + (rented ? "1" : "0");
}

// ===== Motorcycle =====
Motorcycle::Motorcycle(string id, string brand, double rate, int engineCC, bool rented)
    : Vehicle(id, brand, rate, rented), engineCC(engineCC) {}

void Motorcycle::display() const {
    Vehicle::display();
    cout << "Engine CC: " << engineCC << endl;
}
double Motorcycle::calculateFee(int days) const { return rentalRate * days; }
string Motorcycle::toFileString() const {
    return "Motorcycle " + id + " " + brand + " " + to_string(rentalRate) + " " +
           to_string(engineCC) + " " + (rented ? "1" : "0");
}

// ===== Truck =====
Truck::Truck(string id, string brand, double rate, int towingCapacity, bool rented)
    : Vehicle(id, brand, rate, rented), towingCapacity(towingCapacity) {}

void Truck::display() const {
    Vehicle::display();
    cout << "Towing Capacity: " << towingCapacity << " kg" << endl;
}
double Truck::calculateFee(int days) const { return rentalRate * days; }
string Truck::toFileString() const {
    return "Truck " + id + " " + brand + " " + to_string(rentalRate) + " " +
           to_string(towingCapacity) + " " + (rented ? "1" : "0");
}

// ===== Factory function for loading from file =====
Vehicle* Vehicle::loadFromLine(const string& line) {
    stringstream ss(line);
    string type, id, brand;
    double rate;
    int extra;
    int rented;

    ss >> type >> id >> brand >> rate >> extra >> rented;

    if (type == "Car") return new Car(id, brand, rate, extra, rented);
    if (type == "Motorcycle") return new Motorcycle(id, brand, rate, extra, rented);
    if (type == "Truck") return new Truck(id, brand, rate, extra, rented);
    if (type == "Bicycle") return new Bicycle(id, brand, rate, extra, rented);

    return nullptr;
}

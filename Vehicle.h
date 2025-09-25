#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Vehicle {
protected:
    string id;
    string brand;
    double rentalRate;
    bool rented;

public:
    Vehicle(string id, string brand, double rate, bool rented=false);
    virtual ~Vehicle() {}

    virtual void display() const;
    virtual double calculateFee(int days) const = 0; 

    void rent();
    void returnVehicle();
    bool getStatus() const { return rented; }
    string getId() const { return id; }
    string getBrand() const { return brand; }
    double getRate() const { return rentalRate; }

    // file I/O
    virtual string toFileString() const = 0;
    static Vehicle* loadFromLine(const string& line);
};

class Car : public Vehicle {
    int numDoors;
public:
    Car(string id, string brand, double rate, int numDoors, bool rented=false);
    void display() const override;
    double calculateFee(int days) const override;
    string toFileString() const override;
    int getNumDoors() const { 
        return numDoors; 
    }
};

class Motorcycle : public Vehicle {
    int engineCC;
public:
    Motorcycle(string id, string brand, double rate, int engineCC, bool rented=false);
    void display() const override;
    double calculateFee(int days) const override;
    string toFileString() const override;
    int getEngineCC() const { 
        return engineCC;
    }
};

class Truck : public Vehicle {
    int towingCapacity;
public:
    Truck(string id, string brand, double rate, int towingCapacity, bool rented=false);
    void display() const override;
    double calculateFee(int days) const override;
    string toFileString() const override;
    int getTowingCapacity() const { 
        return towingCapacity; 
    }
};

class Bicycle : public Vehicle {
    int seats;
public:
    Bicycle(string id, string brand, double rate, int seats, bool rented=false);
    void display() const override;
    double calculateFee(int days) const override;
    string toFileString() const override;
    int getSeats() const { 
        return seats; 
    }
};

#endif

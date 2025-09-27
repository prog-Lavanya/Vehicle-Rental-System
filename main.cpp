#include "Vehicle.h"
#include <fstream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

// Save vehicles to file
void saveVehicles(const vector<Vehicle*>& vehicles, const string& filename) {
    ofstream fout(filename);
    for (auto v : vehicles) fout << v->toFileString() << endl;
    fout.close();
}

// Table header
void printTableHeader() {
    cout << left << setw(5) << "No."
         << setw(10) << "ID"
         << setw(12) << "Brand"
         << setw(10) << "Rate"
         << setw(15) << "Extra"
         << setw(10) << "Status" << endl;
    cout << string(62, '-') << endl;
}

// Display vehicles in table, optionally filtered by category and availability
void displayVehicles(const vector<Vehicle*>& vehicles, const string& category="", bool availableOnly=false) {
    printTableHeader();
    int idx = 1;
    for (auto v : vehicles) {
        bool match = false;
        if (category.empty()) match = true;
        else if (category == "Car" && dynamic_cast<Car*>(v)) match = true;
        else if (category == "Motorcycle" && dynamic_cast<Motorcycle*>(v)) match = true;
        else if (category == "Truck" && dynamic_cast<Truck*>(v)) match = true;
        else if (category == "Bicycle" && dynamic_cast<Bicycle*>(v)) match = true;

        if (match && (!availableOnly || !v->getStatus())) {
            cout << left << setw(5) << idx++;
            cout << setw(10) << v->getId();
            cout << setw(12) << v->getBrand();
            cout << setw(10) << v->getRate();

            string extra = "-";
            if (Car* c = dynamic_cast<Car*>(v)) extra = to_string(c->getNumDoors()) + " doors";
            else if (Motorcycle* m = dynamic_cast<Motorcycle*>(v)) extra = to_string(m->getEngineCC()) + " CC";
            else if (Truck* t = dynamic_cast<Truck*>(v)) extra = to_string(t->getTowingCapacity()) + " kg";
            else if (Bicycle* b = dynamic_cast<Bicycle*>(v)) extra = to_string(b->getSeats()) + " seats";

            cout << setw(15) << extra;
            cout << setw(10) << (v->getStatus() ? "Rented" : "Available") << endl;
        }
    }
    cout << endl;
}

// Display by category
void displayByCategory(const vector<Vehicle*>& vehicles) {
    cout << "Enter category to display (Car/Motorcycle/Truck/Bicycle): ";
    string cat; cin >> cat;
    displayVehicles(vehicles, cat);
}

// Get index from user
int getVehicleIndex(int max) {
    int choice;
    while (true) {
        cout << "Enter vehicle number (0 to cancel): ";
        cin >> choice;
        if (cin.fail() || choice < 0 || choice > max) {
            cout << "Invalid choice. Try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else break;
    }
    return choice - 1; // zero-based
}

// Auto-generate ID
string generateId(const vector<Vehicle*>& vehicles, const string& category) {
    int maxNum = 0;
    for (auto v : vehicles) {
        if (category == "Car" && dynamic_cast<Car*>(v)) {
            int n = stoi(v->getId().substr(1));
            if (n > maxNum) maxNum = n;
        } else if (category == "Motorcycle" && dynamic_cast<Motorcycle*>(v)) {
            int n = stoi(v->getId().substr(1));
            if (n > maxNum) maxNum = n;
        } else if (category == "Truck" && dynamic_cast<Truck*>(v)) {
            int n = stoi(v->getId().substr(1));
            if (n > maxNum) maxNum = n;
        } else if (category == "Bicycle" && dynamic_cast<Bicycle*>(v)) {
            int n = stoi(v->getId().substr(1));
            if (n > maxNum) maxNum = n;
        }
    }
    char prefix = category[0]; // first letter as ID prefix
    return string(1, prefix) + to_string(maxNum + 1);
}

// Add new vehicle
void addVehicle(vector<Vehicle*>& vehicles) {
    cout << "Select type: 1.Car 2.Motorcycle 3.Truck 4.Bicycle: ";
    int type; cin >> type;
    string category;
    switch(type) {
        case 1: category="Car"; break;
        case 2: category="Motorcycle"; break;
        case 3: category="Truck"; break;
        case 4: category="Bicycle"; break;
        default: cout << "Invalid type\n"; return;
    }

    string brand; double rate; int extra;
    cout << "Enter Brand: "; cin >> brand;
    cout << "Enter Rate per day: "; cin >> rate;
    cout << "Enter ";
    if (category=="Car") cout << "number of doors: ";
    else if (category=="Motorcycle") cout << "engine CC: ";
    else if (category=="Truck") cout << "towing capacity: ";
    else if (category=="Bicycle") cout << "number of seats: ";
    cin >> extra;

    string id = generateId(vehicles, category);

    if (category=="Car") vehicles.push_back(new Car(id, brand, rate, extra));
    else if (category=="Motorcycle") vehicles.push_back(new Motorcycle(id, brand, rate, extra));
    else if (category=="Truck") vehicles.push_back(new Truck(id, brand, rate, extra));
    else if (category=="Bicycle") vehicles.push_back(new Bicycle(id, brand, rate, extra));

    cout << category << " added with ID " << id << "!\n";
}

// Rent or return vehicle
void rentOrReturn(vector<Vehicle*>& vehicles, bool rent=true) {
    cout << "Enter category (Car/Motorcycle/Truck/Bicycle): ";
    string cat; 
    cin >> cat;

    vector<Vehicle*> filtered;
    for (auto v : vehicles) {
        bool match = false;
        if (cat == "Car" && dynamic_cast<Car*>(v)) 
            match = true;
        else if (cat == "Motorcycle" && dynamic_cast<Motorcycle*>(v)) 
            match = true;
        else if (cat == "Truck" && dynamic_cast<Truck*>(v)) 
            match = true;
        else if (cat == "Bicycle" && dynamic_cast<Bicycle*>(v)) 
            match = true;

        if (match && ((rent && !v->getStatus()) || (!rent && v->getStatus())))
            filtered.push_back(v);
    }

    if (filtered.empty()) {
        cout << "No vehicles available in this category for this action.\n";
        return;
    }

    displayVehicles(filtered, cat, rent);
    int idx = getVehicleIndex(filtered.size());
    if (idx >= 0) {
        if (rent) 
            filtered[idx]->rent();
        else 
            filtered[idx]->returnVehicle();
        cout << (rent ? "Vehicle rented!" : "Vehicle returned!") << endl;
    }
}

// Main menu
void menu(vector<Vehicle*>& vehicles, const string& filename) {
    int choice;
    do {
        cout << "\n--- Vehicle Rental System ---\n";
        cout << "1. Display all vehicles\n";
        cout << "2. Display by category\n";
        cout << "3. Add vehicle\n";
        cout << "4. Rent vehicle\n";
        cout << "5. Return vehicle\n";
        cout << "0. Exit\n";
        cout << "Enter choice: "; cin >> choice;
        switch(choice) {
            case 1: displayVehicles(vehicles); break;
            case 2: displayByCategory(vehicles); break;
            case 3: addVehicle(vehicles); saveVehicles(vehicles, filename); break;
            case 4: rentOrReturn(vehicles,true); saveVehicles(vehicles, filename); break;
            case 5: rentOrReturn(vehicles,false); saveVehicles(vehicles, filename); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice\n"; break;
        }
    } while(choice != 0);
}

// Main
int main() {
    vector<Vehicle*> vehicles;
    string filename = "vehicles.txt";
    ifstream fin(filename);
    string line;
    while (getline(fin, line)) {
        Vehicle* v = Vehicle::loadFromLine(line);
        if(v) 
            vehicles.push_back(v);
    }
    fin.close();

    menu(vehicles, filename);

    for (auto v : vehicles) delete v;
    return 0;
}

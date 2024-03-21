#include <iostream>
#include <fstream>
#include <sstream>
#include <forward_list>
#include <string>
#include <iomanip>

using namespace std;

class Car;

class Customer;

Car *chooseCar(const forward_list<Car *> &carlist);

Customer *findCustomer(const forward_list<Customer *> &customersList, const string &name);

void addCustomer(forward_list<Customer *> &customersList);

void printCarList(const forward_list<Car *> &carList);

void printCustomerList(const forward_list<Customer *> &customerList);

void addCustomer(forward_list<Customer *> &customersList);


class Car {
public:
    bool isRented;
    bool isReturned;
    string carType;
    string brand;
    string model;
    string year;

public:
    Car(const string &carType, const string &brand, const string &model, const string &year) : carType(carType),
                                                                                               brand(brand),
                                                                                               model(model),
                                                                                               year(year) {
        isReturned = false;
        isRented = false;
    }
};


class Customer {

public:

    string name;
    forward_list<Car *> rentedCars;
    forward_list<Car> rentHistory;

    Customer(const string &name) : name(name) {}

    void rentACar(Car *car) {
        if (!car->isRented) {

            car->isReturned = false;
            car->isRented = true;
            rentedCars.push_front(car);
            rentHistory.push_front(*car);
        } else {
            cout << "This car is already rented." << endl;
        }
    }

    void returnCar(Car *car) {
        if (car->isRented && car != nullptr) {

            car->isReturned = true;
            car->isRented = false;
            cout << "Car " << car->brand << " returned" << endl;
            rentedCars.remove(car);
        } else {

            cout << "This car is not currently rented." << endl;
        }
    }


    void rentedCarList() const {

        cout << "Currently Rented Cars: " << endl;

        for (Car *car: rentedCars) {

            cout << left << setw(10) << "Car Type: " << setw(15) << car->carType
                 << setw(7) << "Brand: " << setw(15) << car->brand
                 << setw(7) << "Model: " << setw(20) << car->model
                 << setw(6) << "Year: " << setw(8) << car->year << endl;

        }


    }

    void returnRentedCar() {

        rentedCarList();

        string Model, Brand;

        cout << "Select Car Brand you want to return: ";
        cin >> Brand;

        cout << "Select Car Model you want to return: ";
        cin >> Model;

        for (Car *RentedCar: rentedCars) {

            if ((Model == RentedCar->model) && (Brand == RentedCar->brand)) {
                returnCar(RentedCar);
                break;
            }
        }
    }


    void rentalHistoryList() const {
        cout << "Rental History:" << endl;

        for (const Car &car: rentHistory) {
            cout << left << setw(10) << "Car Type: " << setw(15) << car.carType
                 << setw(7) << "Brand: " << setw(15) << car.brand
                 << setw(7) << "Model: " << setw(20) << car.model
                 << setw(6) << "Year: " << setw(8) << car.year << endl;
        }
    }


};


int main() {
    forward_list<Car *> cars;
    forward_list<Customer *> customers;

    ifstream myfile("cars.txt");

    if (myfile.is_open()) {
        string line;
        while (getline(myfile, line)) {


            /*Windows' new line is '\r\n' so none Windows system reads Year with the '\r' end of it */
            if (!line.empty() && line[line.size() - 1] == '\r') {
                line.erase(line.size() - 1);
            }


            stringstream ss(line);
            string carType, brand, model, yearStr;
            getline(ss, carType, ',');
            getline(ss, brand, ',');
            getline(ss, model, ',');
            getline(ss, yearStr, ',');

            cars.push_front(new Car(carType, brand, model, yearStr));
        }
        myfile.close();

    } else {
        cout << "Unable to open file" << endl;
    }

    int choice = 0;

    while (choice != 7) {

        choice = 0;
        cout << "\nEliteDrive Car Rental System\n";
        cout << "1. Display available cars\n";
        cout << "2. Rent a car\n";
        cout << "3. Return a rented car\n";
        cout << "4. Display customer information\n";
        cout << "5. Register new customer\n";
        cout << "6. View customer accounts and make new reservations\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;


        switch (choice) {
            case 1:

                printCarList(cars);

                break;
            case 2: {
                if (customers.empty()) {
                    cout << "No customers available. Add a new customer." << endl;

                } else {
                    string customerName;
                    cout << "Enter customer name to rent a car: ";
                    cin >> customerName;
                    Customer *existingCustomer = findCustomer(customers, customerName);

                    if (existingCustomer != nullptr) {

                        printCarList(cars);

                        Car *carChoosen = chooseCar(cars);

                        if (carChoosen != nullptr)
                            existingCustomer->rentACar(carChoosen);
                        else
                            cout << "Couldnt find Car" << endl;
                    } else {

                        cout << "Couldn't find customer" << endl;

                    }

                }
                break;
            }

            case 3: {
                if (customers.empty()) {
                    cout << "No customers available. Add a new customer." << endl;

                } else {
                    string customerName;
                    cout << "Enter customer name to return rented car: ";
                    cin >> customerName;
                    Customer *existingCustomer = findCustomer(customers, customerName);

                    if (existingCustomer != nullptr) {

                        existingCustomer->returnRentedCar();
                    } else {

                        cout << "Couldn't find customer" << endl;
                    }

                }
            }

                break;
            case 4: {

                if (customers.empty()) {
                    cout << "No customers available. Add a new customer." << endl;

                } else {


                    string customerName;
                    cout << "Enter customer name to display information: ";
                    cin >> customerName;
                    Customer *existingCustomer = findCustomer(customers, customerName);

                    if (existingCustomer != nullptr) {

                        cout << existingCustomer->name << ": " << endl;

                        if (!existingCustomer->rentedCars.empty()) {

                            existingCustomer->rentedCarList();
                        } else
                            cout << "Customer Has no rented cars." << endl;

                        if (!existingCustomer->rentHistory.empty()) {

                            existingCustomer->rentalHistoryList();
                        } else
                            cout << "Customer hasn't rented anything yet" << endl;


                    } else {

                        cout << "Couldn't find customer" << endl;
                    }

                }

            }

                break;
            case 5: {

                addCustomer(customers);

            }
                break;
            case 6: {

                if (customers.empty()) {
                    cout << "No customers available. Add a new customer." << endl;

                } else {

                    printCustomerList(customers);

                    string customerName;
                    cout << "Enter customer name to view account and make a reservation: ";
                    cin >> customerName;
                    Customer *existingCustomer = findCustomer(customers, customerName);

                    if (existingCustomer != nullptr) {

                        if (!existingCustomer->rentedCars.empty()) {

                            existingCustomer->rentedCarList();
                        } else
                            cout << "Customer Has no rented cars." << endl;

                        if (!existingCustomer->rentHistory.empty()) {

                            existingCustomer->rentalHistoryList();
                        } else
                            cout << "Customer hasn't rented anything yet" << endl;

                        char makeReservation;
                        cout << "Would you like to make a new reservation? (Y/N): ";
                        cin >> makeReservation;

                        if (makeReservation == 'Y' || makeReservation == 'y') {
                            printCarList(cars);

                            Car *carToRent = chooseCar(cars);

                            if (carToRent != nullptr) {

                                existingCustomer->rentACar(carToRent);
                            } else {
                                cout << "No available cars match your selection." << endl;
                            }
                        }
                    } else {
                        cout << "Customer not found. Please try again." << endl;
                    }

                }

            }

                break;
            case 7:

                cout << "Exiting..." << endl;

                break;
            default:

                cout << "Enter Valid Choice" << endl;

                break;
        }
    }

    for (Car *car: cars) {
        delete car;
    }

    for (Customer *customer: customers) {
        delete customer;
    }

    return 0;
}


Customer *findCustomer(const forward_list<Customer *> &customersList, const string &name) {
    for (Customer *customer: customersList) {
        if (customer->name == name) {
            return customer;
        }
    }
    cout << "Couldn't find customer" << endl;
    return nullptr;
}

Car *chooseCar(const forward_list<Car *> &carlist) {
    string type, brand, model, year;
    bool typeSelected = false, brandSelected = false, modelSelected = false;

    cout << "Please enter the type of car you want to rent: ";
    cin >> type;
    cout << "Available cars of type " << type << ":" << endl;
    for (const Car *car: carlist) {
        if (car->carType == type) {
            cout << car->brand << " " << car->model << " " << car->year << endl;
            typeSelected = true;
        }
    }
    if (!typeSelected) {
        cout << "No cars available for the selected type." << endl;
        return nullptr;
    }

    cout << "Please enter the brand of the car you want to rent: ";
    cin >> brand;
    cout << "Available " << type << " cars of brand " << brand << ":" << endl;
    for (const Car *car: carlist) {
        if (car->carType == type && car->brand == brand) {
            cout << car->model << " " << car->year << endl;
            brandSelected = true;
        }
    }
    if (!brandSelected) {
        cout << "No cars available for the selected brand." << endl;
        return nullptr;
    }

    cout << "Please enter the model of the car you want to rent: ";
    cin >> model;
    cout << "Available " << type << " " << brand << " cars of model " << model << ":" << endl;
    for (Car *car: carlist) {
        if (car->carType == type && car->brand == brand && car->model == model && !car->isRented) {
            return car;
        }
    }

    cout << "No available car found with the specifications." << endl;
    return nullptr;
}


void printCustomerList(const forward_list<Customer *> &customerList) {

    cout << "All Customers :" << endl;
    for (const Customer *customers: customerList) {

        cout << customers->name << endl;
    }


}

void printCarList(const forward_list<Car *> &carList) {
    cout << "Available Cars:" << endl;
    for (const Car *car: carList) {
        if (!car->isRented) {
            cout << left << setw(10) << "Car Type: " << setw(15) << car->carType
                 << setw(7) << "Brand: " << setw(15) << car->brand
                 << setw(7) << "Model: " << setw(20) << car->model
                 << setw(6) << "Year: " << setw(8) << car->year << endl;
        }
    }
}

void addCustomer(forward_list<Customer *> &customersList) {
    string customerName;
    cout << "Enter the customer's name: ";
    cin >> customerName;
    Customer *newCustomer = new Customer(customerName);
    customersList.push_front(newCustomer);
    cout << "Customer " << customerName << " has been added successfully." << endl;
}
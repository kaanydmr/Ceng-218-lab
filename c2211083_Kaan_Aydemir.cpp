#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

//Functions for menu
void flight_menu()
{

    cout << "|===============================|\n"
         << "||         Flight Menu         ||\n"
         << "||=============================||\n";

}

void flight_menu(string option)
{

    cout << "||" << setw(29) << left << option << "||\n"
         << "||-----------------------------||" << endl;


}


using namespace std;

class Passengers
{
private:
    string name;
    string surname;
    string gender;
    string seat_number;

public:
    Passengers() : name("EMPTY"), surname("EMPTY"), gender("NONE"), seat_number("NONE") {}

    Passengers(const string &NAME, const string &SURNAME, const string &GENDER) :
        name(NAME), gender(GENDER), seat_number("NONE")
    {
        // Convert the surname to uppercase
        std::string upperSurname = SURNAME;
        for (char &c: upperSurname)
        {
            c = std::toupper(c);
        }
        surname = upperSurname;
    }


    // Getters and setters
    string get_name() const
    {
        return name;
    }

    string get_surname() const
    {
        return surname;
    }

    string get_gender() const
    {
        return gender;
    }

    void set_name(const string &Name)
    {
        name = Name;
    }

    void set_surname(const string &Surname)
    {
        surname = Surname;
    }

    void set_gender(const string &Gender)
    {
        gender = Gender;
    }

};

class Flight
{
private:
    string flight_no;
    int maximum_number_of_seats;
    int number_of_passengers;
    vector<Passengers> list_of_passengers;

public:
    Flight() : flight_no("ABC123"), maximum_number_of_seats(25), number_of_passengers(0) {}

    Flight(const string &flightNo, int maximumNumberOfSeats, int numberOfPassengers,
           const vector<Passengers> &listOfPassengers) : flight_no(flightNo),
        maximum_number_of_seats(maximumNumberOfSeats),
        number_of_passengers(numberOfPassengers),
        list_of_passengers(listOfPassengers) {}

	//For sorting Passengers by surname
    static bool comparePassengersBySurname(const Passengers &a, const Passengers &b)
    {
        return a.get_surname() < b.get_surname();
    }

    void sortPassengersBySurname()
    {
        std::sort(list_of_passengers.begin(), list_of_passengers.end(), comparePassengersBySurname);
    }


    // Reserve seats
    bool reserve_seats(Passengers &Pass)
    {
        if (number_of_passengers < maximum_number_of_seats)
        {
            list_of_passengers.push_back(Pass); //pushback copya olusturuyo kendisini atmıyo içerde kopyası oluyo
            number_of_passengers++;
            cout << "Added passenger named: " << Pass.get_name() << endl;
            return true;
        }
        else
        {
            cout << "Sorry, the flight is full." << endl;
            return false;
        }
    }

	//Chacks Passengers Name, Surname and gender for confirming passenger is on flight
    void checkResrevation(Passengers &pass_to_check)
    {

        bool already_exist = false;

        for (int i = 0; i < list_of_passengers.size(); i++)
        {
            if (pass_to_check.get_name() == list_of_passengers[i].get_name() &&
                    pass_to_check.get_surname() == list_of_passengers[i].get_surname() &&
                    pass_to_check.get_gender() == list_of_passengers[i].get_gender())
            {

                already_exist = true;

            }
        }
        if (already_exist == true)
            cout << "You have reservation on plane" << endl;
        else
            cout << "You dont have any reservation" << endl;

    }

    // Cancel reservation
    bool cancel_reservation(Passengers &pass_remove)
    {
        for (int i = 0; i < list_of_passengers.size(); i++)
        {
            if (pass_remove.get_name() == list_of_passengers[i].get_name())
            {
                list_of_passengers.erase(list_of_passengers.begin() + i);
                cout << "Passenger named " << pass_remove.get_name() << " deleted" << endl;
                number_of_passengers--;
                return true;
            }

        }
        cout << "Passenger not found" << endl;
        return false;

    }

    // Print number of passengers
    int numberOfPassengers() const
    {
        return number_of_passengers;
    }

    // Print list of passengers
    void printPassengers()
    {
		//before printing sorts the vector
        sortPassengersBySurname();
        for (int i = 0; i < list_of_passengers.size(); i++)
        {
            cout << "Name: " << list_of_passengers[i].get_name() << ", Surname: " << list_of_passengers[i].get_surname()
                 << ", Gender: " << list_of_passengers[i].get_gender() << endl;
        }
    }

	string getFlightNo(){
		
		return flight_no;
		
	}
};


class FlightManager
{
private:
	
	vector<Flight> flights;

public:	
	
	void addFlight(const Flight& flight){		
		
		flights.push_back(flight);
	}
	
	void removeFlight(const std::string& flightNumber){
		
		for(size_t i = 0 ; i <= flights.size(); i++){
			if(flights[i].getFlightNo() == flightNumber){
				
				cout << "Flight with number: " << flightNumber << " is removed" << endl;
				flights.erase(flights.begin() + i);
				break;
			}	
		}
		cout << "No match for the flight number" << endl;
	}
	
	void listAllFlights(){
	}
	
	Flight getFlightByNumber(const std::string& flightNumber){
	}
	
	Flight getFlightByDestination(const std::string&destination){
	}
	
	
};



//For Entering correct inputs 
void getUserInput(string &input, const string &prompt)
{
    while (true)
    {
        cout << prompt;
        getline(cin, input);
        if (!input.empty())
        {
            break; // Break the loop if input is not empty
        }
        else
        {
            cout << "Error: Please enter a valid input." << endl;
            cin.clear(); // Clear any error flags
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }
    }
}


int main()
{

    Flight flight1;

    string Name, Surname, Gender;
    
    //Added passengers 
    Passengers pass1, pass2("Kaan", "Aydemir", "erkek"), pass3("Faruk", "aye", "erkek");

    flight1.reserve_seats(pass3);

    flight1.reserve_seats(pass1);
    flight1.reserve_seats(pass2);

    //fligth menu and option for operating menu
	int option(0);

    flight_menu();
    flight_menu("1. Reserve A ticket");
    flight_menu("2. Cancel Reservation");
    flight_menu("3. Check Reservation");
    flight_menu("4. Display Passengers");
    flight_menu("5. EXit");

    while (option != 5)
    {

        cout << "Choose an Operation: ";
        cin >> option;

  		
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (option)
        {

        case 1:
        {
            string name, surname, gender;
            getUserInput(name, "Enter your name: ");
            getUserInput(surname, "Enter your surname: ");
            getUserInput(gender, "Enter your gender: ");

            Passengers passenger(name, surname, gender);
            flight1.reserve_seats(passenger);
            break;
        }

        case 2:
        {
            string name, surname, gender;
            getUserInput(name, "Enter your name: ");
            getUserInput(surname, "Enter your surname: ");
            getUserInput(gender, "Enter your gender: ");

            Passengers passenger(name, surname, gender);
            flight1.cancel_reservation(passenger);
            break;
        }

        case 3:
        {
            string name, surname, gender;
            getUserInput(name, "Enter your name: ");
            getUserInput(surname, "Enter your surname: ");
            getUserInput(gender, "Enter your gender: ");

            Passengers passenger(name, surname, gender);
            flight1.checkResrevation(passenger);
            break;
        }

        case 4:
            flight1.printPassengers();
            break;

        case 5:
            cout << "Exiting..." << endl;
            break;
		//Entering other than 1-5 just gives an error
        default:
            cout << "Invalid option. Please choose again." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    }
    return 0;
}

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

int seatToInt(string seat);

//Functions for menu
void flight_menu()
{

    cout << "|====================================================|\n"
         << "||                   Flight Menu                    ||\n"
         << "||==================================================||\n";

}

void flight_menu(const string& option)
{

    cout << "||" << setw(50) << left << option << "||\n"
         << "||--------------------------------------------------||" << endl;


}


using namespace std;

class Passengers
{
private:
    string name;
    string surname;
    string gender;
    string seat_number;
    string nameAndSurname = (name + surname);
public:
    basic_string<char> getNameAndSurname() {
        return (name + " " + surname);
    }


private:

    bool seated = false;


public:
    const string &getSeatNumber() const {
        return seat_number;
    }
    int seatRow, seatCol;
    void setSeatNumber(int Row, string col) {

        seatRow = Row;
        seatCol = seatToInt(col);

        seat_number = to_string(Row) + col;
    }


    bool isSeated() const {
        return seated;
    }

    string seatXO(){

        if(Passengers::seated == true)
            return "X";
        else
            return "O";

    };

    void setSeated(bool seate) {

        seated = seate;
    }

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
    string destination;
    int maximum_number_of_seats = 40;
    int number_of_passengers;
    vector<Passengers> list_of_passengers;

    Passengers seatPlan[40][4];

public:
    Flight() : flight_no("ABC123"), maximum_number_of_seats(40), number_of_passengers(0) {}

    Flight(const string &flightNo, int maximumNumberOfSeats, int numberOfPassengers,
           const vector<Passengers> &listOfPassengers) : flight_no(flightNo),maximum_number_of_seats(maximumNumberOfSeats),number_of_passengers(numberOfPassengers),list_of_passengers(listOfPassengers) {}

    Flight(const string& flightNo, const string& Destination) : flight_no(flightNo), destination(Destination){}
    //For sorting Passengers by surname
    static bool comparePassengersBySurname(const Passengers &a, const Passengers &b)
    {
        return a.get_surname() < b.get_surname();
    }

    void setDestination(const string &destination) {
        Flight::destination = destination;
    }
    void sortPassengersBySurname()
    {
        std::sort(list_of_passengers.begin(), list_of_passengers.end(), comparePassengersBySurname);
    }

    string getDestination() const
    {
        return destination;
    }

    int getAvailableSeats() const
    {
        return maximum_number_of_seats - number_of_passengers;
    }

    string ColToChar(int col){

        if(col == 1)
            return "A";
        else if(col == 2)
            return "B";
        else if (col == 3)
            return "C";
        else if(col == 4)
            return "D";

    }

    // Reserve seats
    bool reserve_seats(Passengers &Pass, int ROW, int COL)
    {
        if (number_of_passengers < maximum_number_of_seats)
        {

            Pass.setSeatNumber(ROW, ColToChar(COL));
            Pass.setSeated(true);
            number_of_passengers++;
            cout << "Added passenger named: " << Pass.get_name() << endl;
            Pass.setSeated(true);
            seatPlan[ROW - 1][COL - 1] = Pass;
            list_of_passengers.push_back(Pass); //pushback copya olusturuyo kendisini atmıyo içerde kopyası oluyo
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
        Passengers pass;
        for (int i = 0; i < list_of_passengers.size(); i++)
        {
            if (pass_remove.get_name() == list_of_passengers[i].get_name())
            {
                list_of_passengers.erase(list_of_passengers.begin() + i);
                cout << "Passenger named " << pass_remove.get_name() << " deleted" << endl;
                number_of_passengers--;
                seatPlan[pass_remove.seatRow][pass_remove.seatCol] = pass;
                pass_remove.setSeated(false);
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
        if(list_of_passengers.size() == 0)
            cout << "There are no passengers" << endl;
    }

    bool isFlyingTo(const std::string& destinations){


    }

    string getFlightNo(){

        return flight_no;

    }

    void displaySeats(){


        cout << "||----------------Front----------------||" << endl;
        for (int i = 0; i < 40; i++) {
            cout << "| ";
            for (int j = 0; j < 4; j++) {
                cout << setw(2) << left << i + 1 << char ('A' + j)<< setw(2) << left << " " << seatPlan[i][j].seatXO() << " || ";
            }
            cout << endl;
        }


    }

    void passengerList(){


        if(list_of_passengers.empty() == false) {
            cout << "Passenger List for Flight " << flight_no << ": " << endl;
            cout << setw(5) << "Seat" << "|" << setw(15) << "Passenger Name" << "|" << setw(1) << "Gender\n";
            cout << "-----|---------------|------\n";
            for (size_t i = 0; i < list_of_passengers.size(); i++) {
                cout << setw(5) << list_of_passengers[i].getSeatNumber() << "|" << setw(15)
                     << (list_of_passengers[i].getNameAndSurname().length() > 15 ?
                         list_of_passengers[i].getNameAndSurname().substr(0, 15) + "."
                                                                                 : list_of_passengers[i].getNameAndSurname())
                     << "|" << setw(1) << list_of_passengers[i].get_gender() << endl;
            }
        }
        else
            cout << "There are no passengers" << endl;

    }

};


class FlightManager
{
private:

    vector<Flight*> flights;

public:

    void addFlight(Flight* flight){
        flights.push_back(flight);
        cout << "Added Flight " << flight->getFlightNo() << endl;
    }

    void removeFlight(const std::string& flightNumber){

        if(flights.size() != 0){
            bool found(false);
            for(size_t i = 0 ; i < flights.size(); i++){
                if(flights[i]->getFlightNo() == flightNumber){

                    cout << "Flight with number: " << flights[i]->getFlightNo() << " is removed" << endl;
                    found = true;
                    flights.erase(flights.begin() + i);

                }
            }
            if(found == false)
                cout << "Couldn't find Flight with number: " << flightNumber << endl;

        }
        else
            cout << "There are no flights yet."<< endl;


    }

    void listAllFlights(){

        if(false == flights.empty()) {
            cout << "List of all flights:" << endl;
            for (size_t i = 0; i < flights.size(); i++) {
                cout << "Flight Number: " << flights[i]->getFlightNo() << ", Destination: "
                     << flights[i]->getDestination() << ", Available Seats: " << flights[i]->getAvailableSeats() << endl;
            }
        }
        else
            cout << "There are no flights yet" << endl;
    }

    bool isEmpty(){

        if (flights.empty())
            return true;
        else
            return false;
    }
    Flight& getFlightByNumber(const std::string& flightNumber){
        for(size_t i = 0 ; i < flights.size(); i++){
            if(flights[i]->getFlightNo() == flightNumber){

                return *flights[i];
            }
        }
        cout << "Flight not found." << endl;
    }

    Flight& getFlightByDestination(const std::string&destination){

        for(size_t i = 0 ; i < flights.size(); i++){
            if(flights[i]->getDestination() == destination){

                return *flights[i];
            }
        }
    }

    ~FlightManager() {
        for (Flight* flight : flights) {
            delete flight;
        }
    }



};

int seatToInt(string seat){

    if(seat == "A")
        return 1;
    else if(seat == "B")
        return 2;
    else if (seat == "C")
        return 3;
    else if(seat == "D")
        return 4;


}

//For Entering correct inputs
void getUserInput(string &input, const string &prompt)
{
    while (true)
    {
        cout << prompt;

        if (getline(cin, input) && !input.empty())
        {
            break; // Break the loop if input is not empty
        }
        else
        {
            cout << "Error: Please enter a valid input." << endl;
            cin.clear();


        }
    }
}



int main()
{

    Flight flight1;

    FlightManager flightManager;

    string Name, Surname, Gender;

    //Added passengers
    Passengers pass1, pass2("Kaan", "Aydemir", "erkek"), pass3("Faruk", "aye", "erkek");
    Flight fligh4;
    /* flight1.reserve_seats(pass3);

     flight1.reserve_seats(pass1);
     flight1.reserve_seats(pass2);*/
   // flightManager.addFlight(fligh4);
    //fligth menu and option for operating menu
    int option(0);

    flight_menu();
    flight_menu("1. Add a Flight");
    flight_menu("2. Remove a Flight");
    flight_menu("3. List All Flights");
    flight_menu("4. Select a Flight and Manege Passengers");
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
                string destination, flightNum;


                getUserInput(flightNum, "Enter Flight Number: ");
                getUserInput(destination, "Enter destination: ");

                Flight* newFlight = new Flight(flightNum, destination);
                newFlight->setDestination(destination);

                flightManager.addFlight(newFlight);
                break;
            }

            case 2: {


                string flightNum;
                flightManager.listAllFlights();

                if (flightManager.isEmpty() == false) {

                    getUserInput(flightNum, "Enter Number of Flight to Remove: ");
                    flightManager.removeFlight(flightNum);
                }

                break;
            }

            case 3:
            {


                flightManager.listAllFlights();
                break;
            }

            case 4: {



                int select;
                string flightNum;
                flightManager.listAllFlights();
                getUserInput(flightNum, "Enter Flight Number for Management: ");

                cout << endl << endl;

                cout << "||==================================================||" << endl;
                flight_menu("1. Reserve a Seat");
                flight_menu("2. Cancel Reservation");
                flight_menu("3. View Passenger list");
                flight_menu("4. Back to flight Management Menu");
                cout << "Choose an operation: ";
                cin >> select;
                cin.ignore();


                switch (select) {

                    case 1:
                    {

                        flightManager.getFlightByNumber(flightNum).displaySeats();

                        string seatCol;
                        int  seatRow;

                        cout << "Select a seat row to reserve(Ex: 3): ";
                        cin >> seatRow;
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line
                        getUserInput(seatCol, "Select Seat to reserve (Ex: A): ");

                        string name, surname, gender;
                        getUserInput(name, "Enter your name: ");
                        getUserInput(surname, "Enter your surname: ");
                        getUserInput(gender, "Enter your gender(For male 'M' and For Female 'F'): ");

                        Passengers passenger(name, surname, gender);

                        flightManager.getFlightByNumber(flightNum).reserve_seats(passenger, seatRow, seatToInt(seatCol));

                        break;

                    }
                    case 2:{

                        flightManager.getFlightByNumber(flightNum).displaySeats();


                        string name, surname, gender;

                        cout  << "To Cancel Reservation "<< endl ;


                        getUserInput(name, "Enter your name: ");
                        getUserInput(surname, "Enter your surname: ");
                        getUserInput(gender, "Enter your gender: ");

                        Passengers passenger(name, surname, gender);

                        flightManager.getFlightByNumber(flightNum).cancel_reservation(passenger);



                        break;

                    }
                    case 3:
                    {

                        flightManager.getFlightByNumber(flightNum).passengerList();


                        break;

                    }
                    case 4:
                    {

                        // Option to go back to flight management menu
                        // This statement does nothing


                        break;
                    }

                    default:
                        cout << "Invalid option. Please choose again." << endl;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        continue;

                }

                break;
            }
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

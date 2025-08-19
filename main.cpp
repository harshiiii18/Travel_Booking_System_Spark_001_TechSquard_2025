#include<iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

bool isValidPhone(long long phone) {
    return (phone >= 1000000000LL && phone <= 9999999999LL);
}

bool isValidAge(int age) {
    return ( age>0 && age<100);
}

bool isValidName(const string& name) {
    if (name.empty()) return false;

    for (char c : name) {
        if (!isalpha(c) && c != ' ') {
            return false;
        }
    }

    return true;
}

bool isValidDestination(const string& destination) {
    if (destination.empty()) return false;

    for (char c : destination) {
        if (!isalpha(c) && c != ' ') {
            return false;
        }
    }
    return true;
}





class Booking {

    
    string passengerName;
    long long int PhoneNo;
    int seatNo;
    string destination;
    int age;
    int bookingID;
    
    public:
    Booking(){

    }

    Booking(long long int PhoneNo , string destination , int bookingID , int age , int seatNo , string passengerName) {
        this-> PhoneNo = PhoneNo;
        this-> destination = destination;
        this-> bookingID = bookingID;
        this-> age = age;
        this-> passengerName = passengerName;
        this-> seatNo = seatNo;
    }

   void inputDetails() {
    

    do {
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, passengerName);

    if (!isValidName(passengerName)) {
        cout << "Invalid name! . Enter Again : "<<" "<<endl;;
    } else {
        break;
    }
} while (true);
    
    do {
        cout << "Enter Phone Number: ";
        cin >> PhoneNo;

        if (!isValidPhone(PhoneNo)) {
            cout << "Invalid Phone Number! Try Again : " ;
        } else {
            break;
        }
    } while (true); 

    
    do {
        cout << "Enter Age: ";
        cin >> age;

        if (!isValidAge(age)) {
            cout << "Invalid Age!.Try Again : ";
        } else {
            break;
        }
    } while (true); 


    do {
    cout << "Enter Destination: ";
    cin.ignore();
    getline(cin, destination);


    if (!isValidDestination(destination)) {
        cout << "Invalid destination . Enter Again : ";
    } else {
        break;
    }
} while (true);

     do {
    cout << "Enter Seat Number: ";
    cin >> seatNo;

    if (seatNo <= 0) {
        cout << "Invalid seat number! .Enter Again :" << endl;
    }
    else {
        break;
    }
} while (true);
   }  


    void saveToFile() {
        bookingID = getNextID();
        ofstream file("bookings.txt", ios::app);
        file << bookingID << "," << passengerName << "," << destination << "," << seatNo << endl;
        file.close();
        cout << "Booking added successfully!" << endl;
    }

    static int getNextID() {
        ifstream file("bookings.txt");
        string line;
        int lastID = 0;
        while (getline(file, line)) {
            stringstream ss(line);
            string idStr;
            getline(ss, idStr, ',');
            lastID = stoi(idStr);
        }
        file.close();
        return lastID + 1;
    }

    static void showAllBookings() {
        ifstream file("bookings.txt");
        string line;
        cout << "\n--- All Bookings ---\n";
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }

    static void cancelBooking(int id) {
        ifstream file("bookings.txt");
        ofstream temp("temp.txt");
        string line;
        bool found = false;

        while (getline(file, line)) {
            stringstream ss(line);
            string idStr;
            getline(ss, idStr, ',');
            if (stoi(idStr) != id) {
                temp << line << endl;
            } else {
                found = true;
            }
        }

        file.close();
        temp.close();
        remove("bookings.txt");
        rename("temp.txt", "bookings.txt");

        if (found)
            cout << "Booking cancelled successfully." << endl;
        else
            cout << "Booking ID not found." << endl;
    }

    static void editBooking(int id) {
        ifstream file("bookings.txt");
        ofstream temp("temp.txt");
        string line;
        bool found = false;

        while (getline(file, line)) {
            stringstream ss(line);
            string idStr;
            getline(ss, idStr, ',');
            if (stoi(idStr) == id) {
                found = true;
                Booking b;
                b.bookingID = id;
                cout << "Enter new details:\n";
                b.inputDetails();
                temp << b.bookingID << "," << b.passengerName << "," << b.destination << "," << b.seatNo << "\n";
            } else {
                temp << line << endl;
            }
        }

        file.close();
        temp.close();
        remove("bookings.txt");
        rename("temp.txt", "bookings.txt");

        if (found)
            cout << "Booking updated successfully." << endl;
        else
            cout << "Booking ID not found." << endl;
    }

    static void displayAllTabular() {
    ifstream file("bookings.txt");
    string line;
    cout << "\nBookingID | Name           | Phone       | Age | Destination | Seat\n";
    cout << "---------------------------------------------------------------\n";
    
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, phone, age, dest, seat;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, phone, ',');
        getline(ss, age, ',');
        getline(ss, dest, ',');
        getline(ss, seat, ',');

        cout << id << "\t  " << name << "\t" << phone << "\t" << age << "\t" << dest << "\t" << seat << endl;
    }
    file.close();
}

    static void searchBooking() {
    int choice;
    string search;
    cout << "Search by:\n1. Name\n2. Destination\nEnter choice: ";
    cin >> choice;
    cin.ignore();
    cout << "Enter search text: ";
    getline(cin, search);

    ifstream file("bookings.txt");
    string line;
    bool found = false;

    while (getline(file, line)) {
        if ((choice == 1 && line.find(search) != string::npos) ||
            (choice == 2 && line.find(search) != string::npos)) {
            cout << line << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No matching booking found.\n";
    }

    file.close();
}


    static void seatAvailability() {
    bool booked[51] = {false}; 
    ifstream file("bookings.txt");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string temp;
        int count = 0;
        while (getline(ss, temp, ',')) {
            count++;
            if (count == 6) {  
                int seat = stoi(temp);
                if (seat >= 1 && seat <= 50)
                    booked[seat] = true;
            }
        }
    }
    file.close();

    cout << "\nSeat Availability (1-50):\n";
    for (int i = 1; i <= 50; i++) {
        if (booked[i])
            cout << "Seat " << i << ": Booked\n";
        else
            cout << "Seat " << i << ": Available\n";
    }
}
        
          
};



int main() {
    int choice;

    do {
        cout << "\n**** Travel Booking System ****\n";
        cout << "1. Add Booking\n";
        cout << "2. Show All Bookings\n";
        cout << "3. Cancel Booking\n";
        cout << "4. Edit Booking\n";
        cout << "5. View Bookings\n";
        cout << "6. Search Bookings\n";
        cout << "7. Check Seat Availability\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            Booking b;
            b.inputDetails();
            b.saveToFile();
        } else if (choice == 2) {
            Booking::showAllBookings();
        } else if (choice == 3) {
            int id;
            cout << "Enter Booking ID to cancel: ";
            cin >> id;
            Booking::cancelBooking(id);
        } else if (choice == 4) {
            int id;
            cout << "Enter Booking ID to edit: ";
            cin >> id;
            Booking::editBooking(id);
        } else if (choice == 5) {
            Booking::displayAllTabular();
        } else if (choice == 6) {
            Booking::searchBooking();
        } else if (choice == 7) {
            Booking::seatAvailability(); 
        } else if (choice == 8) {
            cout << "Exiting...\n";
        } else {
            cout << "Invalid choice.\n";
        }

    } while (choice != 8);

    return 0;
}
//
//  Airplane.h
//  Assignment4
//
//  Created by Victor Chen on 7/30/15.
//  Copyright (c) 2015 Victor Chen. All rights reserved.
//


/* Airplane Seating Layout
Symbol: w-window    a-aisle     m-middle
 
 First Class
 w   a   a   w
 w   a   a   w
 w   a   a   w
 w   a   a   w
 w   a   a   w
 
 Economy Class
 w m a   a m w
 w m a   a m w
 w m a   a m w
 w m a   a m w
 w m a   a m w
 w m a   a m w
 w m a   a m w
 w m a   a m w
 w m a   a m w
 w m a   a m w
 w m a   a m w
 w m a   a m w
 w m a   a m w
 w m a   a m w
 w m a   a m w
 w m a   a m w
 w m a   a m w
 w m a   a m w
 w m a   a m w
 w m a   a m w
 w m a   a m w
 w m a   a m w
 w m a   a m w
 w m a   a m w
 w m a   a m w
 w m a   a m w
 w m a   a m w
 w m a   a m w
 w m a   a m w
 w m a   a m w
 
*/

#ifndef __Assignment4__Airplane__
#define __Assignment4__Airplane__

#include <iostream>
#include <map>
#include <string>
#include "Seat.h"
#include "Passenger.h"

using namespace std;

//second value bool identifies if the seat is occupied by a passenger
typedef map<Seat*, bool> vacancy_by_seats_map;

class Airplane {
public:
    Airplane() {
        
        //dynamically create the first class char map
        first_class = new char*[5];
        for(int f = 0; f < 5; ++f)
            first_class[f] = new char[4];
        
        //dynamically create the economy class char map
        economy_class = new char*[30];
        for(int e = 0; e < 30; ++e)
            economy_class[e] = new char[6];
        
        //dummy variables
        TYPE seat_type              = UNKNOWN_TYPE;
        TRAVEL_CLASS travel_class   = UNKNOWN_CLASS;
        Seat* temp_seat_ptr;
        
        //allocate space for FIRST class seats, which has 5 by 4 seats
        travel_class = FIRST;
        for (int first_r =0; first_r < 5; first_r++) {
            for (int first_c =0; first_c < 4; first_c++) {
                //Determine the seat type by the column
                switch (first_c) {
                    case 0: seat_type = WINDOW; break;
                    case 1: seat_type = AISLE; break;
                    case 2: seat_type = AISLE; break;
                    case 3: seat_type = WINDOW; break;
                    default: break;
                }
                //populate the 2d first_class char map
                first_class[first_r][first_c] = getSeatSymbol(seat_type);
                
                //Dynamically create a new Seat with its attributes filled
                temp_seat_ptr = new Seat(first_r, first_c, travel_class, seat_type);
                
                //insert seat into the airplane seat map
                m_seat_map.insert(vacancy_by_seats_map::value_type(temp_seat_ptr, false));
                
                //set temporary seat pointer to null to avoid problems
                temp_seat_ptr = NULL;
            }
        }
        
        //allocate space for ECONOMY class seats, which has 30 by 6 seats
        travel_class = ECONOMY;
        for (int econ_r =0; econ_r < 30; econ_r++) {
            for (int econ_c =0; econ_c < 6; econ_c++) {
                //Determine the seat type by the column
                switch (econ_c) {
                    case 0: seat_type = WINDOW; break;
                    case 1: seat_type = MIDDLE; break;
                    case 2: seat_type = AISLE; break;
                    case 3: seat_type = AISLE; break;
                    case 4: seat_type = MIDDLE; break;
                    case 5: seat_type = WINDOW; break;
                    default: break;
                }
                //initialize the 2d economy_class char map
                economy_class[econ_r][econ_c] = getSeatSymbol(seat_type);
                
                //Dynamically create a new Seat with its attributes filled
                temp_seat_ptr = new Seat(econ_r, econ_c, travel_class, seat_type);
                
                //insert seat into the airplane seat map
                m_seat_map.insert(vacancy_by_seats_map::value_type(temp_seat_ptr, false));
                
                //set temporary seat pointer to null to avoid problems
                temp_seat_ptr = NULL;
            }
        }
    }
    
    //Destructor, takes care of delete dynamic memory
    ~Airplane() {
        //delete the dynamic first_class 2d char array
        for(int f = 0; f < 5; ++f)
            delete [] first_class[f];
        delete[] first_class;

        //delete the dynamic first_class 2d char array
        for(int e = 0; e < 30; ++e)
            delete [] economy_class[e];
        delete[] economy_class;
        
        //create a iterator to interate through m_seat_map
        vacancy_by_seats_map::iterator i;
        
        //loop through the m_seat_map
        for(i = m_seat_map.begin(); i != m_seat_map.end(); i++) {
            //Check and see if Seat is being occupied by a Passenger
            if(i->second == true) {
                //delete Passenger objects that were dynamically created
                delete i->first->getPassenger();
                //set the Seat's Passenger pointer to NULL
                i->first->setPassenger(NULL);
            }
            
            //delete the Seat object that was created
            delete i->first;
        }
    }
    
    //Display the menu to the user
    void showMenu() {
        int input;
        bool bad_input = false;
        do {
            cout << "Welcome aboard the CSC300 Airplane" << endl << endl;
            
            cout << "1. Add a Passenger" << endl;
            cout << "2. Show a map of the available seats" << endl;
            cout << "3. Log Off" << endl;
            
            cout << "Please choose between the above options: ";
            
            //validate user input
            validateNumericInput(input, bad_input);
            
            //User entered good input
            if (!bad_input) {
                switch (input) {
                    case 1:
                        cout<< endl;
                        addPassenger();
                        break;
                    case 2:
                        cout<< endl;
                        showSeating();
                        break;
                    case 3: break;
                    default:
                        cout << "\tPlease enter a digit between 1 and 3" << endl << endl;
                        break;
                }
            }
        }while(bad_input || input != 3);
    }
    
    //ask for the class(first or economy), the number of passengers traveling together (1 to 2 in the first class, 1 to 3 in economy) and the seating preference (aisle or window in the first class; aisle, center, or window in economy). Then try to find a match and assign the seats, if no match then exit and print a message.
    void addPassenger() {
        //Values required
        TRAVEL_CLASS tc_option = UNKNOWN_CLASS;
        TYPE type_option = UNKNOWN_TYPE;
        int num_of_passengers = 0;
        
        //Variables used to capture user input and validate bad ones
        int input;
        bool bad_input;
        
        //Prompt to choose Travel Class
        do {
            //reset user inputs
            input = -1;
            bad_input = false;
            
            cout << "1. First Class" << endl;
            cout << "2. Economy Class" << endl;
            cout << "Please enter your preferred travel class: ";
            validateNumericInput(input, bad_input);
            
            //Enters here only if good numeric input is recognized
            if (!bad_input) {
                switch(input) {
                    case 1: tc_option = FIRST;      break;
                    case 2: tc_option = ECONOMY;    break;
                    default:
                        cout << "\tPlease enter a digit between 1 and 2" << endl;
                        break;
                }
            }
        }while(bad_input || input < 1 || input > 2 );
        cout<< endl;
        
        //Prompt to enter number of traveling passengers
        do {
            //reset user inputs
            input = -1;
            bad_input = false;
            
            cout << "Enter number of traveling passengers (max is 3): ";
            validateNumericInput(input, bad_input);
            
            //Enters here only if good numeric input is recognized
            if (!bad_input) {
                switch(input) {
                    case 1:
                    case 2:
                        num_of_passengers = input;
                        break;
                    case 3:
                        if(tc_option == ECONOMY) {
                            num_of_passengers = input;
                            break;
                        }
                    default:
                        cout << "\tIf traveling First class, only 1 to 2 Passengers are allowed.\n";
                        cout << "\tIf traveling Economy class, only 1 to 3 Passengers are allowed." << endl;
                        if (tc_option == FIRST) {
                            bad_input = true;
                        }
                        else {
                            break;
                        }
                }
            }
        }while(bad_input || input < 1 || input > 3 );
        cout << endl;
        
        //Prompt to enter seating preferences
        do {
            //reset user inputs
            input = -1;
            bad_input = false;
            
            cout << "1. Window Seat" << endl;
            cout << "2. Aisle Seat" << endl;
            cout << "3. Center Seat" << endl;
            cout << "Please enter your preferred seating type: ";
            validateNumericInput(input, bad_input);
            
            //Enters here only if good numeric input is recognized
            if (!bad_input) {
                switch(input) {
                    case 1: type_option = WINDOW;       break;
                    case 2: type_option = AISLE;        break;
                    case 3:
                        if (tc_option == ECONOMY) {
                            type_option = MIDDLE;
                            break;
                        }
                    default:
                        cout << "\tIf traveling First class, only Window or Aisle seats are available\n";
                        cout << "\tIf traveling Economy class, only Window, Center, or Aisle seats are available." << endl;
                        if (tc_option == FIRST) {
                            bad_input = true;
                        }
                        else {
                            break;
                        }
                }
            }
        }while(bad_input || input < 1 || input > 3 );
        cout<< endl;
        
        //try to find a match and assign the seats, if no match then exit and print a message.
        Passenger* new_passenger_ptr;
        for (int x = 0; x < num_of_passengers; x ++) {
            new_passenger_ptr = new Passenger(this, tc_option, type_option);
            cout << "Passenger " << x << ":" << endl;
            new_passenger_ptr->find_n_book_seat();
        }
    }
    
    //When this method is called, it will display the above Airplane Seating Layout
    //Occupied seats will be replaced with 'P' for passenger
    void showSeating() {
        //print first class seating layout
        cout << "First Class" << endl;
        for (int fc_r = 0; fc_r < 5; fc_r++) {
            for (int fc_c = 0; fc_c < 4; fc_c++) {
                cout << first_class[fc_r][fc_c];
                if (fc_c != 3) {
                    cout << "   ";
                }
                else {
                    cout << endl;
                }
            }
        }
        cout << endl;
        
        //print economy class seating layout
        cout << "Economy Class" << endl;
        for (int ec_r = 0; ec_r < 30; ec_r++) {
            for (int ec_c = 0; ec_c < 6; ec_c++) {
                cout << economy_class[ec_r][ec_c];
                if (ec_c == 2) {
                    cout << "   ";
                }
                else if (ec_c == 5) {
                    cout << endl;
                }
                else {
                    cout << " ";
                }
            }
        }
        cout << endl << endl;
    }
    /***************************Helper Get Functions***************************/
    vacancy_by_seats_map::iterator getSeatMapBeginItr() {
        return m_seat_map.begin();
    }
    
    vacancy_by_seats_map::iterator getSeatMapEndItr() {
        return m_seat_map.end();
    }
    
    char** getFirstMap() const {
        return first_class;
    }
    
    char** getEconomyMap() const {
        return economy_class;
    }

private:
    vacancy_by_seats_map m_seat_map;
    char** first_class;
    char** economy_class;
    
    /********************Private helper methods********************/
    void validateNumericInput(int& input, bool& bad) {
        //User entered bad input
        if (!(cin >> input)) {
            bad = true;
            //clear the error  flag in the cin object
            cin.clear();
            //discard erroneous user input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            //display error
            cerr << "Please enter a valid numeric digit" << endl << endl;
        }
    }
    
    char getSeatSymbol(TYPE tt) {
        switch(tt) {
            case WINDOW: return 'w';
            case AISLE: return 'a';
            case MIDDLE: return 'm';
            default: return '.';
        }
    }
    
    /***************************************************************/
};
#endif /* defined(__Assignment4__Airplane__) */

//
//  Passenger.cpp
//  Assignment4
//
//  Created by Victor Chen on 7/30/15.
//  Copyright (c) 2015 Victor Chen. All rights reserved.
//

#include "Passenger.h"
#include "Airplane.h"
#include <map>

using namespace std;

void Passenger::find_n_book_seat() {
    bool found_seat = false;
    map<Seat*, bool>::iterator itr = m_airplane->getSeatMapBeginItr();
    map<Seat*, bool>::iterator itr_end = m_airplane->getSeatMapEndItr();
    
    //First, Find the first available travel class equal to m_pref_class
    //Next, find the first available seat type equal to m_pref_type
    //Third, assign this passenger to the matching seat, if no match available, display error
    while(itr != itr_end) {
        
        if ( !(itr->second)                 //check to see if seat has been occupied
            && itr->first->getClass() == m_pref_class //match the passenger preferred class with the seat's travel class
            && itr->first->getSeatType() == m_pref_type) //match the passenger preferred seat type with the seat's seat type
        {
            itr->second = true;     //set the airplane seat map to reflect an occupied seat
            itr->first->setPassenger(this);   //assign the seat to this passenger
            
            //update the first class or economy class char map
            switch(m_pref_class) {
                case FIRST:
                    m_airplane->getFirstMap()[itr->first->getRow()][itr->first->getColumn()] = 'P';
                    break;
                case ECONOMY:
                    m_airplane->getEconomyMap()[itr->first->getRow()][itr->first->getColumn()] = 'P';
                    break;
                default:
                    break;
            }
            
            found_seat = true;
            cout << "Base on your preferences: " << ((m_pref_class == 0)? "First": "Economy") << " Class and ";
            cout << ((m_pref_type == 0)? "Aisle": ( (m_pref_type == 1)? "Center" : "Window") ) << " seating," << endl;
            cout << "Your assigned seat is Row " << itr->first->getRow()+1 << " and Column " << itr->first->getColumn()+1 << endl << endl;
            break;
        }
        
        //iterator to next seat in the airplane seat map
        itr++;
    }
    
    //display error that there is no seat available that match
    if(!found_seat) {
        cerr << "Unable to locate a matching " << ((m_pref_class == 0)? "First": "Economy") << " Class with " << ((m_pref_type == 0)? "Aisle": ( (m_pref_type == 1)? "Center" : "Window") ) << " seating." << endl << endl;
    }
}
//
//  Seat.h
//  Assignment4
//
//  Created by Victor Chen on 7/30/15.
//  Copyright (c) 2015 Victor Chen. All rights reserved.
//

#ifndef __Assignment4__Seat__
#define __Assignment4__Seat__

#include <iostream>

enum TRAVEL_CLASS {FIRST, ECONOMY, UNKNOWN_CLASS};     //tells the travel class of the seat
enum TYPE {AISLE, MIDDLE, WINDOW, UNKNOWN_TYPE};     //identifies the seat's attribute as aisle seat, middle seat, or window seat

class Passenger;

class Seat {
public:
    
    Seat(int r, int c, TRAVEL_CLASS tc, TYPE t)
    : m_row(r), m_column(c), m_class(tc), m_type(t)
    {
        m_passenger = NULL; //A seat when created should not have a Passenger yet
    }
    
    /* The seat's destructor is not needed since the dynamic Passenger object was deleted in the Airplane's destructor
    ~Seat()
    */
    
    /*******************Getters***********************/
    Passenger* getPassenger() const {
        return m_passenger;
    }
    
    TRAVEL_CLASS getClass() const {
        return m_class;
    }
    
    int getRow() const {
        return m_row;
    }
    
    int getColumn() const {
        return m_column;
    }
    
    TYPE getSeatType() const {
        return m_type;
    }
    
    /*******************Setters***********************/
    void setPassenger(Passenger* p) {
        m_passenger = p;
    }
    
private:
    Passenger*      m_passenger;
    TRAVEL_CLASS    m_class;
    int             m_row;
    int             m_column;
    TYPE            m_type;
};

#endif /* defined(__Assignment4__Seat__) */

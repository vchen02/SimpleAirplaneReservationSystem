//
//  Passenger.h
//  Assignment4
//
//  Created by Victor Chen on 7/30/15.
//  Copyright (c) 2015 Victor Chen. All rights reserved.
//

#ifndef __Assignment4__Passenger__
#define __Assignment4__Passenger__

#include <iostream>
#include "Seat.h"

class Airplane;
class Passenger {
    
public:
    
    //When passengers are first created, he needs to belong to an Airplane but does not need to know his seating at the time of creation
    Passenger(Airplane* air, TRAVEL_CLASS tc, TYPE t)
    :m_airplane(air), m_pref_class(tc), m_pref_type(t)
    {
        m_seat = NULL;
    }
    
    //When this method is called, it will try to find a seat matching the passenger's preference and assign the passenger to the seat within the airplane.
    void find_n_book_seat();
    
    /*******************Getters***********************/
    //None
    
    /*******************Setters***********************/
    //None
    
private:
    Airplane*       m_airplane;
    Seat*           m_seat;
    TRAVEL_CLASS    m_pref_class;
    TYPE            m_pref_type;
    
};

#endif /* defined(__Assignment4__Passenger__) */

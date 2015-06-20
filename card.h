//
//  card.h
//  BillZeng.Summative
//
//  Created by Bill Zeng on 2015-06-13.
//  Copyright (c) 2015 Bill Zeng. All rights reserved.
//

#include <iostream>
using namespace std;
#ifndef BillZeng_Summative_card_h
#define BillZeng_Summative_card_h
class card{
public:
    int value;
    char suit;
    //constructors
    card();
    card(int a, char b);

    string toString();
    int suitvalue();
};

card::card(){
    value = 1;
    suit = 'S';
}

card::card(int a, char b){
    value = a;
    suit = b;
}
string card::toString() {
    string s = "";

    if(value == 14)
        s += "A";

    else if(value > 1 && value < 10) {
        switch(value) {
            case 2:
                s += "2";
                break;
            case 3:
                s += "3";
                break;
            case 4:
                s += "4";
                break;
            case 5:
                s += "5";
                break;
            case 6:
                s += "6";
                break;
            case 7:
                s += "7";
                break;
            case 8:
                s += "8";
                break;
            case 9:
                s += "9";
                break;
        }
    }

    else {
        switch(value) {
            case 10:
                s += "T";
                break;
            case 11:
                s += "J";
                break;
            case 12:
                s += "Q";
                break;
            case 13:
                s += "K";
                break;
        }
    }

    s += suit;

    return s;
}

int card::suitvalue(){
    if(suit=='S')
    {
        return 4;
    }
    if(suit=='H')
    {
        return 3;
    }
    if(suit=='C')
    {
        return 2;
    }
    if(suit=='D')
    {
        return 1;
    }
return 0;
}
#endif

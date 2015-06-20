//
//  deck.h
//  BillZeng.Summative
//
//  Created by Bill Zeng on 2015-06-13.
//  Copyright (c) 2015 Bill Zeng. All rights reserved.
//

#include "card.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#ifndef BillZeng_Summative_deck_h
#define BillZeng_Summative_deck_h
class deck{
public:
    vector<card> c;
    deck();
    void shuffle();
    card draw();
};

deck::deck() {
    char s;
    card temp;

    s = 'S';
    temp.suit = s;
    for(int i = 2; i <= 14; i++) {
        temp.value = i;
        c.push_back(temp);
    }

    s = 'H';
    temp.suit = s;
    for(int i = 2; i <= 14; i++) {
        temp.value = i;
        c.push_back(temp);
    }

    s = 'D';
    temp.suit = s;
    for(int i = 2; i <= 14; i++) {
        temp.value = i;
        c.push_back(temp);
    }

    s = 'C';
    temp.suit = s;
    for(int i = 2; i <= 14; i++) {
        temp.value = i;
        c.push_back(temp);
    }

    shuffle();
}

card deck::draw() {
    card s = c.front();
    c.push_back(c.front());
    c.erase(c.begin());
    return s;
}

void deck::shuffle() {

    srand(time(NULL));

    int j;
    card t;
    for(int i = 51; i >= 1; i--) {
        j = rand() % (i+1);
        t = c[i];
        c[i] = c[j];
        c[j] = t;
    }
}
#endif

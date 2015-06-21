//
//  Multiplayer.h
//  BillZeng.Pokergame
//
//  Created by Bill Zeng on 2015-06-20.
//  Copyright (c) 2015 Bill Zeng. All rights reserved.
//

#include "card.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#ifndef BillZeng_Pokergame_Multiplayer_h
#define BillZeng_Pokergame_Multiplayer_h
class player{
public:
    int money;
    int bet;
    string playername;
    bool check;
    bool fold;
    vector<card> p;
    
    player(int startingmoney, string pname);
    
    vector<card> getvector();
    void getcards();
    void vectorclear();
    void addcard(card c);
};

player::player(int startingmoney, string pname)
{
    money = startingmoney;
    playername = pname;
    bet = 0;
    check = false;
    fold = false;
}

vector<card> player::getvector()
{
    return p;
}

void player::getcards()
{
    for(int i = 0; i < p.size(); i++)
    {
        cout << p[i].toString() << " ";
    }
}
void player::addcard(card c)
{
    p.push_back(c);
}
void player::vectorclear()
{
    p.clear();
}

#endif

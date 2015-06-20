//
//  poker.h
//  BillZeng.Summative
//
//  Created by Bill Zeng on 2015-06-14.
//  Copyright (c) 2015 Bill Zeng. All rights reserved.
//
#include "card.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#ifndef BillZeng_Summative_poker_h
#define BillZeng_Summative_poker_h
class ai{
public:
    vector<card> cpu;
    int money;
    int ainumber;
    bool callif;
ai(int smoney, int num);
vector<card> getvector();
void getcards();
void vectorclear();
void addcard(card c);
void subtract(int sub);
void setcallif(bool call);
int bet(double p);
bool call(int p, int p2);
bool fold(int p);
};

ai::ai(int smoney,int num)
{
    money = smoney;
    ainumber = num;
    vector<card> cpu;
}
void ai::vectorclear()
{
    cpu.clear();
}
void ai::setcallif(bool call)
{
    callif = call;
}
void ai::subtract(int sub)
{
    money -= sub;
}
void ai::getcards()
{
    for(int i = 0; i < cpu.size(); i++)
    {
        cout << cpu[i].toString() << " ";
    }
}
void ai::addcard(card c)
{
    cpu.push_back(c);
}
vector<card> ai::getvector()
{
    return cpu;
}
int ai::bet(double p)
{
    srand(time(NULL));
    int random = rand()%12;
    if(random == 1)
    {
        return money;
    }
    else if(random < 4)
    {
        double a = random%10;
        a = a/10;
        return money*a;
    }
    if(p < 20)
    {
        return 0;
    }
    else
    {
        if(money > 200)
        {
            if(p < 40 and money > 500)
            {
                return money*0.1;
            }
            else if(p < 60 and money > 300)
            {
                return money*0.1;
            }
            else if(p < 80)
            {
                return money*0.2;
            }
            else if(p < 120)
            {
                return money*0.3;
            }
        }
        else if(p < 160)
        {
            return money*0.4;
        }
        else if(p < 180)
        {
            return money*0.5;
        }
        else if(p < 200)
        {
            return money;
        }

    }
return 0;
}
bool ai::call(int p, int p2)
{
    srand(time(NULL));
    if(p >= p2)
    {
        if(rand()%10 > 2)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if(rand()%7 > 2)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return true;
}
bool ai::fold(int p)
{
    if(p < 7)
    {
        return true;
    }
    return false;
}
#endif

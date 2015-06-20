//
//  main.cpp
//  BillZeng.Summative
//
//  Created by Bill Zeng on 2015-06-14.
//  Copyright (c) 2015 Bill Zeng. All rights reserved.
//

#include "card.h"
#include "poker.h"
#include "deck.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
vector<card> hand(vector<card> player, vector<card> comcards)
{
    int points;
    vector<card> p;
    vector<card> highestp;
    //creating a vector of all cards
    for(int i = 0; i < player.size(); i++)
    {
        p.push_back(player[i]);
    }
    for(int i = 0; i < comcards.size(); i++)
    {
        p.push_back(comcards[i]);
    }
    //creating a vector of all cards
    //sorting from high to low by value
    for(int i = 0; i < p.size()-1; i++)
    {
        card temp = p[i];
        for(int j = i+1; j < p.size(); j++)
        {
            if(p[i].value < p[j].value)
            {
                p[i] = p[j];
                p[j] = temp;
                temp = p[i];
            }
            else if(p[i].value == p[j].value and p[i].suitvalue() < p[j].suitvalue())
            {
                p[i] = p[j];
                p[j] = temp;
                temp = p[i];
            }
        }
    }
    //sorting from high to low by value
    //high card 0
    points = p[0].value;
    highestp.push_back(p[0]);
    //high card 0
    //one pair 20
    while(1)
    {
        for(int i = 0; i < p.size()-1; i++)
        {
            if(p[i].value==p[i+1].value)
            {
                points = 20+p[i].value;
                highestp.clear();
                highestp.push_back(p[i]);
                highestp.push_back(p[i+1]);
                break;
            }
        }
        break;
    }
    //one pair 20
    //two pair 40
    while(1)
    {
        for(int i = 0; i < p.size()-1; i++)
        {
            for(int j = i+2; j < p.size()-3; j++)
            {
                if(p[i].value==p[i+1].value and p[j].value==p[j+1].value)
                {
                    points = 40+p[i].value;
                    highestp.clear();
                    highestp.push_back(p[i]);
                    highestp.push_back(p[i+1]);
                    highestp.push_back(p[j]);
                    highestp.push_back(p[j+1]);
                    break;
                }
            }
        }
        break;
    }
    //two pair 40
    //three of a kind 60
    while(1)
    {
        for(int i = 0; i < p.size()-2; i++)
        {
            if(p[i].value==p[i+1].value and p[i].value==p[i+2].value)
            {
                points = 60+p[i].value;
                highestp.clear();
                highestp.push_back(p[i]);
                highestp.push_back(p[i+1]);
                highestp.push_back(p[i+2]);
                //full house 120
                for(int j = 0; j < p.size()-1; j++)
                {
                    if(p[j].value == p[j+1].value)
                    {
                        if(p[j].value != highestp[0].value)
                        {
                            points += 60;
                            highestp.clear();
                            highestp.push_back(p[i]);
                            highestp.push_back(p[i+1]);
                            break;
                        }
                    }
                }
                //full house 120
                break;
            }
        }
        break;
    }
    //three of a kind 60
    //straight 80
    //delete all duplicates optimally
    vector<card> p2 = p;
    int suitcount[4] = {0};
    string suits = "SHCD";
    for(int i = 0; i < p2.size(); i++)
    {
        if(p2[i].suit == 'S')
        {
            suitcount[0]++;
        }
        if(p2[i].suit == 'H')
        {
            suitcount[1]++;
        }
        if(p2[i].suit == 'C')
        {
            suitcount[2]++;
        }
        if(p2[i].suit == 'D')
        {
            suitcount[3]++;
        }
    }
    for(int i = 0; i < p2.size()-1; i++)
    {
        if(p2[i].value == p2[i+1].value)
        {
            if(suitcount[0] >= 5 or suitcount[1] >= 5 or suitcount[2] >= 5 or suitcount[3] >= 5)
            {
                for(int j = 0; j < 4; j++)
                {
                    if(suitcount[j] >= 5)
                    {
                        if(p2[i].suit == suits[j])
                        {
                            p2.erase(p2.begin()+i+1);
                        }
                        else if(p2[i+1].suit == suits[j])
                        {
                            p2.erase(p2.begin()+i);
                        }
                        else if(p2[i].suit != suits[j] and p2[i+1].suit != suits[j])
                        {
                            p2.erase(p2.begin()+i+1);
                        }
                    }
                }
            }
            else
            {
                p2.erase(p2.begin()+i+1);
            }
        }
    }
    //delete all duplicates optimally
    //check for 5 4 3 2 A
    while(1)
    {
        if(p2.size() > 4)
        {
            for(int i = 0; i < p2.size()-3; i++)
            {
                if(p2[i].value == 5 and p2[i+1].value == 4 and p2[i+2].value == 3 and p2[i+3].value == 2 and p2[0].value == 14)
                {
                    points = 80+p2[i].value;
                    highestp.clear();
                    highestp.push_back(p2[i]);
                    highestp.push_back(p2[i+1]);
                    highestp.push_back(p2[i+2]);
                    highestp.push_back(p2[i+3]);
                    highestp.push_back(p2[0]);
                    //straight flush 160
                    if(highestp[0].suit == highestp[1].suit and highestp[0].suit == highestp[2].suit and highestp[0].suit == highestp[3].suit and highestp[0].suit == highestp[4].suit)
                    {
                        points += 80;
                    }
                    //straight flush 160
                    break;
                }
            }
        }
        break;
    }
    //check for 5 4 3 2 A
    //check for the rest of the possibilities
    while(1)
    {
        if(p2.size() > 4)
        {
            for(int i = 0; i < p2.size()-4; i++)
            {
                if(p2[i].value == p2[i+1].value+1 and p2[i].value == p2[i+2].value+2 and p2[i].value == p2[i+3].value+3 and p2[i].value == p2[i+4].value+4)
                {
                    points = 80+p2[i].value;
                    highestp.clear();
                    highestp.push_back(p2[i]);
                    highestp.push_back(p2[i+1]);
                    highestp.push_back(p2[i+2]);
                    highestp.push_back(p2[i+3]);
                    highestp.push_back(p2[i+4]);
                    //straight flush 160
                    if(highestp[0].suit == highestp[1].suit and highestp[0].suit == highestp[2].suit and highestp[0].suit == highestp[3].suit and highestp[0].suit == highestp[4].suit)
                    {
                        points += 80;
                        //royal flush 180
                        if(highestp[0].value == 14 and highestp[1].value == 13 and highestp[2].value == 12 and highestp[3].value == 11 and highestp[4].value == 10)
                        {
                            points += 20;
                        }
                        //royal flush 180
                    }
                    //straight flush 160
                    break;
                }
            }
        }
        break;
    }
    //check for the rest of the possibilities
    //straight 80
    //flush 100
    vector<card> p3 = p;
    //sorting from high to low by suits
    for(int i = 0; i < p3.size()-1; i++)
    {
        card temp = p3[i];
        for(int j = i+1; j < p3.size(); j++)
        {
            if(p3[i].suitvalue() < p3[j].suitvalue())
            {
                p3[i] = p3[j];
                p3[j] = temp;
                temp = p3[i];
            }
            else if(p3[i].suitvalue() == p3[j].suitvalue() and p3[i].value < p3[j].value)
            {
                p3[i] = p3[j];
                p3[j] = temp;
                temp = p3[i];
            }
        }
    }
    //sorting from high to low by suits
    while(1)
    {
        for(int i = 0; i < p3.size()-4; i++)
        {
            if(p3[i].suit == p3[i+1].suit and p3[i].suit == p3[i+2].suit and p3[i].suit == p3[i+3].suit and p3[i].suit == p3[i+4].suit)
            {
                if(points < 100)
                {
                    points = 100+p3[i].value;
                    highestp.clear();
                    highestp.push_back(p3[i]);
                    highestp.push_back(p3[i+1]);
                    highestp.push_back(p3[i+2]);
                    highestp.push_back(p3[i+3]);
                    highestp.push_back(p3[i+4]);
                    break;
                }
            }
        }
        break;
    }
    //flush 100
    //four of a kind 140
    for(int i = 0; i < p.size() - 3; i++)
    {
        if(p[i].value==p[i+1].value and p[i].value==p[i+2].value and p[i].value == p[i+3].value)
        {
            points = 140 + p[i].value;
            highestp.clear();
            highestp.push_back(p[i]);
            highestp.push_back(p[i+1]);
            highestp.push_back(p[i+2]);
            highestp.push_back(p[i+3]);
        }
    }
    //four of a kind 140
    return highestp;
}


int points(vector<card> player, vector<card> comcards)
{
    int points;
    vector<card> p;
    vector<card> highestp;
    //creating a vector of all cards
    for(int i = 0; i < player.size(); i++)
    {
        p.push_back(player[i]);
    }
    for(int i = 0; i < comcards.size(); i++)
    {
        p.push_back(comcards[i]);
    }
    //creating a vector of all cards
    //sorting from high to low by value
    for(int i = 0; i < p.size()-1; i++)
    {
        card temp = p[i];
        for(int j = i+1; j < p.size(); j++)
        {
            if(p[i].value < p[j].value)
            {
                p[i] = p[j];
                p[j] = temp;
                temp = p[i];
            }
            else if(p[i].value == p[j].value and p[i].suitvalue() < p[j].suitvalue())
            {
                p[i] = p[j];
                p[j] = temp;
                temp = p[i];
            }
        }
    }
    //sorting from high to low by value
    //high card 0
    points = p[0].value;
    highestp.push_back(p[0]);
    //high card 0
    //one pair 20
    while(1)
    {
        for(int i = 0; i < p.size()-1; i++)
        {
            if(p[i].value==p[i+1].value)
            {
                points = 20+p[i].value;
                highestp.clear();
                highestp.push_back(p[i]);
                highestp.push_back(p[i+1]);
                break;
            }
        }
        break;
    }
    //one pair 20
    //two pair 40
    while(1)
    {
        for(int i = 0; i < p.size()-1; i++)
        {
            for(int j = i+2; j < p.size()-3; j++)
            {
                if(p[i].value==p[i+1].value and p[j].value==p[j+1].value)
                {
                    points = 40+p[i].value;
                    highestp.clear();
                    highestp.push_back(p[i]);
                    highestp.push_back(p[i+1]);
                    highestp.push_back(p[j]);
                    highestp.push_back(p[j+1]);
                    break;
                }
            }
        }
        break;
    }
    //two pair 40
    //three of a kind 60
    while(1)
    {
        for(int i = 0; i < p.size()-2; i++)
        {
            if(p[i].value==p[i+1].value and p[i].value==p[i+2].value)
            {
                points = 60+p[i].value;
                highestp.clear();
                highestp.push_back(p[i]);
                highestp.push_back(p[i+1]);
                highestp.push_back(p[i+2]);
                //full house 120
                for(int j = 0; j < p.size()-1; j++)
                {
                    if(p[j].value == p[j+1].value)
                    {
                        if(p[j].value != highestp[0].value)
                        {
                            points += 60;
                            highestp.clear();
                            highestp.push_back(p[i]);
                            highestp.push_back(p[i+1]);
                            break;
                        }
                    }
                }
                //full house 120
                break;
            }
        }
        break;
    }
    //three of a kind 60
    //straight 80
    //delete all duplicates optimally
    vector<card> p2 = p;
    int suitcount[4] = {0};
    string suits = "SHCD";
    for(int i = 0; i < p2.size(); i++)
    {
        if(p2[i].suit == 'S')
        {
            suitcount[0]++;
        }
        if(p2[i].suit == 'H')
        {
            suitcount[1]++;
        }
        if(p2[i].suit == 'C')
        {
            suitcount[2]++;
        }
        if(p2[i].suit == 'D')
        {
            suitcount[3]++;
        }
    }
    for(int i = 0; i < p2.size()-1; i++)
    {
        if(p2[i].value == p2[i+1].value)
        {
            if(suitcount[0] >= 5 or suitcount[1] >= 5 or suitcount[2] >= 5 or suitcount[3] >= 5)
            {
                for(int j = 0; j < 4; j++)
                {
                    if(suitcount[j] >= 5)
                    {
                        if(p2[i].suit == suits[j])
                        {
                            p2.erase(p2.begin()+i+1);
                        }
                        else if(p2[i+1].suit == suits[j])
                        {
                            p2.erase(p2.begin()+i);
                        }
                        else if(p2[i].suit != suits[j] and p2[i+1].suit != suits[j])
                        {
                            p2.erase(p2.begin()+i+1);
                        }
                    }
                }
            }
            else
            {
                p2.erase(p2.begin()+i+1);
            }
        }
    }
    //delete all duplicates optimally
    //check for 5 4 3 2 A
    while(1)
    {
        if(p2.size() > 4)
        {
            for(int i = 0; i < p2.size()-3; i++)
            {
                if(p2[i].value == 5 and p2[i+1].value == 4 and p2[i+2].value == 3 and p2[i+3].value == 2 and p2[0].value == 14)
                {
                    points = 80+p2[i].value;
                    highestp.clear();
                    highestp.push_back(p2[i]);
                    highestp.push_back(p2[i+1]);
                    highestp.push_back(p2[i+2]);
                    highestp.push_back(p2[i+3]);
                    highestp.push_back(p2[0]);
                    //straight flush 160
                    if(highestp[0].suit == highestp[1].suit and highestp[0].suit == highestp[2].suit and highestp[0].suit == highestp[3].suit and highestp[0].suit == highestp[4].suit)
                    {
                        points += 80;
                    }
                    //straight flush 160
                    break;
                }
            }
        }
        break;
    }
    //check for 5 4 3 2 A
    //check for the rest of the possibilities
    while(1)
    {
        if(p2.size() > 4)
        {
            for(int i = 0; i < p2.size()-4; i++)
            {
                if(p2[i].value == p2[i+1].value+1 and p2[i].value == p2[i+2].value+2 and p2[i].value == p2[i+3].value+3 and p2[i].value == p2[i+4].value+4)
                {
                    points = 80+p2[i].value;
                    highestp.clear();
                    highestp.push_back(p2[i]);
                    highestp.push_back(p2[i+1]);
                    highestp.push_back(p2[i+2]);
                    highestp.push_back(p2[i+3]);
                    highestp.push_back(p2[i+4]);
                    //straight flush 160
                    if(highestp[0].suit == highestp[1].suit and highestp[0].suit == highestp[2].suit and highestp[0].suit == highestp[3].suit and highestp[0].suit == highestp[4].suit)
                    {
                        points += 80;
                        //royal flush 180
                        if(highestp[0].value == 14 and highestp[1].value == 13 and highestp[2].value == 12 and highestp[3].value == 11 and highestp[4].value == 10)
                        {
                            points += 20;
                        }
                        //royal flush 180
                    }
                    //straight flush 160
                    break;
                }
            }
        }
        break;
    }
    //check for the rest of the possibilities
    //straight 80
    //flush 100
    vector<card> p3 = p;
    //sorting from high to low by suits
    for(int i = 0; i < p3.size()-1; i++)
    {
        card temp = p3[i];
        for(int j = i+1; j < p3.size(); j++)
        {
            if(p3[i].suitvalue() < p3[j].suitvalue())
            {
                p3[i] = p3[j];
                p3[j] = temp;
                temp = p3[i];
            }
            else if(p3[i].suitvalue() == p3[j].suitvalue() and p3[i].value < p3[j].value)
            {
                p3[i] = p3[j];
                p3[j] = temp;
                temp = p3[i];
            }
        }
    }
    //sorting from high to low by suits
    while(1)
    {
        for(int i = 0; i < p3.size()-4; i++)
        {
            if(p3[i].suit == p3[i+1].suit and p3[i].suit == p3[i+2].suit and p3[i].suit == p3[i+3].suit and p3[i].suit == p3[i+4].suit)
            {
                if(points < 100)
                {
                    points = 100+p3[i].value;
                    highestp.clear();
                    highestp.push_back(p3[i]);
                    highestp.push_back(p3[i+1]);
                    highestp.push_back(p3[i+2]);
                    highestp.push_back(p3[i+3]);
                    highestp.push_back(p3[i+4]);
                    break;
                }
            }
        }
        break;
    }
    //flush 100
    //four of a kind 140
    for(int i = 0; i < p.size() - 3; i++)
    {
        if(p[i].value==p[i+1].value and p[i].value==p[i+2].value and p[i].value == p[i+3].value)
        {
            points = 140 + p[i].value;
            highestp.clear();
            highestp.push_back(p[i]);
            highestp.push_back(p[i+1]);
            highestp.push_back(p[i+2]);
            highestp.push_back(p[i+3]);
        }
    }
    //four of a kind 140
    return points;
}




int singleplayer(int startingmoney,int bigblind,int smallblind,int players)
{
    srand(time(NULL));
    //intro
    cout << "Starting Money: " << startingmoney << endl;
    cout << "Big Blind: " << bigblind << endl;
    cout << "Small Blind: " << smallblind << endl;
    cout << "Number of Computer Players: " << players << endl;
    cout << "Game is starting... Press anything to start" << endl;
    int uselessthing;
    cin >> uselessthing;
    //end of intro
    //vectors for the player, cpu and community cards
    vector<card> player;
    vector<ai> cpu;
    vector<card> communitycards;
    for(int i = 0; i < players; i++)
    {
        ai temp(startingmoney, i+1);
        cpu.push_back(temp);
    }
    //deck
    deck d;
    //vectors and others for game aspects
    int bet;
    int game;
    int turnorriver = 0;
    int pot = 0;
    int money = startingmoney;
    int blinds = rand()%(players+1);
    vector<int> bets;
    vector<int> point;
    vector<bool> check;
    vector<bool> fold;
    for(int i = 0; i < players+1; i++)
    {
        bets.push_back(0);
        fold.push_back(false);
        check.push_back(false);
    }
    while(1)
    {
        while(1)
        {
        if(money <= 0)
        {
            cout << "You have lost!" << endl;
            return 0;
        }
        for(int i = 0; i < cpu.size(); i++)
        {
            if(cpu[i].money <= 0)
            {
                cout << "CPU " << cpu[i].ainumber << " is out!" << endl;
                cpu.erase(cpu.begin()+i);
                point.erase(point.begin()+i+1);
                bets.erase(bets.begin()+i+1);
                check.erase(check.begin()+i+1);
                fold.erase(fold.begin()+i+1);
            }
        }
        if(cpu.size()==0)
        {
            cout << "Congratulations! You win!" << endl;
            return 1;
        }
        for(int i = 0; i < cpu.size()+1; i++)
        {
            bet = 0;
            pot = 0;
            bets[i] = 0;
            fold[i] = false;
            check[i] = false;
        }
        //deal hole cards for the player
        player.clear();
        for(int i = 0; i < 2; i++)
        {
            player.push_back(d.draw());
        }
        //deal community cards
        communitycards.clear();
        for(int i = 0; i < 3; i++)
        {
            communitycards.push_back(d.draw());
        }
        //deal hole cards for the ai
        for(int i = 0; i < cpu.size(); i++)
        {
            cpu[i].vectorclear();
            for(int j = 0; j < 2; j++)
            {
                cpu[i].addcard(d.draw());
            }
        }
        for(int i = 0; i < cpu.size(); i++)
        {
            int a = points(cpu[i].getvector(), communitycards);
            int b = points(player, communitycards);
            bool c = cpu[i].call(a,b);
            cpu[i].setcallif(c);
        }
        if(blinds == 0)
        {
            int playerbet;
            int cpubet;
            cout << "You are the big blind (Automatically have to put in " << bigblind << "$)" << endl;
            cout << "CPU " << cpu[0].ainumber << " is the small blind (Automatically have to put in " << smallblind << "S)" << endl << endl;
            if(money < bigblind)
            {
                playerbet = money;
                money -= playerbet;
            }
            else
            {
                playerbet = bigblind;
                money -= bigblind;
            }
            if(cpu[0].money < smallblind)
            {
                cpubet = cpu[0].money;
                cpu[0].money -= cpubet;
            }
            else
            {
                cpubet = smallblind;
                cpu[0].money -= smallblind;
            }
            bet = bigblind;
            pot += playerbet;
            pot += cpubet;
            bets[0] += playerbet;
            bets[1] += cpubet;
            blinds++;
        }
        else if(blinds == cpu.size())
        {
            int playerbet;
            int cpubet;
            cout << "CPU " << cpu[cpu.size()].ainumber << " is the big blind (Automatically have to put in " << bigblind << "S)" << endl;
            cout << "You are the small blind (Automatically have to put in " << smallblind << "$)" << endl << endl;
            if(cpu[cpu.size()].money < bigblind)
            {
                cpubet = cpu[cpu.size()].money;
                cpu[cpu.size()].money -= playerbet;
            }
            else
            {
                cpubet = bigblind;
                cpu[cpu.size()].money -= bigblind;
            }
            if(money < smallblind)
            {
                playerbet = money;
                money -= playerbet;
            }
            else
            {
                playerbet = smallblind;
                money -= smallblind;
            }
            bet = bigblind;
            pot += playerbet;
            pot += cpubet;
            bets[0] += playerbet;
            bets[cpu.size()] += cpubet;
            blinds = 0;
        }
        else
        {
            int aibet;
            int cpubet;
            cout << "CPU" << cpu[blinds-1].ainumber << " is the big blind (Automatically have to put in " << bigblind << "S)" << endl;
            cout << "CPU" << cpu[blinds].ainumber << " is the small blind (Automatically have to put in " << smallblind << "S)" << endl << endl;
            if(cpu[blinds-1].money < bigblind)
            {
                cpubet = cpu[blinds-1].money;
                cpu[blinds-1].money -= cpubet;
            }
            else
            {
                cpubet = bigblind;
                cpu[blinds-1].money -= bigblind;
            }
            if(cpu[blinds].money < smallblind)
            {
                aibet = cpu[blinds].money;
                cpu[blinds].money -= aibet;
            }
            else
            {
                aibet = smallblind;
                cpu[blinds].money -= smallblind;
            }
            bet = bigblind;
            pot += aibet;
            pot += cpubet;
            bets[blinds] += cpubet;
            bets[blinds+1] += aibet;
            blinds++;
        }
        if(money <= 0)
        {
            money = 0;
            cout << "You are now all in!" << endl;
        }
        for(int i = 0; i < cpu.size(); i++)
        {
            if(cpu[i].money <= 0)
            {
                 cout << "CPU " << cpu[i].ainumber << " is now all in!" << endl;
                 cpu[i].money = 0;
            }
        }
        cout << "The dealer deals a new hand" << endl;
        int turn;
        if(cpu.size() == 1)
        {
            turn = blinds;
        }
        else
        {
            turn = blinds+1;
            if(turn > cpu.size())
            {
                turn = 0;
            }
        }
        game = 1;
        while(game == 1)
        {
            if(turn == 0)
            {
                if(fold[0] == true)
                {
                    cout << "You have folded" << endl;
                    turn++;
                }
                else
                {
                if(check[0] == false)
                {
                cout << "It is your turn, what do you want to do?" << endl;
                cout << "Community cards: ";
                for(int i = 0; i < communitycards.size(); i++)
                {
                    cout << communitycards[i].toString() << " ";
                }
                cout << endl << "Hole cards: ";
                for(int i = 0; i < player.size(); i++)
                {
                    cout << player[i].toString() << " ";
                }
                cout << endl;
                cout << "Your current money: " << money << endl;
                cout << "The current pot: " << pot << endl;
                cout << "Highest bet: " << bet;
                if(bets[0] == bet)
                {
                    cout << " (You are up to the current highest bet)" << endl;
                }
                else
                {
                    cout << endl << "Your current bet: " << bets[0] << endl;
                }
                if(money == 0)
                {
                    int choice;
                    cout << "You are all in!" << endl;
                    cout << "1.Check" << endl;
                    cout << "2.Fold" << endl;
                    cin >> choice;
                    if(choice == 1)
                    {
                        check[0] = true;
                        turn++;
                    }
                    if(choice == 2)
                    {
                        fold[0] = true;
                        turn++;
                    }
                }
                else if(bet > money)
                {
                    int choice;
                    cout << "1.Call (All in)" << endl;
                    cout << "2.Fold" << endl;
                    cin >> choice;
                    if(choice == 1)
                    {
                        int choice1;
                        cout << "Are you sure?" << endl;
                        cout << "1.Yes" << endl;
                        cout << "2.No" << endl;
                        cin >> choice1;
                        if(choice1 == 1)
                        {
                            pot += money;
                            bet += money;
                            bets[0] = bet;
                            money = 0;
                            turn++;
                        }
                    }
                    if(choice == 2)
                    {
                        fold[0] = true;
                        turn++;
                    }
                }
                else if(bets[0] < bet)
                {
                    int choice;
                    if(bet == bigblind)
                    {
                        cout << "1.Raise" << endl;
                    }
                    else
                    {
                        cout << "1.Re-raise" << endl;
                    }
                    cout << "2.Call" << endl;
                    cout << "3.All in" << endl;
                    cout << "4.Fold" << endl;
                    cin >> choice;
                    if(choice == 1)
                    {
                        int amount;
                        cout << "By how much:";
                        cin >> amount;
                        if(amount < 0)
                        {
                            cout << "Please enter a positive number" << endl;
                        }
                        else if(amount + (bet - bets[0]) > money)
                        {
                            cout << "Amount cannot be greater than your total money" << endl;
                        }
                        else
                        {
                            money -= amount + (bet - bets[0]);
                            pot += amount + (bet - bets[0]);
                            bet += amount;
                            bets[0] = bet;
                            turn++;
                            for(int i = 0; i < check.size(); i++)
                            {
                                check[i] = false;
                            }
                        }
                    }
                    if(choice == 2)
                    {
                        money -= bet - bets[0];
                        pot += bet - bets[0];
                        bets[0] = bet;
                        turn ++;
                    }
                    if(choice == 3)
                    {
                        int choice1;
                        cout << "Are you sure you want to go all in?" << endl;
                        cout << "1.Yes" << endl;
                        cout << "2.No" << endl;
                        cin >> choice1;
                        if(choice1 == 1)
                        {
                            pot += money;
                            bet += money;
                            bets[0] = bet;
                            money = 0;
                            turn++;
                            for(int i = 0; i < check.size(); i++)
                            {
                                check[i] = false;
                            }
                        }
                    }
                    else if(choice == 4)
                    {
                        fold[0] = true;
                        turn++;
                    }
                }
                //money already equal to the bet
                else if(bets[0] == bet)
                {
                    int choice;
                    cout << "1.Raise" << endl;
                    cout << "2.Check" << endl;
                    cout << "3.All in" << endl;
                    cout << "4.Fold" << endl;
                    cin >> choice;
                    if(choice == 1)
                    {
                        int amount;
                        cout << "By how much:";
                        cin >> amount;
                        if(amount < 0)
                        {
                            cout << "Please enter a positive number" << endl;
                        }
                        else if(amount > money)
                        {
                            cout << "Amount cannot be greater than your total money" << endl;
                        }
                        else
                        {
                            money -= amount;
                            pot += amount;
                            bet += amount;
                            bets[0] = bet;
                            turn++;
                            for(int i = 0; i < check.size(); i++)
                            {
                                check[i] = false;
                            }
                        }
                    }
                    if(choice == 2)
                    {
                        check[0] = true;
                        turn ++;
                    }
                    if(choice == 3)
                    {
                        int choice1;
                        cout << "Are you sure you want to go all in?" << endl;
                        cout << "1.Yes" << endl;
                        cout << "2.No" << endl;
                        cin >> choice1;
                        if(choice1 == 1)
                        {
                            pot += money;
                            bet += money;
                            bets[0] = bet;
                            money = 0;
                            turn ++;
                            for(int i = 0; i < check.size(); i++)
                            {
                                check[i] = false;
                            }
                        }
                    }
                    if(choice == 4)
                    {
                        fold[0] = true;
                        turn++;
                    }
                }
                }
                else
                {
                    turn++;
                }
                }
            }
            else
            {
                if(cpu[turn-1].money <= 0)
                {
                    cout << "CPU " << cpu[turn-1].ainumber << " is all in!" << endl;
                }
                else if(fold[turn] == false)
                {
                    int raise = cpu[turn-1].bet(points(cpu[turn-1].getvector(), communitycards));
                    if(bet < (cpu[turn-1].money*0.3) and rand()%10 < 3 and raise > 0 and cpu[turn-1].money > raise + (bet-bets[turn]))
                    {
                        cout << "CPU " << cpu[turn-1].ainumber << " raises the pot by " << raise << "$" << endl;
                        pot += raise + (bet - bets[turn]);
                        bets[turn] += raise +(bet - bets[turn]);
                        bet = bets[turn];
                        check[0] = false;
                        for(int i = 0; i < check.size(); i++)
                        {
                            check[i] = false;
                        }
                    }
                    else if(bets[turn] < bet and cpu[turn-1].callif == true)
                    {
                        if(bet > (cpu[turn-1].money*0.6))
                        {
                            if(rand()%8 > 5)
                            {
                                cout << "CPU " << cpu[turn-1].ainumber << " calls" << endl;
                                int aicall = bet - bets[turn];
                                if(aicall > cpu[turn].money)
                                {
                                    aicall = cpu[turn].money;
                                }
                                cpu[turn].money -= aicall;
                                pot += aicall;
                                bets[turn] = bet;
                            }
                            else
                            {
                                cout << "CPU " << cpu[turn-1].ainumber << " folds" << endl;
                                fold[turn] = true;
                            }
                        }
                        else
                        {
                            cout << "CPU " << cpu[turn-1].ainumber << " calls" << endl;
                            int aicall = bet - bets[turn];
                            if(aicall > cpu[turn].money)
                            {
                                aicall = cpu[turn].money;
                            }
                            cpu[turn].money -= aicall;
                            pot += aicall;
                            bets[turn] = bet;
                        }
                    }
                    else if(bets[turn] < bet and cpu[turn-1].callif == false)
                    {
                        if(rand()%7 > 4)
                        {
                            cout << "CPU " << cpu[turn-1].ainumber << " calls" << endl;
                            int aicall = bet - bets[turn];
                            if(aicall > cpu[turn].money)
                            {
                                aicall = cpu[turn].money;
                            }
                            cpu[turn].money -= aicall;
                            pot += aicall;
                            bets[turn] = bet;
                        }
                        else
                        {
                            cout << "CPU " << cpu[turn-1].ainumber << " folds" << endl;
                            fold[turn] = true;
                        }
                    }
                    else if(bets[turn] == bet)
                    {
                        cout << "CPU " << cpu[turn-1].ainumber << " checks" << endl;
                        check[turn] = true;
                    }
                    else
                    {
                        cout << "CPU " << cpu[turn-1].ainumber << " folds" << endl;
                        fold[turn] = true;
                    }
                }
                else
                {
                    cout << "CPU " << cpu[turn-1].ainumber << " has folded" << endl;
                }
                int nextcard = 0;
                for(int i = 0; i < cpu.size()+1; i++)
                {
                    if(check[i] == true or fold[i] == true)
                    {
                        nextcard++;
                    }
                }
                int folds = 0;
                for(int i = 0; i < cpu.size()+1; i++)
                {
                    if(fold[i] == true)
                    {
                        folds++;
                    }
                }
                if(nextcard == cpu.size()+1 or folds == cpu.size())
                {
                    point.clear();
                    if(communitycards.size() == 5 or folds == cpu.size())
                    {
                        if(fold[0] == false)
                        {
                            point.push_back(points(player, communitycards));
                        }
                        for(int i = 0; i < cpu.size(); i++)
                        {
                            if(fold[i+1] == false)
                            {
                                 point.push_back(points(cpu[i].getvector(), communitycards));
                            }
                        }
                        if(point.size() > 1)
                        {
                            for(int i = 0; i < point.size()-1; i++)
                            {
                                int temp = point[i];
                                for(int j = i+1; j < point.size(); j++)
                                {
                                    if(point[i] < point[j])
                                    {
                                        point[i] = point[j];
                                        point[j] = temp;
                                        temp = point[i];
                                    }
                                }
                            }
                        }
                        int winners = 1;
                        for(int i = 0; i < point.size()-1; i++)
                        {
                            if(point[i] == point[i+1])
                            {
                                winners++;
                            }
                        }
                        vector<int> thewinners;
                        thewinners.clear();
                        for(int i = 0; i < cpu.size()+1; i++)
                        {
                            if(i == 0)
                            {
                                if(fold[0] == false)
                                {
                                    if(points(player, communitycards) == point[0])
                                    {
                                        cout << "You ";
                                        thewinners.push_back(i);
                                        if(point[0] == point[1])
                                        {
                                            cout << "and ";
                                        }
                                    }
                                }
                            }
                            else if(points(cpu[i-1].getvector(), communitycards) == point[0] and fold[i] == false)
                            {
                                cout << "CPU " << cpu[i-1].ainumber << " ";
                                thewinners.push_back(i);
                            }
                        }
                        cout << "has won the pot! (" << pot << ")" << endl << "It will be given accordingly" << endl;
                        cout << "The winning hand was: ";
                        vector<card> winhand;
                        winhand.clear();
                        for(int i = 0; i < point.size(); i++)
                        {
                            if(i == 0)
                            {
                                if(points(player, communitycards) == point[0])
                                {
                                    winhand = hand(player,communitycards);
                                    break;
                                }
                            }
                            else
                            {
                                if(points(cpu[i-1].getvector(), communitycards) == point[0])
                                {
                                    winhand = hand(cpu[i-1].getvector(),communitycards);
                                    break;
                                }
                            }
                        }
                        for(int i = 0; i < winhand.size(); i++)
                        {
                            cout << winhand[i].toString() << " ";
                        }
                        cout << endl;
                        for(int i = 0; i < thewinners.size(); i++)
                        {
                            if(i == 0 and thewinners[i] == 0)
                            {
                                money += pot/winners;
                            }
                            else
                            {
                                cpu[thewinners[i]-1].money += pot/winners;
                            }
                        }
                        game = 0;
                    }
                    else if(turnorriver%2 == 1)
                    {
                        cout << "The dealer has put out the river" << endl;
                        communitycards.push_back(d.draw());
                        turnorriver++;
                    }
                    else
                    {
                        cout << "The dealer has put out the turn" << endl;
                        communitycards.push_back(d.draw());
                        turnorriver++;
                    }
                    for(int i = 0; i < bets.size(); i++)
                    {
                        check[i] = false;
                    }
                }
                if(turn == cpu.size())
                {
                    turn = 0;
                }
                else
                {
                    turn++;
                }
            }
        }
    }
        }
    return 0;
}




int main()
{
    //useful varibles
    int startingmoney = 1000;
    int bigblind = 50;
    int smallblind = 25;
    int players;
    int wins = 0;
    int loses = 0;
    while(1)
    {
        int option;
        cout << "Welcome to Poker!" << endl;
        cout << "1.Single-player" << endl;
        cout << "2.Multi-player" << endl;
        cout << "3.Settings and Info" << endl;
        cin >> option;
        if(option == 1)
        {
            cout << "How many computer players are there:";
            cin >> players;
            if(players > 0)
            {
                if(singleplayer(startingmoney,bigblind,smallblind,players)==0)
                {
                    loses++;
                }
                else
                {
                    wins++;
                }
            }
            else
            {
                cout << "You must enter a number higher than 0" << endl;
            }

        }
        if(option == 2)
        {
            cout << "How many players are there:";
            cin >> players;
            //multiplayer(startingmoney,bigblind,smallblind,players);
        }
        if(option == 3)
        {
            int option1;
            cout << endl << "Settings and info" << endl;
            cout << "1.Game Info" << endl;
            cout << "2.Change Starting Money (Current:" << startingmoney << ")" << endl;
            cout << "3.Change Blinds (Current Small Blind:" << smallblind << ", Current Big Blind:" << bigblind << ")" << endl;
            cin >> option1;
            if(option1==1)
            {
                cout << "Each player starts with two hole cards. There are three rounds of community cards. These are dealt face up, for every player to use, with betting after each round." << endl << endl;
                cout << "The best 5-card hand using any combination of the five community cards and two hole cards wins." << endl << endl;
                cout << "Each new hand begins with a small blind, a big blind, and a round of betting." << endl << endl;
                cout << "Once the first round of betting is complete, the dealer then puts out the first three community cards, or 'the flop'. There is a round of betting." << endl << endl;
                cout << "The dealer then puts out the fourth community card or 'the turn'. There is a round of betting." << endl << endl;
                cout << "The dealer then puts out the fifth community card or 'the river'. There is a final round of betting." << endl << endl;
                cout << "After the last round of betting, the pot will be awarded to the person with best hand." << endl << endl;
                cout << "All suits are equal in poker." << endl << endl;
                cout << "These are the poker hand ranks, 1 being the best, and 10 being the worst" << endl << endl;
                cout << "10. High Card (Your highest card, only used when you dont have any other hands)" << endl << endl;
                cout << "9.One Pair (Two cards of the same rank)" << endl << endl;
                cout << "8.Two Pair (Two cards of the same rank together with another two cards of the same rank)" << endl << endl;
                cout << "7.Three of a kind (Any three cards of the same rank)" << endl << endl;
                cout << "6.Straight (Any five consecutive cards of different suits, aces can count as either a high(14) or a low(1) card)" << endl << endl;
                cout << "5.Flush (Any five cards of the same suit (not consecutive), the highest card of the five determines the rank of the flush)" << endl << endl;
                cout << "4.Full house (Any three cards of the same rank together with any two cards of the same rank)" << endl;
                cout << "3.Four of a kind (Any four cards of the same rank)" << endl << endl;
                cout << "2.Straight Flush (Any straight with all five cards of the same suit)" << endl << endl;
                cout << "1.Straight Flush (A straight from a ten to an ace with all five cards of the same suit)" << endl << endl;
                cout << "Player Info" << endl;
                cout << "Starting Money:" << startingmoney << endl;
                cout << "Big Blind:" << bigblind << endl;
                cout << "Small Blind:" << smallblind << endl;
                cout << "Loses:" << loses << endl;
                cout << "Wins:" << wins << endl << endl;
            }
            if(option1==2)
            {
                cout << "Current Starting Money:" << startingmoney << endl;
                cout << "New Starting Money:";
                cin >> startingmoney;
            }
            if(option1==3)
            {
                cout << "Current Big Blind:" << bigblind << " (The Small Blind is half the Big Blind)"<< endl;
                cout << "New Big Blind (preferably an even number):";
                cin >> bigblind;
                smallblind = bigblind/2;
            }
        }
    }
}


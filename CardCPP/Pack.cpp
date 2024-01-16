#include <cassert>
#include <iostream>
#include <array>
#include <string>
#include "Pack.hpp"
#include "Card.hpp"

using namespace std;



Pack::Pack(){
    int index = 0;
    for (int i = SPADES; i <= DIAMONDS; ++i)
    {
        for (int j = NINE; j <= ACE; ++j)
        {
            cards[index] = Card(static_cast<Rank> (j),static_cast<Suit> (i));
            ++index;
        }
    }
    next = 0;
}

Pack::Pack(std::istream& pack_input){
    Card tempCard = Card();
    int index = 0;
    while(pack_input >> tempCard){
        cards[index] = tempCard;
        ++index;
    }
    next = 0;
}

Card Pack::deal_one(){
    Card deltCard = cards[next];
    ++next;
    return deltCard;
}

void Pack::reset(){
    next = 0;
}

void Pack::shuffle(){
    for(int i = 0; i < 7; ++i){
        Card copy[24];
        for(int j = 0; j < 24; ++j){
            copy[j] = cards[j];
        }
        
        int moveBottom = 1;
        int moveTop = 12;

        for(int c = 0; c < 12; ++c){
            cards[c+moveBottom] = copy[c];
            ++moveBottom;
        }
        for(int c = 12; c < 24; ++c){
            cards[c-moveTop] = copy[c];
            --moveTop;
        }
    }
    reset();

}

bool Pack::empty() const{
   
    if(next == 24){
        return true;
    }

    else{
        return false;
    }


}
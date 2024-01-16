#include <cassert>
#include <iostream>
#include <array>
#include <string>
#include <vector>
#include "Card.hpp"
#include "Player.hpp"
#include <algorithm>

using namespace std;

class Human : public Player
{
private:
    string name;
    vector<Card> hand;

    void print_hand() const
    {
        for (size_t i = 0; i < hand.size(); ++i)
            cout << "Human player " << name << "'s hand: "
                 << "[" << i << "] " << hand[i] << "\n";
    }

public:
    Human(string name_in, vector<Card> handIn)
        : name(name_in), hand(handIn) {}

    Human(string name_in)
        : name(name_in){}

    const string &get_name() const override
    {
        return name;
    }

    void add_card(const Card &c) override
    {
        hand.push_back(c);
        sort(hand.begin(), hand.end());
    }

    bool make_trump(const Card &upcard, bool is_dealer,
                    int round, Suit &order_up_suit) const override
    {

        if (round == 1)
        {
            print_hand();

            cout << "Human player " << name << ", order up or \"pass\n";

            string decision;
            cin >> decision;

            if (decision != "pass")
            {
                order_up_suit = upcard.get_suit();
                return true;
            }
            else
            {
                return false;
            }
        }

        else if (round == 2)
        {
            cout << "Human player " << name << ", please enter a suit, or \"pass\n";

            string decision;
            cin >> decision;

            if (decision != "pass")
            {
                order_up_suit = string_to_suit(decision);
                return true;
            }
            else
            {
                return false;
            }
        }

        // else
        // {

        //     if (is_dealer == true)
        //     {
        //         Suit decCard;

        //         if (upcard.get_suit() == DIAMONDS)
        //         {
        //             Suit decCard = CLUBS;
        //         }

        //         else
        //         {
        //             Suit decCard = DIAMONDS;
        //         }

        //         string decision;
        //         cout << "Pick a suit to be the trump suit";

        //         while (decCard != upcard.get_suit())
        //         {
        //             cout << "Pick a suit other than the upcard ";
        //             cin >> decision;

        //             if (string_to_suit(decision) != upcard.get_suit())
        //             {
        //                 order_up_suit = string_to_suit(decision);
        //                 decCard = upcard.get_suit();
        //                 return true;
        //             }

        //             else
        //             {

        //             }
        //         }
            //}
        //}
        else{
            return false;
        }
    }
    void add_and_discard(const Card &upcard) override{

        int pickCardInd;
        print_hand();
        cout << "Discard upcard: [-1]\n";

        cout << "Human player " << name << ", please select a card to discard:\n";

        cin >> pickCardInd;

       // hand.erase(hand.begin() + pickCardInd); 
        hand.at(pickCardInd) = upcard;


    }

    Card lead_card(Suit trump) override{
        int leadCardIn;
        cout << "Human player " << name << " please select a card:"<< endl;
        cin >> leadCardIn;
        Card leadCard =  hand.at(leadCardIn);
        hand.erase(hand.begin() + leadCardIn);
        return leadCard;
    }

   Card play_card(const Card &led_card, Suit trump) override{
        int playCardIn;
        cout << "Human player " << name << " please select a card:"<< endl;
        cin >> playCardIn;
        Card playCard =  hand.at(playCardIn);
        hand.erase(hand.begin() + playCardIn);
        return playCard;


   }

};


class SimplePlayer : public Player{

private:
    string name;
    vector<Card> simHand;

public:
    SimplePlayer(string name_in)
        : name(name_in) {}

    SimplePlayer(string name_in, vector<Card> simHand_in)
        : name(name_in), simHand(simHand_in) {}


    const string &get_name() const override{
        return name;
    }

    void add_card(const Card &c) override{

        simHand.push_back(c);

    }

    bool make_trump(const Card &upcard, bool is_dealer,
    int round, Suit &order_up_suit) const override{
        if (round == 1)
        {
            int cardSuitandFace = 0;
            for (int i = 0; i < MAX_HAND_SIZE; ++i)
            {

                if (simHand[i].get_suit() == upcard.get_suit() && (simHand[i].is_face_or_ace()))
                {
                    ++cardSuitandFace;
                }
                if(simHand[i].is_left_bower(upcard.get_suit())){
                    ++cardSuitandFace;
                }
            }

            if (cardSuitandFace >= 2){
                order_up_suit = upcard.get_suit();
                return true;
            }

            else{
                return false;
            }


        }
        if(round == 2){
            int sameColor = 0;
            Suit chosenSuit;
            
            if(is_dealer){
                order_up_suit = Suit_next(upcard.get_suit());
                return true;
            }
    
            for(int i = 0; i < MAX_HAND_SIZE; ++i){
                if(simHand[i].get_suit() == Suit_next(upcard.get_suit()) && simHand[i].is_face_or_ace()){
                    ++sameColor;
                    chosenSuit = simHand[i].get_suit();
                }
                if(simHand[i].is_left_bower(upcard.get_suit())){
                    ++sameColor;
                    chosenSuit = simHand[i].get_suit();
                }
            }
            if(sameColor >= 1){
                
                order_up_suit = chosenSuit;
                return true;
                
            }
            else{
                return false;
            }

        }
        else{
            return false;
        }
    }

    void add_and_discard(const Card &upcard) override{
        Card minCard = upcard;
        int minIndex = 0;
        for(int i = 0; i < MAX_HAND_SIZE; ++i){
            if(Card_less(simHand[i], minCard, upcard.get_suit())){
                minCard = simHand[i];
                minIndex = i;
            }
          
        }
        if(minCard != upcard){
            simHand.at(minIndex) = upcard;
        }
        else{

        }
    }


    Card lead_card(Suit trump) override{
        bool alltrumpCard = true;

        for(int i = 0; i < MAX_HAND_SIZE; ++i){
            if(simHand[i].get_suit() != trump){
                alltrumpCard =false;
                break;
            }
        }

        vector<bool> isTrump;

        for(int i = 0; i < MAX_HAND_SIZE; ++i){
            if(simHand[i].get_suit() == trump){
                isTrump.push_back(true);
            }
            else{
                isTrump.push_back(false);
            }

        }


        Card highestCard = simHand[0];
        int highcardIndex = 0;
        if(alltrumpCard == true){
            for(int i = 0; i < MAX_HAND_SIZE; ++i){
                if(Card_less(highestCard, simHand[i], trump)){
                    highestCard = simHand[i];
                    highcardIndex = i;
                }
            }
            Card playCard =  simHand[highcardIndex];
            simHand.erase(simHand.begin() + highcardIndex);
            return playCard;


        }

        else{

            int noTmaxIndex = 0;
            int firstFalse = 0;
            Card noTcard; //= simHand[0];
    
            for(int j = 0; j < MAX_HAND_SIZE; ++j){
                if(isTrump[j] == false && firstFalse == 0){
                    noTcard = simHand[j];
                    ++firstFalse;
                    noTmaxIndex = j;
                }

                else if(isTrump[j] == false){
                   if( simHand[j] > noTcard){
                    noTcard = simHand[j];
                    noTmaxIndex = j;
                   }
                }
            }
            Card playCard =  simHand[noTmaxIndex];
            simHand.erase(simHand.begin() + noTmaxIndex);
            return playCard;
            


        }

    }

    Card play_card(const Card &led_card, Suit trump) override{
        Card highestCard = simHand[0];
        int highestSuitCardIndex = 0;

        int minIndex = 0;
        Card minCard = simHand[0];

        bool followSuit = false;

        for(int i = 0; i < simHand.size(); ++i){
            if(simHand[i].get_suit() == led_card.get_suit() || 
            (trump == led_card.get_suit() && simHand[i].is_left_bower(trump))){
                followSuit = true;

                if(highestCard.get_suit() == simHand[i].get_suit() || 
                (trump == led_card.get_suit() && simHand[i].is_left_bower(trump))){
                    if(Card_less(highestCard, simHand[i], trump)){
                        highestSuitCardIndex = i;
                        highestCard = simHand[i];
                    }
                
                }

                else if(highestCard.is_left_bower(trump) && trump == led_card.get_suit()){
                    if(Card_less(highestCard, simHand[i], trump)){
                        highestSuitCardIndex = i;
                        highestCard = simHand[i];
                    }
                    else{
                        
                    }
                }

                else{
                        highestSuitCardIndex = i;
                        highestCard = simHand[i];
                    }
            }
            else if(simHand[i].get_suit() != led_card.get_suit()){

                if(Card_less(simHand[i], minCard, trump)){
                    minIndex = i;
                    minCard = simHand[i];
                }


            }
        }
        if(followSuit == true){
            Card playCard =  simHand[highestSuitCardIndex];
            simHand.erase(simHand.begin() + highestSuitCardIndex);
            return playCard;
        }
        else{
            Card playCard =  simHand[minIndex];
            simHand.erase(simHand.begin() + minIndex);
            return playCard;
        }

    }





};

ostream & operator<<(ostream &os, const Player &p)
{
    os << p.get_name();
    return os;
}

Player * Player_factory(const std::string &name, 
                        const std::string &strategy) {
  // We need to check the value of strategy and return 
  // the corresponding player type.
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new SimplePlayer(name);
  }
  // Repeat for each other type of Player
  if(strategy == "Human"){

    return new Human(name);
  }
  // Invalid strategy if we get here
  assert(false);
  return nullptr;
}
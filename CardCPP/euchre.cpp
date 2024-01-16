#include <cassert>
#include <iostream>
#include <array>
#include <string>
#include <vector>
#include "Card.hpp"
#include "Player.hpp"
#include "Pack.hpp"
#include <fstream>

using namespace std;

struct Even{
    int tricksWon = 0;
    int points = 0; 
    bool ordered_up = false;
    Player *evenplayer0;
    Player *evenplayer2;
};

struct Odd{
    int tricksWon = 0;
    int points = 0; 
    bool ordered_up = false;
    Player *oddplayer1;
    Player *oddplayer3;
};

class Game{
public:
    Game(bool shuffle_in, string points_in, istream &filename_in, vector <Player*> players_in){
        players[0] = players_in[0];
        teamEven.evenplayer0 = players_in[0];

        players[1] = players_in[1];
        teamOdd.oddplayer1 = players_in[1];
        
        players[2] = players_in[2];
        teamEven.evenplayer2 = players_in[2];
        
        players[3] = players_in[3];
        teamOdd.oddplayer3 = players_in[3];

        isShuffle = shuffle_in;
        pointsWin = stoi(points_in);
        pack = Pack(filename_in);
    }

    void play(){
        while(teamOdd.points < pointsWin && teamEven.points < pointsWin){
            cout << "Hand " << round-1 << endl;
            cout << players[3] << " deals" << endl;
            if(isShuffle){
                pack.shuffle();
            }
            else{
                pack.reset();
            }
            
            deal(pack, players);
            cout << upcard << " turned up" << endl;

            make_trump();

            play_hand();
            ++round;
        }

        if(teamOdd.points > teamEven.points){
            cout << teamOdd.oddplayer1 << " and ";
            cout << teamOdd.oddplayer3 << " win!" << endl;
        }
        else{
            cout << teamEven.evenplayer0 << " and ";
            cout << teamEven.evenplayer2 << " win!" << endl;
        }
    };
private:
    std::vector<Player*> players;
    int pointsWin;
    bool isShuffle;
    Pack pack;    
    Card upcard;
    Suit trump;
    Odd teamOdd;
    Even teamEven;
    int round;

    void deal2andAdd(Player *player_in, Pack pack_in){
        Card card1 = pack_in.deal_one();
        Card card2 = pack_in.deal_one();

        player_in->add_card(card1);
        player_in->add_card(card2);
    };

    void deal3andAdd(Player *player_in, Pack pack_in){

        Card card1 = pack_in.deal_one();
        Card card2 = pack_in.deal_one();
        Card card3 = pack_in.deal_one();

        player_in->add_card(card1);
        player_in->add_card(card2);
        player_in->add_card(card3);
    };

    void shuffle(bool isShuffle_in){
        if(isShuffle_in){
            pack.shuffle();
        }
    };

    void deal(Pack pack_in, vector<Player*> players_in){
        
        // first deal batch
            // deal3andAdd(players_in[(startDealerIndex+1)%4], pack_in);
            // deal2andAdd(players_in[(startDealerIndex+2)%4], pack_in);
            // deal3andAdd(players_in[(startDealerIndex+3)%4], pack_in);
            // deal2andAdd(players_in[(startDealerIndex+4)%4], pack_in);

            deal3andAdd(players_in[0], pack_in);
            deal2andAdd(players_in[1], pack_in);
            deal3andAdd(players_in[2], pack_in);
            deal2andAdd(players_in[3], pack_in);

        // second deal batch

            deal2andAdd(players_in[0], pack_in);
            deal3andAdd(players_in[1], pack_in);
            deal2andAdd(players_in[2], pack_in);
            deal3andAdd(players_in[3], pack_in);

        //deal upcard
        upcard = pack.deal_one();



    };
    void make_trump(){

        int trumpRound = 1;
        bool isDealerTrumpRound = false;
        bool trumpStatus = false;
        
        // first round 

        for(int i = 0; i < 4; ++i){
            trumpStatus = players[i] ->make_trump(upcard, isDealerTrumpRound, trumpRound, trump);
            if(trumpStatus){

                if(players[i] == teamOdd.oddplayer1 || players[i] == teamOdd.oddplayer3){
                    teamOdd.ordered_up = true;
                }

                else if(players[i] == teamEven.evenplayer0 || players[i] == teamEven.evenplayer2){
                    teamEven.ordered_up = true;
                }

                cout << players[i] << " orders up " << trump << endl;
                break;
            }

            else{
                cout << players[i] << " passes" << endl;
            }
        }
        ++trumpRound; 

        // round 2

        if (!trumpStatus){
            for (int j = 0; j < 4; ++j){
                if (j == 3){
                    isDealerTrumpRound = true;
                }

                trumpStatus = players[j]->make_trump(upcard, isDealerTrumpRound, trumpRound, trump);
                if(!trumpStatus){
                    cout << players[j] << " passes" << endl;
                }

                else{
                    
                    if(players[j] == teamOdd.oddplayer1 || players[j] == teamOdd.oddplayer3){
                        teamOdd.ordered_up = true;
                    }

                    else if(players[j] == teamEven.evenplayer0 || players[j] == teamEven.evenplayer2){
                        teamEven.ordered_up = true;
                    }

                    cout << players[j] << " orders up " << trump << endl;
                    break;
                }
            }
        }
    };



    void play_hand(){
        int leadPersonIndex = 0;
        leadPersonIndex = play_trick(leadPersonIndex);
        leadPersonIndex = play_trick(leadPersonIndex);
        leadPersonIndex = play_trick(leadPersonIndex);
        leadPersonIndex = play_trick(leadPersonIndex);
        leadPersonIndex = play_trick(leadPersonIndex);
        
        if(teamOdd.tricksWon > teamEven.tricksWon){
            if(teamOdd.ordered_up){
                if(teamOdd.tricksWon == 5){
                    teamOdd.points += 2;
                    cout << teamOdd.oddplayer1 << " and ";
                    cout << teamOdd.oddplayer3 << " win the hand" << endl;
                    cout << "march!" << endl;
                }

                else{
                    teamOdd.points += 1;
                    cout << teamOdd.oddplayer1 << " and ";
                    cout << teamOdd.oddplayer3 << " win the hand" << endl;
                }
            }
            
            else{
                teamOdd.points += 2;
                cout << teamOdd.oddplayer1 << " and ";
                cout << teamOdd.oddplayer3 << " win the hand" << endl;
                cout << "euchred!" << endl;
            }
        }

        else{
            if(teamEven.ordered_up){
                if(teamEven.tricksWon == 5){
                    teamEven.points += 2;
                    cout << teamEven.evenplayer0 << " and ";
                    cout << teamEven.evenplayer2 << " win the hand" << endl;
                    cout << "march!" << endl;
                }

                else{
                    teamEven.points += 1;
                    cout << teamEven.evenplayer0 << " and ";
                    cout << teamEven.evenplayer2 << " win the hand" << endl;
                }
            }
            
            else{
                teamEven.points += 2;
                cout << teamEven.evenplayer0 << " and ";
                cout << teamEven.evenplayer2 << " win the hand" << endl;
                cout << "euchred!" << endl;
            }
        }

        cout << teamEven.evenplayer0 << " and ";
        cout << teamEven.evenplayer2 << " have " << teamEven.points << " points" << endl;
        cout << teamOdd.oddplayer1 << " and ";
        cout << teamOdd.oddplayer3 << " have " << teamOdd.points << " points" << endl;

        teamOdd.tricksWon = 0;
        teamEven.tricksWon = 0;

        for(int i = 0; i < 4; ++i){
            vector<Player*> playerCopy = players;
            players[(i+3)%4] = playerCopy[i];
        }

    };

    int play_trick(int leadPersonIndexPlay){
        Card leadCardPlayed = players[leadPersonIndexPlay] -> lead_card(trump);
        Card maxCard = leadCardPlayed;
        Player *winner = players[0];
        int winnerInd;

        cout << leadCardPlayed << " led by " << players[leadPersonIndexPlay] << endl;
        for(int i = 1; i < 4; ++i){
            Card playedCard = players[(leadPersonIndexPlay+i)%4] -> play_card(leadCardPlayed, trump);
            cout << playedCard << " played by " << players[(leadPersonIndexPlay+i)%4] << endl;

            if(Card_less(maxCard,playedCard, leadCardPlayed, trump)){
                playedCard = maxCard;
                winner = players[(leadPersonIndexPlay+i)%4];
                winnerInd = (leadPersonIndexPlay+i)%4;
            }

            // cout << players[2] -> play_card(leadCardPlayed, trump) << " played by " << players[2] << endl;
            // cout << players[3] -> play_card(leadCardPlayed, trump) << " played by " << players[3] << endl;

        }

        cout << winner << " takes the trick" << endl;
            if(winner == teamOdd.oddplayer1 || winner == teamOdd.oddplayer3){
                ++teamOdd.tricksWon;
            }

            else if(winner == teamEven.evenplayer0 || winner == teamEven.evenplayer2){
                ++teamEven.tricksWon;
            }

        return winnerInd;
    }

};

int main(int argc, char **argv) {
  // Read command line args and check for errors

  string fileName = argv[1];
  ifstream fin(fileName);

  string shuffleDec = argv[2];
  bool shuffleArg = false;
  if(shuffleDec == "shuffle" || shuffleDec == "noshuffle"){
    shuffleArg = true;
  }

  string points = argv[3];

  vector <Player*> paraPlayer;

  string name0 = argv[4];
  string type0 = argv[5];
  Player * player0 = Player_factory(name0, type0);
  paraPlayer.push_back(player0);

  string name1 = argv[6];
  string type1 = argv[7];
  Player * player1 = Player_factory(name1, type1);
  paraPlayer.push_back(player1);

  string name2 = argv[8];
  string type2 = argv[9];
  Player * player2 = Player_factory(name2, type2);
  paraPlayer.push_back(player2);

  string name3 = argv[10];
  string type3 = argv[11];
  Player * player3 = Player_factory(name3, type3);
  paraPlayer.push_back(player3);

  if (argc != 12 || !fin.is_open() || (!shuffleArg) || !(1 <= stoi(points) && stoi(points) <= 100) 
        || (type0 != "Simple" && type0 != "Human") || (type1 != "Simple" && type1 != "Human") || 
        (type2 != "Simple" && type2 != "Human") || (type3 != "Simple" && type3 != "Human")){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
           << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
           << "NAME4 TYPE4" << endl;
      return -1;
  }


    //cout << argv[0] << argv[1] << argv[2] << argv[3] << argv[4] << argv[5] << argv[6] 
    //<< argv[7] << argv[8] << argv[9] << argv[10] << argv[11] ;

    Game game(shuffleArg, points, fin, paraPlayer);
    game.play();
}
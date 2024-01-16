#include <cassert>
#include <iostream>
#include <array>
#include <string>
#include "Card.hpp"

using namespace std;

/////////////// Rank operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const RANK_NAMES[] = {
    "Two",   // TWO
    "Three", // THREE
    "Four",  // FOUR
    "Five",  // FIVE
    "Six",   // SIX
    "Seven", // SEVEN
    "Eight", // EIGHT
    "Nine",  // NINE
    "Ten",   // TEN
    "Jack",  // JACK
    "Queen", // QUEEN
    "King",  // KING
    "Ace"    // ACE
};

// REQUIRES str represents a valid rank ("Two", "Three", ..., "Ace")
Rank string_to_rank(const std::string &str)
{
  for (int r = TWO; r <= ACE; ++r)
  {
    if (str == RANK_NAMES[r])
    {
      return static_cast<Rank>(r);
    }
  }
  assert(false); // Input string didn't match any rank
  return {};
}

// EFFECTS Prints Rank to stream, for example "Two"
std::ostream &operator<<(std::ostream &os, Rank rank)
{
  os << RANK_NAMES[rank];
  return os;
}

// REQUIRES If any input is read, it must be a valid rank
// EFFECTS Reads a Rank from a stream, for example "Two" -> TWO
std::istream &operator>>(std::istream &is, Rank &rank)
{
  string str;
  if (is >> str)
  {
    rank = string_to_rank(str);
  }
  return is;
}

/////////////// Suit operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const SUIT_NAMES[] = {
    "Spades",   // SPADES
    "Hearts",   // HEARTS
    "Clubs",    // CLUBS
    "Diamonds", // DIAMONDS
};

// REQUIRES str represents a valid suit ("Spades", "Hearts", "Clubs", or "Diamonds")
Suit string_to_suit(const std::string &str)
{
  for (int s = SPADES; s <= DIAMONDS; ++s)
  {
    if (str == SUIT_NAMES[s])
    {
      return static_cast<Suit>(s);
    }
  }
  assert(false); // Input string didn't match any suit
  return {};
}

// EFFECTS Prints Suit to stream, for example "Spades"
std::ostream &operator<<(std::ostream &os, Suit suit)
{
  os << SUIT_NAMES[suit];
  return os;
}

// REQUIRES If any input is read, it must be a valid suit
// EFFECTS Reads a Suit from a stream, for example "Spades" -> SPADES
std::istream &operator>>(std::istream &is, Suit &suit)
{
  string str;
  if (is >> str)
  {
    suit = string_to_suit(str);
  }
  return is;
}

/////////////// Write your implementation for Card below ///////////////

// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//   operator>>
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=

Card::Card()
    : rank(TWO), suit(SPADES) {}

Card::Card(Rank rank_in, Suit suit_in)
    : rank(rank_in), suit(suit_in) {}

Rank Card::get_rank() const
{
  return rank;
}
Suit Card::get_suit() const
{
  return suit;
}
Suit Card::get_suit(Suit trump) const
{

  // if (trump == DIAMONDS && rank == JACK && suit == HEARTS)
  // {
  //   return DIAMONDS;
  // }
  // else if (trump == HEARTS && rank == JACK && suit == DIAMONDS)
  // {
  //   return HEARTS;
  // }
  // else if (trump == SPADES && rank == JACK && suit == CLUBS)
  // {
  //   return SPADES;
  // }
  // else if (trump == CLUBS && rank == JACK && suit == SPADES)
  // {
  //   return CLUBS;
  // }
  // else
  // {
  //   return suit;
  // }

  if(Card::is_left_bower(trump)){
    return trump;
  }
  else{
    return get_suit();
  }

}

bool Card::is_face_or_ace() const{
  if(rank == JACK || rank == QUEEN ||
  rank == KING || rank == ACE){
    return true;
    
  }
  else{
    return false;
  }

 }

bool Card::is_right_bower(Suit trump) const{
  if(rank == JACK && suit == trump){
    return true;
  }
  else{
    return false;
  }
}

bool Card::is_left_bower(Suit trump) const{

  if(suit == Suit_next(trump) && rank == JACK){
    return true;
  }
  else{
    return false;
  }

  // if(trump == DIAMONDS && rank == JACK && suit == HEARTS){
  //   return true;
  // }
  // else if(trump == HEARTS && rank == JACK && suit == DIAMONDS){
  //   return true;
  // }
  // else if(trump == SPADES && rank == JACK && suit == CLUBS){
  //   return true;
  // }
  // else if(trump == CLUBS && rank == JACK && suit == SPADES){
  //   return true;
  // }
  // else{
  //   return false;
  // }

}

bool Card::is_trump(Suit trump) const{

  bool left_bower = Card::is_left_bower(trump);
  if(suit == trump || left_bower){
    return true;
  }
  else{
    return false;
  }

  

}

std::ostream & operator<<(std::ostream &os, const Card &card){
  os << card.get_rank() << " of " << card.get_suit();
  return os;

}

std::istream & operator>>(std::istream &is, Card &card){
  string space;
  
  is >> card.rank >> space >> card.suit;

  return is;
}

bool operator<(const Card &lhs, const Card &rhs){
  if(lhs == rhs){
    return false;
  }

  else if(lhs.get_rank() != rhs.get_rank()){
    return (lhs.get_rank() < rhs.get_rank());
  }

  else{
    return (lhs.get_suit() < rhs.get_suit());
  }


}

bool operator<=(const Card &lhs, const Card &rhs){
 if(lhs == rhs){
    return true;
  }

  else if(lhs.get_rank() != rhs.get_rank()){
    return (lhs.get_rank() < rhs.get_rank());
  }

  else{
    return (lhs.get_suit() < rhs.get_suit());
  }

}

bool operator>(const Card &lhs, const Card &rhs){

  if(lhs == rhs){
    return false;
  }

  else if(lhs.get_rank() != rhs.get_rank()){
    return (lhs.get_rank() > rhs.get_rank());
  }

  else{
    return (lhs.get_suit() > rhs.get_suit());
  }

}

bool operator>=(const Card &lhs, const Card &rhs){
   
  if(lhs == rhs){
    return true;
  }

  else if(lhs.get_rank() != rhs.get_rank()){
    return (lhs.get_rank() > rhs.get_rank());
  }

  else{
    return (lhs.get_suit() > rhs.get_suit());
  }

}

bool operator==(const Card &lhs, const Card &rhs){

  return (lhs.get_rank() == rhs.get_rank()) && 
  (lhs.get_suit() == rhs.get_suit()); 


}

bool operator!=(const Card &lhs, const Card &rhs){
  return (lhs.get_rank() != rhs.get_rank()) || 
  (lhs.get_suit() != rhs.get_suit()); 

}

Suit Suit_next(Suit suit){

  if(suit == DIAMONDS){
    return HEARTS;
  }
  else if(suit == HEARTS){
    return DIAMONDS;
  }
  else if(suit == SPADES){
    return CLUBS;
  }
  else{
    return SPADES;
  }
}

bool Card_less(const Card &a, const Card &b, Suit trump){

  Suit aSuit = a.get_suit();
  Suit bSuit = b.get_suit();

  if (a == b)
  {
    return false;
  }

  else if (b.is_right_bower(trump))
  {
    return true;
  }

  else if (a.is_left_bower(trump))
  {
    return false;
  }

  else if (a.is_right_bower(trump))
  {
    return false;
  }

  else if (b.is_left_bower(trump))
  {
    return true;
  }

  // else
  // {

  // when b is trump and a is not then a is always smaller
  else if (bSuit == trump && aSuit != trump)
  {
    return true;
  }

  else if (aSuit == trump && bSuit != trump)
  {
    return false;
  }

  // if b is RB and a is LB then a is always smaller
  // if(b.is_right_bower(trump) && a.is_left_bower(trump)){
  //   return true;
  // }

  else if (aSuit == trump && bSuit == trump)
  {
    if (a < b)
    {
      return true;
    }

    else
    {
      return false;
    }
  }
  // // when a is trump and b is trump a < b based only on rank with expections
  // if(aSuit == trump && bSuit == trump){
  //   // if b is a jack and trump than that is RB so a is always smaller
  //   if(bRank == JACK){
  //     return true;
  //   }
  //   // if a is LB and b is anything other than jack than a is never smaller
  //   if(a.is_left_bower(trump) && bRank != JACK){
  //     return false;
  //   }
  //   else{
  //     return a < b;
  //   }

  // }

  // if neither cards are trump than rank them according to the rank and the suit enums

  else if (aSuit != trump && bSuit != trump)
  {

    if (a.get_rank() != b.get_rank())
    {
      return (a < b);
    }

    else
    {
      return (aSuit < bSuit);
    }
  }

  return false;
  // }
}


bool Card_less(const Card &a, const Card &b, const Card &led_card, Suit trump){

  Suit aSuit = a.get_suit();
  Suit bSuit = b.get_suit();
  Suit ledSuit = led_card.get_suit();

  if (a == b)
  {
    return false;
  }

  else if (b.is_right_bower(trump))
  {
    return true;
  }

  else if (a.is_left_bower(trump))
  {
    return false;
  }

  else if (a.is_right_bower(trump))
  {
    return false;
  }

  else if (b.is_left_bower(trump))
  {
    return true;
  }

  // else
  // {

  // when b is trump and a is not then a is always smaller
  else if (bSuit == trump && aSuit != trump)
  {
    return true;
  }

  else if (aSuit == trump && bSuit != trump)
  {
    return false;
  }

  // if b is RB and a is LB then a is always smaller
  // if(b.is_right_bower(trump) && a.is_left_bower(trump)){
  //   return true;
  // }

  else if (aSuit == trump && bSuit == trump)
  {
    if (a < b)
    {
      return true;
    }

    else
    {
      return false;
    }
  }
  // // when a is trump and b is trump a < b based only on rank with expections
  // if(aSuit == trump && bSuit == trump){
  //   // if b is a jack and trump than that is RB so a is always smaller
  //   if(bRank == JACK){
  //     return true;
  //   }
  //   // if a is LB and b is anything other than jack than a is never smaller
  //   if(a.is_left_bower(trump) && bRank != JACK){
  //     return false;
  //   }
  //   else{
  //     return a < b;
  //   }

  // }

  // if neither cards are trump than rank them according to the rank and the suit enums

  else if (aSuit != trump && bSuit != trump && aSuit != ledSuit && bSuit != ledSuit)
  {

    if (a.get_rank() != b.get_rank())
    {
      return (a < b);
    }

    else
    {
      return (aSuit < bSuit);
    }
  }


  //comparing when considering led suit
  else if (bSuit == ledSuit && aSuit != ledSuit)
  {
    return true;
  }

  else if (aSuit == ledSuit && bSuit != ledSuit)
  {
    return false;
  }

  else if (aSuit == ledSuit && bSuit == ledSuit)
  {
    if (a < b)
    {
      return true;
    }

    else
    {
      return false;
    }
  }
  // // when a is trump and b is trump a < b based only on rank with expections
  // if(aSuit == trump && bSuit == trump){
  //   // if b is a jack and trump than that is RB so a is always smaller
  //   if(bRank == JACK){
  //     return true;
  //   }
  //   // if a is LB and b is anything other than jack than a is never smaller
  //   if(a.is_left_bower(trump) && bRank != JACK){
  //     return false;
  //   }
  //   else{
  //     return a < b;
  //   }

  // }

  // if neither cards are trump than rank them according to the rank and the suit enums

  else if (aSuit != ledSuit && bSuit != ledSuit)
  {

    if (a.get_rank() != b.get_rank())
    {
      return (a < b);
    }

    else
    {
      return (aSuit < bSuit);
    }
  }

  return false;
  // }
}
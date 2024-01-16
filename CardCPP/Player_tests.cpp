#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

// Add more tests here

// TEST(test_player_insertion) {
//   // Create neither a Simple nor a Human player
//   Player * SimplePlayer = Player_factory("NotRobot", "Cyborg");

//   // Verify that the pointer returned is the null pointer
//   ASSERT_EQUAL( * SimplePlayer, nullptr);

//   // Clean up players that were created using Player_factory()
//   delete SimplePlayer;
// }

TEST(test_play_card1) {
  Player *bob = Player_factory("Bob", "Simple");

  Card c1 = Card(TEN,DIAMONDS);
  Card c2 = Card(JACK,CLUBS);
  Card c3 = Card(QUEEN,HEARTS);
  Card c4 = Card(NINE,SPADES);
  Card c5 = Card(ACE, SPADES);

  Card ledCard = Card(TEN,SPADES);

  bob->add_card(c1);
  bob->add_card(c2);
  bob->add_card(c3);
  bob->add_card(c4);
  bob->add_card(c5);

  Card play1 = bob->play_card(ledCard, SPADES);
  Card play2 = bob->play_card(ledCard, SPADES);
  Card play3 = bob->play_card(ledCard, SPADES);
  Card play4 = bob->play_card(ledCard, SPADES);
  Card play5 = bob->play_card(ledCard, SPADES);

  ASSERT_EQUAL(play1,c2);
  ASSERT_EQUAL(play2,c5);
  ASSERT_EQUAL(play3,c4);
  ASSERT_EQUAL(play4,c1);
  ASSERT_EQUAL(play5,c3);
  delete bob;
}

TEST(test_play_card2) {
  Player *bob = Player_factory("Bob", "Simple");

  Card c1 = Card(TEN,SPADES);
  Card c2 = Card(JACK,SPADES);
  Card c3 = Card(QUEEN,SPADES);
  Card c4 = Card(NINE,SPADES);
  Card c5 = Card(ACE,SPADES);

  Card ledCard = Card(KING,SPADES);

  bob->add_card(c1);
  bob->add_card(c2);
  bob->add_card(c3);
  bob->add_card(c4);
  bob->add_card(c5);

  Card play1 = bob->play_card(ledCard, DIAMONDS);
  Card play2 = bob->play_card(ledCard, DIAMONDS);
  Card play3 = bob->play_card(ledCard, DIAMONDS);
  Card play4 = bob->play_card(ledCard, DIAMONDS);
  Card play5 = bob->play_card(ledCard, DIAMONDS);

  ASSERT_EQUAL(play1,c5);
  ASSERT_EQUAL(play2,c3);
  ASSERT_EQUAL(play3,c2);
  ASSERT_EQUAL(play4,c1);
  ASSERT_EQUAL(play5,c4);
  delete bob;
}

TEST(test_play_card3) {
  Player *bob = Player_factory("Bob", "Simple");

  Card c1 = Card(JACK,SPADES);
  Card c2 = Card(JACK,HEARTS);
  Card c3 = Card(JACK,DIAMONDS);
  Card c4 = Card(JACK,CLUBS);
  Card c5 = Card(ACE,CLUBS);

  Card ledCard = Card(TEN,DIAMONDS);

  bob->add_card(c1);
  bob->add_card(c2);
  bob->add_card(c3);
  bob->add_card(c4);
  bob->add_card(c5);

  Card play1 = bob->play_card(ledCard, DIAMONDS);
  Card play2 = bob->play_card(ledCard, DIAMONDS);
  Card play3 = bob->play_card(ledCard, DIAMONDS);
  Card play4 = bob->play_card(ledCard, DIAMONDS);
  Card play5 = bob->play_card(ledCard, DIAMONDS);

  ASSERT_EQUAL(play1,c3);
  ASSERT_EQUAL(play2,c2);
  ASSERT_EQUAL(play3,c1);
  ASSERT_EQUAL(play4,c4);
  ASSERT_EQUAL(play5,c5);
  delete bob;
}

TEST(test_play_card4) {
  Player *bob = Player_factory("Bob", "Simple");

  Card c1 = Card(JACK,SPADES);
  Card c2 = Card(JACK,HEARTS);
  Card c3 = Card(JACK,DIAMONDS);
  Card c4 = Card(JACK,CLUBS);
  Card c5 = Card(ACE, SPADES);

  Card ledCard = Card(TEN,SPADES);

  bob->add_card(c1);
  bob->add_card(c2);
  bob->add_card(c3);
  bob->add_card(c4);
  bob->add_card(c5);

  Card play1 = bob->play_card(ledCard, SPADES);
  Card play2 = bob->play_card(ledCard, SPADES);
  Card play3 = bob->play_card(ledCard, SPADES);
  Card play4 = bob->play_card(ledCard, SPADES);
  Card play5 = bob->play_card(ledCard, SPADES);

  ASSERT_EQUAL(play1,c1);
  ASSERT_EQUAL(play2,c4);
  ASSERT_EQUAL(play3,c5);
  ASSERT_EQUAL(play4,c2);
  ASSERT_EQUAL(play5,c3);
  delete bob;
}
TEST(test_add_and_discard_change) {
  Player *bob = Player_factory("Bob", "Simple");

  Card c1 = Card(TEN,SPADES);
  Card c2 = Card(JACK,SPADES);
  Card c3 = Card(QUEEN,SPADES);
  Card c4 = Card(NINE,SPADES);
  Card c5 = Card(ACE, SPADES);
  Card upcard = Card(KING,SPADES);

  Card ledCard = Card(TEN,SPADES);

  bob->add_card(c1);
  bob->add_card(c2);
  bob->add_card(c3);
  bob->add_card(c4);
  bob->add_card(c5);

  bob->add_and_discard(upcard);

  Card play1 = bob->play_card(ledCard, DIAMONDS);
  Card play2 = bob->play_card(ledCard, DIAMONDS);
  Card play3 = bob->play_card(ledCard, DIAMONDS);
  Card play4 = bob->play_card(ledCard, DIAMONDS);
  Card play5 = bob->play_card(ledCard, DIAMONDS);

  ASSERT_EQUAL(play1,c5);
  ASSERT_EQUAL(play2,upcard);
  ASSERT_EQUAL(play3,c3);
  ASSERT_EQUAL(play4,c2);
  ASSERT_EQUAL(play5,c1);
  delete bob;
}

TEST(test_add_and_discard_no_change) {
  Player *bob = Player_factory("Bob", "Simple");

  Card c1 = Card(TEN,SPADES);
  Card c2 = Card(JACK,SPADES);
  Card c3 = Card(QUEEN,SPADES);
  Card c4 = Card(KING,SPADES);
  Card c5 = Card(ACE, SPADES);
  Card upcard = Card(NINE,SPADES);

  Card ledCard = Card(TEN,SPADES);

  bob->add_card(c1);
  bob->add_card(c2);
  bob->add_card(c3);
  bob->add_card(c4);
  bob->add_card(c5);

  bob->add_and_discard(upcard);

  Card play1 = bob->play_card(ledCard, DIAMONDS);
  Card play2 = bob->play_card(ledCard, DIAMONDS);
  Card play3 = bob->play_card(ledCard, DIAMONDS);
  Card play4 = bob->play_card(ledCard, DIAMONDS);
  Card play5 = bob->play_card(ledCard, DIAMONDS);

  ASSERT_EQUAL(play1,c5);
  ASSERT_EQUAL(play2,c4);
  ASSERT_EQUAL(play3,c3);
  ASSERT_EQUAL(play4,c2);
  ASSERT_EQUAL(play5,c1);
  delete bob;
}

TEST(test_add_and_discard_trump) {
  Player *bob = Player_factory("Bob", "Simple");

  Card c1 = Card(TEN,SPADES);
  Card c2 = Card(JACK,SPADES);
  Card c3 = Card(QUEEN,HEARTS);
  Card c4 = Card(KING,SPADES);
  Card c5 = Card(ACE, SPADES);
  
  Card upcard = Card(NINE,DIAMONDS);

  Card ledCard = Card(QUEEN,SPADES);

  bob->add_card(c1);
  bob->add_card(c2);
  bob->add_card(c3);
  bob->add_card(c4);
  bob->add_card(c5);

  bob->add_and_discard(upcard);

  Card play1 = bob->play_card(ledCard, DIAMONDS);
  Card play2 = bob->play_card(ledCard, DIAMONDS);
  Card play3 = bob->play_card(ledCard, DIAMONDS);
  Card play4 = bob->play_card(ledCard, DIAMONDS);
  Card play5 = bob->play_card(ledCard, DIAMONDS);

  ASSERT_EQUAL(play1,c5);
  ASSERT_EQUAL(play2,c4);
  ASSERT_EQUAL(play3,c2);
  ASSERT_EQUAL(play4,c3);
  ASSERT_EQUAL(play5, upcard);
  delete bob;
}

TEST(test_lead_card1) {
  Player *bob = Player_factory("Bob", "Simple");

  Card c1 = Card(TEN,SPADES);
  Card c2 = Card(JACK,SPADES);
  Card c3 = Card(QUEEN,HEARTS);
  Card c4 = Card(KING,SPADES);
  Card c5 = Card(ACE, SPADES);

  bob->add_card(c1);
  bob->add_card(c2);
  bob->add_card(c3);
  bob->add_card(c4);
  bob->add_card(c5);

  Card leadCard = bob->lead_card(SPADES);

  ASSERT_EQUAL(leadCard,c3);
  delete bob;
}

TEST(test_lead_card2) {
  Player *bob = Player_factory("Bob", "Simple");

  Card c1 = Card(TEN,SPADES);
  Card c2 = Card(JACK,SPADES);
  Card c3 = Card(QUEEN,HEARTS);
  Card c4 = Card(KING,SPADES);
  Card c5 = Card(KING, DIAMONDS);

  bob->add_card(c1);
  bob->add_card(c2);
  bob->add_card(c3);
  bob->add_card(c4);
  bob->add_card(c5);

  Card leadCard = bob->lead_card(SPADES);

  ASSERT_EQUAL(leadCard,c5);
  delete bob;
}

TEST(test_lead_card3) {
  Player *bob = Player_factory("Bob", "Simple");

  Card c1 = Card(TEN,SPADES);
  Card c2 = Card(JACK,SPADES);
  Card c3 = Card(QUEEN,SPADES);
  Card c4 = Card(ACE, SPADES);
  Card c5 = Card(KING,SPADES);

  bob->add_card(c1);
  bob->add_card(c2);
  bob->add_card(c3);
  bob->add_card(c4);
  bob->add_card(c5);

  Card leadCard = bob->lead_card(SPADES);

  ASSERT_EQUAL(leadCard,c2);
  delete bob;
}

TEST(test_simple_player_make_trump_r1_bower) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(QUEEN, CLUBS));
  bob->add_card(Card(JACK, CLUBS));
  bob->add_card(Card(ACE, SPADES));

  // Bob makes trump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, SPADES);

  delete bob;
}

TEST(test_simple_player_make_trump_r1_two_faces) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(QUEEN, CLUBS));
  bob->add_card(Card(JACK, SPADES));
  bob->add_card(Card(ACE, SPADES));


  // Bob makes trump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, SPADES);

  delete bob;
}

TEST(test_simple_player_make_trump_r2_one_face) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(KING, DIAMONDS));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(QUEEN, CLUBS));
  bob->add_card(Card(JACK, SPADES));
  bob->add_card(Card(ACE, CLUBS));


  // Bob makes trump
  Card nine_spades(NINE, HEARTS);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    false,           // Bob is also the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, DIAMONDS);

  delete bob;
}

TEST(test_simple_player_make_trump_r2_bower) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(TEN, HEARTS)); 
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(JACK, CLUBS));
  bob->add_card(Card(ACE, DIAMONDS));


  // Bob makes trump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    false,           // Bob is also the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, CLUBS);

  delete bob;
}

TEST(test_simple_player_make_trump_r1_one_faces) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(QUEEN, CLUBS));
  bob->add_card(Card(JACK, DIAMONDS));
  bob->add_card(Card(ACE, SPADES));


  // Bob makes trump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_FALSE(orderup);
  //ASSERT_EQUAL(trump, SPADES);

  delete bob;
}

TEST(test_simple_player_make_trump_r1_right_bower) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(QUEEN, CLUBS));
  bob->add_card(Card(JACK, SPADES));
  bob->add_card(Card(ACE, CLUBS));


  // Bob makes trump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_FALSE(orderup);
  //ASSERT_EQUAL(trump, SPADES);

  delete bob;
}

TEST(test_simple_player_make_trump_r2_none) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(QUEEN, HEARTS));
  bob->add_card(Card(TEN, DIAMONDS));
  bob->add_card(Card(NINE, HEARTS));


  // Bob makes trump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    false,           // Bob is also the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_FALSE(orderup);
  //ASSERT_EQUAL(trump, SPADES);

  delete bob;
}

TEST(test_simple_player_make_trump_r2_random_false) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, CLUBS));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(QUEEN, DIAMONDS));
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(ACE, HEARTS));


  // Bob makes trump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    false,           // Bob is also the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_FALSE(orderup);
  //ASSERT_EQUAL(trump, SPADES);

  delete bob;
}

TEST(test_simple_player_make_trump_r2_is_dealer) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(TEN, DIAMONDS));
  bob->add_card(Card(QUEEN, DIAMONDS));
  bob->add_card(Card(JACK, DIAMONDS));
  bob->add_card(Card(ACE, DIAMONDS));


  // Bob makes trump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, CLUBS);

  delete bob;
}


TEST_MAIN()

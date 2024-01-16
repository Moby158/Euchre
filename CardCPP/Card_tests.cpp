#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

TEST(test_card_empty) { 
    Card neutral = Card();
    ASSERT_EQUAL(TWO, neutral.get_rank());
    ASSERT_EQUAL(SPADES, neutral.get_suit());
}

TEST(test_get_trump_clubs_suit){
    Card leftBower = Card(JACK, SPADES);
    ASSERT_EQUAL(JACK, leftBower.get_rank());
    ASSERT_EQUAL(CLUBS, leftBower.get_suit(CLUBS));
}

TEST(test_get_trump_spades_suit){
    Card leftBower = Card(JACK, CLUBS);
    ASSERT_EQUAL(JACK, leftBower.get_rank());
    ASSERT_EQUAL(SPADES, leftBower.get_suit(SPADES));
}

TEST(test_get_trump_hearts_suit){
    Card leftBower = Card(JACK, DIAMONDS);
    ASSERT_EQUAL(JACK, leftBower.get_rank());
    ASSERT_EQUAL(HEARTS, leftBower.get_suit(HEARTS));
}

TEST(test_get_trump_diamonds_suit){
    Card leftBower = Card(JACK, HEARTS);
    ASSERT_EQUAL(JACK, leftBower.get_rank());
    ASSERT_EQUAL(DIAMONDS, leftBower.get_suit(DIAMONDS));
}

TEST(test_get_trump_not_jack_suit){
    Card leftBower = Card(QUEEN, SPADES);
    ASSERT_EQUAL(QUEEN, leftBower.get_rank());
    ASSERT_EQUAL(SPADES, leftBower.get_suit(CLUBS));
}

TEST(test_is_face_or_ace_true){
    Card c = Card(JACK, SPADES);
    ASSERT_TRUE(c.is_face_or_ace());
}

TEST(test_is_face_or_ace_false){
    Card c = Card();
    ASSERT_FALSE(c.is_face_or_ace());
}

// TEST(test_is_right_bower_true){
//     Card c = Card(JACK, SPADES);
//     ASSERT_TRUE(c.is_right_bower(SPADES));

// }

// TEST(test_is_right_bower_false){
//     Card c = Card(ACE, SPADES);
//     ASSERT_FALSE(c.is_right_bower(SPADES));

// }

TEST(test_is_left_bower_D_true){
    Card c = Card(JACK, DIAMONDS);
    ASSERT_TRUE(c.is_left_bower(HEARTS));
}

TEST(test_is_left_bower_H_true){
    Card c = Card(JACK, HEARTS);
    ASSERT_TRUE(c.is_left_bower(DIAMONDS));
}

// TEST(test_is_left_bower_S_true){
//     Card c = Card(JACK, SPADES);
//     ASSERT_TRUE(c.is_left_bower(CLUBS));
// }

TEST(test_is_left_bower_C_true){
    Card c = Card(JACK, CLUBS);
    ASSERT_TRUE(c.is_left_bower(SPADES));
}

// TEST(test_is_left_bower__false){
//     Card c = Card(JACK, HEARTS);
//     ASSERT_FALSE(c.is_left_bower(SPADES));
// }

// TEST(test_is_trump_true){
//     Card c = Card(TWO, HEARTS);
//     ASSERT_TRUE(c.is_trump(HEARTS));
// }

// TEST(test_is_trump_lb_true){
//     Card c = Card(JACK, DIAMONDS);
//     ASSERT_TRUE(c.is_trump(HEARTS));
// }

// TEST(test_is_trump_false){
//     Card c = Card(FOUR, DIAMONDS);
//     ASSERT_FALSE(c.is_trump(HEARTS));
// }

TEST(operator_function_print){
    
    Card c = Card(JACK, SPADES);
    ostringstream oss;
    oss << c;
    ASSERT_EQUAL(oss.str(), "Jack of Spades");
}

// TEST(test_card_extraction) {
//     istringstream iss("Three of Spades");
//     Card c;
//     iss >> c;
//     ASSERT_EQUAL(c, Card(THREE, SPADES));
// }

TEST(lessThan_true_operater){

    Card c = Card(THREE, SPADES);
    Card b = Card(TEN, SPADES);

    ASSERT_TRUE(c < b);

}

TEST(lessThan_false_operater){

    Card c = Card(TEN, SPADES);
    Card b = Card(THREE, SPADES);

    ASSERT_FALSE(c < b);

}

TEST(lessThanOrEq_true_operater){

    Card c = Card(TEN, HEARTS);
    Card b = Card(TEN, HEARTS);

    ASSERT_TRUE(c <= b);

}

TEST(lessThanOrEq_false_operater){

    Card c = Card(QUEEN, SPADES);
    Card b = Card(TEN, HEARTS);

    ASSERT_FALSE(c <= b);

}

TEST(GreaterThan_true_operater){

    Card c = Card(JACK, SPADES);
    Card b = Card(TEN, HEARTS);

    ASSERT_TRUE(c > b);

}

TEST(GreaterThan_false_operater){

    Card c = Card(QUEEN, SPADES);
    Card b = Card(KING, HEARTS);

    ASSERT_FALSE(c > b);

}

TEST(GreaterThanOrEq_true_operater){

    Card c = Card(TEN, SPADES);
    Card b = Card(TEN, SPADES);

    ASSERT_TRUE(c >= b);

}

TEST(GreaterThanOrEq_false_operater){

    Card c = Card(NINE, SPADES);
    Card b = Card(TEN, HEARTS);

    ASSERT_FALSE(c >= b);

}

TEST(card_EQ){

    Card c = Card(TEN,DIAMONDS);
    Card b = Card(TEN,DIAMONDS); 

    ASSERT_TRUE(c == b);
}

TEST(card_not_suit_EQ){

    Card c = Card(TEN,SPADES);
    Card b = Card(TEN,DIAMONDS); 

    ASSERT_FALSE(c == b);
}

TEST(card_not_rank_EQ){

    Card c = Card(TWO,SPADES);
    Card b = Card(TEN,DIAMONDS); 

    ASSERT_FALSE(c == b);
}

TEST(not_EQ){
    Card c = Card(TWO,SPADES);
    Card b = Card(TEN,DIAMONDS); 

    ASSERT_TRUE(c != b);

}

TEST(Card_less_false1){
    Card a = Card(TWO,SPADES);
    Card b = Card(TEN,DIAMONDS); 

    ASSERT_FALSE(Card_less(a,b,SPADES));

}

TEST(Card_less_false2){
    Card a = Card(JACK,SPADES);
    Card b = Card(JACK,CLUBS); 

    ASSERT_FALSE(Card_less(a,b,SPADES));

}

TEST(Card_less_false3){
    Card a = Card(ACE,DIAMONDS);
    Card b = Card(ACE,CLUBS); 

    ASSERT_FALSE(Card_less(a,b,SPADES));

}

TEST(Card_less_false4){
    Card a = Card(TEN,SPADES);
    Card b = Card(TEN,DIAMONDS); 

    ASSERT_FALSE(Card_less(a,b,SPADES));

}

TEST(Card_less_false5){
    Card a = Card(JACK,CLUBS);
    Card b = Card(ACE,SPADES); 

    ASSERT_FALSE(Card_less(a,b,SPADES));

}

TEST(Card_less_false6){
    Card a = Card(NINE,CLUBS);
    Card b = Card(NINE,HEARTS); 

    ASSERT_FALSE(Card_less(a,b,SPADES));

}

TEST(Card_less_true1){
    Card a = Card(TWO,HEARTS);
    Card b = Card(TEN,DIAMONDS); 

    ASSERT_TRUE(Card_less(a,b,SPADES));

}

TEST(Card_less_true2){
    Card a = Card(JACK,CLUBS);
    Card b = Card(JACK,SPADES); 

    ASSERT_TRUE(Card_less(a,b,SPADES));

}

TEST(Card_less_true3){
    Card a = Card(ACE,SPADES);
    Card b = Card(JACK,CLUBS); 

    ASSERT_TRUE(Card_less(a,b,SPADES));

}

TEST(Card_less_true4){
    Card a = Card(KING,DIAMONDS);
    Card b = Card(KING,SPADES); 

    ASSERT_TRUE(Card_less(a,b,SPADES));

}

TEST(Card_less_true5){
    Card a = Card(KING,CLUBS);
    Card b = Card(KING,DIAMONDS); 

    ASSERT_TRUE(Card_less(a,b,SPADES));

}

TEST(Card_less_true6){
    Card a = Card(JACK,DIAMONDS);
    Card b = Card(JACK,CLUBS); 

    ASSERT_TRUE(Card_less(a,b,SPADES));

}

TEST(Card_less_led_false1){
    Card a = Card(TEN,DIAMONDS);
    Card b = Card(ACE,CLUBS);
    Card leadCard = Card(NINE,DIAMONDS); 

    ASSERT_FALSE(Card_less(a,b,leadCard,SPADES));

}

TEST(Card_less_led_false2){
    Card a = Card(TEN,DIAMONDS);
    Card b = Card(JACK,SPADES);
    Card leadCard = Card(NINE,DIAMONDS); 

    ASSERT_FALSE(Card_less(a,b,leadCard,HEARTS));

}

TEST(Card_less_led_false3){
    Card a = Card(JACK,SPADES);
    Card b = Card(TEN,DIAMONDS);
    Card leadCard = Card(NINE,HEARTS); 

    ASSERT_FALSE(Card_less(a,b,leadCard,HEARTS));

}

TEST(Card_less_led_false4){
    Card a = Card(JACK,HEARTS);
    Card b = Card(JACK,DIAMONDS);
    Card leadCard = Card(NINE,HEARTS); 

    ASSERT_FALSE(Card_less(a,b,leadCard,HEARTS));

}

TEST(Card_less_led_false5){
    Card a = Card(JACK,SPADES);
    Card b = Card(TEN,HEARTS);
    Card leadCard = Card(NINE,HEARTS); 

    ASSERT_FALSE(Card_less(a,b,leadCard,CLUBS));

}

TEST(Card_less_led_false6){
    Card a = Card(JACK,SPADES);
    Card b = Card(TEN,CLUBS);
    Card leadCard = Card(NINE,SPADES); 

    ASSERT_FALSE(Card_less(a,b,leadCard,CLUBS));

}

TEST(Card_less_led_false7){
    Card a = Card(KING,CLUBS);
    Card b = Card(TEN,SPADES);
    Card leadCard = Card(NINE,SPADES); 

    ASSERT_FALSE(Card_less(a,b,leadCard,CLUBS));

}

TEST(Card_less_led_true1){
    Card a = Card(JACK,SPADES);
    Card b = Card(TEN,DIAMONDS);
    Card leadCard = Card(NINE,DIAMONDS); 

    ASSERT_TRUE(Card_less(a,b,leadCard,HEARTS));

}

TEST(Card_less_led_true2){
    Card a = Card(TEN,DIAMONDS);
    Card b = Card(JACK,SPADES);
    Card leadCard = Card(NINE,DIAMONDS); 

    ASSERT_TRUE(Card_less(a,b,leadCard,SPADES));

}

TEST(Card_less_led_true3){
    Card a = Card(TEN,DIAMONDS);
    Card b = Card(JACK,SPADES);
    Card leadCard = Card(NINE,DIAMONDS); 

    ASSERT_TRUE(Card_less(a,b,leadCard,CLUBS));

}

TEST(Card_less_led_true4){
    Card a = Card(TEN,DIAMONDS);
    Card b = Card(KING,DIAMONDS);
    Card leadCard = Card(NINE,DIAMONDS); 

    ASSERT_TRUE(Card_less(a,b,leadCard,HEARTS));

}

TEST(Card_less_led_true5){
    Card a = Card(TEN,DIAMONDS);
    Card b = Card(NINE,SPADES);
    Card leadCard = Card(NINE,DIAMONDS); 

    ASSERT_TRUE(Card_less(a,b,leadCard,SPADES));

}

TEST(Card_less_led_true6){
    Card a = Card(TEN,HEARTS);
    Card b = Card(QUEEN,HEARTS);
    Card leadCard = Card(NINE,DIAMONDS); 

    ASSERT_TRUE(Card_less(a,b,leadCard,SPADES));
}

// Add more test cases here

TEST_MAIN()
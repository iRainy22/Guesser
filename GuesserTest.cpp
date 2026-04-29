/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};


// TEST Distance
/*
  Returns an whole number representing the distance between the guess,
  provided as an argument, and the secret. The distance represents the number
  of characters that would have to be changed at the same location to match
  the other string. When the two strings are identical, the distance is 0,
  but for each letter different, the distance increases by 1. When the
  strings are different lengths, each of the extra characters in the longer
  string also counts as an increase in 1 to the distance, up to the length of
  the secret; in other words, if m_secret has a 10 characters and the guess
  has 100, the distance is 10.
*/
TEST(GuesserTest, D_EmptySecret) {
    Guesser object("");
    int actual = Guesser.distance("AAA");
    ASSERT_EQ(0, actual);

}

TEST(GuesserTest, D_OneOff) {
    Guesser object("ABC");
    int actual = Guesser.distance("ABD");
    ASSERT_EQ(1, actual)
}

TEST(GuesserTest, D_EmptyString) {
    Guesser object("ABCde");
    int actual = Guesser.distance("");
    ASSERT_EQ(5, actual)
}

TEST(GuesserTest, D_Capsdif) {
    Guesser object("ABC");
    int actual = Guesser.distance("abc");
    ASSERT_EQ(3, actual)
}

TEST(GuesserTest, D_SpecialChars) {
    Guesser object("abcdef");
    int actual = Guesser.distance("@$&>^\");
    ASSERT_EQ(6, actual)
}

TEST(GuesserTest, D_NumbersPass) {
    Guesser object("123");
    int actual = Guesser.distance("123");
    ASSERT_EQ(0, actual)
}

TEST(GuesserTest, D_NumbersFail) {
    Guesser object("512");
    int actual = Guesser.distance("215");
    ASSERT_EQ(2, actual)
}

TEST(GuesserTest, D_LongGuess) {
    Guesser object("ABC");
    int actual = Guesser.distance("AlphabetAlphabetAlphabet");
    ASSERT_EQ(3, actual)
}

TEST(GuesserTest, D_LongSecret) {
    Guesser object("AlphabetAlphabetAlphabet");
    int actual = Guesser.distance("one");
    ASSERT_EQ(21, actual)
}


// TEST Match
/*
  Determines and returns whether the provided guess matches the secret
  phrase. However, the function also returns false if the secret is locked,
  which happens if either (or both): 
    (A) there are no remaining guesses allowed
    (B) the function detects brute force, as indicated by a guess that has a
        distance greater than 2 from the secret
  See the distance() functions for specifications regarding determining the 
  distance between a guess and the secret.
  
  A Guesser object allows up to
  three (3) consecutive guesses without a match. If three guesses are made
  without any being a true match, the secret is locked. However, whenever
  an unlocked secret is guessed with a true match, the guesses remaining
  reset to three (3). If the secret is locked for any other reason, such
  as a big distance in a guess, the count of remaining guesses should still
  count down as usual to hide that the secret has been locked.
*/

TEST(GuesserTest, M_Pass) {
    Guesser object("AAA");
    int actual = Guesser.match("AAA");
    ASSERT_EQ(true, actual);
}

TEST(GuesserTest, M_OneOff) {
    Guesser object("AAA");
    int actual = Guesser.match("AaA");
    ASSERT_EQ(false, actual);
}

TEST(GuesserTest, M_NumbersPass) {
    Guesser object("123");
    int actual = Guesser.match("123");
    ASSERT_EQ(true, actual);
}

TEST(GuesserTest, M_NumbersFail) {
    Guesser object("321");
    int actual = Guesser.match("320");
    ASSERT_EQ(false, actual);
}

TEST(GuesserTest, M_emptysecret) {
    Guesser object("");
    int actual = Guesser.match("A");
    ASSERT_EQ(false, actual);
}

TEST(GuesserTest, M_emptystring) {
    Guesser object("A");
    int actual = Guesser.match("");
    ASSERT_EQ(false, actual);
}

TEST(GuesserTest, M_UnlockandPass) {
    Guesser object("abc");

    Guesser.match("ab");
    Guesser.match("ab");
    Guesser.match("abc") //unlock
    int actual = Guesser.match("abc");

    ASSERT_EQ(true, actual);
}

TEST(GuesserTest, M_LockandFail) {
    Guesser object("abc");

    Guesser.match("ab");
    Guesser.match("ab");
    Guesser.match("ab"); //lock

    int actual = Guesser.match("abc");
    ASSERT_EQ(true, actual);
}


TEST(GuesserTest, M_LongLockandFail) {
    Guesser object("abc");
    Guesser.match("abcdef"); //lock

    int actual = Guesser.match("abc");
    ASSERT_EQ(true, actual);
}


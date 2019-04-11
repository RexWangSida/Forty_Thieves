/**
 * \file CardTypes.h
 * \Sida Wang
 * \brief This module defines the Card Types with its features
 */
#ifndef A3_CARD_TYPES_H_
#define A3_CARD_TYPES_H_

/**
 * \brief Total number of cards
 */
#define TOTAL_CARDS = 104
/** 
 * \brief The nat which represents the natural number is defined by unsigned integer
 */
typedef unsigned int nat;
/**
 * \brief Describes the suit of a card
 */
enum SuitT{Heart, Diamond, Club, Spade};

/**
 * \brief Describes a card stack or a Sequence of card stacks
 */
enum CategoryT{Tableau, Foundation, Deck, Waste};

/**
 * \brief Describes the rank of a card
 */

typedef unsigned short int RankT;

/**
 * \brief RankT for an Ace
 */
#define ACE    1

/**
 * \brief RankT for an Jack
 */
#define JACK   11

/**
 * \brief RankT for a Queen
 */
#define QUEEN  12

/**
 * \brief RankT for a King.
 */
#define KING   13
/**
 * \brief Define a Card Type.
 */
struct CardT{
    enum SuitT s;
    RankT r;
};


#endif

#ifndef A3_GAME_BOARD_H_
#define A3_GAME_BOARD_H_
/**
 *  \file Stack.h
 *  \author Sida Wang
 *  \brief Game Board ADT Module defines a BoardT type including all methods of operations on the Game Board
 */

#include "CardTypes.h"
#include "CardStack.h"
#include <vector>
/**
 * \brief Decribes a Sequence of CardStackT
 */
typedef std::vector<CardStackT> SeqCrdStckT;

class BoardT{

    private:
        //all local functions that support  the implementation of a Game Board and its operations
////////////////////////////////////////////////////////////////////////////////
        SeqCrdStckT T,F;
        CardStackT D,W;
        //used by valid_mc_exists, check if there is a valid move from Tableau
        bool valid_tab_mv();
        //used by valid_mc_exists, check if there is a valid move from Waste
        bool valid_waste_mv();
        //check if there are only two of each cards in the whole Game Board
        bool two_decks(SeqCrdStckT T,SeqCrdStckT F,CardStackT D,CardStackT W);
        //count the cards in Sequence of CardStackT S
        nat cnt_cards_seq(SeqCrdStckT S);
        //count the cards in CardStackT s
        nat cnt_cards_stack(CardStackT s);
        //count the cards in the Game Board
        nat cnt_cards(SeqCrdStckT T,SeqCrdStckT F,CardStackT D, CardStackT W);
        //initialize a sequence of n empty CardStackT
        SeqCrdStckT init_seq(nat n);
        //initialize a sequence of n empty CardStackT
        SeqCrdStckT tab_deck(std::vector<CardT> deck);
        //check if an index represented by natural number n is valid in CategoryT(Tableau or Foundation)
        bool is_valid_pos(CategoryT c,nat n);
        //check if a card move from Tab to Tab is valid
        bool valid_tab_tab(nat n0,nat n1);
        //check if a card move from Tab to Foundation is valid
        bool valid_tab_foundation(nat n0,nat n1);
        //check if a card move from Waste to Tab is valid
        bool valid_waste_tab(nat n);
        //check if a card move from Waste to Foundation is valid
        bool valid_waste_foundation(nat n);
        //check if a card move to an unempty Tab is valid
        bool tab_placeable(CardT c, CardT d);
        //check if a card move to an unempty Foundation is valid
        bool foundation_placeable(CardT c,CardT d);

    public:
        /**
         *  \brief Constructs a new BoardT represent the Game Board
         *  \param deck A sequence of CardT
         */
        BoardT(std::vector<CardT> deck);
        /**
         *  \brief Determine is it a valid move from Tableau to other positions
         *  \param c The position where that card will be moved to
         *  \param n0 The index of CardStack in Tableau where the card is belong to
         *  \param n1 The index of CardStack in Tableau or Foundation where the card will be moved to
         *  \return A boolean value to determine the eligibility of card moving
         */
        bool is_valid_tab_mv(CategoryT c ,nat n0 ,nat n1);
        /**
         *  \brief Determine is it a valid move from Waste to other positions
         *  \param c The position where that card will be moved to
         *  \param n The index of CardStack in Tableau or Foundation where the card will be moved to
         *  \return A boolean value to determine the eligibility of card moving
         */
        bool is_valid_waste_mv(CategoryT c, nat n);
        /**
         *  \brief Determine is it a valid move from Deck to other positions
         *  \return A boolean value to determine the eligibility of card moving
         */
        bool is_valid_deck_mv();
        /**
         *  \brief Execute the card moving from Tableau to other positions
         *  \param c The position where that card will be moved to
         *  \param n0 The index of CardStack in Tableau where the card is belong to
         *  \param n1 The index of CardStack in Tableau or Foundation where the card will be moved to
         */
        void tab_mv(CategoryT c, nat n0, nat n1);
        /**
         *  \brief Execute the card moving from Waste to Tableau or Foundation
         *  \param c The position where that card will be moved to
         *  \param n The index of CardStack in Tableau or Foundation where the card will be moved to
         */
        void waste_mv(CategoryT c, nat n);
        /**
         *  \brief Execute the card moving from Deck to Waste
         *  \param c The position where that card will be moved to
         *  \param n The index of CardStack in Tableau or Foundation where the card will be moved to
         */
        void deck_mv();
        /**
         *  \brief Get the CardStackT at a certain index of Tableau
         *  \param i Index of Tableau
         *  \return A CardStackT at a certain index of Tableau
         */
        CardStackT get_tab(nat i);
        /**
         *  \brief Get the CardStackT at a certain index of Foundation
         *  \param i Index of Foundation
         *  \return A CardStackT at a certain index of Foundation
         */
        CardStackT get_foundation(nat i);
        /**
         *  \brief Get the CardStackT that represents the Deck
         *  \return A CardStackT that represents the Deck
         */
        CardStackT get_deck();
        /**
         *  \brief Get the CardStackT that represents the Waste
         *  \return A CardStackT that represents the Waste
         */
        CardStackT get_waste();
        /**
         *  \brief Determine if these is a valid move exists on the Game Board
         *  \return A boolean value to determine the existence of a valid card move
         */
        bool valid_mv_exists();
        /**
         *  \brief Determine if the game is at win state
         *  \return A boolean value to determine the game is at win state or not
         */
        bool is_win_state();
};
#endif

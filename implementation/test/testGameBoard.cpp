#include "catch.h"
#include "GameBoard.h"
#include "CardTypes.h"
#include "CardStack.h"
#include <vector>
using namespace std;


TEST_CASE("test for BoardT", "[BoardT]"){
////////////////////////////////////////////////////Normal & Boundary test start
    vector<CardT> deck;
    for (RankT rank = ACE; rank <= KING; rank++) {
        for (unsigned int suit = 0; suit < 4; suit++) {
            CardT n = { static_cast<SuitT>(suit), rank };
            deck.push_back(n);
            deck.push_back(n);
        }
    }
    
    BoardT board = BoardT(deck);
    SECTION("Test: get_tab"){
        CardStackT result = board.get_tab(0);
        REQUIRE((result.top().s == Diamond and result.top().r == ACE));
    }
    board.tab_mv(Foundation,0,0);
    SECTION("Test: get_foundation"){
        CardStackT result = board.get_foundation(0);
        REQUIRE((result.top().s == Diamond and result.top().r == ACE));
    }
    SECTION("Test: get_deck"){
        CardStackT result = board.get_deck();
        REQUIRE((result.top().s == Spade and result.top().r == KING));
    }
    board.deck_mv();
    SECTION("Test: get_waste"){
        CardStackT result = board.get_waste();
        REQUIRE((result.top().s == Spade and result.top().r == KING));
    }



    BoardT board01 = BoardT(deck);
    SECTION("Test: tab_mv with c = Tableau"){
        board01.tab_mv(Tableau,0,2);
        CardStackT result = board01.get_tab(2);
        REQUIRE((result.top().s == Diamond and result.top().r == 1));
    }

 
    SECTION("Test: tab_mv with c = Foundation"){
        board01.tab_mv(Foundation,1,0);
        CardStackT result = board01.get_foundation(0);
        REQUIRE((result.top().s == Spade and result.top().r == ACE));
    }


    BoardT board02 = BoardT(deck);
    SECTION("Test: deck_mv"){
        //////////deck card all moved to waste
        for (nat i = 40; i <= 103; i++){
            board02.deck_mv();
        }
        CardStackT result = board02.get_waste();
        REQUIRE((result.top().s == Heart and result.top().r == 6));
    }

    BoardT board03 = BoardT(deck);
    SECTION("Test: waste_mv with c = Tableau"){
        //////////deck card all moved to waste, left 2
        for (nat i = 40; i <= 101; i++){
            board03.deck_mv();
        }
        board03.tab_mv(Foundation,0,1);
        board03.tab_mv(Foundation,0,2);
        board03.tab_mv(Foundation,0,3);
        board03.tab_mv(Foundation,0,4);
        board03.waste_mv(Tableau,0);
        CardStackT result = board03.get_tab(0);
        REQUIRE((result.top().s == Diamond and result.top().r == 6));
    }

    BoardT board04 = BoardT(deck);
    SECTION("Test: waste_mv with c = Foundation"){
        //////////deck card all moved to waste, left 2
        for (nat i = 40; i <= 101; i++){
            board04.deck_mv();
        }
        board04.tab_mv(Foundation,0,0);
        board04.tab_mv(Foundation,2,0);
        board04.tab_mv(Foundation,4,0);
        board04.tab_mv(Foundation,6,0);
        board04.tab_mv(Foundation,8,0);
        board04.waste_mv(Foundation,0);
        CardStackT result = board04.get_foundation(0);
        REQUIRE((result.top().s == Diamond and result.top().r == 6));
    }





    BoardT board1 = BoardT(deck);

    SECTION("Test: is_valid_tab_mv with implict test on valid_tab_tab(true) and tab_placeable(true)"){
        
        REQUIRE(board1.is_valid_tab_mv(Tableau,0,2));
    }

    BoardT board2 = BoardT(deck);
    SECTION("Test: is_valid_tab_mv with implict test on valid_tab_tab(false) and tab_placeable(false)"){
        
        REQUIRE(not board2.is_valid_tab_mv(Tableau,0,3));
    }

    BoardT board3 = BoardT(deck);
    board3.tab_mv(Foundation,0,0);
    board3.tab_mv(Foundation,0,1);
    board3.tab_mv(Foundation,0,2);
    board3.tab_mv(Foundation,0,3);
    SECTION("Test: is_valid_tab_mv with implict test on valid_tab_tab(true) and T[n1].size() = 0"){
        
        REQUIRE(board3.is_valid_tab_mv(Tableau,1,0));
    }

    BoardT board4 = BoardT(deck);
    board4.tab_mv(Foundation,0,0);
    board4.tab_mv(Foundation,0,1);
    board4.tab_mv(Foundation,0,2);
    board4.tab_mv(Foundation,0,3);
    SECTION("Test: is_valid_tab_mv with implict test on valid_tab_tab(false) and T[n0].size() = 0"){
        
        REQUIRE(not board4.is_valid_tab_mv(Tableau,0,1));
    }


    BoardT board5 = BoardT(deck);
    board5.tab_mv(Foundation,0,0);
    SECTION("Test: is_valid_tab_mv with implict test on valid_tab_foundation(true) and foundation_placeable(true)"){
        
        REQUIRE(board5.is_valid_tab_mv(Foundation,2,0));
    }

    BoardT board6 = BoardT(deck);
    board6.tab_mv(Foundation,0,0);
    SECTION("Test: is_valid_tab_mv with implict test on valid_tab_foundation(false) and foundation_placeable(false)"){
        
        REQUIRE(not board6.is_valid_tab_mv(Foundation,9,0));
    }

    BoardT board7 = BoardT(deck);
    SECTION("Test: is_valid_tab_mv with implict test on valid_tab_foundation(true) and F[n1].size() = 0 and T[n0].top().r = ACE"){
        
        REQUIRE(board7.is_valid_tab_mv(Foundation,0,0));
    }

    BoardT board8 = BoardT(deck);
    SECTION("Test: is_valid_tab_mv with implict test on valid_tab_foundation(true) and F[n1].size() = 0 and not T[n0].top().r = ACE"){
        
        REQUIRE(not board8.is_valid_tab_mv(Foundation,9,0));
    }



    BoardT board9 = BoardT(deck);
    SECTION("Test: is_valid_tab_mv with c = Deck"){
        REQUIRE(not board9.is_valid_tab_mv(Deck,9,0));
    }

    BoardT board10 = BoardT(deck);
    SECTION("Test: is_valid_tab_mv with c = Waste"){
        REQUIRE(not board10.is_valid_tab_mv(Waste,9,0));
    }

    BoardT board11 = BoardT(deck);
    board11.tab_mv(Foundation,0,0);
    board11.tab_mv(Foundation,0,1);
    board11.tab_mv(Foundation,0,2);
    board11.tab_mv(Foundation,0,3);
    board11.deck_mv();
    SECTION("Test: is_valid_waste_mv with c = Tableau"){
        REQUIRE(board11.is_valid_waste_mv(Tableau,0));
    }

    BoardT board12 = BoardT(deck);
    SECTION("Test: is_valid_waste_mv with c = Foundation"){
        //////////deck card all moved to waste, left 2
        for (nat i = 40; i <= 101; i++){
            board12.deck_mv();
        }
        board12.tab_mv(Foundation,0,0);
        board12.tab_mv(Foundation,2,0);
        board12.tab_mv(Foundation,4,0);
        board12.tab_mv(Foundation,6,0);
        board12.tab_mv(Foundation,8,0);

        REQUIRE(board12.is_valid_waste_mv(Foundation,0));
    }


    BoardT board13 = BoardT(deck);
    board13.deck_mv();
    SECTION("Test: is_valid_waste_mv with c = Deck"){
        REQUIRE(not board13.is_valid_waste_mv(Deck,0));
    }

    BoardT board14 = BoardT(deck);
    board14.deck_mv();
    SECTION("Test: is_valid_waste_mv with c = Waste"){
        REQUIRE(not board14.is_valid_waste_mv(Waste,0));
    }

    BoardT board15 = BoardT(deck);
    SECTION("Test for is_valid_deck_mv"){

        REQUIRE(board15.is_valid_deck_mv());
    }



    BoardT board16 = BoardT(deck);
    SECTION("Test: valid_mv_exists"){
        //////////deck card all moved to waste, left 2
        for (nat i = 40; i <= 101; i++){
            board16.deck_mv();
        }

        REQUIRE(board16.valid_mv_exists());
    }

    SECTION("Test: is_win_state"){

        REQUIRE(not board16.is_win_state());
    }


    
    
////////////////////////////////////////////////////Normal & Boundary test end

////////////////////////////////////////////////////Exception test start
    vector<CardT> deck_exc;

    for (RankT rank = ACE; rank <= KING; rank++) {
        for (unsigned int suit = 0; suit < 4; suit++) {
            CardT n = { static_cast<SuitT>(suit), rank };
            deck_exc.push_back(n);
            deck_exc.push_back(n);
        }
    }
    deck_exc.pop_back();

    SECTION("exception test for BoardT (Constructor)"){
        REQUIRE_THROWS_AS(BoardT(deck_exc), ::invalid_argument);
    }

    BoardT board_a = BoardT(deck);
    SECTION("exception test for is_valid_tab_mv with c = Tableau"){
        REQUIRE_THROWS_AS(board_a.is_valid_tab_mv(Tableau,11,11), ::out_of_range);
    }

    SECTION("exception test for is_valid_tab_mv with c = Foundation"){
        REQUIRE_THROWS_AS(board_a.is_valid_tab_mv(Foundation,11,11), ::out_of_range);
    }

    SECTION("exception test for is_valid_waste_mv with W.size() = 0"){
        REQUIRE_THROWS_AS(board_a.is_valid_waste_mv(Tableau ,7), ::invalid_argument);
    }

    board_a.deck_mv();
    SECTION("exception test for is_valid_waste_mv with c = Tableau"){
        REQUIRE_THROWS_AS(board_a.is_valid_waste_mv(Tableau,11), ::out_of_range);
    }

    SECTION("exception test for is_valid_waste_mv with c = Foundation"){
        REQUIRE_THROWS_AS(board_a.is_valid_waste_mv(Foundation,11), ::out_of_range);
    }

    BoardT board_b = BoardT(deck);
    SECTION("exception test for tab_mv"){
        REQUIRE_THROWS_AS(board_b.tab_mv(Tableau, 0 , 3), ::invalid_argument);
    }

    SECTION("exception test for waste_mv"){
        REQUIRE_THROWS_AS(board_b.waste_mv(Tableau , 3), ::invalid_argument);
    }
    SECTION("exception test for deck_mv"){
        //////////deck card all moved to waste
        for (nat i = 40; i <= 103; i++){
            board_b.deck_mv();
        }
        REQUIRE_THROWS_AS(board_b.deck_mv(), ::invalid_argument);
    }

    SECTION("exception test for get_tab"){
        REQUIRE_THROWS_AS(board_b.get_tab(11), ::out_of_range);
    }

    SECTION("exception test for get_foundation"){
        REQUIRE_THROWS_AS(board_b.get_foundation(11), ::out_of_range);
    }


////////////////////////////////////////////////////Exception test end
}

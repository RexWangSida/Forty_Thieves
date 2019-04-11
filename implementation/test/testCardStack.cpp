#include "catch.h"
#include "CardStack.h"
#include <vector>
using namespace std;


TEST_CASE("test for CardStackT", "[CardStackT]"){
//////////////////////////////////////////////////Normal test start
    vector<CardT> test1;
    CardT a,b,c;
    a.r = 1;
    a.s = Heart;
    b.r = 2;
    b.s = Club;
    c.r = 3;
    c.s = Spade;

    test1.push_back(a);
    test1.push_back(b);
    test1.push_back(c);

    CardStackT result1 = CardStackT(test1);

    SECTION("normal test for top"){

        REQUIRE(result1.top().r == 3);
    }

    SECTION("normal test for pop"){
        result1 = result1.pop();
        REQUIRE(result1.top().r == 2);
    }
    
    SECTION("normal test for push"){
        result1 = result1.push(c);
        REQUIRE(result1.top().r== 3);
    }



    SECTION("normal test for size"){
        REQUIRE(result1.size() == 3);
    }

    SECTION("normal test for toSeq"){
        vector<CardT> result = result1.toSeq();
        CardT temp = result.back();
        REQUIRE(temp.r == 3);
    }
//////////////////////////////////////////////////Normal test end

//////////////////////////////////////////////////Boundary test start
    vector<CardT> test2;

    a.r = 1;
    a.s = Heart;
    b.r = 2;
    b.s = Club;
    c.r = 3;
    c.s = Spade;
    test2.push_back(c);


    CardStackT result2 = CardStackT(test2);

    SECTION("boundary test for size & pop"){
        result2 = result2.pop();
        REQUIRE(result2.size() == 0);
    }

    SECTION("boundary test for push & top"){
        result2 = result2.push(a);
        REQUIRE(result2.top().r== 1);
    }

    SECTION("boundary test for toSeq"){
        vector<CardT> result = result2.toSeq();
        REQUIRE(result2.size() == 1);
    }
//////////////////////////////////////////////////Boundary test end

//////////////////////////////////////////////////Exception test start
    vector<CardT> test3;

    CardStackT result3 = CardStackT(test3);

    SECTION("exception test for pop"){
        REQUIRE_THROWS_AS(result3.pop(), ::out_of_range);
    }

    SECTION("exception test for top"){
        REQUIRE_THROWS_AS(result3.top(), ::out_of_range);
    }


//////////////////////////////////////////////////Exception test end

}

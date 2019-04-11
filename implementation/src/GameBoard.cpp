#include "GameBoard.h"

#include "CardStack.h"
#include "CardTypes.h"
#include <stdexcept>
#include <vector>

using namespace std;

BoardT::BoardT(vector<CardT> deck){
    vector<CardT> empty,Tab,Deck;
    if(not two_decks(init_seq(10), init_seq(8), CardStackT(deck),CardStackT(empty)))
        throw invalid_argument("The gameboard cannot be initialized");
    
    for(int i = 0; i <= 39; i++)
        Tab.push_back(deck[i]);

    for(int i = 40; i <= 103; i++)
        Deck.push_back(deck[i]);

    this->T = tab_deck(Tab);
    this->F = init_seq(8);
    this->D = CardStackT(Deck);
    this->W = CardStackT(empty);
    
}

bool BoardT::is_valid_tab_mv(CategoryT c,nat n0,nat n1){
    if(c == Tableau){
        if(not (is_valid_pos(Tableau,n0) && is_valid_pos(Tableau,n1)))
            throw out_of_range("It is not a valid position");

        return valid_tab_tab(n0,n1);
    }
    else if (c == Foundation){
        if(not (is_valid_pos(Tableau,n0) && is_valid_pos(Foundation,n1)))
            throw out_of_range("It is not a valid position");

        return valid_tab_foundation(n0,n1);
    }
    else if (c == Deck || c == Waste)   return false;

    else return false;
}


bool BoardT::is_valid_waste_mv(CategoryT c,nat n){

        if(this->W.size() == 0){
            throw invalid_argument("The Waste is empty, cannot move from Waste");
        }

        if (c == Tableau){
            if(not is_valid_pos(Tableau, n))
                throw out_of_range("It is not a valid position");

            return valid_waste_tab(n);
        }
        
        else if (c == Foundation){
            if(not is_valid_pos(Foundation, n))
                throw out_of_range("It is not a valid position");

            return valid_waste_foundation(n);
        }

        else if (c == Deck || c == Waste)   return false;

        else{ return false;}

}

bool BoardT::is_valid_deck_mv(){
    return this->D.size() > 0;
}

void BoardT::tab_mv(CategoryT c,nat n0,nat n1){
    try{
        if(not is_valid_tab_mv(c,n0,n1))
            throw invalid_argument("not a valid move from Tableau");
    }catch(out_of_range &e){throw invalid_argument("not a valid move from Tableau");};
    if(c == Tableau){
        this->T[n1] = this->T[n1].push(this->T[n0].top());
        this->T[n0] = this->T[n0].pop();
    }

    else if(c == Foundation){
        this->F[n1] = this->F[n1].push(this->T[n0].top());
        this->T[n0] = this->T[n0].pop();
    }
}

void BoardT::waste_mv(CategoryT c,nat n){
    try{
        if(not is_valid_waste_mv(c,n))
            throw invalid_argument("not a valid move from Waste");
    }catch(invalid_argument &e){throw invalid_argument("not a valid move from Waste");}catch(out_of_range &e){throw invalid_argument("not a valid move from Waste");};

    if(c == Tableau){
        this->T[n] = this->T[n].push(this->W.top());
        this->W = this->W.pop();
    }

    else if(c == Foundation){
        this->F[n] = this->F[n].push(this->W.top());
        this->W = this->W.pop();    
    }
}

void BoardT::deck_mv(){
    if(not is_valid_deck_mv())
        throw invalid_argument("The Deck is empty, cannot move from Deck");
    
    else{
        this->W = this->W.push(this->D.top());
        this->D = this->D.pop();
    }
}

CardStackT BoardT::get_tab(nat i){
    if(not is_valid_pos(Tableau,i))
        throw out_of_range("It is not a valid position");
    
    else{
        return this->T[i];
    }
}

CardStackT BoardT::get_foundation(nat i){
    if(not is_valid_pos(Foundation,i))
        throw out_of_range("It is not a valid position");
   
    else{
        return this->F[i];
    }
}

CardStackT BoardT::get_deck(){
    return this->D;
}

CardStackT BoardT::get_waste(){
    return this->W;
}


bool BoardT::valid_mv_exists(){

    return valid_tab_mv() or valid_waste_mv() or is_valid_deck_mv();
}

bool BoardT::is_win_state(){
    for(nat i = 0; i<= 7; i++){
        if(not (this->F[i].size() > 0 && this->F[i].top().r == KING))
            return false;
    }

    return true;
}





////////////////////////////Local Functions/////////////////////////////////////////
bool BoardT::valid_tab_mv(){
    try{
        for(nat index = 0; index < 10; index ++){
            for(nat i = 0; i < 10; i++){
                if(is_valid_pos(Tableau,index) && is_valid_pos(Tableau,i)){
                    if(is_valid_tab_mv(Tableau,index,i))    {return true;}
                }
            }


            for(nat i = 0; i < 8; i++){
                if(is_valid_pos(Tableau,index) && is_valid_pos(Foundation,i)){
                    if(is_valid_tab_mv(Foundation,index,i))     {return true;}
                }
            }
        }

        return false;
    }catch(invalid_argument &e){return false;};

}

bool BoardT::valid_waste_mv(){
    try{
        for(nat i = 0; i < 10; i++){
            if(is_valid_pos(Tableau,i)){
                if(is_valid_waste_mv(Tableau, i))   {return true;}
            }
        }


        for(nat i = 0; i < 8; i++){
            if(is_valid_pos(Foundation,i)){
                if(is_valid_waste_mv(Foundation, i))   {return true;}
            }
        }

        return false;
    }catch(invalid_argument &e){return false;};
}


bool BoardT::two_decks(SeqCrdStckT T,SeqCrdStckT F,CardStackT D,CardStackT W){

    for(RankT s = 1; s <=13; s++ ){
        int count1 = 0; //Card with suit Spade and rank i
        int count2 = 0; //Card with suit Heart and rank i
        int count3 = 0; //Card with suit Diamond and rank i
        int count4 = 0; //Card with suit Club and rank i


        for(nat i = 0; i < T.size(); i++){
            vector<CardT> temp = T[i].toSeq();
                for(nat j = 0; j < temp.size(); j++){
                    if(temp[j].s == Spade && temp[j].r == s) count1 += 1;
                    else if(temp[j].s == Heart && temp[j].r == s)   count2 += 1;  
                    else if(temp[j].s == Diamond && temp[j].r == s)   count3 += 1;  
                    else if(temp[j].s == Club && temp[j].r == s)   count4 += 1;  
                }
        }

        for(nat i = 0; i < F.size(); i++){
            vector<CardT> temp = F[i].toSeq();
                for(nat j = 0; j < temp.size(); j++){
                    if(temp[j].s == Spade && temp[j].r == s) count1 += 1;
                    else if(temp[j].s == Heart && temp[j].r == s)   count2 += 1;  
                    else if(temp[j].s == Diamond && temp[j].r == s)   count3 += 1;  
                    else if(temp[j].s == Club && temp[j].r == s)   count4 += 1;  
                }
        }
        vector<CardT> tempD = D.toSeq();
        for(nat i = 0; i < tempD.size(); i++){
            if(tempD[i].s == Spade && tempD[i].r == s) count1 += 1;
            else if(tempD[i].s == Heart && tempD[i].r == s)   count2 += 1;  
            else if(tempD[i].s == Diamond && tempD[i].r == s)   count3 += 1;  
            else if(tempD[i].s == Club && tempD[i].r == s)   count4 += 1;

        }

        vector<CardT> tempW = W.toSeq();
        for(nat i = 0; i < tempW.size(); i++){
            if(tempW[i].s == Spade && tempW[i].r == s) count1 += 1;
            else if(tempW[i].s == Heart && tempW[i].r == s)   count2 += 1;  
            else if(tempW[i].s == Diamond && tempW[i].r == s)   count3 += 1;  
            else if(tempW[i].s == Club && tempW[i].r == s)   count4 += 1;

        }
        
        if (not(count1 == 2 && count2 == 2 && count3 == 2 && count4 == 2))
            return false;

    }
    return true;
}



nat BoardT::cnt_cards(SeqCrdStckT T,SeqCrdStckT F,CardStackT D,CardStackT W){
    
    return  cnt_cards_seq(T) + cnt_cards_seq(F) +  cnt_cards_stack(D) +  cnt_cards_stack(W);

}

nat BoardT::cnt_cards_seq(SeqCrdStckT S){
    nat count;
    for (nat i = 0; i < S.size(); i++)
        count +=  cnt_cards_stack(S[i]);
    return count;
}

nat BoardT::cnt_cards_stack(CardStackT s){
    nat count = s.size();
    return count;
}

SeqCrdStckT BoardT::init_seq(nat n){
    SeqCrdStckT result;
    for(nat i = 0; i < n; i++){
        CardStackT empty;
        result.push_back(empty);
    }
    return result;

}


SeqCrdStckT BoardT::tab_deck(vector<CardT> deck){
    SeqCrdStckT T;
    for(nat i = 0; i < 10; i++){
        vector<CardT> temp;
        for(nat count = 0; count < 4; count++){
            temp.push_back(deck[4*i + count]);
        }
        T.push_back(CardStackT(temp));
    }
    return T;
}

bool BoardT::is_valid_pos(CategoryT c, nat n){
    if(c == Tableau && not (0<=n && n <= 9))
        return false;
    else if(c == Foundation && not (0<=n && n <= 7))
        return false;
    return true;
        
}

bool BoardT::valid_tab_tab(nat n0, nat n1){
    if(this->T[n0].size() > 0){
        if(this->T[n1].size() > 0)
            return  tab_placeable(this->T[n0].top(),this->T[n1].top());
        else if(this->T[n1].size() == 0)
            return true;
        return false;
    }

    else if(this->T[n0].size() == 0){
        if(this->T[n1].size() > 0 || this->T[n1].size() == 0)
            return false;
        return true;
    }

    else return false;
}

bool BoardT::valid_tab_foundation(nat n0, nat n1){
    if(this->T[n0].size() > 0){
        if(this->F[n1].size() > 0)
            return  foundation_placeable(this->T[n0].top(),this->F[n1].top());
        else if(this->F[n1].size() == 0)
            return this->T[n0].top().r == ACE;
        return true;
    }

    else if(this->T[n0].size() == 0){
        if(this->F[n1].size() > 0 || this->F[n1].size() == 0)
            return false;
        return false;
    }

    else return false;
}

bool BoardT::valid_waste_tab(nat n){
    if(this->T[n].size() > 0) return  tab_placeable(this->W.top(),this->T[n].top());
    else if(this->T[n].size() == 0) return true;

    else return false;
}

bool BoardT::valid_waste_foundation(nat n){
    if(this->T[n].size() > 0) return  foundation_placeable(this->W.top(),this->F[n].top());
    else if(this->T[n].size() == 0) return this->W.top().r == ACE;

    else return false;
}

bool BoardT::tab_placeable(CardT c, CardT d){
    return (c.s == d.s && c.r == d.r - 1);
}

bool BoardT::foundation_placeable(CardT c, CardT d){
    return (c.s == d.s && c.r == d.r + 1);
}

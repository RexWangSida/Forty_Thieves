// Implementation here
#include "Stack.h"
#include "CardTypes.h"
#include <stdexcept>

using namespace std;

template <class T>
Stack<T>::Stack(vector<T> s)
{

    this->S = s;
}

template <class T>
Stack<T>::Stack()
{

    this->S = {};
}

template <class T>
Stack <T> Stack<T>::push(T e)
{
    this->S.push_back(e);
    return Stack<T>(this->S);
}


template <class T>
Stack<T> Stack<T>::pop()
{
    if(this->S.size() == 0){ throw out_of_range("The Stack is empty, cannot pop a value from top");}
    else{
        this->S.pop_back();
        return Stack<T>(this->S);
    }
}

template <class T>
T Stack<T>::top()
{
    if(this->S.size() == 0){ throw out_of_range("The Stack is empty, cannot get a value from top");}
    else{
        return this->S.back();

    }
}


template <class T>
nat Stack<T>::size()
{
    return this->S.size();
}

template <class T>
vector<T> Stack<T>::toSeq()
{
    return this->S;
}


// Keep this at bottom
template class Stack<CardT>;



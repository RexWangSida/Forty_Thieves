/**
 *  \file Stack.h
 *  \author Sida Wang
 *  \brief Generic Stack Module as a template to generate instance of a stack of T type
 */
#ifndef A3_STACK_H_
#define A3_STACK_H_
#include <vector>
/** 
 * \brief The nat which represents the natural number is defined by unsigned integer
 */
typedef unsigned int nat;

/**
 *  \brief Class representing a stack of T type
 *  \details The class supports fundamental utilities of a stack
 */
template <class T>
class Stack
{
    private:
        ///The sequence of T
        std::vector<T> S;
    public:
        /**
         *  \brief Constructs a new stack of T type
         *  \param s A sequence of T to be implemented as a stack
         */
        Stack(std::vector<T> s);
        /**
         *  \brief Constructs a new empty Stack of T types(default constructor)
         */
        Stack();
        /**
         *  \brief Push an element to the stack
         *  \param e An element to be pushed of T type
         *  \return A new stack with the pushed element
         */
        Stack<T> push(T e);
        /**
         *  \brief Pop an element to the stack
         *  \return A new stack without the poped element
         */
        Stack<T> pop();
        /**
         *  \brief Get the element on the top of the stack
         *  \return A T type element at the top of the stack
         */
        T top();
        /**
         *  \brief Get the size of the stack
         *  \return The size of the stack, which is represented by an natural number
         */
        nat size();
        /**
         *  \brief Convert the stack to a sequence of T
         *  \return A sequence of T, whose elements are in the same order as in stack
         */
        std::vector<T> toSeq();  
};
#endif

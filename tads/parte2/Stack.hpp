#ifndef _TSTACK_TAD_
#define _TSTACK_TAD_

#include <iostream>
#include "../../funciones/lists.hpp"

using namespace std;

template<typename T>
struct Stack
{
   Node<T>* nodoPila;
   int pos;
   int size;
};

template<typename T>//Crea una pila vacía
Stack<T> stack()
{
   Stack<T> st;
   st.nodoPila = NULL;
   st.pos = 0;
   st.size = 0;
   return st;
}

template<typename T>//Apila el elemento e
T* stackPush(Stack<T>& st,T e)
{
   Node<T>* aux = push<T>(st.nodoPila,e);
   T* r = &aux->info;
   st.size++;
   return r;
}

template<typename T>//Desapila un elemento
T stackPop(Stack<T>& st)
{
   T r = pop<T>(st.nodoPila);
   st.size--;
   return r;
}

template<typename T>//Retorna true o false según la pila tenga elementos o no
bool stackIsEmpty(Stack<T> st)
{
   return isEmpty<T>(st.nodoPila);
}

template<typename T>//Retorna la cantidad de elementos que tiene la pila
int stackSize(Stack<T> st)
{
   return st.size;
}

#endif

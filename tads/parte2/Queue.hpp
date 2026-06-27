#ifndef _TQUEUE_TAD_
#define _TQUEUE_TAD_

#include <iostream>
#include "../../funciones/lists.hpp"

using namespace std;

template<typename T>
struct Queue
{
   Node<T>* nodoInicial;
   Node<T>* nodoFinal;
   int pos;
   int size;
};

template<typename T>//Crea una cola vacía
Queue<T> queue()
{
   Queue<T> q;
   q.nodoInicial = NULL;
   q.nodoFinal = NULL;
   q.pos = 0;
   q.size = 0;
   return q;
}

template<typename T>//Encola el elemento e
T* queueEnqueue(Queue<T>& q,T e)
{
   Node<T>* aux = enqueue<T>(q.nodoInicial,q.nodoFinal,e);
   T* r = &aux->info;
   q.size++;
   return r;
}

template<typename T>//Desencola un elemento
T queueDequeue(Queue<T>& q)
{
   T r = dequeue<T>(q.nodoInicial,q.nodoFinal);
   q.size--;
   return r;
}

template<typename T>//Retorna true o false según la cola tenga elementos o no
bool queueIsEmpty(Queue<T> q)
{
   return isEmpty<T>(q.nodoInicial);
}

template<typename T>//Retorna la cantidad de elementos que tiene la cola
int queueSize(Queue<T> q)
{
   return q.size;
}

#endif

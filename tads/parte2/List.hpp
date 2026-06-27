#ifndef _TLIST_TAD_
#define _TLIST_TAD_

#include <iostream>
#include "../../funciones/lists.hpp"

using namespace std;

template<typename T>
struct List
{
   Node<T>* nodoInicial;
   int pos;
   int size;
};

template<typename T>//Crea una lista vacía
List<T> list()
{
   List<T> lst;
   lst.nodoInicial = NULL;
   lst.pos = 0;
   lst.size = 0;
   return lst;
}

template<typename T>//Agrega un elemento al final de la lista
T* listAdd(List<T>& lst,T e)
{
   Node<T>* aux = add<T>(lst.nodoInicial,e);
   T* r = &aux->info;
   lst.size++;
   return r;
}

template<typename T>//Agrega el elemento e al inicio de la lista
T* listAddFirst(List<T>& lst,T e)
{
   Node<T>* aux = addFirst<T>(lst.nodoInicial,e);
   T* r = &aux->info;
   lst.size++;
   return r;
}

template<typename T,typename K>//Remueve el elemento que concuerde con k según la función cmpTK
T listRemove(List<T>& lst,K k,int cmpTK(T,K))
{
   T r = remove<T,K>(lst.nodoInicial,k,cmpTK);
   lst.size--;
   return r;
}

template<typename T>//Desenlaza y libera el primer nodo de la lista enlazada, retornando el valor del elemento que contenía
T listRemoveFirst(List<T>& lst)
{
   T r = removeFirst<T>(lst.nodoInicial);
   lst.size--;
   return r;
}

template<typename T,typename K>//Retorna la dirección del primer elemento concordante con k según cmpTK
T* listFind(List<T> lst,K k,int cmpTK(T,K))
{
   Node<T>* aux = find<T,K>(lst.nodoInicial,k,cmpTK);
   T* r = &aux->info;
   return r;
}

template<typename T>//Indica si la lista está vacía o tiene elementos
bool listIsEmpty(List<T> lst)
{
   return isEmpty<T>(lst.nodoInicial);
}

template<typename T>//Indica cuántos elementos tiene la lista
int listSize(List<T> lst)
{
   return lst.size;
}

template<typename T>//Libera la memoria que ocupa la lista
void listFree(List<T>& lst)
{
   free<T>(lst.nodoInicial);
   List<T>* aux = &lst;
   delete aux;
   lst = NULL;
}

template<typename T>//Busca en la lista la primera ocurrencia de t, y retorna la dirección del valor. Si t no existe en la lista entonces lo insertar en orden, según el criterio establecido por cmpTT, y retorna la dirección del valor insertado
T* listDiscover(List<T>& lst,T t,int cmpTT)
{
   bool aux1;
   Node<T>* aux2 = searchAndInsert<T>(lst.nodoInicial,t,aux1,cmpTT);
   T* r = &aux2->info;
   if(!aux1){
      lst.size++;
   }
   return r;
}

template<typename T>//Inserta un elemento según el orden que establece cmpTT. La lista debe estar ordenada (según cmpTT) o vacía
T* listOrderedInsert(List<T>& lst,T t,int cmpTT(T,T))
{
   Node<T>* aux = orderedInsert<T>(lst.nodoInicial,t,cmpTT);
   lst.size++;
   T* r = &aux->info;
   return r;
}

template<typename T>//Ordena la lista según el criterio que establece cmpTT
void listSort(List<T>& lst,int cmpTT(T,T))
{
   sort<T>(lst.nodoInicial,cmpTT);
}

template<typename T>//Prepara la lista para iterarla
void listReset(List<T>& lst)
{
   lst.pos = 0;
}

template<typename T>//Indica si quedan más elementos para seguir iterando la lista
bool listHasNext(List<T> lst)
{
   if(lst.pos<lst.size){
      return true;
   }else{
      return false;
   }
}

template<typename T>//Retorna la dirección del siguiente elemento de la lista en la iteración
T* listNext(List<T>& lst)
{
   Node<T>* aux = lst.nodoInicial;
   for(int f=0; f<lst.pos; f++){
      aux = aux->sig;
   }
   T* r = &aux->info;
   lst.pos++;
   return r;
}

template<typename T>//Retorna la dirección del siguiente elemento de la lista en la iteración, cambiando el valor de endOfList en funcion de si se llego al final de la lista
T* listNext(List<T>& lst,bool& endOfList)
{
   T* r = listNext<T>(lst);
   if(listHasNext<T>(lst)){
      endOfList = false;
   }else{
      endOfList = true;
   }
   return r;
}

#endif

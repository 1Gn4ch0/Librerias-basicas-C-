#ifndef _TARR_TAD_
#define _TARR_TAD_

#include <iostream>
#include <stdlib.h>
#include "../../funciones/arrays.hpp"

using namespace std;

template<typename T>
struct Array
{
   T* arr = new T[10];
   int longitud = 0;
   int cap = 10;
};

template<typename T>//Crea un Array vacio
Array<T> array()
{
   Array<T> ret;
   return ret;
}

template<typename T>//Agrega un elemento al final del Array
int arrayAdd(Array<T>& a,T t)
{
   if(a.cap==a.longitud){
      T* aux = new T[a.cap*2];
      for(int f=0; f<a.longitud; f++){
         aux[f]=a.arr[f];
      }
      a.cap*2;
      delete [] a.arr;
      a.arr = aux;
   }
   return add<T>(a.arr,a.longitud,t);
}

template<typename T>//Retorna la dirección del elemento de a ubicado en la posición p (empezando de 0)
T* arrayGet(Array<T> a,int p)
{
   return a.arr+p;
}

template<typename T>//Asigna el elemento t en la posición p del Array a
void arraySet(Array<T>& a,int p,T t)
{
   if(p>=a.longitud){
      arrayAdd<T>(a, t);
   }else{
      remove<T>(a.arr,a.longitud,p);
      insert<T>(a.arr,a.longitud,t,p);
   }
}

template<typename T>//Inserta t en la posición p del array a
void arrayInsert(Array<T>& a,T t,int p)
{
   if(a.cap==a.longitud){
      T* aux = new T[a.cap*2];
      for(int f=0; f<a.longitud; f++){
         aux[f]=a.arr[f];
      }
      a.cap*2;
      delete [] a.arr;
      a.arr = aux;
   }
   insert<T>(a.arr,a.longitud,t,p);
}

template<typename T>//Retorna la longitud actual del array
int arraySize(Array<T> a)
{
   return a.longitud;
}

template<typename T>//Devuelve y remueve el elemento de a ubicado en la posición p
T arrayRemove(Array<T>& a,int p)
{
   return remove<T>(a.arr,a.longitud,p);
}

template<typename T>//Remueve todos los elemento de a dejándolo vacío, con longitud 0
void arrayRemoveAll(Array<T>& a)
{
   T* aux = new T[10];
   delete [] a.arr;
   a.arr = aux;
   a.longitud = 0;
}

template<typename T,typename K>//Retorna la posición que k ocupa dentro de a, según la función de comparación cmpTK, o -1 si a no contiene a k
int arrayFind(Array<T> a,K k,int cmpTK(T,K))
{
   return find<T,K>(a.arr,a.longitud,k,cmpTK);
}

template<typename T>//Inserta t en a según el criterio de precedencia que establece cmpTT
int arrayOrderedInsert(Array<T>& a,T t,int cmpTT(T,T))
{
   return orderedInsert<T>(a.arr,a.longitud,t,cmpTT);
}

template<typename T>//Descubre (busca, y si no encuentra lo agrega) al elemento t en el array a
T* arrayDiscover(Array<T>& a,T t,int cmpTT(T,T))
{
   if(arrayFind<T,T>(a,t,cmpTT)==-1){
      arrayAdd<T>(a,t);
      return arrayGet<T>(a,a.longitud-1);
   }else{
      return arrayGet<T>(a,arrayFind<T,T>(a,t,cmpTT));
   }
}

template<typename T>//Ordena el array a según establece cmpTT
void arraySort(Array<T>& a,int cmpTT(T,T))
{
   sort<T>(a.arr,a.longitud,cmpTT);
}

#endif

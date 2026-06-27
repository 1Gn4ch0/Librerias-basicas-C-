#ifndef _TCOLL_T_
#define _TCOLL_T_

#include <iostream>
#include "../../funciones/strings.hpp"

using namespace std;

template<typename T>
struct Coll
{
   string list;
   char sep;
   int pos;
};

template<typename T>//Colección vacía preparada para contener elementos tipo T con separador sep
Coll<T> coll(char sep)
{
   Coll<T> c;
   c.list = "";
   c.sep = sep;
   c.pos = 0;
   return c;
}

template<typename T>//Colección vacía preparada para contener elementos tipo T con separador '|'
Coll<T> coll()
{
   return coll<T>('|');
}

template<typename T>//Cantidad de elementos que tiene la colección c
int collSize(Coll<T> c)
{
   return tokenCount(c.list, c.sep);
}

template<typename T>//Remueve de la colección c todos sus elementos, dejándola vacía
void collRemoveAll(Coll<T>& c)
{
   c.list = "";
   c.pos = 0;
}

template<typename T>//Remueve de la colección c el elemento ubicado en la posición p
void collRemoveAt(Coll<T>& c, int p)
{
   removeTokenAt(c.list, c.sep, p);
}

template<typename T>//Agrega el elemento t al final de la colección c
int collAdd(Coll<T>& c,T t,string tToString(T))
{
   addToken(c.list, c.sep, tToString(t));
   if(collSize(c)==findToken(c.list, c.sep, tToString(t))){
      return -1;
   }else{
      return 0;
   }
}

template <typename T>//Reemplaza por t al elemento que se ubica en la posición p
void collSetAt(Coll<T>& c,T t,int p,string tToString(T))
{
   if(collSize(c)==1){
      c.list = tToString(t);
   }else{
      setTokenAt(c.list, c.sep, tToString(t), p);
   }
}

template <typename T>//Elemento que se ubica en la posición p de la colección c
T collGetAt(Coll<T> c,int p,T tFromString(string))
{
   if(collSize(c)==1){
      return tFromString(c.list);
   }else{
      return tFromString(getTokenAt(c.list, c.sep, p));
   }
}

template <typename T, typename K>//Determina la posicion del elemento k en la colección c
int collFind(Coll<T> c,K k,int cmpTK(T,K),T tFromString(string))
{
   for(int f=0;f<collSize(c);f++){
      if(cmpTK(collGetAt<T>(c, f, tFromString), k) == 0){
         return f;
      }
   }
   return -1;
}

template <typename T>//Ordena los elementos de la colección c de menor a mayor según el criterio de precedencia que establece cmpTT
void collSort(Coll<T>& c,int cmpTT(T,T),T tFromString(string),string tToString(T))
{
   T menor;
   Coll<T> neC = coll<T>(c.sep);
   int aux1 = collSize(c);
   int aux2 = aux1;
   int p = 0;
   for(int b=0; b<aux1; b++){
      if(aux2 != 1){
         menor = collGetAt<T>(c,0,tFromString);
         for(int v=1; v<aux2; v++){
            if(cmpTT(menor,collGetAt<T>(c,v,tFromString))<=0){ // collGetAt<T>(c,v,tFromString)-menor
               menor = collGetAt<T>(c,v,tFromString);
               p = v;
            }
         }
         aux2--;
         collAdd(neC,menor,tToString);
         collRemoveAt(c,p);
         p = 0;
      }else{
         neC.list = neC.list + neC.sep + c.list;
      }
   }
   c = neC;
}

template<typename T>//Retorna true o false según queden, en la colección c, más elementos para continuar iterando
bool collHasNext(Coll<T> c)
{
   if(c.pos == collSize(c)){
      return false;
   }else{
      return true;
   }
}

template<typename T>//Retorna el elemento actual de la colección c
T collNext(Coll<T>& c,T tFromString(string))
{
   T r = collGetAt<T>(c, c.pos, tFromString);
   c.pos++;
   return r;
}

template<typename T>//Retorna el elemento actual de la colección c, indicando si se llegó al final de la colección
T collNext(Coll<T>& c,bool& endOfColl,T tFromString(string)) //en tu puta vida la uses
{
   T r = collGetAt<T>(c, c.pos, tFromString);
   c.pos++;
   if(collHasNext(c)){
      endOfColl = false;
   }else{
      endOfColl = true;
   }
   return r;
}

template<typename T>//Reinicia la colección c para que la podamos volver a iterar
void collReset(Coll<T>& c)
{
   c.pos = 0;
}

#endif

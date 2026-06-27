#ifndef _TMAP_TAD_
#define _TMAP_TAD_

#include <iostream>
#include "Array.hpp"

using namespace std;

template<typename K,typename V>
struct Map
{
   Array<K> keys;
   Array<V> values;
   int posK = 0;
   int posV = 0;
};

template<typename K,typename V>//Crea un Map vacio
Map<K,V> map()
{
   Map<K,V> m;
   return m;
}

template<typename K,typename V>//Retorna la dirección de memoria del valor asociado a la clave k o NULL si m no contiene ningún valor asociado a dicha clave
V* mapGet(Map<K,V> m,K k)
{
   int p = -1;
   for(int f=0; f<arraySize<K>(m.keys); f++){
      if(m.keys.arr[f]==k){
         p = f;
         f = arraySize<K>(m.keys);
      }
   }
   if(p==-1){
      return NULL;
   }else{
      return arrayGet<V>(m.values,p);
   }
}

template<typename K,typename V>//Agrega al map m el elemento v asociado a la clave k. Si existía una entrada vinculada a k reemplaza el valor anterior por v. Devuelve la dirección de v en m
V* mapPut(Map<K,V>& m,K k,V v)
{
   V* di = mapGet<K,V>(m,k);
   if(di == NULL){
      arrayAdd<K>(m.keys,k);
      arrayAdd<V>(m.values,v);
      return arrayGet<V>(m.values,m.values.longitud-1);
   }else{
      *di = v;
      return di;
   }
}

template<typename K,typename V>//Verifica si m contiene a k
bool mapContains(Map<K,V> m,K k)
{
   V* di = mapGet<K,V>(m,k);
   if(di == NULL){
      return false;
   }else{
      return true;
   }
}

template<typename K,typename V>//Devuelve y elimina de m la entrada identificada con la clave k
V mapRemove(Map<K,V>& m,K k)
{
   int p;
   for(int f=0; f<arraySize<K>(m.keys); f++){
      if(m.keys.arr[f]==k){
         p = f;
         f = arraySize<K>(m.keys);
      }
   }
   arrayRemove<K>(m.keys,p);
   return arrayRemove<V>(m.values,p);
}

template<typename K,typename V>//Elimina todas las entradas del map m
void mapRemoveAll(Map<K,V>& m)
{
   arrayRemoveAll<K>(m.keys);
   arrayRemoveAll<V>(m.values);
   m.posK = 0;
   m.posV = 0;
}

template<typename K,typename V>//Retorna la cantidad actual de entradas que tiene m
int mapSize(Map<K,V> m)
{
   return arraySize<K>(m.keys);
}

template<typename K,typename V>//Indica si quedan más elementos para continuar iterando el map
bool mapHasNext(Map<K,V> m)
{
   if(m.posK<m.keys.longitud & m.posV<m.values.longitud){
      return true;
   }else{
      return false;
   }
}

template<typename K,typename V>//Permite iterar sobre las claves del map. Esta función es mutuamente excluyente respecto de mapNextValue
K mapNextKey(Map<K,V>& m)
{
   m.posK++;
   return m.keys.arr[m.posK-1];
}

template<typename K,typename V>//Permite iterar sobre los valores que contiene el map. Esta función es mutuamente excluyente despecto de mapNextKey
V* mapNextValue(Map<K,V>& m)
{
   m.posV++;
   return m.values.arr+m.posV-1;
}

template<typename K,typename V>//Prepara el map para comenzar una nueva iteración
void mapReset(Map<K,V>& m)
{
   m.posK = 0;
   m.posV = 0;
}

template<typename K,typename V>//Descubre (busca, y si no encuentra agrega) una entrada {k,v} en el map m
V* mapDiscover(Map<K,V>& m,K k,V v)
{
   V* va = mapGet<K,V>(m,k);
   if(va!=NULL){
      if(*va!=v){cout << "mapDiscover horror" << endl;}
      int p;
      for(int f=0; f<arraySize<K>(m.keys); f++){
         if(m.keys.arr[f]==k){
            p = f;
            f = arraySize<K>(m.keys);
         }
      }
      m.posK = p+1;
      m.posV = p+1;
   }else{
      va = mapPut<K,V>(m,k,v);
      int p;
      for(int f=0; f<arraySize<K>(m.keys); f++){
         if(m.keys.arr[f]==k){
            p = f;
            f = arraySize<K>(m.keys);
         }
      }
      m.posK = p+1;
      m.posV = p+1;
   }
   return va;
}

template<typename K,typename V>//Ordena el map aplicando sobre sus claves el criterio que establece cmpKK
void mapSortByKeys(Map<K,V>& m,int cmpKK(K,K))
{
   Array<K> auxK = array<K>();
   for(int f = 0; f<m.keys.longitud; f++){
      arrayAdd<K>(auxK,m.keys.arr[f]);
   }
   arraySort<K>(auxK,cmpKK);
   Array<V> auxV = array<V>();
   for(int f = 0; f<m.values.longitud; f++){
      V* diV = mapGet<K,V>(m,auxK.arr[f]);
      arrayAdd<V>(auxV,*diV);
   }
   delete [] m.keys;
   m.keys = auxK;
   delete [] m.values;
   m.values = auxV;
}

template<typename K,typename V>//Ordena el map aplicando sobre sus values el criterio que establece cmpVV
void mapSortByValues(Map<K,V>& m,int cmpVV(V,V))
{
   Array<V> auxV = array<V>();
   Array<K> auxK = array<K>();
   V menor;
   K menorK;
   int pm;
   int auxL = m.values.longitud;
   for(int b=0; b<m.values.longitud; b++){
      menor = m.values.arr[0];
      menorK = m.keys.arr[0];
      pm = 0;
      for(int v=1; v<auxL; v++){
         if(cmpTT(m.values.arr[v],menor)<=0){
            menor = m.values.arr[v];
            menorK = m.keys.arr[v];
            pm = v;
         }
      }
      arrayAdd<V>(auxV,menor);
      arrayRemove<V>(m.values,pm);
      arrayAdd<K>(auxK,menorK);
      arrayRemove<K>(m.keys,pm);
   }
   delete [] m.values;
   m.values = auxV;
   delete [] m.keys;
   m.keys = auxK;
}

#endif

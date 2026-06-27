#ifndef _TARRAYS_T_
#define _TARRAYS_T_

#include <iostream>

template <typename T>//Agrega el elemento e al final de arr incrementando su longitud len
int add(T arr[],int& len,T e)
{
   arr[len] = e;
   len++;
   return len-1;
}

template <typename T>//Inserta el elemento e en la posición p del array arr. Desplaza los elementos ubicados a partir de p+1 e incrementa la longitud len
void insert(T arr[],int& len,T e,int p)
{
   for(int f = len; f>p; f--){
      arr[f]=arr[f-1];
   }
   arr[p]=e;
   len++;
}

template <typename T>//Remueve el elemento ubicado en la posición p del array arr. Desplaza ubicados a partir de p y decrementa la longitud len
T remove(T arr[],int& len,int p)
{
   len--;
   T ret = arr[p];
   for(int f = p; f<len; f++){
      arr[f]=arr[f+1];
   }
   return ret;
}

template <typename T, typename K>//Retorna la posición de la primera ocurrencia de k dentro de arr o un valor negativo si arr no contiene a k
int find(T arr[],int len,K k,int cmpTK(T,K))
{
   for(int f=0; f<len; f++){
      if(cmpTK(arr[f],k)==0){
         return f;
      }
   }
   return -1;
}

template <typename T>//Inserta e dentro de arr según el criterio de precedencia que establece cmpTT, y retorna la posición donde dicho elemento quedó insertado. El array arr debe estar ordenado o vacío. (El orden predeterminado es de menor a mayor)
int orderedInsert(T arr[],int& len,T e,int cmpTT(T,T))
{
   int p = 0;
   for(int f = 0; f<len; f++){
      if((cmpTT(arr[f],e)<=0 && cmpTT(arr[f+1],e)>0)){
         p = f+1;
         insert<T>(arr,len,e,p);
         len++;
         return p;
      }
      if(cmpTT(arr[f],e)>0){
         insert<T>(arr,len,e,0);
         len++;
         return 0;
      }
   }
   return -1; //error
}

template <typename T>//Ordena arr según el criterio de precedencia que establece cmpTT
void sort(T arr[],int len,int cmpTT(T,T))
{
   T neA[len];
   int neLen = 0;
   T menor;
   int pm;
   int aux = len;
   for(int b=0; b<len; b++){
      menor = arr[0];
      pm = 0;
      for(int v=1; v<aux; v++){
         if(cmpTT(arr[v],menor)<=0){ //arr[v]-menor
            menor = arr[v];
            pm = v;
         }
      }
      add<T>(neA,neLen,menor);
      remove<T>(arr,aux,pm);
   }
   for(int f=0; f<len; f++){
      arr[f]=neA[f];
   }
}

#endif

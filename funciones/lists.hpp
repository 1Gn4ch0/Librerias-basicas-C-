#ifndef _TLIST_T_
#define _TLIST_T_

#include <iostream>
#include <stdio.h>

template <typename T>
struct Node
{
   T info;
   Node<T>* sig;
};

template <typename T>//Agrega el elemento e al final de la lista direccionada por p
Node<T>* add(Node<T>*& p,T e)
{
   Node<T>* nuevo = new Node<T>;
   nuevo->info = e;
   nuevo->sig = NULL;
   if(p==NULL){
      p = nuevo;
   }else{
      Node<T>* aux = p;
      while(aux->sig!=NULL){
         aux = aux->sig;
      }
      aux->sig = nuevo;
   }
   return nuevo;
}

template <typename T>//Agrega el elemento e al inicio de la lista direccionada por p
Node<T>* addFirst(Node<T>*& p,T e)
{
   Node<T>* nuevo = new Node<T>;
   nuevo->info = e;
   nuevo->sig = p;
   p = nuevo;
   return nuevo;
}

template <typename T, typename K>//Remueve la primera ocurrencia del elemento concordante con cmpTK
T remove(Node<T>*& p,K k,int cmpTK(T,K))
{
   T r;
   Node<T>* auxP = p;
   if(cmpTK(auxP->info,k)==0){
      p = auxP->sig;
      r = auxP->info;
      delete auxP;
   }else{
      while(auxP->sig!=NULL && cmpTK((auxP->sig)->info,k)!=0){
         auxP = auxP->sig;
      }
      if(auxP->sig==NULL){
         cout << "list.remove: valor no pertenece a la lista" << endl;
      }
      Node<T>* auxR = auxP->sig;
      auxP->sig = (auxP->sig)->sig;
      r = auxR->info;
      delete auxR;
   }
   return r;
}

template <typename T>//Remueve el primer elemento de la lista direccionada por p
T removeFirst(Node<T>*& p)
{
   T r;
   Node<T>* auxP = p;
   p = auxP->sig;
   r = auxP->info;
   delete auxP;
   return r;
}

template <typename T, typename K>//Retorna la dirección del nodo que contiene la primera ocurrencia de k según cmpTK o NULL si ningún elemento concuerda
Node<T>* find(Node<T>* p,K k,int cmpTK(T,K))
{
   if(p!=NULL){
      while(p->sig!=NULL && cmpTK(p->info,k)!=0){
         p = p->sig;
      }
      if(p->sig==NULL && cmpTK(p->info,k)!=0){
         return NULL;
      }else{
         return p;
      }
   }else{
      return NULL;
   }
}

template <typename T>//Inserta el elemento e en la lista direccionada por p según el criterio que establece la función cmpTT. La lista debe estar vacía u ordenada según cmpTT (el orden predeterminado es menor a mayor)
Node<T>* orderedInsert(Node<T>*& p,T e,int cmpTT(T,T))
{
   if(p==NULL || cmpTT(p->info,e)>=0){
      return addFirst<T>(p,e);
   }else{
      Node<T>* auxP = p;
      while(auxP->sig!=NULL){
         if(cmpTT(auxP->info,e)<=0 && cmpTT((auxP->sig)->info,e)>=0){
            Node<T>* nuevo = new Node<T>;
            nuevo->info = e;
            nuevo->sig = auxP->sig;
            auxP->sig = nuevo;
            return nuevo;
         }
         auxP = auxP->sig;
      }
      return add<T>(p,e);
   }
}

template <typename T>//Busca en la lista direccionada por p la primera ocurrencia de e, y retorna la dirección del nodo que lo contiene. Si e no existe en la lista entonces lo insertar en orden, según el criterio establecido por cmpTT, y retorna la dirección del nodo insertado. Asigna true o false a enc según e fue encontrado o insertado
Node<T>* searchAndInsert(Node<T>*& p,T e,bool& enc,int cmpTT(T,T))
{
   Node<T>* r = find<T,T>(p,e,cmpTT);
   if(r==NULL){
      enc = false;
      return orderedInsert<T>(p,e,cmpTT);
   }else{
      enc = true;
      return r;
   }
}

template <typename T>//Ordena la lista direccionada por p según el criterio que establece la función de comparación cmpTT (el orden predeterminado es menor a mayor)
void sort(Node<T>*& p,int cmpTT(T,T))
{
   Node<T>* newP = NULL;
   while(p!=NULL){
      orderedInsert<T>(newP,removeFirst<T>(p),cmpTT);
   }
   p = newP;
}

template <typename T>//Indica si la lista direccionada por p tiene o no elemento
bool isEmpty(Node<T>* p)
{
   if(p==NULL){
      return true;
   }else{
      return false;
   }
}

template <typename T>//Libera la memoria que utiliza lista direccionada por p. Asigna NULL a p
void free(Node<T>*& p)
{
   while(p!=NULL){
      removeFirst<T>(p);
   }
}

//---------------------------------------------------------------------------------------------------

template <typename T>//Inserta un nodo conteniendo a e al inicio de la lista direccionada por p (stack)
Node<T>* push(Node<T>*& p,T e)
{
   return addFirst<T>(p,e);
}

template <typename T>//Remueve el primer nodo de la lista direccionada por p (stack)
T pop(Node<T>*& p)
{
   return removeFirst<T>(p);
}

//---------------------------------------------------------------------------------------------------

template <typename T>//Agrega el elemento e al final la lista direccionada por q (queue)
Node<T>* enqueue(Node<T>*& p,Node<T>*& q,T e)
{
   q = add<T>(p,e);
   return q;
}

template <typename T>//Agrega el elemento e al final la lista circular direccionada por q (queue)
Node<T>* enqueue(Node<T>*& q,T e)
{
   if(q==NULL){
      q = add<T>(q,e);
      q->sig = q;
      return q;
   }else{
      Node<T>* aux;
      if(q->sig==NULL){
         aux = q;
      }else{
         aux = q->sig;
         while(aux->sig!=q){
            aux=aux->sig;
         }
      }
      aux->sig = new Node<T>;
      (aux->sig)->info = e;
      (aux->sig)->sig = q;
      return aux->sig;
   }
}

template <typename T>//Remueve el primer nodo de la lista direccionada por p (queue)
T dequeue(Node<T>*& p, Node<T>*& q)
{
   return removeFirst<T>(p);
}

template <typename T>//Remueve el primer nodo de la lista circular direccionada por q (queue)
T dequeue(Node<T>*& q)
{
   if(q->sig!=q){
      Node<T>* aux = q;
      while(aux->sig!=q){
         aux=aux->sig;
      }
      aux->sig=q->sig;
   }else{
      q->sig = NULL;
   }
   T r = removeFirst<T>(q);
   return r;
}

#endif

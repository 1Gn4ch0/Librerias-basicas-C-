#ifndef _TTOKENS_T_
#define _TTOKENS_T_

#include <iostream>
#include <stdio.h>
#include "strings.hpp"
using namespace std;

//Cantidad tokens que el separador sep genera en s
int tokenCount(string s,char sep)
{
   if(s==""){
      return 0;
   }else{
      int count = 1;
      count += charCount(s,sep);
      return count;
   }
}

//Agrega el token t al final de la cadena s
void addToken(string& s,char sep,string t)
{
   if(s!=""){
      s=s+sep+t;
   }else{
      s=t;
   }
}

//i-ésimo token de la cadena tokenizada s
string getTokenAt(string s,char sep, int i)
{
   if(i==0){
      return substring(s,0,indexOf(s,sep,0));
   }else{
      return substring(s,indexOfN(s,sep,i)+1,indexOfN(s,sep,i+1));
   }
}

//Remueve de s el token ubicado en la posición i
void removeTokenAt(string& s,char sep, int i)
{
   if(i==0){
      while(s[0]!=sep){
         s = removeAt(s,0);
      }
      s = removeAt(s,0);
   }else{
      int aux = indexOfN(s,sep,i);
      s = removeAt(s,aux);
      while(s[aux]!=sep && s[aux]!='\0'){
         s = removeAt(s,aux);
      }
   }
}

//Reemplaza por t el token de s ubicado en la posición i
void setTokenAt(string& s,char sep, string t,int i)
{
   removeTokenAt(s,sep,i);
   if(i==0){
      s=insertAt(s,0,sep);
      for(int f=length(t)-1;f>=0;f--){
         s=insertAt(s,0,t[f]);
      }
   }else{
      int aux = indexOfN(s,sep,i);
      for(int f=length(t)-1;f>=0;f--){
         s=insertAt(s,aux,t[f]);
      }
      s=insertAt(s,aux,sep);
   }
}

//Determina la posición que el token t ocupa dentro de la cadena s
int findToken(string s,char sep, string t)
{
   int aux = indexOf(s,t);
   for(int f=1;f<charCount(s,sep);f++){
      if(aux < indexOfN(s,sep,f) && getTokenAt(s,sep,f-1)==t){
         return f-1;
      }
   }
   return -1;
}

#endif

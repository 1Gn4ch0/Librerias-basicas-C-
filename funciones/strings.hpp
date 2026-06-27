#ifndef _TSTRINGS_T_
#define _TSTRINGS_T_

#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;

//Cantidad de caracteres que componen la cadena s
int length(string s)
{
   int cant = 0;
   while(s[cant] != '\0'){
      cant++;
   }
   return cant;
}

//Cantidad de veces que aparece el carácter c dentro de s
int charCount(string s,char c)
{
   int cant = 0;
   int cont = 0;
   while(s[cant] != '\0'){
      if(s[cant] == c){
         cont++;
      }
      cant++;
   }
   return cont;
}

//Subcadena de s comprendida entre las posiciones d (inclusive) y h (no inclusive)
string substring(string s,int d,int h)
{
   string r = "";
   for(d; d != h; d++){
      r = r + s[d]; 
   }
   return r;
}

//Subcadena de s comprendida entre la posición d y el final de la cadena
string substring(string s,int d)
{
   return substring(s,d,length(s));
}

/*Posición que ocupa la primera ocurrencia de un carácter c dentro de la cadena s, 
descartando los primeros offeset caracteres (desplazamiento inicial)*/
int indexOf(string s,char c,int offSet)
{
   int r = -1;
   for(int i=offSet+1; r==-1 && s[i]!='\0'; i++){
      if(s[i] == c){r = i;}
   }
   return r;
}

//Posición que ocupa la primera ocurrencia del carácter c dentro de la cadena s
int indexOf(string s,char c)
{
   return indexOf(s, c, -1);
}

/*Posición que ocupa la primera ocurrencia de toSearch dentro de la cadena s, 
descartando los primeros offeset caracteres (desplazamiento inicial)*/
int indexOf(string s,string toSearch,int offset)
{
   int r = -1;
   for(int i=offset+1; r==-1 && s[i]!='\0'; i++){
      if(s[i]==toSearch[0]){
         if(toSearch == substring(s, i, i+length(toSearch))){
            r=i;
         }
      }
   }
   return r;
}

//Primera ocurrencia de toSearch dentro de la cadena s
int indexOf(string s,string toSearch)
{
   return indexOf(s, toSearch, -1);
}

//Posición de la última ocurrencia del carácter c dentro de s
int lastIndexOf(string s,char c)
{
   int r = -1;
   for(int i=length(s); r==-1 && i!=-1; i--){
      if(s[i] == c){r = i;}
   }
   return r;
}

/*Posición de la n-ésima ocurrencia de c dentro de s. Si n es 0 (cero) retorna -1;
si n es mayor que la cantidad de ocurrencias de c retorna la longitud 
de la cadena s*/
int indexOfN(string s,char c,int n) 
{
   if(n==0){
      return -1;
   }else{
      int r = -1;
      for(n; n>0; n--){
         r = indexOf(s, c, r);
         if(r == -1){
            return length(s);
         }
      }
      return r;
   }
}

//Valor numérico que representa el carácter c (A-Z:10-35, 0-9:0-9)
int charToInt(char c)
{
   if(c>64){
      return toupper(c)-55;
   }else{
      return c-48;
   }
}

//Carácter que representa al valor de i (10-35:A-Z, 0-9:0-9)
char intToChar(int i)
{
   if(i>9){
      return i+55;
   }else{
      return i+48;
   }
}

//I-ésimo dígito del valor de n dentro de i
int getDigit(int n,int i)
{
   int e = 1;
   for(int f=0; f<i; f++){e=e*10;}
   int r = n/e;
   int aux = n/(10*e);
   r = (r*e - aux*e*10)/e;
   return r;
}

//Cantidad de dígitos que contiene el int n
int digitCount(int n)
{
   return length(to_string(n));
}

//Cadena de caracteres representando el int i
string intToString(int i)
{
   return to_string(i);
}

//Valor numérico representado en la cadena s, considerando que dicho valor está expresado en la base numérica b
int stringToInt(string s,int b)
{
   int r = 0;
   for(int f=0; f<length(s); f++){
      r = r+charToInt(s[length(s)-1-f])*pow(b,f);
   }
   return r;
}

//Valor numérico de la cadena s, que sólo debe contener dígitos numéricos en base 10
int stringToInt(string s)
{
   return stringToInt(s, 10);
}

//Cadena cuyo único carácter es c
string charToString(char c)
{
   string r = " ";
   r[0]=c;
   return r;
}

//Unico carácter que contiene la cadena s
char stringToChar(string s)
{
   return s[0];
}

//Retorna la misma cadena que recibe (???)
string stringToString(string s)
{
   return s;
}

//Cadena representando el valor contenido en d
string doubleToString(double d)
{
   string r = to_string(d);
   int l = length(r);
   for(int f=0; f<l; f++){
      if(r[l-1-f]!='0'){
         f=l;
      }else{
      r[l-1-f]='\0';
      }
   }
   return r;
}

//Valor numérico representado en la cadena s
double stringToDouble(string s)
{
   double a, b;
   a = stringToInt(substring(s,0,indexOf(s,'.')));
   b = stringToInt(substring(s,indexOf(s,'.')+1));
   return a+b/pow(10,length(s)-indexOf(s,'.')-1);
}

//True o False según s sea o no la cadena vacía
bool isEmpty(string s)
{
   if(s[0]=='\0'){
      return true;
   }else{
      return false;
   }
}

//True o False según si x es prefijo de s
bool startsWith(string s,string x)
{
   for(int f=0; f<length(x); f++){
      if(s[f]!=x[f]){
         return false;
      }
   }
   return true;
}

//True o False según si x es sufijo de s
bool endsWith(string s,string x)
{
   for(int f=length(x); f>=0; f--){
      if(s[f+length(s)-length(x)]!=x[f]){
         return false;
      }
   }
   return true;
}

//True o False según si la cadena s contiene al carácter c
bool contains(string s,char c)
{
   if(charCount(s,c)==0){
      return false;
   }else{
      return true;
   }
}

//Reemplaza en s todas las ocurrencias de oldChar por newChar
string replace(string s,char oldChar,char newChar)
{
   for(int f=charCount(s,oldChar); f>0; f--){
      s[indexOfN(s,oldChar,f)]=newChar;
   }
   return s;
}

//Insertar el carácter c en la posición pos de la cadena s
string insertAt(string s,int pos,char c)
{
   return substring(s, 0, pos) + c + substring(s, pos);
}

//Remover de s el carácter ubicado en la posición pos
string removeAt(string s,int pos)
{
   return substring(s, 0, pos) + substring(s, pos+1);
}

//Recorta los espacios en blanco que se encuentren a la izquierda de s
string ltrim(string s)
{
   for(int f=0; s[f]==' '; f++){
      if(s[f+1]!=' '){
         return substring(s,f+1);
      }
   }
   return "";
}

//Recorta los espacios en blanco que se encuentren a la derecha de s
string rtrim(string s)
{
   for(int f=length(s)-1; s[f]==' '; f--){
      if(s[f-1]!=' '){
         return substring(s,0,f);
      }
   }
   return "";
}

//Recorta los espacios en blanco que se encuentren a la derecha e izquierda de s
string trim(string s)
{
   s=ltrim(s);
   s=rtrim(s);
   return s;
}

//Cadena de caracteres compuesta por n caracteres c
string replicate(char c,int n)
{
   string r = "";
   for(int f=0; f<n; f++){
      r = r + c;
   }
   return r;
}

//Cadena de caracteres compuesta por n caracteres ' '
string spaces(int n)
{
   return replicate(' ', n);
}

/*Cadena idéntica a s, con longitud n completando, si fuese necesario, 
con caracteres c a la izquierda hasta llegar a la longitud requerida*/
string lpad(string s,int n,char c)
{
   return replicate(c,n-length(s))+s;
}

/*Cadena idéntica a s, con longitud n completando, si fuese necesario, 
con caracteres c a la derecha hasta llegar a la longitud requerida*/
string rpad(string s,int n,char c)
{
   return s+replicate(c,n-length(s));
}

/*Cadena idéntica a s, con longitud n completando, si fuese necesario, 
con caracteres c a ambos lados hasta llegar a la longitud requerida
(si n es impar, la derecha tiene prioridad)*/
string cpad(string s,int n,char c)
{
   int l = (n-length(s))/2;
   int r = l;
   if((n-length(s))%2==1){r++;}
   return replicate(c,l)+s+replicate(c,r);
}

//True o False según si el valor de c corresponde o no a un dígito numérico
bool isDigit(char c)
{
   if(charToInt(c)>=0 && charToInt(c)<=9){
      return true;
   }else{
      return false;
   }
}

//True o False si el valor de c corresponde o no a una letra
bool isLetter(char c)
{
   return !isDigit(c);
}

//True o False si el valor de c corresponde a una letra mayúscula
bool isUpperCase(char c)
{
   if(c>=65 && c<=90){
      return true;
   }else{
      return false;
   }
}

//True o False si el valor de c corresponde a una letra minúscula
bool isLowerCase(char c)
{
   return !isUpperCase(c);
}

//Valor de c a mayúscula
char toUpperCase(char c)
{
   return toupper(c);
}

//Valor de c a minúscula
char toLowerCase(char c)
{
   return tolower(c);
}

//Cadena idéntica a s pero completamente en mayúsculas
string toUpperCase(string s)
{
   for(int f=0; f<length(s); f++){
      s[f]=toUpperCase(s[f]);
   }
   return s;
}

//Cadena idéntica a s pero completamente en minúsculas
string toLowerCase(string s)
{
   for(int f=0; f<length(s); f++){
      s[f]=toLowerCase(s[f]);
   }
   return s;
}

//Compara alfabéticamente dos cadenas (a<b:-1, a>b:1, a=b:0)
int cmpString(string a,string b)
{
   if(toUpperCase(a)<toUpperCase(b)){return -1;}
   if(toUpperCase(a)>toUpperCase(b)){return 1;}
   return 0;
}

//Compara dos valores (a<b:-1, a>b:1, a=b:0)
int cmpDouble(double a,double b)
{
   if(a<b){return -1;}
   if(a>b){return 1;}
   return 0;
}

#endif
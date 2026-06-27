#ifndef _TFILES_T_
#define _TFILES_T_

#include <iostream>
#include <stdio.h>

//Escribe el valor t en la posición actual del archivo f
template<typename T> void write(FILE* f, T t)
{
   fseek(f,0,SEEK_CUR);
   fwrite(&t, sizeof(T), 1, f); 
}

//Lee del archivo f un registro tipo T y retorna el valor leído
template<typename T> T read(FILE* f)
{
   fseek(f,0,SEEK_CUR);
   T t;
   fread(&t, sizeof(T), 1, f);
   return t;
}

//Mueve el indicador de posición del archivo f al inicio del registro n
template<typename T> void seek(FILE* f, int n)
{
   fseek(f,n*sizeof(T),SEEK_SET);
}

//Cantidad de registros tipo T que contiene el archivo f
template<typename T> int fileSize(FILE* f)
{
   int aux = ftell(f);
   fseek(f,0,SEEK_END);
   int r = ftell(f)/sizeof(T);
   fseek(f,aux,SEEK_SET);
   return r;
}

//Número de registro que está siendo apuntado por el indicador de posición del archivo f
template<typename T> int filePos(FILE* f)
{
   return ftell(f);
}

#endif

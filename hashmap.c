#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


//--------------------------------------------------------------------------------------------



HashMap * createMap(long capacity) {
  //1.- Implemente la función *createMap* en el archivo hashmap.c. Esta función crea una variable     de tipo HashMap, inicializa el arreglo de buckets con casillas nulas, inicializa el resto de       variables y retorna el mapa. Inicialice el índice current a -1.
    HashMap *map = (HashMap *)calloc(1,sizeof(HashMap));
    map->buckets = (Pair **)calloc(capacity,sizeof(Pair));
    map->capacity = capacity;
    map->size = 0;
    map->current = -1;
  
    return map;
}

void insertMap(HashMap * map, char * key, void * value) {
//2.- Implemente la función void insertMap(HashMap * map, char * key, void * value). Esta función inserta un nuevo dato (key,value) en el mapa y actualiza el índice current a esa posición.


  Pair *newPair = createPair(key,value);
  size_t i = hash(key,map->capacity);//size_t == long long
  while(1){
    if(map->buckets[i]==NULL ){   
      map->buckets[i] = newPair;
      map->size ++;
      map->current = i;
      return;
    }
    i++;
    if (i == map->capacity){
      i = 0;
    }
  }
}

Pair * searchMap(HashMap * map,  char * key) {   
  //3.- Implemente la función Pair * searchMap(HashMap * map,  char * key), la cual retorna el **Pair** asociado a la clave ingresada. 

  size_t i = hash(key,map->capacity);
  size_t cont= 0;
  while(1){
    if (map->buckets[i] == NULL){return NULL;}
    if(is_equal(map->buckets[i]->key,key)){
      map->current = i;
      return map->buckets[i];
    }  
    i++;  
    cont ++;
    if(cont == map->capacity){return NULL;}
    if(i == map->capacity){
      i = 0;
    } 
  }
  
}

void eraseMap(HashMap * map,  char * key) {    
//4.- Implemente la función void eraseMap(HashMap * map,  char * key). Está función elimina el dato correspondiente a la clave key. Para hacerlo debe buscar el dato y luego *marcarlo* para que no sea válido.
//**No elimine el par**, sólo invalídelo asignando NULL a la clave (pair->key=NULL).
//Recuerde actualizar la variable size.
  size_t i = hash(key,map->capacity);
  size_t cont= 0;
  while(1){
    if (map->buckets[i] == NULL){return ;}
    if(is_equal(map->buckets[i]->key,key)){
      map->buckets[i]->key = NULL;
      map->size-=1;
      return;
    }
    i++;
    cont ++;
    if(cont == map->capacity){return;}
    if(i == map->capacity){
      i = 0;
    }
  }
  return;
}

Pair * firstMap(HashMap * map) {
//Pair * firstMap(HashMap * map) retorna el primer **Pair** válido del arreglo buckets. Recuerde actualizar el índice.
  size_t i = 0;
  //size_t cont=0;
  while(1){
    if (map->buckets[i] != NULL){
      if(map->buckets[i]->key != NULL){
        map->current = i; 
        return map->buckets[i];
      }
    }
    i++;
    //if (cont == 1){return NULL;}
    if(i == map->capacity){
      //cont++;
      i = 0;
    }
  }
}


Pair * nextMap(HashMap * map) {
//Pair * nextMap(HashMap * map) retorna el siguiente **Pair** del arreglo buckets a partir índice current. Recuerde actualizar el índice.
  size_t i = map->current;
  while(1){
    i++;
    if (map->buckets[i] != NULL && map->buckets[i]->key != NULL){
        map->current = i;
        return map->buckets[i];
    } 
    if (i == map->capacity){
      return NULL;
    }
  }
}


void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)
//6.- Implemente la función void enlarge(HashMap * map). Esta función agranda la capacidad del arreglo buckets y reubica todos sus elementos. Para hacerlo es recomendable mantener referenciado el arreglo *actual/antiguo* de la tabla con un puntero auxiliar. Luego, los valores de la tabla se reinicializan con un nuevo arreglo con el **doble de capacidad**. Por último los elementos del arreglo antiguo se insertan en el mapa *vacío* con el método *insertMap*.
//Puede seguir los siguientes pasos:

//a - Cree una variable auxiliar de tipo Pair** para matener el arreglo map->buckets (*old_buckets*);

//b - Duplique el valor de la variable capacity.

//c - Asigne a map->buckets un nuevo arreglo con la nueva capacidad.

//d - Inicialice size a 0.

//e - Inserte los elementos del arreglo *old_buckets* en el mapa (use la función insertMap que ya implementó).
  HashMap * newMap = createMap(map->capacity*2)  ;
  size_t i = 0;
  printf("%zu",map->capacity)
  while(1){
    //size_t indice = hash(map->buckets[i]->key,map->capacity);
    //insertMap(newMap, map->buckets[i]->key, map->buckets[i]->value);
    i++;
    puts("101011001");
    if (i == newMap->capacity){return;}
  }

  return;
}
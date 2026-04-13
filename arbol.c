#include <stdlib.h>
#include <stdio.h>
#include "arbol.h"
#include "cola.h"
#define max(a,b)(a>b?a:b)
#define min(a,b)(a<b?a:b)

//
// Reserva de memoria para un nuevo nodo de árbol binario
//
Arbol creaNodo(tipoInfo info)
{ tipoNodo * nuevo;

  //   nuevo =(tipoNodo *)calloc(1, sizeof(tipoNodo));
  if ((nuevo =(tipoNodo *)malloc(sizeof(tipoNodo)))==NULL)
	return NULL;
  else
  { 	nuevo->info=info;
	nuevo->izq=NULL;
	nuevo->der=NULL;
	return nuevo;
   }
}

//
// Recorrido en amplitud o por niveles: necesita una cola de punteros a nodos de árbol binario!!!
//

void amplitudr(Arbol raiz)
{ Cola c;
  tipoNodo *nodo;
  colaCreaVacia(&c);
  nodo = raiz;
  if (raiz!=NULL) colaInserta(&c,nodo);
  while (!colaVacia(&c))
  { nodo = (Arbol) colaSuprime(&c);
    printf(" %c ", nodo->info);
    if (nodo->izq!=NULL) colaInserta(&c,nodo->izq);
    if (nodo->der!=NULL) colaInserta(&c,nodo->der);
  }
}

int altura(Arbol raiz)
{
  if (raiz != NULL)
  {
    return max(altura(raiz->izq), altura(raiz->der)) + 1;
  }
  return 0;
}

int numNodos(Arbol raiz)
{
  if (raiz != NULL)
  {
    return numNodos(raiz->izq) + numNodos(raiz->der) + 1;
  }
  return 0;
}

Arbol anula(Arbol raiz)
{
  if (raiz != NULL)
  {
    anula(raiz->izq);
    anula(raiz->der);
    free(raiz);
  }
  return NULL;
}

int sustiuye(Arbol raiz, tipoInfo x, tipoInfo y)
{
  if (raiz != NULL)
  {
    if (raiz->info == x)
    {
      raiz->info = y;
      return 1 + sustiuye(raiz->izq, x, y) + sustiuye(raiz->der, x, y);
    }
    return sustiuye(raiz->izq, x, y) + sustiuye(raiz->der, x, y);
    
  }
  return 0;
}

int numNodosHoja(Arbol raiz)
{
  if (raiz != NULL)
  {
    if (numNodosHoja(raiz->izq) + numNodosHoja(raiz->der) == 0)
      return 1;
    return numNodosHoja(raiz->izq) + numNodosHoja(raiz->der);
  }
  return 0;
}

int numNodosInternos(Arbol raiz)
{
  if (raiz != NULL)
  {
    if (numNodosInternos(raiz->izq) == -1 || numNodosInternos(raiz->der) == -1)
      return 0;
    return 1 + numNodosInternos(raiz->izq) + numNodosInternos(raiz->der);
  }
  return -1;
}

int numHijoUnico(Arbol raiz)
{
  if (raiz != NULL)
  {
    if (numHijoUnico(raiz->izq) == -1 && numHijoUnico(raiz->der) == -1)
      return 0;
    if (numHijoUnico(raiz->izq) == -1)
      return 1 + numHijoUnico(raiz->der);
    if (numHijoUnico(raiz->der) == -1)
      return 1 + numHijoUnico(raiz->izq);
    return numHijoUnico(raiz->der) + numHijoUnico(raiz->izq);
  }
  return -1;
}

Arbol buscarMax(Arbol raiz)
{
  if (raiz != NULL)
  {
    return max(max(raiz->info, buscarMax(raiz->izq)), buscarMax(raiz->der));
  }
  return 0;
}

Arbol buscarMin(Arbol raiz)
{
  if (raiz != NULL)
  {
    return min(min(raiz->info, buscarMin(raiz->izq)), buscarMin(raiz->der));
  }
  return 0;
}

int similares(Arbol r1, Arbol r2)
{
  if (r1 != NULL && r2 != NULL)
  {
    if (similares(r1->izq, r2->izq) == 0 || similares(r1->der , r2->der) == 0)
      return 0;
    return 1;
  }
  if (r1 == NULL && r2 == NULL)
    return 1;
  return 0;
}

int equivalentes(Arbol r1, Arbol r2)
{
  if (r1 != NULL && r2 != NULL)
  {
    if (r1->info != r2->info || similares(r1->izq, r2->izq) == 0 || similares(r1->der , r2->der) == 0)
      return 0;
    return 1;
  }
  if (r1 == NULL && r2 == NULL)
    return 1;
  return 0;
}

Arbol especular(Arbol raiz)
{
  if (raiz != NULL)
  {
    Arbol temporal;
    temporal = raiz->izq;
    raiz->izq = especular(raiz->der);
    raiz->der = especular(temporal);
    return(raiz);
  }
  return NULL;
}

int Posicion(tipoInfo inorden[], int inInicio, int inFin, tipoInfo info)
{
  for (int i = inInicio; i <= inFin; i++)
  {
    if (inorden[i] == info)
      return i;
  }
  return -1;
}

Arbol construirArbol(tipoInfo preOrden[], tipoInfo inorden[], int inInicio, int inFin, int * preIndex)
{

  if (inInicio > inFin)
  {
    return NULL;
  }

  Arbol raizNueva = malloc(sizeof(tipoNodo));
  raizNueva->info = preOrden[*preIndex];
  raizNueva->der = raizNueva ->izq = NULL;

  (*preIndex)++;

  if (inInicio == inFin)
    return raizNueva;

  int inIndex = Posicion(inorden, inInicio, inFin, raizNueva->info);
  
  raizNueva->izq = construirArbol(preOrden, inorden, inInicio, inIndex - 1, preIndex);
  raizNueva->der = construirArbol(preOrden, inorden, inIndex + 1, inFin, preIndex);

  return raizNueva;

}

// 
// Recorridos en profundidad "recursivos"
//
void preOrden(Arbol raiz)
{ if (raiz!=NULL)
  { printf("%c ",raiz->info);
    preOrden(raiz->izq);
    preOrden(raiz->der);
  }
}
void enOrden(Arbol raiz)
{ if (raiz!=NULL)
  { enOrden(raiz->izq);
    printf("%c ",raiz->info);
    enOrden(raiz->der);
  }
}
void postOrden(Arbol raiz)
{ if (raiz!=NULL)
  { postOrden(raiz->izq);
    postOrden(raiz->der);
    printf("%c ",raiz->info);
  }
}




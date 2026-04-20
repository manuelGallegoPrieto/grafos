/*
 * grafos.c
 *
 *  Created on: 21/04/2014
 *      Author: MJ Polo
 */
#include <stdio.h>
#include <stdlib.h>
#include "cola.h"
#include "grafos.h"
#include "monticulo.h"

/**********************************************
/ Inicia correctamente directorio de vertices *
***********************************************/
void iniciar(tipoGrafo *g)
{
  pArco temporal;
  for (int i = 1; i <= g->orden; i++){
    g->directorio[i].alcanzado = 0;
    g->directorio[i].gradoEntrada = 0;
    g->directorio[i].ordenTop = 0;
    g->directorio[i].distancia = INF;
    g->directorio[i].peso = INF;
    g->directorio[i].anterior = 0;
  }
  for (int i = 1; i <= g->orden; i++){
    temporal = g->directorio[i].lista;
    while (temporal != NULL){
      g->directorio[temporal->v].gradoEntrada += 1;
      temporal = temporal->sig;
    }
  }
}

void profundidadMejorado(int v_inicio,tipoGrafo *g)
{ int w;
  pArco  p;
  printf("%d ",v_inicio);
  g->directorio[v_inicio].alcanzado=1;
  p = g->directorio[v_inicio].lista;
  while (p!=NULL)
  { w=p->v;
    if (!g->directorio[w].alcanzado)
        profundidadMejorado(w,g);
    p = p->sig;
  }
  for(int i = 1; i <= g->orden; i++)
    if (!g->directorio[i].alcanzado)
      profundidadMejorado(i, g);
}

void amplitudMejorado(int v_inicio,tipoGrafo *g)
{ int w;
  pArco  p;
  Cola c;

  colaCreaVacia(&c);
  colaInserta(&c,v_inicio);
  while (!colaVacia(&c))  {
	w =colaSuprime(&c);
    if (!g->directorio[w].alcanzado) {
      printf("%d ",w);
            g->directorio[w].alcanzado=1;
            p =g->directorio[w].lista;
      while (p!=NULL){
        w = p->v;
        colaInserta(&c,w);
        p = p->sig;
      }
	  }
  }  
  for(int i = 1; i <= g->orden; i++)
    if (!g->directorio[i].alcanzado)
      amplitudMejorado(i, g);
}

/* Ejercicio 2*/

int buscarVerticeGradoCero(tipoGrafo grafo)
{
  for (int i = 1; i <= grafo.orden; i++)
    if (grafo.directorio[i].gradoEntrada == 0 && !grafo.directorio[i].ordenTop)
      return i;
  return -1;
}

int ordenTop1(tipoGrafo *grafo)
{
  int v;
  pArco p;
  iniciar(grafo);
  for (int i = 1; i <= grafo->orden; i++){
    v = buscarVerticeGradoCero(*grafo);
    if (v == -1) return -1;
    grafo->directorio[v].ordenTop = i;
    p = grafo->directorio[v].lista;
    while (p != NULL){
      grafo->directorio[p->v].gradoEntrada -= 1;
      p = p->sig;
    }
  }
}

int ordenTop2(tipoGrafo *grafo)
{
  int v, w;
  Cola c;
  int orden = 1;

  iniciar(grafo);
  colaCreaVacia(&c);
  for (v = 1; v <= grafo->orden; v++)
    if (grafo->directorio[v].gradoEntrada == 0) colaInserta(&c, v);

  while (!colaVacia(&c)){
    v = colaSuprime(&c);
    grafo->directorio[v].ordenTop = orden++;
    pArco p = grafo->directorio[v].lista;
    while (p != NULL){
      w = p->v;
      grafo->directorio[w].gradoEntrada -= 1;
      if (grafo->directorio[w].gradoEntrada == 0) colaInserta(&c, w);
      p = p->sig;
    }
  }

  if (orden <= grafo->orden) return -1; // grafo cíclico
  return 0;
}

/******************************************************************************/
/* Recorrido en PROFUNDIDAD de un grafo. ¡CUIDADO! Depende del vertice inicial y del tipo de grafo */
/*********************************************************************************/
void profundidad(int v_inicio,tipoGrafo * grafo)
{ int w;
  pArco  p;
  printf("%d ",v_inicio);
  grafo->directorio[v_inicio].alcanzado=1;
  p = grafo->directorio[v_inicio].lista;
  while (p!=NULL)
  { w=p->v;
    if (!grafo->directorio[w].alcanzado)
        profundidad(w,grafo);
    p = p->sig;
  }
}
/************************************************************************************************/
/* Recorrido en AMPLITUD de un grafo. ¡CUIDADO! Depende del vertice inicial y del tipo de grafo */
/************************************************************************************************/
void amplitud(int v_inicio,tipoGrafo *grafo)
{ int w;
  pArco  p;
  Cola c;

  colaCreaVacia(&c);
  colaInserta(&c,v_inicio);
  while (!colaVacia(&c))  {
	w =colaSuprime(&c);
        if (!grafo->directorio[w].alcanzado) {
		printf("%d ",w);
	        grafo->directorio[w].alcanzado=1;
        	p =grafo->directorio[w].lista;
 		while (p!=NULL){
			w = p->v;
			colaInserta(&c,w);
			p = p->sig;
		}
	}
  }
	  
}
/**********************************************************************************************/
/* Función auxiliar para ver el contenido de la estructura que representa un grafo en memoria */
/**********************************************************************************************/
void verGrafo(tipoGrafo *g)
{  int i;
   pArco p;

   printf("\nGrafo  (Orden %d)\n\n",g->orden);
   printf("       alc gEnt oTop dist peso ant \n");
   printf("     +----+----+----+----+----+----+\n");

   for(i=1;i<=g->orden;i++)
   {  printf("  %2d | %2d | %2d | %2d |", i, g->directorio[i].alcanzado,
                       g->directorio[i].gradoEntrada, g->directorio[i].ordenTop);
       if (g->directorio[i].distancia == INF) printf("  * |");
       else   printf(" %2d |", g->directorio[i].distancia);
       if (g->directorio[i].peso == INF) printf("  * |");
       else   printf(" %2d |", g->directorio[i].peso);
       printf(" %2d |",g->directorio[i].anterior);
       p = g->directorio[i].lista;
       while (p != NULL)
       {   printf(" ->%2d", p->v);	// Grafos no ponderados
           //printf(" ->%2d, %2d", p->v, p->peso); // Grafos ponderados
           p = p->sig;
       }
       printf("\n");
   }
   printf("     +----+----+----+----+----+----+\n\n");
}

/* Ejercicio 3: Caminos mínimos en grafos dirigidos */
/* a) NO Ponderados */

void caminos1(int vInicio, tipoGrafo *g)
{
  pArco p;
  int v, w;
  int distActual;
  iniciar(g);
  g->directorio[vInicio].distancia = 0;
  for (distActual = 0; distActual < g->orden; distActual++){
    for (v == 1; v < g->orden; v++){
      if (g->directorio[v].alcanzado == 0 && g->directorio[v].distancia == distActual){
        g->directorio[v].alcanzado = 1;
        p = g->directorio[v].lista;
        while (p != NULL){
          w = p->v;
          if (g->directorio[w].distancia = INF){
            g->directorio[w].distancia = g->directorio[v].distancia + 1;
            g->directorio[w].anterior = v;
          }
          p = p->sig;
        }
      }
    }
  }
}

void caminos2(int vInicio, tipoGrafo *g)
{
  pArco p;
  int v, w;
  Cola c;
  iniciar(g);
  g->directorio[vInicio].distancia = 0;
  colaCreaVacia(&c);
  colaInserta(vInicio, &c);
  while (!colaVacia(&c)){
    v = colaSuprime(&c);
    p = g->directorio[v].lista;
    while (p != NULL){
      w = p->v;
      if (g->directorio[w].distancia = INF){
        g->directorio[w].distancia = g->directorio[v].distancia + 1;
        g->directorio[w].anterior = v;
        colaInserta(w, &c);
      }
      p = p->sig;
    }
  }
}

/* b) PONDERADOS */
void dijkstra1(int vInicio, tipoGrafo *g)
{
  pArco p;
  int v, w;
  int distActual, i;
  iniciar(g);
  g->directorio[vInicio].distancia = 0;
  for (i = 1; i <= g->orden; i++){
    v = buscarVerticeDistanciaMinimaNoAlcanzado(g);
    if (v == -1) i = g->orden + 1;
    else{
      g->directorio[v].alcanzado = 1;
      p = g->directorio[v].lista;
      while (p != NULL){
        w = p->v;
        if (g->directorio[w].alcanzado == 0){
          if (g->directorio[v].distancia + p->peso < g->directorio[w].distancia){
            g->directorio[w].distancia = g->directorio[v].distancia + p->peso;
            g->directorio[w].anterior = v;
          }
        }
        p = p->sig;
      }
    }
  }
}

void dijkstra2(int vInicio, tipoGrafo *g)
{
  Monticulo m;
  tipoElementoM x;
  pArco p;
  tipoInfo v, w;
  iniciar(g);
  g->directorio[vInicio].distancia = 0;
  iniciaMonticulo(&m);
  x.clave = 0;
  x.v = vInicio;
  insertar(x, &m);
  while (!vacioMonticulo(m)){
    eliminarMinimo(&m, &x);
    v = x.v;
    if (g->directorio[v].alcanzado == 0){
      g->directorio[v].alcanzado = 1;
      p = g->directorio[v].lista;
      while (p != NULL){
        w = p->v;
        if (g->directorio[w].alcanzado == 0){
          if (g->directorio[v].alcanzado == 1){
            g->directorio[w].distancia = g->directorio->distancia + p->peso;
            g->directorio[w].anterior = v;
            x.clave = g->directorio[w].distancia;
            x.v = w;
            insertar(x, &m);
          }
        }
        p = p->sig;
      }
    }
  }
}

int buscarVerticeDistanciaMinimaNoAlcanzado(tipoGrafo *g)
{
  int v, minDistancia = INF, verticeMin = -1;
  for (v = 1; v <= g->orden; v++){
    if (g->directorio[v].alcanzado == 0 && g->directorio[v].distancia < minDistancia){
      minDistancia = g->directorio[v].distancia;
      verticeMin = v;
    }
  }
  return verticeMin;
}
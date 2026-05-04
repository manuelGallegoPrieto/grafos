#include "conjuntos.h"
#include <stdio.h>


/// Incluir aqui las funciones que implementan las tres operaciones básicas 
/// en la representación de CONJUNTOS DISJUNTOS mediante ÁRBOLES
/// ......................................................................

/*
        ESTA ES LA IMPLEMENTACIÓN BÁSICA -------------------------------------------------------------------------------------

void crea(particion P){
    tipoConjunto i = 0;
    while (i<MAXIMO)
    {
        P[i] = i;
        i++;
    }
    return;
}

tipoConjunto buscar(tipoElementoConjunto x, particion P){
    if (P[x] == x)
        return x;
    return buscar(P[x], P);
}

// Implementación de operación unir con control de representantes:
// Si x e y son los representantes de sus clases de equivalencia las unen y devuelven VERDADERO,
// en otro caso no hace nada y devuelve FALSO

int unir(tipoConjunto x, tipoConjunto y, particion P){
    if (P[x] != x || P[y] != y || x == y)
        return 0;
    P[y] = x;
    return 1;
}*/

/*
        ESTA ES LA IMPLEMENTACIÓN POR TAMAÑOS --------------------------------------------------------------------------------

void crea(particion P){
    tipoConjunto i = 0;
    while (i<MAXIMO)
    {
        P[i] = -1;
        i++;
    }
    return;
}

tipoConjunto buscar(tipoElementoConjunto x, particion P){
    if (P[x] < 0)
        return x;
    return buscar(P[x], P);
}

// Implementación de operación unir con control de representantes:
// Si x e y son los representantes de sus clases de equivalencia las unen y devuelven VERDADERO,
// en otro caso no hace nada y devuelve FALSO

int unir(tipoConjunto x, tipoConjunto y, particion P){
    if (P[x] >= 0 || P[y] >= 0|| x == y)
        return 0;
    if (P[x] <= P[y])
    {
        P[x] += P[y];
        P[y] = x;
        return 1;
    }
    P[y] += P[x];
    P[x] = y;
    return 1;
}*/

// IMPLEMENTACIÓN POR ALTURA --------------------------------------------------------------------------------

void crea(particion P){
    tipoConjunto i = 0;
    while (i<MAXIMO)
    {
        P[i] = -1;
        i++;
    }
    return;
}

tipoConjunto buscar(tipoElementoConjunto x, particion P){
    if (P[x] < 0)
        return x;
    P[x] = buscar(P[x], P);
    return P[x];
}

// Implementación de operación unir con control de representantes:
// Si x e y son los representantes de sus clases de equivalencia las unen y devuelven VERDADERO,
// en otro caso no hace nada y devuelve FALSO

int unir(tipoConjunto x, tipoConjunto y, particion P){
    if (P[x] >= 0 || P[y] >= 0|| x == y)
        return 0;
    if (P[x] < P[y])
    {
        P[y] = x;
        return 1;
    }
    else if(P[x] > P[y])
    {
        P[x] = y;
        return 1;
    }
    else
    {
        P[x] -= 1;
        P[y] = x;
        return 1;
    }

}

//
// Función auxiliar para ver contenido de Partición 
//
void verParticion(particion P)
{ int i;
    printf("\n");
    for (i =0;i<MAXIMO;i++) printf("|%2d",P[i]);
    printf("| contenido  vector\n");
    for (i =0;i<MAXIMO;i++) printf("---");
    printf("\n");
    for (i =0;i<MAXIMO;i++) printf(" %2d",i);
    printf("  índices vector\n\n");
}

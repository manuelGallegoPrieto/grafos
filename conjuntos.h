#ifndef __CONJUNTOS_A_H
#define __CONJUNTOS_A_H

#define MAXIMO 50

typedef int particion[MAXIMO];
typedef int tipoConjunto;
typedef int tipoElementoConjunto;

// Funciones a implementar

void crea(particion P); 

tipoConjunto buscar(tipoElementoConjunto x, particion P);

// Implementación de operación unir con control de representantes:
// Si x e y son los representantes de sus clases de equivalencia las unen y devuelven VERDADERO,
// en otro caso no hace nada y devuelve FALSO

int unir(tipoConjunto x, tipoConjunto y, particion P);

// Función proporcionada
void verParticion(particion P);
#endif


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "cola.h"



int colaCreaVacia(Cola *c) {
    c->frente = c->fondo = NULL;
    return 0;
}

int colaVacia(Cola *c) {
    if (c->frente == NULL) {
        return -1;
    } else {
        return 0;
    }
}

int colaInserta(Cola *c,tipoElemento elemento) {
    tipoCelda * nuevo;
    if (NULL == (nuevo = (tipoCelda *) malloc(sizeof(tipoCelda)))) {
        fprintf(stderr, "Error en malloc\n");
        return -1;
    }
    nuevo->elemento = elemento;
    nuevo->sig = NULL;
    if (c->fondo == NULL) {
        c->frente = c->fondo = nuevo;
    } else {
        c->fondo->sig = nuevo;
        c->fondo = nuevo;
    }
    return 0;
}

tipoElemento colaSuprime(Cola *c) {
    tipoElemento elemento;
    tipoCelda * aBorrar;
    if (colaVacia(c) == -1) {
        fprintf(stderr, "Error: cola vacía\n");
        return NULL;
    }
    elemento = c->frente->elemento;
    aBorrar = c->frente;
    c->frente = c->frente->sig;
    if (c->frente == NULL) {
        c->fondo = NULL;
    }
    free(aBorrar);
    return elemento;
}

#include <stdlib.h>
#include <stdio.h>
#include "monticulo.h"

void iniciaMonticulo(Monticulo *m)
{
    m->tamanno = 0;
    return;
}

int vacioMonticulo(Monticulo m)
{
    if (m.tamanno == 0)
        return 1;
    return 0;
}

int insertar(tipoElementoM x, Monticulo *m)
{
    m->tamanno++;
    m->elemento[m->tamanno] = x;
    filtradoAscendente(m, m->tamanno);
}

int eliminarMinimo(Monticulo *m, tipoElementoM *minimo)
{
    if (vacioMonticulo(*m))
        return -1;
    *minimo = m->elemento[1];
    m->elemento[1] = m->elemento[m->tamanno];
    m->tamanno--;
    filtradoDescendente(m, 1);
}

void decrementarClave(int pos, tipoClave cantidad, Monticulo *m)
{
    if (pos > m->tamanno)
        return;
    m->elemento[pos].clave = m->elemento[pos].clave - cantidad;
    filtradoAscendente(m, pos);
}

void incrementarClave(int pos, tipoClave cantidad, Monticulo *m)
{
    if (pos > m->tamanno)
        return;
    m->elemento[pos].clave = m->elemento[pos].clave + cantidad;
    filtradoDescendente(m, pos);
}

int esMonticulo(Monticulo m)
{
    if (vacioMonticulo(m))
        return 1;
    int i = 1;
    while (i<m.tamanno/2)
    {
        if (m.elemento[i].clave > m.elemento[i*2].clave)
            return 0;
        if (i*2 != m.tamanno)
            if (m.elemento[i].clave > m.elemento[i*2 + 1].clave)
                return 0;
        i++;
    }
}

/* Funciones auxiliares que conviene implementar: las dos estrategias de filtrado en las 
   que se basan todos los algoritmos que manejan montículos */

  void filtradoDescendente(Monticulo *m, int i)
  {
    tipoElementoM temporal = m->elemento[i];
    int hijo = 0;
    while (i*2 <= m->tamanno)
    {
        hijo = i*2;

        if (hijo < m->tamanno && m->elemento[hijo+1].clave < m->elemento[hijo].clave)
            hijo++;

        if (m->elemento[hijo].clave >= temporal.clave)
            break;

        m->elemento[i] = m->elemento[hijo];

        i = hijo;
    }

    m->elemento[i] = temporal;

  }

  void filtradoAscendente(Monticulo *m, int i)
  {
    tipoElementoM temporal = m->elemento[i];
    int pos = i;
    while (pos > 1 && m->elemento[pos/2].clave > temporal.clave)
    {
        m->elemento[pos] = m->elemento[pos/2];
        pos = pos/2;
    }
    m->elemento[pos] = temporal;
  }

/* Operación crearMonticulo la utilizaremos en ejercicio 2 y en tema de grafos */ 

  void crearMonticulo(Monticulo *m);

  void heapshort(Monticulo *m)
  {
    int i = m->tamanno;
    tipoElementoM temporal;
    while (i>0)
    {
        eliminarMinimo(m, &temporal);
        m->elemento[i] = temporal;
    }
  }
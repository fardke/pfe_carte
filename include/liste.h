#ifndef __LISTE_H__
#define __LISTE_H__
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct element_fn{
    void* elem;
    struct element_fn* next;
}element;
typedef struct liste_fn{
    int taille;
    element* tete;
}liste;
void initListe(liste* l);
int push(liste*, void*, int);
int delElem(liste*, void* elem, int(*comp)());
void* getElem(liste*, const void* elem, int(*comp)());
void printList(liste* l, void(*print)());
#endif

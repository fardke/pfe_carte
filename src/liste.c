#include "liste.h"

void initListe(liste* l){
    l->tete = NULL;
    l->taille = 0;

}
int push(liste* l, void* elem, int sizeElement){
        element* maillon = l->tete;
        element* temp;
        
	if(l->taille==0){
		printf("Ajout en tete\n");
		//l = malloc(sizeof(liste));
		//l->elem = malloc(sizeElement);
                maillon = malloc(sizeof(element));
                maillon->elem = malloc(sizeElement);
		memcpy(maillon->elem, elem, sizeElement);
		maillon->next = NULL;
                l->tete = maillon;
                l->taille++;
		return 0;
	}
	else if(maillon!=NULL){
            printf("ajout en queue\n");
		while(maillon->next!=NULL){
			maillon = maillon->next;
		}
		
		//maillon = maillon->next;
                temp = malloc(sizeof(element));
		temp->elem = malloc(sizeElement);
		memcpy(temp->elem, elem, sizeElement);
		temp->next = NULL;
                maillon->next = temp;
                l->taille++;
                printf("taille : %d\n", l->taille);
		return 0;
	}
}

int delElem(liste* l, void* elem, int(* cmp)()){
	int i=1;
	element* temp;
	element* maillon;
	if(l->taille==0 || elem == NULL){
		return -1;
	}
	if(cmp(l->tete->elem, elem)==0){//on supprime la tete
            temp = l->tete;
            l->tete=l->tete->next;

            free(temp);
            l->taille--;
            return 0;
        }
	
        maillon = l->tete;
	while(maillon->next!=NULL){
            temp = maillon->next;
            if(cmp(temp->elem, elem)==0){
                maillon->next = temp->next;
		free(temp);
                l->taille--;
		return 0;
            }
            maillon = maillon->next;
	}
	return -1;
}

void* getElem(liste* l,const void* elem, int(*comp)()){
    element* maillon;
    if(l->taille==0)
        return NULL;
    maillon = l->tete;
    while(maillon!=NULL){
        if(comp( maillon->elem, elem)==0){
            return maillon->elem;
        }
        maillon = maillon->next;
    }
    return NULL;
}

void printList(liste* l, void(*print)()){
    element* maillon;
    if(l->taille==0)
        return;
    maillon = l->tete;
    while(maillon!=NULL){
        print(maillon->elem);
        maillon = maillon->next;
    }
}

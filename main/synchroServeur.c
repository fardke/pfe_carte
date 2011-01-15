#include "bt_p.h"

int main(void){
	char addr[256];
	printf("Adresse de la carte avec qui nous allons faire la synchronisation: ");
	scanf("%s",addr);
	synchroServeur(addr);
	return 1;
}

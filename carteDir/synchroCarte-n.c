#include <stdio.h>
#include <bluetooth/bluetooth.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>

#include <bluetooth/l2cap.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

#define PORT 0x1231
#define CONFIG_FILE "/root/config"


int synchroCarte(){
	struct sockaddr_l2 acceptedAddr = {0};
	struct sockaddr_l2 clientAddr = {0};
	int sock,client;
	size_t size;
	char buff[256];
	FILE* flux;
	bacpy(&acceptedAddr.l2_bdaddr, BDADDR_ANY);
	acceptedAddr.l2_family = AF_BLUETOOTH;
	acceptedAddr.l2_psm = htobs(PORT);
	if ((sock = socket(AF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP)) < 0) {
		perror("Synchro socket create");
		return;
	}
	
	if (bind(sock, (struct sockaddr*) &acceptedAddr, sizeof(acceptedAddr)) < 0) {
		perror("Bind synchro");
		return;
	}
	if (listen(sock, 7) < 0) {
		perror("listen synchro");
		return;
	}

	if ((client = accept(sock, (struct sockaddr*) &clientAddr, &size))>= 0) {

		if (recv(client, buff, sizeof(buff), 0) >= 0) {
			if((flux =fopen(CONFIG_FILE,"a"))== NULL){
				perror("Config file don't exists");
				return;
			}
			fprintf(flux,"%s",batostr(&(clientAddr.l2_bdaddr)));
			fputc('\0',flux);
			fclose(flux);
		}
	}
}

int main(void){
	printf("En attente de la synchronisation sur le pc serveur...\n");
	synchroCarte();
	return 1;
}

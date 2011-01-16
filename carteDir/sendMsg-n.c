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
int sendMsg();
int readAddr(struct sockaddr_l2* addr);


int sendMsg(){
	struct sockaddr_l2 addrDest = {0};
	char buff[6] = "Salut";
	int sock;
	readAddr(&addrDest);
	if ((sock = socket(AF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP)) < 0) {
		perror("SendMsg socket create");
		return;
	}
	if(connect(sock, (struct sockaddr*)&addrDest, sizeof(addrDest))<0){
		perror("SendMsg connect");
		return;
	}
	write (sock, buff, sizeof(buff));

	close(sock);
}

int readAddr(struct sockaddr_l2* addr){
	FILE* flux;
	char buff[256];
	char c;
	int i=0;
	if((flux =fopen(CONFIG_FILE,"r"))== NULL){
		perror("Config file don't exists");
		return;
	}
	printf("icii\n");
	while((c=fgetc(flux))!='\0'){
			buff[i]=c;
			i++;
		printf("%c", c);
	}
	printf("\nlaaa\n");
	printf("Adresse serveur : %s\n",buff);
	fclose(flux);

	bacpy(&(addr->l2_bdaddr),strtoba(buff));
	addr->l2_family = AF_BLUETOOTH;
	addr->l2_psm = htobs(PORT);
	fclose(flux);
	return;
}

int main(void){
	printf("Envoi de salut au serveur\n");
	sendMsg();
	return 1;
}

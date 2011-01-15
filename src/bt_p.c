#include "bt_p.h"

int scanBt(){
	inquiry_info* info = NULL;
	int max_rsp = 255;
	int flags = IREQ_CACHE_FLUSH;
	int num_rsp = 0;
	bdaddr_t addr;
	int i, sock;
	int DEVIDHCI=0;

	info = malloc(max_rsp * sizeof(inquiry_info));
	memset(info, 0, max_rsp * sizeof(inquiry_info));
	num_rsp = hci_inquiry(DEVIDHCI, 8, num_rsp, NULL, &info, flags);
	sock = hci_open_dev(DEVIDHCI);
	if (num_rsp < 0) {
		perror("hci_inquiry");
	}

	for (i = 0; i < num_rsp; i++) {
		baswap(&addr, &(info + i)->bdaddr);
		printf("Addr : %s\n", batostr(&addr));
	}
	close(sock);
}

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

int readMsg(){
	struct sockaddr_l2 acceptedAddr = {0};
	struct sockaddr_l2 clientAddr = {0};
	int sock,client;
	size_t size;
	char buff[256];

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
			printf("message recu : %s\n",buff);
		}
	}
	close(client);
	close(sock);
}

int synchroServeur(char* addr){
	struct sockaddr_l2 addrCarte = {0};
	char* buff = "Synchro";
	int sock;
	baswap(&addrCarte.l2_bdaddr,strtoba(addr));
	addrCarte.l2_family = AF_BLUETOOTH;
	addrCarte.l2_psm = htobs(PORT);
	if ((sock = socket(AF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP)) < 0) {
		perror("Synchro socket create");
		return;
	}
	if(connect(sock, (struct sockaddr*)&addrCarte, sizeof(addrCarte))<0){
		perror("Synchro connect");
		return;
	}
	write (sock, buff, sizeof(buff));
	close(sock);
}

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
			fclose(flux);
		}
	}
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
	while((c=fgetc(flux))!=EOF){
		if(c!=EOF){
			buff[i]=c;
			i++;
		}
	}
	buff[i]='\0';
	printf("Adresse serveur : %s\n",buff);
	fclose(flux);

	bacpy(&(addr->l2_bdaddr),strtoba(buff));
	addr->l2_family = AF_BLUETOOTH;
	addr->l2_psm = htobs(PORT);
	fclose(flux);
	return;
}

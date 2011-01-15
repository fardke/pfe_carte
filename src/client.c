#include "client.h"

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

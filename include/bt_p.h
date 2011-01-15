#ifndef __BT_P_H__
#define __BT_P_H__
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <netdb.h>
#include <bluetooth/bluetooth.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>

#include <bluetooth/l2cap.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

#include "liste.h"

#define PORT 0x1231
#define CONFIG_FILE "config"
int scanBt();
int sendMsg();
int readMsg();
int synchroCarte();
int synchroServeur(char* addr);
int readAddr(struct sockaddr_l2* addr);

#endif

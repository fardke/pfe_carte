#ifndef __CLIENT_H__
#define __CLIENT_H__
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

int scanBt();

#endif

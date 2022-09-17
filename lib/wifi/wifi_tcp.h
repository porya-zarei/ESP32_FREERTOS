#include "lwip/err.h"
#include "lwip/sys.h"
#include "lwip/sockets.h"
#include "lwip/netdb.h"

#include <wifi.h>

#ifndef PORT
#define PORT 3333
#endif

#ifndef KEEPALIVE_IDLE
#define KEEPALIVE_IDLE 5
#endif

#ifndef KEEPALIVE_INTERVAL
#define KEEPALIVE_INTERVAL 5
#endif

#ifndef KEEPALIVE_COUNT
#define KEEPALIVE_COUNT 3
#endif
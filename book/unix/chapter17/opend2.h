#include "../apue.h"
#include <errno.h>
#define CL_OPEN "open" /* client’s request for serve
r */
#define CS_OPEN "/home/byz/opend"


extern char errmsg[]; /* error message string to return to client */
extern int oflag; /* open() flag: O_xxx ... */
extern char *pathname; /* of file to open() for client */
extern int debug;

typedef struct {
  int fd;
  uid_t uid;
} Client;

extern Client *client;
extern int client_size;


int cli_args(int, char **);
int client_add(int,uid_t);
void client_del(int);
void loop(void);
void request(char *, int, int,uid_t);

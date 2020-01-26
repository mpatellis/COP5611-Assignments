#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <rpc/rpc.h>
#include <errno.h>
#include <unistd.h>
#include "hcrpc.h"

XDR *server(char **text)
{
        int tmp_fd[2];
        if (pipe(tmp_fd) == -1)
                abort();

        FILE *fp = popen(*text, "r");

        system(*text);
        *text= (char *)malloc(10000*sizeof(char));

        fread(*text, sizeof(char), 1000, fp);

        pclose(fp);
        return((XDR*)text);   /* return network string back to client */
}


int main(void)
{
        //if(fork() != 0) exit(0); /* run this program in the background */
        svc_unregister(SERVICENUM,VERSION);     /* unregister previous running versions of RPC */
        /* register with port mapper so as the client knows where to contact for service */
        registerrpc(SERVICENUM, VERSION, PROCNUM, server, xdr_wrapstring, xdr_wrapstring);
        svc_run();      /* run the server RPC */
        fprintf(stderr,"Never should have gotten here svc_run()\n");
        return 1;
}

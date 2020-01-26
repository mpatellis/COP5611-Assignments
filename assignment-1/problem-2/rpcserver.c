#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <rpc/rpc.h>
#include <errno.h>
#include <unistd.h>
#include "hcrpc.h"

XDR *server(char **text)
{
        char tmp_fd;
        if (pipe(tmp_fd) == -1) /* create temp pipe to store output */
                abort();

        /* Redirect all output to the write end of the pipe */
		// add your code here.

        system(*text) ; /* system so sh or csh runs so we get the
                           advantage of env. vars etc  ... */
        *text= (char *)malloc(10000*sizeof(char));
		
		// output your result from pipe to text

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




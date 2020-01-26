#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <rpc/rpc.h>
#include <errno.h>
#include "hcrpc.h" 
#define COMMAND_LENGTH 4096  

char *read_file(char *);

int main(int argc, char **argv)
{
        int          result;
        static char* data2;
        char         data[COMMAND_LENGTH];

        if(argc !=3)
        {
                fprintf(stderr,"Usage: %s server command\n",argv[0]);
                exit(0);
        }
        data[0] = '\0';
        strcpy(data, argv[2]);
        data2 = data;

        result = callrpc(argv[1],SERVICENUM,VERSION,PROCNUM,xdr_wrapstring,
                        &data2, xdr_wrapstring, &data2); 
                /* xdr_wrapstring is a command to transfer arrays of charaters */
        if (result != 0)
        {
                printf("Error callrpc returned %d\n", result);
                return -1;
        }
        
        printf("Response:\n%s\n", data2);
        return(1);
}


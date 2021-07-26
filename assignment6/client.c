/*
 * client.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "csapp.h"

#define eos(s) ((s) + strlen(s)) // Citation: StackOverflow - How to append strings using sprintf?
#define len = 33


int main(int argc, char **argv) 
{
    int clientfd;
    char *num1, *num2;
    char *host, *port;

    if (argc != 3) {
        fprintf(stderr, "usage: %s <num1> <num2>\n", argv[0]);
        exit(0);
    }

    num1 = argv[1];
    num2 = argv[2];

    host = "localhost";
    port = "8080";

    clientfd = Open_clientfd(host, port);

    /* Pack the Message */
    char buf[MAXLINE];      // Declare Buffer To Store XML Code
    char fer[MAXLINE];      // Declare Buffer To Store XML Code

    // XML Body
    sprintf(fer, "<?xml version=\"1.0\"?>\r\n");
    sprintf(eos(fer), "<methodCall>\r\n");
    sprintf(eos(fer), "<methodName>sample.addmultiply</methodName>\r\n");
    sprintf(eos(fer), "<params>\r\n");
    sprintf(eos(fer), "<param><value><double>%s</double></value></param>\r\n", num1);
    sprintf(eos(fer), "<param><value><double>%s</double></value></param>\r\n", num2);
    sprintf(eos(fer), "</params>\r\n");
    sprintf(eos(fer), "</methodCall>\r\n");

    // XML Header
    sprintf(buf, "POST /RPC2 HTTP/1.1\r\n");
    sprintf(eos(buf), "Content-Type:text/xml\r\n");
    sprintf(eos(buf), "User-Agent:XML-RPC.NET\r\n");
    sprintf(eos(buf), "Content-Length:%ld\r\n", strlen(fer));
    sprintf(eos(buf), "Expect:100-continue\r\n");
    sprintf(eos(buf), "Connection:Keep-Alive\r\n");
    sprintf(eos(buf), "Host:localhost:8080\r\n");
    sprintf(eos(buf), "\r\n");

    sprintf(eos(buf), fer);     // Append body to header

    /* Send the Message */
    rio_writen(clientfd, buf, sizeof(buf));

    /* Receive and interpret the message */
    rio_t rp;
    rio_readinitb(&rp, clientfd);
    for (int i = 0; i < 13; i++) {
        rio_readlineb(&rp, buf, sizeof(buf));
        if (i > 10) {
            for (int j = 15; j < 15 + strlen(buf) - 33; j++) {
                printf("%c", buf[j]);
            }
            printf("   ");
        }
    }
    printf("\n");

    Close(clientfd);
    exit(0);
}

Experiment- 7: Establishing TCP connection works between a Server container and a Client container using Docker.
Description:

TCP communication works like this:

Client  -------- request -------->  Server
Client  <------- response --------  Server

Server
waits for connections

listens on a port

Client
connects to server

sends message

receives reply

Step-1: Create Project Folder

On your EC2 instance:

mkdir tcp-docker
cd tcp-docker
Step-2: Create TCP Server Program and client program in different terminals to unserstand the flow.
vi server.c
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

int main()
{
    int socket_desc, client_sock;
    struct sockaddr_in server, client;
    char message[100], client_message[100];
    int c;

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(5000);

    bind(socket_desc,(struct sockaddr *)&server,sizeof(server));

    listen(socket_desc,3);

    printf("Waiting for connection...\n");

    c = sizeof(struct sockaddr_in);
    client_sock = accept(socket_desc,(struct sockaddr *)&client,(socklen_t*)&c);

    recv(client_sock,client_message,100,0);
    printf("Client message: %s\n",client_message);

    strcpy(message,"Hello from server");
    send(client_sock,message,strlen(message),0);

    close(client_sock);
    close(socket_desc);
}

Now create TCP Client program
vi client.c

#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>

int main()
{
    int sock;
    struct sockaddr_in server;
    char message[100], server_reply[100];
    struct hostent *he;

    sock = socket(AF_INET , SOCK_STREAM , 0);

    he = gethostbyname("server");

    server.sin_family = AF_INET;
    server.sin_port = htons(5000);
    memcpy(&server.sin_addr, he->h_addr_list[0], he->h_length);

    connect(sock , (struct sockaddr *)&server , sizeof(server));

    strcpy(message,"Hello Server");
    send(sock,message,strlen(message),0);

    recv(sock,server_reply,100,0);
    printf("Server reply: %s\n",server_reply);

    close(sock);
}



Now Create Dockerfile for Server
vi Dockerfile.server

FROM gcc:latest
WORKDIR /app
COPY server.c .
RUN gcc server.c -o server
CMD ["./server"]
Now Create Dockerfile for Client
vi Dockerfile.client

FROM gcc:latest
WORKDIR /app
COPY client.c .
RUN gcc client.c -o client
CMD ["./client"]

Build Docker Images
Using Docker:
docker build -t tcp-server -f Dockerfile.server .
docker build -t tcp-client -f Dockerfile.client .
Check images:
docker images
Create Docker Network
docker network create tcp-network
This allows containers to communicate.
docker run -d --name server --network tcp-network -p 5000:5000 tcp-server
Check running container:
docker ps
Run Client Container
docker run --network tcp-network tcp-client
Output:
Server reply: Hello from server
Check Server Logs
docker logs server
Output:
Waiting for connection...
Client message: Hello Server


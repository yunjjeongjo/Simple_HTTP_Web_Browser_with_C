#include < stdio.h > #include < sys / socket.h > #include < arpa / inet.h > #include < netdb.h > #include < stdlib.h > #include < strings.h > #include < unistd.h > #define BUFMAX 1024
int main(int argc, char * argv[]) {
    int simpleSocket = 0;
    int simplePort = 0;
    int returnStatus = 0;
    char buffer[1024] = "";
    char * domain_name = argv[1];
    struct hostent * host;
    struct sockaddr_in simpleServer;
    if (3 != argc) {
        fprintf(stderr, "Usage: %s <server> <port>\n", argv[0]);
        exit(1);
    }
    /* create a streaming socket */
    simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (simpleSocket == -1) {
        fprintf(stderr, "Could not create a socket!\n");
        exit(1);
    } else {
        fprintf(stderr, "Socket created!\n");
    }
    /* retrieve the port number for connecting */
    simplePort = atoi(argv[2]);
    /* set up the address structure */
    host = gethostbyname(domain_name);
    /* use the IP address argument for the server address */
    bzero(& simpleServer, sizeof(simpleServer));
    simpleServer.sin_family = AF_INET;
    simpleServer.sin_addr.s_addr = inet_addr(inet_ntoa( * (struct in_addr *) * host -> h_addr_list));
    simpleServer.sin_port = htons(simplePort);
    /* connect to the address and port with our socket */
    returnStatus = connect(simpleSocket, (struct sockaddr *) & simpleServer, sizeof(simpleServer));
    if (returnStatus == 0) {
        fprintf(stderr, "Connect successful!\n");
    } else {
        fprintf(stderr, "Could not connect to address!\n");
        close(simpleSocket);
        exit(1);
    }
    /* get the message from the server */
    char msg[500] = "GET / HTTP/1.1\r\n";
    strcat(msg, "Host: ssl.kw.ac.kr\r\n\r\n"); // 웹서버로 보낼 헤더 작성
    send(simpleSocket, msg, strlen(msg), 0);
    returnStatus = read(simpleSocket, buffer, sizeof(buffer));
    if (returnStatus > 0) {
        printf("%s", buffer);
    } else {
        fprintf(stderr, "Return Status = %d \n", returnStatus);
    }
    close(simpleSocket);
    return 0;
    close(simpleSocket);
    return 0;
}
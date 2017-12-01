#include "TCPServer.h"
void TCPServer::start(const int PORT)
{
    int opt = TRUE;
    int master_socket , addrlen , new_socket , client_socket[MAX_CLIENTS] ,activity, i , valread , sd;
    int max_sd;
    struct sockaddr_in address;
    char buffer[BUFFER_SIZE];  //data buffer
    fd_set readfds; //set of socket descriptors



    initialize(client_socket,master_socket,opt,address,addrlen,PORT);

    while(TRUE)
    {
        checkForChilds(&readfds,max_sd,master_socket,sd,client_socket);

        //wait for an activity on one of the sockets , timeout is NULL ,
        //so wait indefinitely
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);

        if ((activity < 0) && (errno!=EINTR))
        {
            printf("select error");
        }

        //If something happened on the master socket ,
        //then its an incoming connection
        if (FD_ISSET(master_socket, &readfds))
            acceptConnection(new_socket,master_socket,address,addrlen,client_socket);

        //else its some IO operation on some other socket
        for (i = 0; i < MAX_CLIENTS; i++)
        {
            sd = client_socket[i];

            if (FD_ISSET( sd , &readfds))
            {
                //Check if it was for closing , and also read the
                //incoming message
                valread = read( sd , buffer, BUFFER_SIZE);//se llena el buffer del mensaje que mandó el usuario
                if (valread == 0) {
                    disconnectClient(sd, address, addrlen, client_socket, i);
                }

                else
                {
                    //set the string terminating NULL byte on the end
                    //of the data read
                    //AQUI PASA LA MAGIA(es donde se leen los mensajes entrantes)
                    buffer[valread] = '\0';
                    ParseIncomingMessage(bufferToString(buffer),i,sd);
                }
            }
        }
    }
}




void TCPServer::initialize(int *client_socket, int &master_socket, int &opt, sockaddr_in &address, int &addrlen, const int PORT) {
    //set of socket descriptors
    fd_set readfds;

    //initialise all client_socket[] to 0 so not checked
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        client_socket[i] = 0;
    }

    //create a master socket
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //set master socket to allow multiple connections ,
    //this is just a good habit, it will work without this
    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
                   sizeof(opt)) < 0 )
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    //type of socket created
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    //bind the socket to localhost port 8888
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Listener on port %d \n", PORT);

    //try to specify maximum of 3 pending connections for the master socket
    if (listen(master_socket, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //accept the incoming connection
    addrlen = sizeof(address);
    puts("Waiting for connections ...");
}

void TCPServer::checkForChilds(fd_set *readfds, int &max_sd, int &master_socket, int &sd, int *client_socket) {
    //clear the socket set
    FD_ZERO(readfds);

    //add master socket to set
    FD_SET(master_socket, readfds);
    max_sd = master_socket;

    //add child sockets to set
    for (int i = 0 ; i < MAX_CLIENTS ; i++)
    {
        //socket descriptor
        sd = client_socket[i];

        //if valid socket descriptor then add to read list
        if(sd > 0)
            FD_SET( sd , readfds);

        //highest file descriptor number, need it for the select function
        if(sd > max_sd)
            max_sd = sd;
    }

}

void TCPServer::acceptConnection(int &new_socket, int &master_socket, sockaddr_in &address, int &addrlen,
                                 int *client_socket) {
    char *message = "Conected, welcome to RMLib\0";
    if ((new_socket = accept(master_socket,
                             (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    //inform user of socket number - used in send and receive commands
    printf("New connection , socket fd is %d , ip is : %s , port : %d\n" , new_socket , inet_ntoa(address.sin_addr) , ntohs
            (address.sin_port));

   /* //send new connection greeting message
    if( send(new_socket, message, strlen(message), 0) != strlen(message) )
    {
        perror("send");
    }*/
    usleep(200);
    puts("Welcome message sent successfully");

    //add new socket to array of sockets
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        //if position is empty
        if( client_socket[i] == 0 )
        {
            client_socket[i] = new_socket;
            printf("Adding to list of sockets as %d\n" , i);
            break;
        }
    }


}

void TCPServer::disconnectClient(int &sd, sockaddr_in &address, int &addrlen, int *client_socket, int i) {
//Somebody disconnected , get his details and print
    getpeername(sd , (struct sockaddr*)&address , \
                        (socklen_t*)&addrlen);
    printf("Host disconnected , ip %s , port %d \n" ,
           inet_ntoa(address.sin_addr) , ntohs(address.sin_port));

    //Close the socket and mark as 0 in list for reuse
    close( sd );
    client_socket[i] = 0;
}

std::string TCPServer::bufferToString(char *buffer) {
    return std::__cxx11::string(buffer);
}

void TCPServer::ParseIncomingMessage(std::string message,int i,int sd){
    /*//std::cout<<message<<std::endl;
    json j = json::parse(message);
    if(j["command"]=="n"){
        total_var++;
        memory_used+= sizeof(j["data"]);
    }
    else if(j["command"]=="g"){
        RMnode<int,std::__cxx11::string> node = *clients_maps[i]->search(j["key"]);
        std::string s = node.data;
        send(sd , s.c_str() , BUFFER_SIZE , 0 );
        usleep(200);
    }
    else if(j["command"]=="d"){
        if(clients_maps[i]->search(j["key"])!= nullptr){
        int varsize=sizeof(clients_maps[i]->search(j["key"])->data)/2;
        if(clients_maps[i]->deleteNode(j["key"])){
            memory_used-=varsize;
            total_var--;}
    }}
    else if(j["command"]=="m"){
        json j1;
        j1["clients"]=number_of_clients;
        j1["variables"]=total_var;
        j1["used_mem"]=memory_used;
        send(sd , j1.dump().c_str() , BUFFER_SIZE , 0 );
        usleep(200);
    }

    *///std::cout<<number_of_clients<<std::endl<<total_var<<std::endl<<memory_used<<std::endl;
}

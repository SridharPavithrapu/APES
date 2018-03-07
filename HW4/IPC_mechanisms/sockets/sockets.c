#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>

#define PATH "./IPC_Socket"
#define MAX_STRING_SIZE 1024

typedef struct string_struct
{
        char string[MAX_STRING_SIZE];
        unsigned int string_length;
}string_struct;

typedef struct msg_buffer
{
        string_struct string_message;
        bool led_state;
}msg_buffer;

#define STRUCT_SIZE sizeof(msg_buffer)

int main()
{
	int sockfd, msgsockfd_server, msgsockfd_client;
	pid_t childPID;
	struct sockaddr_un server, client;

     	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);          //Creating a UNIX socket which is listening for connections
	//Error in creating socket
     	if (sockfd < 0) 
	{
        	perror("opening stream socket");
         	exit(1);
     	}
     	server.sun_family = AF_UNIX;			//Setting the family of the socket in the sockaddr_un structure
     	strcpy(server.sun_path, PATH);			//Setting the path for the special file that is going to be created for UNIX socket
        unlink(PATH);

     	if (bind(sockfd, (struct sockaddr *) &server, sizeof(struct sockaddr_un))) 
	{
        	perror("Binding Socket");
         	exit(1);
      	}
      	printf("Socket has name %s\n", server.sun_path);
      	listen(sockfd, 5);				//Maximum limit of 5

	childPID = fork();				//Forking a client process

	if(childPID < 0)
	{
		perror("Error creating a child process");
		close(sockfd);
		exit(1);
	}
	//Code for the client process
	else if(childPID == 0)
	{
		msg_buffer msg;
		char buffer[MAX_STRING_SIZE];
		int retval;

                bzero(&msg, sizeof(msg));
                bzero(buffer, sizeof(buffer));

		msgsockfd_client = socket(AF_UNIX, SOCK_STREAM, 0);          //Creating a socket that is going to be used by client to connect to and send messages to client
		//Error opening sockets
		if (msgsockfd_client < 0)
	        {
                	perror("opening stream socket");
			close(sockfd);
			close(msgsockfd_client);
                	exit(1);
        	}

                socklen_t sockaddr_size = sizeof(struct sockaddr_un);
                retval = connect(msgsockfd_client, (struct sockaddr *)&server, sockaddr_size);    //Client process connecting to the server process using UNIX socket
		perror("return Value:");

		sprintf(buffer, "Should I Switch on the LED on Beaglebone?");
		printf("\nClient Process:\t%s", buffer);
		fflush(stdout);

		(msg.string_message).string_length = strlen(buffer);
		strcpy((msg.string_message).string, buffer);
		
		//If Socket Stream connection to the remote server has been established 
		if(retval==0)
		{
			retval = write(msgsockfd_client,  &msg, STRUCT_SIZE);        
			if(retval > 0)
			{
				bzero(&msg, sizeof(msg));
				retval = read(msgsockfd_client, &msg, STRUCT_SIZE);
				if(retval>0)
				{
					if(msg.led_state)
						printf("\nClient process:\tThe LED is switched on.\n");
					else
						printf("\nClient Process:\tThe LED is switched off.\n");
					fflush(stdout);
				}
			}
		}

		//Closing opened sockets
		close(sockfd);
                close(msgsockfd_client);
	
	}
	//Code for the server process
	else
	{
		msg_buffer msg;
		int retval;

		bzero(&msg, sizeof(msg));

		socklen_t sockaddr_size = sizeof(struct sockaddr_un);
		msgsockfd_server = accept(sockfd, (struct sockaddr *)&client, &sockaddr_size);
		if(msgsockfd_server<0)
		{
			close(sockfd);
			exit(1);
		}
		retval = read(msgsockfd_server, &msg, STRUCT_SIZE);
		if(retval > 0 )
		{
			printf("\nServer Process:\tThe sent message is %s", (msg.string_message).string);
			fflush(stdout);
			bzero(&msg, sizeof(msg));
			msg.led_state = true;
			retval = write(msgsockfd_server,  &msg, STRUCT_SIZE);
		}
		//Closing opened sockets
		close(sockfd);
		close(msgsockfd_server);
	}
	
      	unlink(PATH);
	exit(0);
  }


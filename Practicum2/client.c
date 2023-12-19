/* q4
 * client.c -- TCP Socket Client
 * 
 * adapted from: 
 *   https://www.educative.io/answers/how-to-implement-tcp-sockets-in-c
 */

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{

  int socket_desc;
  struct sockaddr_in server_addr;
    char server_message[BUFFER_SIZE], client_message[BUFFER_SIZE];

  // Clean buffers:
  memset(server_message,'\0',sizeof(server_message));
  memset(client_message,'\0',sizeof(client_message));

  // Create socket:
  socket_desc = socket(AF_INET, SOCK_STREAM, 0);

  if(socket_desc < 0){
    printf("Unable to create socket\n");
    return -1;
  }

  printf("Socket created successfully\n");

  // Set port and IP the same as server-side:
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(2000);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");


  // Send connection request to server:
  if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
    printf("Unable to connect\n");
    return -1;
  }
  printf("Connected with server successfully\n");
    char command[32], filePath1[128], filePath2[128], additionalArg[128];

  // Get command and filename from command line arguments:
  if(argc < 3){
    printf("Usage: %s <command> <file-path>\n", argv[0]);
    return -1;
  }else
  {
      strcpy(command, argv[1]);
      strcpy(filePath1, argv[2]);

      if (argc > 3){
       strcpy(filePath2, argv[3]);

       }

      if (argc > 4) {
             strcpy(additionalArg, argv[4]);

             }
  }
    sprintf(client_message, "%s %s %s %s", command, filePath1, filePath2, argv[4]);

  // Construct the message to send to the server:
//  sprintf(client_message, "%s %s %s %s", argv[1], argv[2], argv[3], argv[4]);
    printf("the client mesage : %s \n", client_message);
      // Send the message to server:
        
        if(strcmp(command, "GET")==0){
            if(send(socket_desc, client_message, strlen(client_message), 0) < 0){
                printf("Unable to send message\n");
                return -1;
            }
            int bytes_received = 0;
            if(argv[3] == NULL){
                FILE *file = fopen(argv[2], "wb");
                
                
                
                if(!file){
                    printf("Error opening file %s\n", argv[3]);
                    return -1;
                }
                
                while((bytes_received = recv(socket_desc, server_message, BUFFER_SIZE, 0)) > 0){
                    fwrite(server_message, 1, bytes_received, file);
                }
                
                if(bytes_received < 0){
                    printf("Error while receiving server's msg\n");
                    return -1;
                }
                
                printf("File received successfully\n");
                
                fclose(file);
            } else {
                FILE *file = fopen(argv[3], "wb");
                
                
                
                if(!file){
                    printf("Error opening file %s\n", argv[3]);
                    return -1;
                }
                
                while((bytes_received = recv(socket_desc, server_message, BUFFER_SIZE, 0)) > 0){
                    fwrite(server_message, 1, bytes_received, file);
                }
                
                if(bytes_received < 0){
                    printf("Error while receiving server's msg\n");
                    return -1;
                }
                
                printf("File received successfully\n");
                
                fclose(file);
                
            }
        }
        else if(strcmp(command, "INFO")==0){
            if(send(socket_desc, client_message, strlen(client_message), 0) < 0){
                printf("Unable to send message\n");
                return -1;
            }
            int bytes_received = 0;
            char *token;

            while((bytes_received = recv(socket_desc, server_message, BUFFER_SIZE, 0)) > 0){
                server_message[bytes_received] = '\0';
                token = strtok(server_message, "\n");

                while(token != NULL){
                    printf("%s\n", token);
                    token = strtok(NULL, "\n");
                }
            }

            if(bytes_received < 0){
                printf("Error while receiving server's msg\n");
                return -1;
            }

        }
        else if(strcmp(command, "MD")==0){
            if(send(socket_desc, client_message, strlen(client_message), 0) < 0){
                printf("Unable to send message\n");
                return -1;
            }
            int bytes_received = 0;
            char *token;

            while((bytes_received = recv(socket_desc, server_message, BUFFER_SIZE, 0)) > 0){
                server_message[bytes_received] = '\0';
                token = strtok(server_message, "\n");

                while(token != NULL){
                    printf("%s\n", token);
                    token = strtok(NULL, "\n");
                }
            }

            if(bytes_received < 0){
                printf("Error while receiving server's msg\n");
                return -1;
            }
        }

       
        
       
        else if(strcmp(command, "PUT") == 0){
            
            

            char client_message[BUFFER_SIZE];
            char client_message_file[BUFFER_SIZE];
            // Open the local file for reading:
            FILE *file = fopen(argv[2], "r");
            int bytes_read = 0;
            memset(client_message, 0, BUFFER_SIZE);
            memset(client_message_file, 0, BUFFER_SIZE);

            if(file == NULL){
                perror("Error opening file");
                return -1;
            }
            else{
                // Read the local file data and store it in a string:
                while((bytes_read = fread(client_message_file, 1, BUFFER_SIZE, file)) > 0){
                    //                   strcat(client_message, client_message_file);
                }
                // Close the file:
                fclose(file);

                // Concatenate the command and file path with the file data:
                if(argv[3] == NULL){
                    sprintf(client_message, "%s %s %s %s", argv[1], argv[2], "NULL", client_message_file);
                }else{
                    sprintf(client_message, "%s %s %s %s", argv[1], argv[2], argv[3], client_message_file);
                }
                printf("the client message: %s\n", client_message);

                // Send the concatenated message to the server:
                if(send(socket_desc, client_message, strlen(client_message), 0) < 0){
                    printf("Unable to send message\n");
                    return -1;
                }

                // Wait for a response from the server:
                if(recv(socket_desc, server_message, sizeof(server_message), 0) < 0){
                    printf("Error while receiving server's msg\n");
                    return -1;
                } else {
                    printf("the server message : %s", server_message);
                }
            }
        }
        else if(strcmp(argv[1], "RM")==0){

            if(send(socket_desc, client_message, strlen(client_message), 0) < 0){
                printf("Unable to send message\n");
                return -1;
            }
            int bytes_received = 0;
            char *token;

            while((bytes_received = recv(socket_desc, server_message, BUFFER_SIZE, 0)) > 0){
                server_message[bytes_received] = '\0';
                token = strtok(server_message, "\n");

                while(token != NULL){
                    printf("%s\n", token);
                    token = strtok(NULL, "\n");
                }
            }

            if(bytes_received < 0){
                printf("Error while receiving server's msg\n");
                return -1;
            }
        }



        // ...

        // Close the socket:
        close(socket_desc);

  return 0;
}








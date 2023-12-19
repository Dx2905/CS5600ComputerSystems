/*q4
 * server.c -- TCP Socket Server
 * 
 * adapted from: 
 *   https://www.educative.io/answers/how-to-implement-tcp-sockets-in-c
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define BUFFER_SIZE 1024
#define CONFIG_FILE "config.txt"
#define CONFIG_FILE1 "config1.txt"

int check_usb_devices_one(const char *file_path1);




void send_file(int client_sock, const char *file_path, const char *file_path1){
  
    char server_message[BUFFER_SIZE];
  char disk_path[BUFFER_SIZE], disk_path1[BUFFER_SIZE];

   FILE* config_file = fopen(CONFIG_FILE, "r");
      if (!config_file) {
        printf("Error opening config file %s\n", CONFIG_FILE);
        // return -1;
      }
      fscanf(config_file, "%s", disk_path);
      fclose(config_file);

   char full_file_path[BUFFER_SIZE];
            
    
    
    FILE* config_file1 = fopen(CONFIG_FILE1, "r");
       if (!config_file1) {
         printf("Error opening config file %s\n", CONFIG_FILE1);
         // return -1;
       }
       fscanf(config_file1, "%s", disk_path1);
       fclose(config_file1);

    char full_file_path1[BUFFER_SIZE];
    

    
    if(check_usb_devices_one(disk_path)) {
//        FILE *file = fopen(full_file_path, "rb");
        if(file_path1 == NULL){
            sprintf(full_file_path, "%s%s/%s", disk_path, (*disk_path != '/') ? "/" : "", file_path);
        } else{
            sprintf(full_file_path, "%s%s/%s", disk_path, (*disk_path != '/') ? "/" : "", file_path);
        }
        
    } else {
        
        if(file_path1 == NULL){
            sprintf(full_file_path, "%s%s/%s", disk_path1, (*disk_path1 != '/') ? "/" : "", file_path);
        } else{
            sprintf(full_file_path, "%s%s/%s", disk_path1, (*disk_path1 != '/') ? "/" : "", file_path);
        }
//        FILE *file = fopen(full_file_path1, "rb");
        
    }
    
    FILE *file = fopen(full_file_path, "rb");
  // FILE *file = fopen(file_path, "rb");
  
  if(!file){
    printf("Error opening file %s\n", file_path);
    return;
  }
  
  int bytes_read = 0;
  
  while((bytes_read = fread(server_message, 1, BUFFER_SIZE, file)) > 0){
    if(send(client_sock, server_message, bytes_read, 0) < 0){
      printf("Can't send\n");
      return;
    }
  }
  
  fclose(file);
}




void send_file_info(int client_sock, const char *file_path){
  char server_message[BUFFER_SIZE];
  struct stat file_stat;
char disk_path[BUFFER_SIZE], disk_path1[BUFFER_SIZE];

  
    FILE* config_file = fopen(CONFIG_FILE, "r");
       if (!config_file) {
         printf("Error opening config file %s\n", CONFIG_FILE);
         // return -1;
       }
       fscanf(config_file, "%s", disk_path);
       fclose(config_file);

    char full_file_path[BUFFER_SIZE];
 //
     
     FILE* config_file1 = fopen(CONFIG_FILE1, "r");
        if (!config_file1) {
          printf("Error opening config file %s\n", CONFIG_FILE1);
          // return -1;
        }
        fscanf(config_file1, "%s", disk_path1);
        fclose(config_file1);

     char full_file_path1[BUFFER_SIZE];
  //
     
     if(check_usb_devices_one(disk_path)) {
 //        FILE *file = fopen(full_file_path, "rb");
         sprintf(full_file_path, "%s%s/%s", disk_path, (*disk_path != '/') ? "/" : "", file_path);
     } else {
 //        FILE *file = fopen(full_file_path1, "rb");
         sprintf(full_file_path, "%s%s/%s", disk_path1, (*disk_path1 != '/') ? "/" : "", file_path);
     }

    
    
  if(stat(full_file_path, &file_stat) < 0){
    printf("Error getting file stats for %s\n", file_path);
    return;
  }
  
  sprintf(server_message, "File: %s", full_file_path);
  send(client_sock, server_message, strlen(server_message), 0);
  
  sprintf(server_message, "Size: %ld bytes", file_stat.st_size);
  send(client_sock, server_message, strlen(server_message), 0);
  
  sprintf(server_message, "Owner: %s", getpwuid(file_stat.st_uid)->pw_name);
  send(client_sock, server_message, strlen(server_message), 0);
  
  sprintf(server_message, "Group: %s", getgrgid(file_stat.st_gid)->gr_name);
  send(client_sock, server_message, strlen(server_message), 0);
  
  sprintf(server_message, "Last modified: %s", ctime(&file_stat.st_mtime));
  send(client_sock, server_message, strlen(server_message), 0);
  
  sprintf(server_message, "Permissions: %o", file_stat.st_mode & 0777);
  send(client_sock, server_message, strlen(server_message), 0);
}

void make_folder(int client_sock, const char *file_path){
    char server_message[BUFFER_SIZE];
    char disk_path[BUFFER_SIZE], disk_path1[BUFFER_SIZE];

    
    FILE* config_file = fopen(CONFIG_FILE, "r");
       if (!config_file) {
         printf("Error opening config file %s\n", CONFIG_FILE);
         // return -1;
       }
       fscanf(config_file, "%s", disk_path);
       fclose(config_file);

    char full_file_path[BUFFER_SIZE];
 //
     
     FILE* config_file1 = fopen(CONFIG_FILE1, "r");
        if (!config_file1) {
          printf("Error opening config file %s\n", CONFIG_FILE1);
          // return -1;
        }
        fscanf(config_file1, "%s", disk_path1);
        fclose(config_file1);

     char full_file_path1[BUFFER_SIZE];
  //
     
     if(check_usb_devices_one(disk_path)) {
 //        FILE *file = fopen(full_file_path, "rb");
         sprintf(full_file_path, "%s%s/%s", disk_path, (*disk_path != '/') ? "/" : "", file_path);
     }
    
    int status = mkdir(full_file_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if(status == 0){
      // Successful directory creation
      strcpy(server_message, "Directory created successfully");
    }
    else{
      // Failed directory creation
      perror("Error creating directory");
      strcpy(server_message, "Error creating directory");
    }
    if(check_usb_devices_one(disk_path1)){
        //        FILE *file = fopen(full_file_path1, "rb");
                sprintf(full_file_path, "%s%s/%s", disk_path1, (*disk_path1 != '/') ? "/" : "", file_path);
            }
    int status1 = mkdir(full_file_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if(status1 == 0){
      // Successful directory creation
      strcpy(server_message, "Directory created successfully");
    }
    else{
      // Failed directory creation
      perror("Error creating directory");
      strcpy(server_message, "Error creating directory");
    }

    if (send(client_sock, server_message, strlen(server_message), 0) < 0){
      printf("Can't send\n");
    }
    
}
int check_usb_devices(const char *file_path1, const char *file_path2) {
  int found_device_1 = 0;
  int found_device_2 = 0;

  // Check for device 1
  DIR* dir_1 = opendir(file_path1);
  if (dir_1 != NULL) {
    found_device_1 = 1;
    closedir(dir_1);
  }

  // Check for device 2
  DIR* dir_2 = opendir(file_path2);
  if (dir_2 != NULL) {
    found_device_2 = 1;
    closedir(dir_2);
  }

  // Return 1 if both devices are found, 0 otherwise
  return (found_device_1 && found_device_2);
}

int check_usb_devices_one(const char *file_path1) {
  int found_device_1 = 0;
//  int found_device_2 = 0;

  // Check for device 1
  DIR* dir_1 = opendir(file_path1);
  if (dir_1 != NULL) {
    found_device_1 = 1;
    closedir(dir_1);
  }


  return (found_device_1);

}

void sync_usb_devices(const char *file_path1, const char *file_path2) {
  // Synchronize files from device 1 to device 2
  char cmd[1024];
//  sprintf(cmd, "sudo rsync -av --delete %s/ %s/ > /dev/null 2>&1", file_path1, file_path2);
//    sprintf(cmd, "sudo rsync -av --delete -p %s/ %s/", file_path1, file_path2);
    sprintf(cmd, "sudo rsync -av --no-perms --delete --exclude='.Trashes' --exclude='.TemporaryItems' --rsync-path=/usr/bin/rsync --super %s/ %s/", file_path1, file_path2);
  system(cmd);

  // Synchronize files from device 2 to device 1
//  sprintf(cmd, "sudo rsync -av --delete %s/ %s/ > /dev/null 1>&2", file_path1, file_path2);
//    sprintf(cmd, "sudo rsync -av --delete -p %s/ %s/ >", file_path1, file_path2);
    sprintf(cmd, "sudo rsync -av --no-perms --delete --exclude='.Trashes' --exclude='.TemporaryItems' --rsync-path=/usr/bin/rsync --super %s/ %s/", file_path1, file_path2);
  system(cmd);
}



    int main(void)
{
        int socket_desc, client_sock;
        socklen_t client_size;
        struct sockaddr_in server_addr, client_addr;
        char client_message[BUFFER_SIZE];
//        char msg[BUFFER_SIZE];
        
        // Create socket:
        socket_desc = socket(AF_INET, SOCK_STREAM, 0);
        
        if(socket_desc < 0){
            printf("Error while creating socket\n");
            return -1;
        }
        
        printf("Socket created successfully\n");
        
        // Set port and IP:
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(2000);
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        
        // Bind to the set port and IP:
        if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0){
            printf("Couldn't bind to the port\n");
            return -1;
        }
        
        printf("Done with binding\n");
       
            // Listen for clients:
            if(listen(socket_desc, 1) < 0){
                printf("Error while listening\n");
                return -1;
            }
            
            printf("\nListening for incoming connections.....\n");
            
            
            while(1){
            // Accept an incoming connection:
            client_size = sizeof(client_addr);
            client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, &client_size);if (client_sock < 0){
                printf("Can't accept\n");
                return -1;
            }
            
            printf("Client connected at IP: %s and port: %i\n",
                   inet_ntoa(client_addr.sin_addr),
                   ntohs(client_addr.sin_port));
            
            // Receive client's message:
            if (recv(client_sock, client_message,
                     sizeof(client_message), 0) < 0){
                printf("Couldn't receive\n");
                return -1;
            }
            
            // Parse the command:
            char command[10], file_path[BUFFER_SIZE], file_path1[BUFFER_SIZE];
//            sscanf(client_message, "%s %s %s %s", command, file_path, file_path1, msg);
                char *msg;
//                if (sscanf(client_message, "%s %s %s", command, file_path, file_path1) < 3) {
                sscanf(client_message, "%s %s %s", command, file_path, file_path1);
//                  printf("Invalid message format\n");
//                  return -1;
//                }
                msg = strstr(client_message, file_path1) + strlen(file_path1) + 1;
                printf("Word 1: %s\n", command);
                printf("Word 2: %s\n", file_path);
                printf("Word 3: %s\n", file_path1);
                printf("Remaining message: %s\n", msg);
                
                
                char disk_path[BUFFER_SIZE], disk_path1[BUFFER_SIZE];

 FILE* config_file = fopen(CONFIG_FILE, "r");
    if (!config_file) {
      printf("Error opening config file %s\n", CONFIG_FILE);
      // return -1;
    }
    fscanf(config_file, "%s", disk_path);
    fclose(config_file);

 char full_file_path[BUFFER_SIZE];
//          sprintf(full_file_path, "%s/%s", disk_path, file_path1);
                sprintf(full_file_path, "%s%s/%s", disk_path, (*disk_path != '/') ? "/" : "", file_path1);

//                char *remote_file_path = full_file_path;
              
              FILE* config_file1 = fopen(CONFIG_FILE1, "r");
                 if (!config_file1) {
                   printf("Error opening config file %s\n", CONFIG_FILE1);
                   // return -1;
                 }
                 fscanf(config_file1, "%s", disk_path1);
                 fclose(config_file1);

              char full_file_path1[BUFFER_SIZE];
//                       sprintf(full_file_path1, "%s/%s", disk_path1, file_path1);
                sprintf(full_file_path1, "%s%s/%s", disk_path1, (*disk_path1 != '/') ? "/" : "", file_path1);


//
                
            if(strcmp(command, "GET") == 0){
                send_file(client_sock, file_path, file_path1);
            }
            else if(strcmp(command, "INFO") == 0){
                send_file_info(client_sock, file_path);
            }
            
            else if(strcmp(command, "MD") == 0){
                make_folder(client_sock, file_path);
            }  else if(strcmp(command, "PUT") == 0){
                
            
                
                  char disk_path[BUFFER_SIZE], disk_path1[BUFFER_SIZE];

   FILE* config_file = fopen(CONFIG_FILE, "r");
      if (!config_file) {
        printf("Error opening config file %s\n", CONFIG_FILE);
        // return -1;
      }
      fscanf(config_file, "%s", disk_path);
      fclose(config_file);

   char full_file_path[BUFFER_SIZE];
//            sprintf(full_file_path, "%s/%s", disk_path, file_path1);
                sprintf(full_file_path, "%s%s/%s", disk_path, (*disk_path != '/') ? "/" : "", file_path1);
                  char *remote_file_path = full_file_path;
                
                FILE* config_file1 = fopen(CONFIG_FILE1, "r");
                   if (!config_file1) {
                     printf("Error opening config file %s\n", CONFIG_FILE1);
                     // return -1;
                   }
                   fscanf(config_file1, "%s", disk_path1);
                   fclose(config_file1);

                char full_file_path1[BUFFER_SIZE];
//                         sprintf(full_file_path1, "%s/%s", disk_path1, file_path1);
                sprintf(full_file_path1, "%s%s/%s", disk_path1, (*disk_path1 != '/') ? "/" : "", file_path1);
                               char *remote_file_path1 = full_file_path1;
                
                  char server_message[BUFFER_SIZE];
                  int bytes_read = 0;
                    
               
                if (strcmp(file_path1,"NULL")==0) {
//                    if (strcmp(file_path1, (null) == 0) {
                    printf("remote_file_path does not exist\n");
                    sprintf(full_file_path, "%s/%s", disk_path, file_path);
                    remote_file_path = full_file_path;
                    
                } else {
                    sprintf(full_file_path, "%s/%s", disk_path, file_path1);
                    remote_file_path = full_file_path;
                }

               
                if (strcmp(file_path1,"NULL")==0) {
//
               
//
                    printf("remote_file_path does not exist\n");
                    sprintf(full_file_path1, "%s/%s", disk_path1, file_path);
                    remote_file_path1 = full_file_path1;
                    
                } else {
                    printf("remote_file_path exist\n");
                    sprintf(full_file_path1, "%s/%s", disk_path1, file_path1);
                    remote_file_path1 = full_file_path1;
                }
                
                FILE *file = fopen(remote_file_path, "w+");
                printf("the contents of file received: %s\n", msg);
                    fwrite(msg, 1, strlen(msg), file);
                
                FILE *file1 = fopen(remote_file_path1, "w+");
                printf("the contents of file received: %s\n", msg);
                    fwrite(msg, 1, strlen(msg), file1);
//                  }

                  // Send the success message to the client:
                  sprintf(server_message, "File uploaded successfully");
                  if(send(client_sock, server_message, strlen(server_message), 0) < 0){
                    printf("Can't send\n");
                    return -1;
                  }

                  fclose(file);
                fclose(file1);
                } 
                 else if(strcmp(command, "RM") == 0){
      // Extract the remote file/folder path from the client message:
        char server_message[BUFFER_SIZE];
        char disk_path[BUFFER_SIZE], disk_path1[BUFFER_SIZE];

       FILE* config_file = fopen(CONFIG_FILE, "r");
      if (!config_file) {
        printf("Error opening config file %s\n", CONFIG_FILE);
        // return -1;
      }
      fscanf(config_file, "%s", disk_path);
      fclose(config_file);

   char full_file_path[BUFFER_SIZE];
//
                     sprintf(full_file_path, "%s%s/%s", disk_path, (*disk_path != '/') ? "/" : "", file_path);
//        char *remote_file_path = strtok(NULL, " ");
        char *remote_file_path = full_file_path;
       
      // Delete the file/folder using the specified path:
      if(remove(remote_file_path) != 0){
        // If the file/folder cannot be deleted, send an error message to the client:
        sprintf(server_message, "Error deleting %s: %s", remote_file_path, strerror(errno));
      }
      else{
        // If the file/folder is successfully deleted, send a success message to the client:
        sprintf(server_message, "%s deleted successfully", remote_file_path);
      }
                     
                     
                     
                     FILE* config_file1 = fopen(CONFIG_FILE1, "r");
                    if (!config_file1) {
                      printf("Error opening config file %s\n", CONFIG_FILE1);
                      // return -1;
                    }
                    fscanf(config_file1, "%s", disk_path1);
                    fclose(config_file1);

                 char full_file_path1[BUFFER_SIZE];
              //            sprintf(full_file_path, "%s/%s", disk_path, file_path);
                                   sprintf(full_file_path1, "%s%s/%s", disk_path1, (*disk_path1 != '/') ? "/" : "", file_path);
              //        char *remote_file_path = strtok(NULL, " ");
                      char *remote_file_path1 = full_file_path1;
                      // char *remote_file_path = file_path;
                    // Delete the file/folder using the specified path:
                    if(remove(remote_file_path1) != 0){
                      // If the file/folder cannot be deleted, send an error message to the client:
                      sprintf(server_message, "Error deleting %s: %s", remote_file_path1, strerror(errno));
                    }
                    else{
                      // If the file/folder is successfully deleted, send a success message to the client:
                      sprintf(server_message, "%s deleted successfully", remote_file_path1);
                    }

      if(send(client_sock, server_message, strlen(server_message), 0) < 0){
        printf("Can't send\n");
        return -1;
      }
    }

            // ...
            
            else{
                printf("Invalid command: %s\n", command);
                return -1;
            }
        
            // Closing the socket:
            close(client_sock);
        }
        
        close(socket_desc);

return 0;
}

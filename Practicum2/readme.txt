Gaurav 
CS5600 spring 2023
Assignment : Practicum2

The .tar file contains client.c , server.c, config.txt, config1.txt and readme.txt


Client.c : managing client side

Server.c : managing server side

Config.txt: path for diskstore1

Config1.txt: path for diskstore2


For running the code: Run the Makefile: $make
                      First run the server: ./fserver
                      Then run the client: ./fget with different command

For getting the file from remote system: ./fget GET remote_path local_path
                                         If remote path absent takes the local path
                                        If one disk is absent takes from another disk

For getting info of file from remote: ./fget INFO remote_path
					If one disk is absent takes from another disk

For making the directory on remote system: ./fget MD remote_path
                                            Makes directory on the both the disk

For making removing the file or directory: ./fget RM remote_path
					   Removes directory on the both the disk

For putting file from local to remote system: ./fget PUT local_path remote_path
                                               If the remote path absent use the local path







# Multithreaded Client/Server File System

## 📌 Project Overview
This project implements a **multithreaded client-server file system** using **TCP socket programming in C**. The system enables clients to interact with remote storage by performing operations like **file retrieval, metadata retrieval, directory creation, file upload, and deletion**.

The file system operates over a **network** and ensures redundancy by storing files across **multiple USB storage devices**.

---

## 📜 Table of Contents
- [Project Overview](#project-overview)
- [Features](#features)
- [Technologies Used](#technologies-used)
- [Installation](#installation)
- [Usage](#usage)
- [Project Files](#project-files)
- [Commands & Functionality](#commands--functionality)
- [Future Enhancements](#future-enhancements)
- [Contributors](#contributors)
- [License](#license)

---

## 🖥 Features
- **Multithreaded Server**: Handles multiple client requests concurrently.
- **File Management**: Supports file retrieval, metadata retrieval, and deletion.
- **Remote Storage Support**: Uses multiple storage paths to enhance fault tolerance.
- **Network Communication**: Clients and server communicate over TCP sockets.
- **Redundant Data Storage**: Ensures reliability across two disk paths.

---

## 💡 Technologies Used
- **Programming Language**: C
- **Networking**: TCP Sockets
- **Concurrency**: Multithreading
- **File System Management**: POSIX APIs
- **Makefile**: Automates compilation

---

## 🛠 Installation
### **1. Clone the Repository**
```bash
git clone https://github.com/Dx2905/CS5100-Foundation-Of-AI.git
cd CS5100-Foundation-Of-AI/MultithreadedFS
```

### **2. Compile the Program**
Run the following command to compile both the server and client programs:
```bash
make
```
This will generate the `fserver` (server executable) and `fget` (client executable).

---

## 🚀 Usage
### **1. Start the Server**
```bash
./fserver
```
This will start the server, waiting for incoming client connections.

### **2. Start the Client**
To interact with the file system, run:
```bash
./fget <command> <file-path>
```
Example:
```bash
./fget GET /remote/path/to/file.txt /local/path/file.txt
```

---

## 📂 Project Files
| File Name | Description |
|-----------|------------|
| `server.c` | Server-side implementation managing file system operations |
| `client.c` | Client-side implementation for interacting with the server |
| `config.txt` | Path configuration for **diskstore1** |
| `config1.txt` | Path configuration for **diskstore2** |
| `Makefile` | Automates compilation of the project |
| `readme.txt` | Additional project documentation |

---

## 🔧 Commands & Functionality
| Command | Usage |
|---------|-------|
| **GET** | Retrieve a file from the remote system:  
`./fget GET <remote-path> <local-path>` |
| **INFO** | Get metadata (size, owner, permissions) of a file:  
`./fget INFO <remote-path>` |
| **MD** | Create a directory on the remote system:  
`./fget MD <remote-path>` |
| **RM** | Remove a file or directory from the remote system:  
`./fget RM <remote-path>` |
| **PUT** | Upload a file from local to remote storage:  
`./fget PUT <local-path> <remote-path>` |

---

## 🔮 Future Enhancements
- **Enhance Security**: Implement authentication and encryption for secure data transfer.
- **Error Handling**: Improve exception handling for file operations.
- **Web-based Interface**: Create a GUI for easier interaction with the file system.
- **Logging System**: Maintain logs of file operations for better monitoring.

---

## 👥 Contributors
- **Gaurav** ([@Dx2905](https://github.com/Dx2905))

📍 **Khoury College, Northeastern University, Portland, Maine, USA**

For inquiries, contact: `lnu.gau@northeastern.edu`

---

## 📜 License
This project is licensed under the **MIT License**. See the [LICENSE](https://github.com/Dx2905/CS5100-Foundation-Of-AI/blob/main/LICENSE) file for more details.

---

🚀 **If you found this project useful, give it a ⭐ on GitHub!** 🎉


# 🗨️ Multithreaded TCP Chat Application (C / Winsock)

## Description
This is a simple multi-client TCP chat application written in C using the Windows Sockets (Winsock) API.  
It allows multiple clients to connect to a server and exchange messages in real time.  

Each message sent by one client is broadcast to all the other connected clients.

---

## 🧠 Overview

The project consists of three main parts:

- **server.c** – Starts a TCP server that listens for incoming client connections on a specific port (default: `2000`).
- **client.c** – Connects to the server and allows the user to send and receive chat messages.
- **utils.c / utils.h** – Contains helper functions for socket creation, address setup, connection handling, and multithreading.

  ![image alt](https://github.com/Aatish-hari/Multithreaded-TCP-Chat-Application/blob/main/working%20example.png?raw=true)

It uses:
- `Winsock2.h` for networking
- `pthread` for handling multiple connections concurrently
- Basic C I/O for the chat interface

---

# ECHO SERVER AND CLIENT

**written in C**

Echo server socket multithread

Client with reception data on socket thread, ping thread, quit command

### Ubuntu

```bash
sudo apt-get update
sudo apt-get install build-essential
```

### Fedora

```bash
sudo dnf install gcc
```

### CentOS

```bash
sudo yum groupinstall "Development Tools"
```

Compile and add execute permission:
```bash
chmod +x build.sh
./build.sh
chmod +x SERVER/server CLIENT/client
```

Now you can run the server that listens for connections:
```bash
./SERVER/server
```

After setting the server on listening it is possible to start as many clients as you need (adjust MAX_CLIENTS defined in socket.h)
```bash
./CLIENT/client
```
# Peer-To-Peer-Communication
## Creating an end to end application based on IPC mechanisms (Sockets, FIFO)

#### For FIFO: 
##### Steps to run:
```bash
make clean
make all
make runF
make runP1
make runP2
```
Main.c is used in fifo to create 2 fifo pipes. This is done to avoid error 
due to p1 trying to read intFifo which does not exist (as it will be 
created in p2). To avoid this we create the fifo files in main.c and use 
these files in p1 and p2 as read only flag or read/write flag. Fifos are 
named pipes and 1 directional so 2 fifo files are needed for both side 
communication.

#### For Sockets: 
##### Steps to run:
```bash
make clean
make all
make runP2
make runP1
```
There is no need to create main.c in sockets as sockets are 2 directional

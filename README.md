# Network-app
Application developed in the C programming language, which implements a network of graphs.

This application simulates a network of PCs that can connect to various routers.

The following instructions have been implemented in this project:
ping x.x.x.x x.x.x.x: says if there is a connection between two stations (takes into account the connections between all routers and the states of the ends);
sipn x.x.x.x: displays the routers with which you have a direct connection;
and x.x.x.x: displays which PCs are connected (status = 1) directly to the router;
trace x.x.x.x x.x.x.x: displays the route from device to device (router ips that form the "shortest path")
up x.x.x.x: open a PC;
lc x.x.x.x x.x.x.x: destroys the connection between 2 routers;
broke x.x.x.x: shut down a PC;
add x.x.x.x x.x.x.x d: add a connection between 2 routers, with "distance" d;

At the base of the trace statement is Dijkstra's algorithm, use to find the minimum cost path.


HYPERCUBE TOPOLOGY ROUTING
=======
PURPOSE
-------
Software implemented to experience with routing in the Hypercube network topology.

DESCRIPTION
-------
The software prints the routing paths for packets based on dimension order single path (bitwise lowest dimension first) and all shortest path routing.

### The program works as following:
#### To Compile:
     make
#### To Execute:
     ./hypercubeRouting [NumberOfEdges(Must be power of 2)] [dim|all]
##### where options are:
     dim: Display dimension order single path routing
     all: Display all shortest path routing
#### Example:  
     ./hypercubeRouting 4 dim
 #### Will ask for:  
     input src dst : (i.e. 0 3)  
 #### Has the following output:
     path from 0 to 3: 0(00)->1(01)->3(11)
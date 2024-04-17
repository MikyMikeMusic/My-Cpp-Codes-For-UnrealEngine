## UDijkstra Class Summary

The `UDijkstra` class appears to be an Unreal Engine 5 component that implements the Dijkstra algorithm for moving an actor along a path defined by nodes. This code is not complete and is currently a prototype. The aim of this prototype is to "spatialize" a moving AudioComponent in 3D space. Here's a brief description of the main methods and member variables:

# Attributes
- ChooseTheNumberOfNode: This attribute represents the number of nodes in the graph. You can set it via the SetChooseTheNumberOfNode function.
- startNodeIndex: This attribute represents the index of the start node for the Dijkstra algorithm.
- actorToMove: This attribute is a pointer to the actor that needs to be moved along the shortest path.
- path: This attribute is an array that contains the shortest path calculated by the Dijkstra algorithm.
- currentNodeIndex: This attribute represents the index of the current node along the path.
- speed: This attribute represents the speed at which the actor moves along the path.
- Nodes: This attribute is an array of nodes in the graph. Each node is a FDijkstraNode structure that contains the node's position and a map of its neighboring nodes and the weights of their connections.

  
# Functions
- UDijkstra(): This is the constructor of the class. It initializes the various attributes.
- BeginPlay(): This function is called at the start of the game. It generates the nodes, calculates the shortest path, and starts moving the actor along the path.
- TickComponent(): This function is called at each frame of the game. It moves the actor along the path.
- SetChooseTheNumberOfNode(): This function sets the number of nodes in the graph.
- GenerateRandomPositions(): This function generates random positions for the nodes.
- AddNode(): This function adds a node to the graph.
- AddEdge(): This function adds an edge between two nodes in the graph.
- FindClosestNode(): This function finds the closest node to a given position.
- DijkstraAlgorithm(): This function implements the Dijkstra algorithm to find the shortest path.
- MoveActorAlongPath(): This function moves the actor along the shortest path.
The FDijkstraNode structure represents a node in the graph. It contains a Position attribute that represents the node's position and a Neighbors attribute which is a map of the neighboring nodes and the weights of their connections.

I hope this summary helps you better understand the `UDijkstra` class. If you need further details on specific parts of the code, don't hesitate to ask.

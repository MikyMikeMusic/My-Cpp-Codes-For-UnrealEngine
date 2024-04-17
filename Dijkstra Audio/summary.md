# UDijkstra Class Summary

The `UDijkstra` class appears to be an Unreal Engine 5 component that implements the Dijkstra algorithm for moving an actor along a path defined by nodes. This code is not complete and is currently a prototype. The aim of this prototype is to "spatialize" a moving AudioComponent in 3D space. Here's a brief description of the main methods and member variables:

- `UDijkstra()`: This is the class constructor. It sets default values for the component's properties, such as the actor to move (`actorToMove`), the number of nodes to choose (`ChooseTheNumberOfNode`), the current node index (`currentNodeIndex`), and the movement speed (`speed`).

- `BeginPlay()`: This method is called at the start of the game. It adds nodes if `ChooseTheNumberOfNode` is greater than zero, finds the node closest to the actor, and starts moving the actor along the path resulting from the Dijkstra algorithm.

- `TickComponent()`: This method is called every game frame. If there's an actor to move, it checks if the actor has reached the current node. If so, it moves on to the next node. If the actor hasn't reached the current node, it moves the actor towards the current node.

- `AddNode()`: This method adds a specified number of nodes to the node map.

- `DijkstraAlgorithm()`: This method implements the Dijkstra algorithm to find the shortest path from a start node to all other nodes.

The main member variables include:

- `actorToMove`: This is the actor that is to be moved along the path.

- `ChooseTheNumberOfNode`: This is the number of nodes to choose.

- `currentNodeIndex`: This is the index of the current node in the path.

- `speed`: This is the speed at which the actor moves along the path.

I hope this summary helps you better understand the `UDijkstra` class. If you need further details on specific parts of the code, don't hesitate to ask.
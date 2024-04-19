# Codes for Physical Audio Phenomena in Unreal Engine

This folder contains various programming codes that I created to explore the physical phenomena of audio in **Unreal Engine** using **C++**.

## Content:
- AudioSorter: The 'AAudioSorter' class is an Unreal Engine actor that provides functionality to sort an array of sounds. It can sort sounds by their duration or name.
- DopplerEffect: This project includes an actor that can be called from the Blueprint class. 
The actor has an audio component and a 'PreviousLocation' variable of type 'FVector'.
The actor uses a function that measures the Doppler effect based on the movement of this actor (sound source) relative to the listener (camera). 
The difference between the listener's position and the listener's previous position is measured, this variable is then added to the constant speed of sound, and the
- Dynamic Fade In & Out: This class dynamically manage the Fade Ins and Fades of a sound based on the use of Float curves, in this way you can "draw" the Fade In and Fade Out as in DAWs like Ableton, Cubase, trying to be less "raw" and more precise than the standard Fade In and Out.
- MusicPlaylist: The 'AMusicPlaylistActor' class uses a number of Unreal Engine data structures, including 'TArray', 'TMap' and 'TQueue', to manage the playlist and its operations. 
It also maintains a number of state variables, such as the index of the current track and whether the playlist is currently playing or in shuffle mode.
- SoundLocalization: In this code I tried to simulate the localization of the sound, without using the settings of the Unreal Engine Attenuation audio engine and without the use of any Middleware. 
I simply created a component class that instantiates two AudioComponents, called LeftEar and RighEar, then calculated the attenuation based on the distance between the actor who owns the component and the camera manager, and finally simulated the Panning effect with Metasound,
Calculating the angle of rotation of the camera and using that value to set the Float parameter associated with the Metasound that reproduces the sound.
- SoundManager: This project implements a sound management system (simulating the MaxHeap tree data structure) for Unreal Engine. The system manages a series of sound effects, each with an associated priority, and can play the sound effect with the highest priority or all sound effects in order of priority. 
The system uses a pool of nodes to optimize memory allocation.
- MyModule : A brief example of using OOP principles, such as composition, aggregation, interfaces, decoupling, and modularity. Just referring to the latter I exported folder with the created module with all its dependencies on other modules.
- SoundSource with Graph Dfs : The class has methods to initialize and position sound sources, perform a depth-first search (DFS), play a sound, and print the position of a sound source. Sound sources are created for each sound provided, positioned at random locations within a defined range, and connected to each other. The depth-first search is performed starting from a specified sound source, playing the sound and printing the position of each visited sound source.
- DijkstraAudio : The `UDijkstra` class appears to be an Unreal Engine 5 component that implements the Dijkstra algorithm for moving an actor along a path defined by nodes. This code is not complete and is currently a prototype. The aim of this prototype is to "spatialize" a moving AudioComponent in 3D space.
- AudioDeviceForTest: This class represents an "abstract audio device" used for testing purposes. The `AudioDeviceForTest` class is initialized with various parameters that describe the characteristics of the audio that will be handled, such as the sample rate, the number of channels, the number of frames per callback, a callback function, and an opaque pointer to user data (the "cookie"). The callback function is called whenever the audio device needs more data. In this example, the callback function simply fills the buffer with zeros. This class can be used to simulate an audio device for testing and debugging your audio code.
- Buffer: These buffering techniques are crucial for ensuring smooth and uninterrupted audio playback in many audio programming applications.
- Audio Engine Multithreaded Simulation : The `AudioEngineMultithreadSimulation` class is designed to simulate a multithreaded audio engine in Unreal Engine. It uses a message queue to handle play and stop requests for sounds, and uses a `TAtomic` object to keep track of the number of messages in the queue.

Feel free to explore and use these codes for your portfolio or personal projects!

Kind regards
Michele Grimaldi



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


Feel free to explore and use these codes for your portfolio or personal projects!

Kind regards
Michele Grimaldi


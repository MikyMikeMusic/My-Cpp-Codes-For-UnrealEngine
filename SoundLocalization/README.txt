Read Before Use It

In this code I tried to simulate the localization of the sound, without using the settings of the Unreal Engine Attenuation audio engine and without the use of any Middleware. 
I simply created a component class that instantiates two AudioComponents, called LeftEar and RighEar, then calculated the attenuation based on the distance between the actor who owns the component and the camera manager, and finally simulated the Panning effect with Metasound,
Calculating the angle of rotation of the camera and using that value to set the Float parameter associated with the Metasound that reproduces the sound.

                                                                                                                                                                                                                                                                                                                                          
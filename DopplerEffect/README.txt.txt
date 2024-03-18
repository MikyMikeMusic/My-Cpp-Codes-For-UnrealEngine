I've created an actor that can be called from the Blueprint class.
This actor will have an Audio Component and a PreviousLocation FVector variable.

This class will use a function that will measure the Doppler effect based on the movement of this actor (sound source) relative to the listener (camera).
The difference between the listener and the listener will be measured, this variable will be added to the constant velocity of the sound, which sum of the latter will be divided by itself.

These values will affect the pitch of the sound source, in this case we will use the SetPitchMultiplier function with argument to the result of the Doppler Effect equation.

This feature also monitors the movement of the listener and the sound source in real time.
# AudioEngineMultithreadSimulation

The `AudioEngineMultithreadSimulation` class is designed to simulate a multithreaded audio engine in Unreal Engine. It uses a message queue to handle play and stop requests for sounds, and uses a `TAtomic` object to keep track of the number of messages in the queue.

## Class Members

- `TQueue<Message> messageQueue`: A message queue that holds the play and stop requests for sounds.
- `TAtomic<int32> FrameMessages`: An atomic counter that keeps track of the number of messages in the queue.
- `bool Stop`: A flag indicating whether the audio engine should stop.

## Class Methods

- `Play(int SoundID)`: Adds a play request to the message queue.
- `Stop(int SoundID)`: Adds a stop request to the message queue.
- `Update()`: Increments the atomic counter `FrameMessages`.
- `ProcessMessages()`: Processes the messages in the queue until there are no more messages or until the `Stop` flag is set to `true`.
- `StopEngine()`: Sets the `Stop` flag to `true`, indicating that the audio engine should stop.
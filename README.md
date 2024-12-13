# NN Food

A momentum controled game with a neural network implementation to train an AI to play

## Build Instructions

Clone repository (git clone) and cd into directory

```
mkdir build
cmake ..
build
```

## Running Intructions

While in ./build you can run the following

```
./Overlord //Play Game
./TrainOverlord [threads] [models per thread] // Train AI
./RunOverlord [NN path] // Run Neural Network WIP
```

## TODO list
 - Add SDL2 to repo to prevent having to clone it
 - Save & load neural network
 - Fully implment the NEAT framework

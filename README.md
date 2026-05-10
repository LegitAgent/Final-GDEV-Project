# OpenGL Millennium Falcon Animation

A small OpenGL 3D animation project featuring a Millennium Falcon-style model with movement, floor scrolling, and a spinning front cylinder thing.

## Features

### 1. Millennium Falcon Animation

The main focus of the project is a 3D Millennium Falcon-style model animated in OpenGL.

The model is rendered in a 3D scene and uses transformations like translation, rotation, and scaling to make it feel more alive instead of just sitting there like a dead mesh.

### 2. Floor Scroll

The floor scroll gives the illusion that the ship is moving forward.

Instead of moving the entire world, the floor texture/geometry scrolls backward, which is kinda the classic “fake movement but it works” trick.

This helps sell the motion without needing a huge environment.

### 3. Spinning Cylinder Thing at the Front

There is also a spinning cylinder-like object at the front of the model.

It is basically the rotating front part of the animation. It adds extra motion and makes the ship feel more mechanical/dynamic instead of being completely static.

## Built With

- OpenGL
- C / C++ 
- 3D transformations
- Texture / floor movement logic
- Basic animation loop

## How It Works

The scene updates every frame using an animation loop.

Each frame:

- the Millennium Falcon model is drawn
- the floor scroll position is updated
- the front cylinder rotation is updated
- OpenGL redraws the scene with the new transformations

The animation is just a bunch of small changes happening every frame until it looks smooth.

## Main Concepts Used

- `glTranslatef()` for moving objects
- `glRotatef()` for spinning/rotating parts
- `glScalef()` for resizing objects
- animation variables that update every frame
- repeated floor movement to fake forward motion

## Notes

Some parts of the model/animation are more visual than physically accurate.

The spinning cylinder thing is mainly there because it looks nice and adds movement to the front of the ship.

The floor scrolling is also a visual trick, it works well enough for making the ship feel like it is flying forward.

## Running the Project

Compile and run the OpenGL project using your usual setup.

Make sure OpenGL and the required graphics libraries are installed before running.

## Author

Made as an OpenGL 3D animation project.
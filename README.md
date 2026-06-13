# QBert

GitHub Link: https://github.com/khinelinkyaw/q-bert

This is a remake of the classic arcade game QBert, made in C++ using SDL3.
The project is structured as a CMake project, and can be built for both Windows and web (using Emscripten).

This project is split into the game (QBert) and the game engine (Minigin).

The game engine is a simple 2D game engine which uses Game Objects and Components. 
It also has a simple resource manager for loading and caching textures and fonts, and loading and saving JSON files.

There is a simple scene manager which can load and unload scenes. A scene is just a collection of game objects.
The usual functionality of a game engine is implemented, such as a main loop, input handling, rendering, and collision detection.

Component-to-component communication is done through a simple message system, relayed through the game object.
Scene-wide broadcast messages are supported. The scene goes through each game object and calls the event function on each of its components.

The sound system is implemented using miniaudio, and is run on a separate thread.

A small UI engine exist for importing JSON data and creating UI elements based on that data. 
The UI elements are also game objects, and can have components just like any other game object.

## Windows version

Either
- Open the root folder in Visual Studio 2026; this will be recognized as a cmake project.
  
Or
- Install CMake 
- Install CMake and CMake Tools extensions in Visual Code
- Open the root folder in Visual Code,  this will be recognized as a cmake project.

Or
- Use whatever editor you like :)

## Emscripten (web) version

### On windows

For installing all of the needed tools on Windows I recommend using [Chocolatey](https://chocolatey.org/). You can then run the following in a terminal to install what is needed:

    choco install -y cmake
    choco install -y emscripten
    choco install -y ninja
    choco install -y python

In a terminal, navigate to the root folder. Run this: 

    mkdir build_web
    cd build_web
    emcmake cmake ..
    emmake ninja

To be able to see the webpage you can start a python webserver in the build_web folder

    python -m http.server

Then browse to http://localhost:8000 and you're good to go.

### On OSX

On Mac you can use homebrew

    brew install cmake
    brew install emscripten
    brew install python

In a terminal on OSX, navigate to the root folder. Run this: 

    mkdir build_web
    cd build_web
    emcmake cmake .. -DCMAKE_OSX_ARCHITECTURES=""
    emmake make

To be able to see the webpage you can start a python webserver in the build_web folder

    python3 -m http.server

Then browse to http://localhost:8000 and you're good to go.

## Github Actions

This project is build with github actions.
- The CMake workflow builds the project in Debug and Release for Windows and serves as a check that the project builds on that platform.
- The Emscripten workflow generates a web version of the project and publishes it as a [github page](https://avadae.github.io/minigin/). 
  - The url of that page will be `https://<username>.github.io/<repository>/`
- You can embed this page with 

```<iframe style="position: absolute; top: 0px; left: 0px; width: 1024px; height: 576px;" src="https://<username>.github.io/<repository>/" loading="lazy"></iframe>```


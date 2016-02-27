# Miniature Space Man - Design Documentation
The design document that will hopefully govern how this project is undertaken.

## General Design Statement
The aim of this project is to create a graphical planetarium that displays a simulation of a solar system (or even galaxies). The planetarium will be three dimensional, and allow free traversing by the 'player' through mouse/keyboard input. There will be a number of predefined setups to choose from, e.g. Earth + moon, Sun + Planets, the Jupiter System etc. The player will be able to create and save their own system using an in game editor. The player will be able to control the speed of the simulation, from real time to highly accelerated time. Various integrators will be available to be used. Simulations will have varying degrees of accuracy, from full N-body Newtonian mechanics (possibly adding in relativistic effects) to simplified 2-body mechanics (eg moon orbiting a planet). There will be varying attempts/levels of optimisation inbetween these extremes, as and when they are attempted, all of which will be selectable.

## Program Flow
From clicking on the application icon to launch the program:
- A splash screen will show that shows the loading progress of the application.
- At the main menu, there will be options for Launch, Edit, Settings and Quit.
- Quit will exit the application.
- Settings will enable the default level of accuracy, the integration scheme and various graphical things to be changed.
- Edit will launch a system editing/creating functionality (design TBD).
- Launch will have a drop down next to it that allows choosing the system to simulate. Clicking launch will transition to the simulation display.
- The background of the main menu will be a display of a random system, running at a resonably large timestep. It will be using either 2-body mechanics, or a higher level optimisation, but not full N-body. Save that for watching in game. It will also switch to a different random system every 90 seconds. There may be some panning and such going on with it.
- Mouse and keyboard controls will enable panning, zooming and translating the view.
- Buttons will exist to modify the time step to use, like KSP has from time warp.
- Planets/objects will be modlled as spheres, with a texture applied.
- Pressing escape will pause the simulation, allowing the integration scheme to be changed, as well as the level of detail. Will also have exit to main menu and exit to desktop options.

## External Libraries
- Eigen3 will be used for linear algebra and Matrix/Vector storage of information. If something that is required is unavailble in eigen, it will be written myself.
- Boost will be used for whatever stuff it can be, partiularly unit tests and such. All code should be tested.
- Graphics will use OpenGL exclusively, using the glfw, glm, and glew packages, and any others that may be required. Graphical stuff will be done last, because it may be difficult to get my head around.

## Various components
Information on (some of) the various components that will be made.

##### Integrators
Integrators will play an important role in this system, probably the most important back end role. As such, there will be a number that will be implemented.
- Runge-Kutta type integrators. Explicit, Adaptive and Implicit methods will be implemented based on Butcher Tableaus. This will provide for a large number of different order integrators to be produced with minimal coding effort. Implicit methods will require a means of determining roots, as such root-finding algorithms will have to be implmented. Initially, this will be just Newton-Raphson and scaled Newton-Raphson, though further ethods, like BFGS may be implemented at a later date.
- Linear multistep methods https://en.wikipedia.org/wiki/Linear_multistep_method.
- Verlet integration: https://en.wikipedia.org/wiki/Verlet_integration
- Leapfrog: https://en.wikipedia.org/wiki/Leapfrog_integration

##### CelestialBody
The CelestialBody object is the object which contains all the information on the various celestial bodies. Data stored will be:
- double mass; the mass of the body. Bodies will be (initially) treated as point particles.
- double radius; the radius of the body spherical body.
- int id; a unique id associated with the body.
- int parent; the id of the parent to this body, i.e. the body which this is orbiting.
- Vector3 position; the coordinates of the body, as reference from it's parent (or maybe 0,0,0).
- Vector3 velocity; the velocity of the body
Functions:
- Vector3 force(other body); the force on this body due to the other body


## Style
A bit of a style guide that should be strictly adheared to.

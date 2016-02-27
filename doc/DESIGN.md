# Miniature Space Man - Design Documentation
The design document that will hopefully govern how this project is undertaken.

## General Design Statement
The aim of this project is to create a graphical planetarium that displays a simulation of a solar system (or even galaxies). The planetarium will be three dimensional, and allow free traversing by the 'player' through mouse/keyboard input. There will be a number of predefined setups to choose from, e.g. Earth + moon, Sun + Planets, the Jupiter System etc. The player will be able to create and save their own system using an in game editor. The player will be able to control the speed of the simulation, from real time to highly accelerated time. Various integrators will be available to be used. Simulations will have varying degrees of accuracy, from full N-body Newtonian mechanics (possibly adding in relativistic effects) to simplified 2-body mechanics (eg moon orbiting a planet). There will be varying attempts/levels of optimisation inbetween these extremes, as and when they are attempted, all of which will be selectable.

## Program Flow
From clicking on the application icon to launch the program:

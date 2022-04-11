
# CASIM

![screenshot.png](./assets/screenshot.png)

**C**ellular **A**utomata **SIM**ulator

A simulator for cellular automata using lua to define rules, available for 3D CA.

## Usage

1. Make sure that qt and opengl is well configured
2. `qmake && make`

## Dependencies

Casim depends on `xtensor` `xlt` and `lua`. The licenses of these libraries are placed under `third_party`

## RoadMap

- [x] Neighbor radius from script
- [x] Messages & information
- [ ] Performance optimization
  - [ ]  (LuaJIT maybe)
  - [ ]  (Game engine maybe)
- [ ] Auto adjusting for viewer
- [ ] Error handling for Automaton

## About

This is my project for the assignment of computer programming class this semester. Yet some implementation in this project is crappy. Maybe I will optimize/refactor them later.


English | [简体中文](README_CN.md) | [课程大作业项目报告](课程大作业项目报告.pdf)

# CASIM

![screenshot.png](./assets/screenshot.png)

**C**ellular **A**utomata **SIM**ulator

A simulator for cellular automata using lua to define rules, available for 3D CA.

## Usage

### From Release

Just download from the release page and unzip to use.

### Compile to Use

1. Clone or download this repo;
2. Make sure that qt and opengl is well configured;
3. `qmake && make` or open from Qt Creator.

## Dependencies

Casim depends on `xtensor` `xlt` `lua` and freeglut. The licenses of these libraries are placed under `third_party`

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

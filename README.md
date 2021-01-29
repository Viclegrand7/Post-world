# Post-world

This is a malfunctioning 3D FPS game written in C++, using SDL2 and OPENGL

## Repositories :

**Engines** : What contains most if not all of the code.

**Game** : What should be interesting players.

## FAQ :

*How do I compile?*
    - Make sure you have SDL2 and its libs installed
    - Make sure you have OPENGL installed
    - `cd Game`
    - `make`

*How do I start a game?*
    - `cd Game`
    - `./bin/RVZD`

*Why doesn't the game work from 'bin' directory?*
    The 'Game/res/main' and the relative paths it contains are badly made. Code use for loading files too. No real reason. 

*Why can't I hit ennemies?*
    They are not where they are drawn. A misunderstanding between the two authors regarding the making of 3D zombies led to this. 

*My camera keeps on moving*
    The game was only tested on one computer. It should work in fullscreen. To enable fullscreen, go in 'Engines/GraphicEngines/src/GrE_Board.cc', 

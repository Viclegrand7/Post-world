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

*How to play?*

    Move using `Z`, `Q`, `S`, `D`, shoot using `Left Mouse Button`, aim using `Right Mouse Button`, leave using `ESCAPE`, reload by pressing `R`

*Why doesn't the game work from 'bin' directory?*

    The 'Game/res/main' and the relative paths it contains are badly made. Code used for loading files too. No real reason. 

*Why can't I hit ennemies?*

    They are not where they are drawn. A misunderstanding between the two authors regarding the making of 3D zombies led to this. 

*My camera keeps on moving, and my mouse is not*

    The game was only tested on one computer. It should work in fullscreen. To enable fullscreen, go in 'Engines/GraphicEngines/src/GrE_Board.cc', line 21, and add ` | SDL_WINDOW_FULLSCREEN_DESKTOP` to the flags. 
    
     I am honeslty not sure it will help, but it should.


*Is this game ever going to be fixed?*

    YES. Without a doubt.

*When I close the game I get a Segfault*

    Yes, me too. I know how to fix it, need a few more hours to do so.

*Why don't I die?*

    I am honestly not sure, player's health should drop. It doesn't.

*What's going on with ennemies's skins?*

    Wish I knew, I made the gun, had my colleague do the ennemies...

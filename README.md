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
    
    Try to hit somewhere near they pixels though.

*Is this game ever going to be fixed?*

    YES. Without a doubt. Most of it comes down to having bad 3D objects

*What's going on with ennemies's skins?*

    Wish I knew, I made the gun, had my colleague do the ennemies...
    
*Is it playable?*

    Well, you don't know where ennemies are exactly, though you see them.
    
    You seem to bounce off of a non existing ennemy in the middle of the map.
    
    Textures certainly didn't load right (except for gun, only thing I personally drew).
    
    Other than that, yeah.
    
    Oh, and there's no gravity so by pressing Space you end up flying. But it works :)

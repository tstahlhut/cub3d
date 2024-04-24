# cub3d

A graphical group project of 42 in which you learn to use raycasting to develop a 3D-game in the fashion of Wolfenstein.

## Usage

The graphical window is created with the help of the mlx library. A basic graphic library created by 42. It is not included in this repository and has to be downloaded first:

	https://github.com/42Paris/minilibx-linux

Follow the guidelines on the github repository.

Then git clone this repo and cd into the folder:

	git clone git@github.com:tstahlhut/cub3d.git
	cd cub3d

Run make to build the executable:

	make

If you get the following error, you have to change the path to the minilibx you downloaded at the beginnning. You can do so in the file ./inc/cub.h in line 16.

	In file included from src/main.c:13:
	src/../inc/cub.h:16:11: fatal error: '../../../minilibx-linux/mlx.h' file not found
	# include "../../../minilibx-linux/mlx.h"
          ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	1 error generated.
	make: *** [<builtin>: src/main.o] Error 1


## Background Knowledge

Although, cub3D looks like a 3D game, just as Wolfenstein does, it is not 3D. The map on which you can move is 2D but with the help of the raycasting technique it appears as 3D. Therefore, raycasting is quite fast. 

### Raycasting

Raycasting is a rendering technique which let’s 2D appear as 3D, more precisely: it gives you a 3D perspective on a 2D map. Therefore, it is impossible to move in the third dimension (moving up or down) or to display different heights.

In order to give this 3D illusion, rays are casted from the point of the spectator. Depending on the length of the rays, the objects that are hit by the rays are displayed as greater or smaller. Moreover, objects, like walls, can be coloured differently depending on which direction they are facing. This increases the 3D illusion effect. 

A very good guide is: https://lodev.org/cgtutor/raycasting.html

Following Lodev's guide, this cub3D program uses vectors in the raycasting part. Thus, no fisheye correction is needed. 

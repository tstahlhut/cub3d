# cub3d

A graphical group project of 42 in which you learn to use raycasting to develop a 3D-game in the fashion of Wolfenstein.

## Background Knowledge

### Raycasting

Raycasting is a rendering technique which let’s 2D appear as 3D, more precisely: it gives you a 3D perspective on a 2D map. Therefore, it is impossible to move in the third dimension (moving up or down) or to display different heights.

In order to give this 3D illusion, rays are casted from the point of the spectator. Depending on the length of the rays, the objects that are hit by the rays are displayed as greater or smaller. Moreover, objects, like walls, can be coloured differently depending on which direction they are facing. This increases the 3D illusion effect. 

A very good guide is: https://lodev.org/cgtutor/raycasting.html

#### DDA Algorithm

DDA is the abbreviation for *Digital Differential Analyzer*. It is one of the simplest and fastest line generation algorithm. By incrementing from one point to the next point, it calculates a line.

Steps:
	1. You have two points, with each two coordinates:
		int x1, y1, x2, y2
	2. You calculate the difference between the two points:
		float dx = x2 - x1;
		float dy = y2 - y1;
	3. Calculate the slope:
		float m = dy / dx;
	4. If m > 1 -> you calculate the next point by:
		float xn = x1 + 1/m
		float yn = y1 + 1
		if m < 1 -> you calculate the next point by:
		float xn = x1 + 1
		float yn = y1 + m
	5. If m = 1 -> you found your point
		x1 = xn
		y1 = yn

This algorithm will be used to find the point where we hit a wall or another object (we can see until there is a object in our way).

#### 

1. Position of player: pos (x, y)
2. Direction they are looking: dir (x, y)
3. "Camera plane": the line on the map that the player sees and that will be displayed on the screen

So, we have 
			pos (x, y)
			dir (x, y)
			central focus point: pos + dir
			leftest point of vision: pos + dir - plane
			rightest point of vision: pos + dir + plane

The Field of Vision (FOV) is calculated through the lenght of dir and of the camera plane. For a first person game, an FOV of 66 degrees is good. This means that the direction vector is slightly longer than the camera plane. 


## TO DO

## Directions

Something seems to be wrong with the directions, either keys or initial values

### Valgrind

1. If texture image too big or small: conditional jump

	c1b3c1% valgrind --track-origins=yes ./cub3d maps/map.cub
	==36495== Memcheck, a memory error detector
	==36495== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
	==36495== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
	==36495== Command: ./cub3d maps/map.cub
	==36495== 
	MAP VALIDDDD
	tex: 0 tex_path: textures/Solid_white.xpmError: at least 1 texture image is too big or small
	==36495== Conditional jump or move depends on uninitialised value(s)
	==36495==    at 0x402DB3: free_textures (exit.c:22)
	==36495==    by 0x402DFF: free_map (exit.c:31)
	==36495==    by 0x402E80: error_exit (exit.c:45)
	==36495==    by 0x402CD1: init_img_xpm (init.c:132)
	==36495==    by 0x405188: read_in_textures (textures.c:38)
	==36495==    by 0x402EEF: open_window (window.c:20)
	==36495==    by 0x40283C: main (main.c:62)
	==36495==  Uninitialised value was created by a heap allocation
	==36495==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
	==36495==    by 0x403915: allocate_map_data (init_map.c:117)
	==36495==    by 0x403A06: initmap (init_map.c:140)
	==36495==    by 0x40280F: main (main.c:57)
	==36495== 
	==36495== 
	==36495== HEAP SUMMARY:
	==36495==     in use at exit: 631 bytes in 18 blocks
	==36495==   total heap usage: 379 allocs, 361 frees, 114,276 bytes allocated
	==36495== 
	==36495== LEAK SUMMARY:
	==36495==    definitely lost: 144 bytes in 4 blocks
	==36495==    indirectly lost: 210 bytes in 10 blocks
	==36495==      possibly lost: 0 bytes in 0 blocks
	==36495==    still reachable: 277 bytes in 4 blocks
	==36495==         suppressed: 0 bytes in 0 blocks
	==36495== Rerun with --leak-check=full to see details of leaked memory
	==36495== 
	==36495== For lists of detected and suppressed errors, rerun with: -s
	==36495== ERROR SUMMARY: 4 errors from 1 contexts (suppressed: 0 from 0)



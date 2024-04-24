/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:04:52 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/24 17:03:23 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../../../minilibx-linux/mlx.h"
# include "../libs/libft/libft.h"
# include "key_codes.h"
# include "color_codes.h"
# include <stdio.h>
# include <fcntl.h>      // for open
# include <unistd.h>     // for close, read, write
# include <stdlib.h>     // for malloc, free, exit
# include <string.h>     // for strerror
# include <errno.h>      // for perror
# include <math.h>       // for math library functions
# include <sys/time.h>	// for calculating frames (get_time)
# include <time.h>

/* ************************************************************************** */
/*							DEFINITIONS										  */
/* ************************************************************************** */

# define SCREEN_WIDTH	1500 //1024 
# define SCREEN_HEIGHT	1000	//dimension taken from Video by 3D Sage
# define MAP_WIDTH 10 // should later be deleted and ...
# define MAP_HEIGHT 10 // ... calculated from given map
# define SQUARE_SIZE 25 //side length of 1 square in the map in pixel
# define NAME	"cub3d"
# define MAP_CHARS "012NSEW"
# define MAP_INSIDE "02NSEW"
# define PLAYER "NSEW"
# define TEX_NUM 5 // number of textures
# define TEX_N 0	//texture for NO side
# define TEX_S 1	//texture for SO side
# define TEX_W 2	//texture for WE side
# define TEX_E 3	//texture for EA side
# define TEX_EXIT 4 //texture for exit
# define TEX_EXIT_PATH "./textures/exit_blue.xpm"
# define EXIT_IMAGE "./textures/win.xpm"

/* ************************************************************************** */
/*								STRUCTURES									  */
/* ************************************************************************** */

/* ************************************************************************ */
/*							IMGAGE STRUCT: img & img_tex			   		*/
/*						EXPLANATION OF VARIABLES							*/
/* 		 all these variables are needed by mlx to create an image          	*/
/*             																*/
/*	void	*img;			-> image pointer								*/
/*	char	*addr;			-> pixel can be accessed: addr[width * y + x] 	*/
/*								for img_tex it has to be int* 				*/
/*	int		bpp;			->	bits_per_pixel								*/
/*	int		line_length;	-> amount of bytes taken by one row of image	*/
/*	int		endian;			-> needed by mlx to create image				*/
/*                                                                          */
/* ************************************************************************ */
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}		t_img;

typedef struct s_img_tex
{
	void	*img;
	int		*addr;
	int		bpp;
	int		line_length;
	int		endian;
}		t_img_tex;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct m_flag
{
	int	move_up;
	int	move_down;
	int	move_left;
	int	move_right;
	int	look_right;
	int	look_left;
	int	map_flag;
}	t_flag;

/* ************************************************************************** */
/*							MAP STRUCT: map			   						  */
/*						EXPLANATION OF VARIABLES							  */
/*                                                                            */
/*	char 	**layout; 		-> whole map: l[0] = y,  l[1] = x	 		      */
/*	int		nlines;			-> y					 						  */
/*	int		max_line_len;	-> x (max x)									  */
/*	int		map_valid_flag;	-> 0 = valid; -1 = not valid		   			  */
/*	t_rgb	*f_color;		-> floor color in rgb							  */
/*	t_rgb	*c_color;		-> ceiling color in rgb							  */
/*	char	*no; 			-> path to north texture; dir = -1, 0			  */
/*	char	*so; 			-> path to south texture; dir = 1, 0			  */
/*	char	*we; 			-> path to west texture; dir = 0, -1			  */
/*	char	*ea; 			-> path to east texture; dir = 0, 1				  */
/*	char 	initial_dir;	-> direction player is facing in beginning (NSEW) */
/*	int		*texture[TEX_NUM]; -> stores color of each pixel of the textures  */
/*	int		tex_width[TEX_NUM]; -> width of all loaded textures				  */
/*	int		tex_height[TEX_NUM]; -> height of all loaded textures			  */
/*																			  */
/* ************************************************************************** */
typedef struct s_map
{
	char	**layout;
	int		nlines;
	int		max_line_len;
	int		map_valid_flag;
	t_rgb	*f_color;
	t_rgb	*c_color;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	initial_dir;
	int		*texture[TEX_NUM];
	int		tex_width[TEX_NUM];
	int		tex_height[TEX_NUM];
}t_map;

/* ************************************************************************** */
/*							MAIN STRUCT: cub		   						  */
/*						EXPLANATION OF VARIABLES							  */
/*                                                                            */
/*	t_map		*map;		-> pointer to map struct (holds all map data)	  */
/*	void		*mlx;		-> mlx pointer									  */
/*	void		*win;		-> mlx window pointer							  */
/*	t_img		*img;		-> pointer to image struct,can hold several images*/
/*	t_img_tex	img_tex; 	-> image textures struct						  */
/*	t_img		img_exit; 	-> image exit struct							  */
/*	double		pos[2];		-> position vector of player: pos[0] = x, [1] = y */
/*	int			exit_pos[2]; -> position of exit door: [0] = x, [1] = y  	  */
/*	int			exit_found; -> 1 if player touched exit, otherwise 0		  */
/*	int			exit_flag;	-> 1 if map has an exit door (a "2" on the map);  */
/*								0 if it doesn't 							  */
/*                                                                            */
/*  VARIABLES for RAYCASTING	([0] = x, [1] = y)							  */
/*	double		dir[2]; 		-> direction player faces					  */
/*	double		camplane[2];	-> camera plane (part you see on screen)	  */
/*	double		raydir[2]; 		-> ray direction							  */
/*	double		deltadist[2]; 	-> length of ray from one x- or y-side 		  */
/*									to next x- or y-side					  */
/*	double		sidedist[2]; 	-> length of ray from current position		  */
/*									to next x- or y-side					  */
/*	int			side;			-> which wall was hit? x (NS) or y (EW)		  */
/*	int			step[2]; 		-> into what direction to step: either -1 or 1*/
/*	double		walldist;		-> wall distance							  */
/*	int			wallheight;		-> how high should wall be drawn on screen	  */
/*	int			startwall; 		-> at which pixel on screen wall starts		  */
/*	int			endwall;		-> at which pixel on screen wall ends		  */
/*                                                                            */
/*	double		speedmove;	-> speed of movement 							  */
/*	double		speedrot;	-> speed of rotation 							  */
/*	t_flag		m_flag;		->												  */
/*	time_t		timer;		-> struct for timer								  */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_cub
{
	t_map		*map;
	void		*mlx;
	void		*win;
	t_img		*img;	
	t_img_tex	img_tex;
	t_img		img_exit;
	double		pos[2];
	int			exit_pos[2];
	int			exit_found; 
	int			exit_flag;	
	double		dir[2];
	double		camplane[2]; 
	double		raydir[2];
	double		deltadist[2];
	double		sidedist[2];
	int			side;
	int			step[2];
	double		walldist;
	int			wallheight;
	int			startwall;
	int			endwall;
	double		speedmove;
	double		speedrot;
	t_flag		m_flag;
	time_t		timer;
}			t_cub;

/* ************************************************************************** */
/*					FUNCTION DECLARATIONS									  */
/* ************************************************************************** */

/* init.c: variables are initialized*/
void			init_cub(t_cub *cub);
void			init_img(t_cub *cub, int width, int height);
void			init_img_xpm(t_cub *cub, t_map *map, int tex);
void			init_movement(t_cub *cub);
void			init_dir(t_cub *cub, char c);
void			init_map(t_map *map);

/* textures.c: init textures (save them so that they are usable)*/
void			malloc_textures(t_cub *cub, t_map *map, int tex);
void			read_in_textures(t_cub *cub, t_map *map);
int				choose_texture(t_cub *cub, int wall_type);

/*	window.c: window management */
void			open_window(t_cub *cub);
void			close_window(t_cub *cub);

/* render_map.c: rendering of 2D map*/

void			render_square(t_cub *cub, int x, int y, unsigned int color);
void			render_minimap(t_cub *cub, int start_x, int start_y);
int				set_right(t_cub *cub);
int				set_down(t_cub *cub);

/* event_handlings.c: management of key and mouse events */
int				deal_key(int key, t_cub *cub);
int				x_close(t_cub *cub);

/* raycasting_calc.c */
void			calculate_ray(t_cub *cub, int x);
void			calculate_step_sidedist(t_cub *cub, int map[2]);
int				calculate_wall_hit(t_cub *cub);
void			calculate_wall_dimensions(t_cub *cub);
int				calculate_tex_x(t_cub *cub, double walldist, int tex);

/* raycasting.c */
void			render_wall_texture(t_cub *cub, int x, int tex);
int				render_3d_view(t_cub *cub);

/*timer.c: timer counts time until exit is found */
void			start_timer(t_cub *cube);
long			ft_get_time(t_cub *cube);
void			print_timer(t_cub *cub);

/* move_player.c: calculates and renders movements of player on 2D map*/
void			look_left(t_cub *cub);
void			look_right(t_cub *cub);
void			move_up(t_cub *cub);
void			move_down(t_cub *cub);
void			move_left(t_cub *cub);
void			move_right(t_cub *cub);
void			check_next_pos(t_cub *cub, int new_x, int new_y);
int				key_press(int key, t_cub *cub);
int				key_release(int key, t_cub *cub);

/* exit.c: handles clean exit */
void			free_map_data(t_map *map);
void			error_exit(t_cub *cub, char *message, char *file);
void			exit_screen(t_cub *cub);

/*map parsing*/
int				initmap(char *path_to_map, t_cub *cube);
int				map_check(t_cub *cube);

/* init_map.c */
void			allocate_map_data(t_cub *cub);
void			save_texture(t_cub *cube, char *line, int i);
void			ft_fill_layout(t_cub *cube, char *line, int current_line);
int				check_valid_file(t_cub *cube, char *pf);
void			set_map_data_to_null(t_map *map);
void			ft_setcolor_f(t_cub *cube, char *line, int i);
void			ft_setcolor_c(t_cub *cube, char *line, int i);
void			allocate_layout(t_cub *cube);
void			save_texture(t_cub *cube, char *line, int i);
void			ft_fill_layout(t_cub *cube, char *line, int current_line);
int				check_valid_file(t_cub *cube, char *pf);
void			set_map_data_to_null(t_map *map);

/* mapchecks utils.c*/
int				checkcolor(t_cub *cube);
int				ft_isspace(char c);
int				check_textures(char *str);
void			set_angle(t_cub *cube, char c);
int				check_all_rows(t_cub *cube);
int				check_only_valid_token(char *line);

/*initmap utils*/
char			*moded_strdup(const char *s);
int				ft_empty(char *line);
void			ft_setcolors(t_cub *cube, char *line, int i);

/* utils.c*/
unsigned int	conv_rgb_hex(t_rgb *rgb);
void			my_pixel_put(t_img *img, int x, int y, unsigned int color);
int				ft_empty(char *line);

#endif

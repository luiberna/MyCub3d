/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:44:49 by luiberna          #+#    #+#             */
/*   Updated: 2025/01/29 00:08:10 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <stdbool.h>
# include <math.h>
# include <GL/gl.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <errno.h>
# include "libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

//Angles and movment
# define SPEED 0.03
# define RSPEED 0.03
# define PI 3.14159265
# define CUBE 64

//Texture arrays
# define N 0
# define E 1
# define S 2
# define W 3

//Keys
#define KW 119  // 'W'
#define KS 115  // 'S'
#define A 97    // 'A'
#define D 100   // 'D'
#define LEFT 65361
#define RIGHT 65363

//Screen sizes
# define SCREEN_W 1080
# define SCREEN_H 600

typedef struct s_image
{
    void        *img;
    char        *addr;
    int         bpp;
    int         size_line;
    int         endian;
    int         width;
    int         height;
    
}               t_image;

typedef struct s_data
{
    char        **map;
    char        **rff_map;
    int         player_pos_x;
    int         player_pos_y;
    int         map_width;
    int         map_height;
    char        **textures;
    int         **texture_buffer;
    int         **pixel_map;
}               t_data;

typedef struct s_player
{
    double      dir_x;
    double      dir_y;
    double      pix_pos_x;
    double      pix_pos_y;
    double      plane_x;
    double      plane_y;
    double      pos_x;
    double      pos_y;
    
    bool        key_up;
    bool        key_down;
    bool        key_left;
    bool        key_right;

    bool        left_rotate;
    bool        right_rotate;

    double      angle;
    
}               t_player;

typedef struct s_cube
{
    void        *mlx;
    void        *win;
    t_image     *img;
    t_player    *player;
    t_data      *data;
}               t_cube;

//Functions:

//Utils
bool check_file(char *str);
void print_error(char *str);
void check_errors(int argc, char **argv);
void print_map(char **map);

//Map
int get_map_height(char *file);
char **get_map(char *file);
int get_map_width(t_data *data);
int **get_pixel_map(t_data *data);

//Textures
char **get_textures(char *file);

//Free
void free_cube(t_cube *cube);

//Minimap
int  draw_minimap(t_cube *cube);
void draw_square(int x, int y, int size, int color, t_cube *cube);
void put_pixel(int x, int y, int color, t_cube *cube);

//Keys & Movement
int key_press(int keycode, t_cube *cube);
int key_release(int keycode, t_cube *cube);
void move_player(t_player *player, char **map);
void move_player2(t_player *player, double sin_angle, double cos_angle);

# endif
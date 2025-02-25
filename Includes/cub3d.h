/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:44:49 by luiberna          #+#    #+#             */
/*   Updated: 2025/02/07 17:32:40 by luiberna         ###   ########.fr       */
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
# define SPEED 0.02
# define RSPEED 0.01
# define PI 3.14159265
# define CUBE 64
#define EPSILON 1e-30

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
# define SCREEN_W 1400
# define SCREEN_H 720

typedef struct s_color
{
	int red;
	int green;
	int blue;
	int	hex_color;
}              t_color;

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
    int         ceiling_color[3];
    int         floor_color[3];
    int         map_position;
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
    char        looking;
    bool        key_up;
    bool        key_down;
    bool        key_left;
    bool        key_right;
    bool        left_rotate;
    bool        right_rotate;
    bool        minimap;
    double      angle;
    
}               t_player;

typedef struct s_ray
{
    double      camera_x;
    double      ray_dir_x;
    double      ray_dir_y;
    double      delta_dist_x;
    double      delta_dist_y;
    int         step_x;
    int         step_y;
    int         map_x;
    int         map_y;
    double      side_dist_x;
    double      side_dist_y;
    int         side;
    double      wall_dist;
    double      wall_height;
    double      wall_x;
    int         text_x;
    int         start_pos_draw;
    int         end_pos_draw;
    int         hit;
}           t_ray;

typedef struct s_cube
{
    void        *mlx;
    void        *win;
    t_image     *img;
    t_player    *player;
    t_data      *data;
    t_ray       *ray;
}           t_cube;

//Functions:

//Utils
bool    check_file(char *str);
void    print_error(t_cube *cube, char *str);
void    check_errors(int argc, char **argv);
void    print_map(char **map);

//Map
char    **get_map(t_data *data, char *file);
void    map_position(t_data *data, char *file);
void    count_config_lines(t_data *data, int fd, int *count, int *flag);
void    count_empty_lines(int fd, int *count);

//Map_Utils
int     get_map_height(t_data *data, char *file);
int     get_map_width(t_data *data);

//Textures
char    **get_textures(char *file);
void	load_textures(t_cube *cube, t_data *data);
void    img_to_texture_buff(t_cube *cube, t_data *data, t_image *img, int dir);

//Clear
void    clear_image(t_cube *cube);
void    clear_pixel_map(t_data *data);
int     close_window(t_cube *cube);

//Free
void    free_cube(t_cube *cube);
void free_pixel_map(t_data *data);
void free_map(t_data *data);
void free_textures(t_data *data);
void free_texture_buffer(t_data *data);

//Minimap
int     draw_minimap(t_cube *cube);
void    draw_square(int x, int y, int size, int color, t_cube *cube);
void    put_pixel(int x, int y, int color, t_cube *cube);

//Keys
int     key_press(int keycode, t_cube *cube);
int     key_release(int keycode, t_cube *cube);

//Movement
void    move_player(t_player *player, char **map);
void    move_player2(t_player *player, char **map);
void    move_player3(t_player *player, char **map, double sin_angle, double cos_angle);
void    check_movement(t_player *player, char **map, double new_x, double new_y);

//Init
void    init_cube(t_cube *cube, char *file);
void    init_data(t_cube *cube, t_data *data, char *file);
void    init_player(t_data *data, t_player *player);
void    init_player2(t_player *player);
void    get_player_position(t_data *data, t_player *player);

//Init_Aux
void    init_texture_buffer(t_cube *cube, t_data *data);
void    init_pixel_map(t_cube *cube,t_data *data);
void    init_color(t_cube * cube, t_data *data, char *file);
void    init_ray(t_data *data, t_player *player, t_ray *ray, int x);

//Color
int     *get_color(t_cube *cube, char *file, char *type);
void    get_rgb(t_cube *cube, char *line, int *color);
int     get_hex_color(int r, int g, int b);
void    free_color(char **color_parts);


//Check_Color
void    check_color5(t_cube *cube, char **color_numbers, char *line, int fd);
void    check_color4(t_cube *cube, char **color_numbers, char *line, int fd);
void    check_color3(t_cube *cube, char *line, int fd);
void    check_color2(t_cube *cube, char *line, int fd);
void    check_color(t_cube *cube, char *file);

//Check
void    verify_player(t_cube *cube, t_data *data);
void    verify_closed_map(t_cube *cube, t_data *data);
void    verify_map(t_cube *cube, t_data *data);

//Draw
void    draw_pixel_map(t_cube *cube, t_data *data);
void    draw_pixel_map_content(t_cube *cube, t_data *data);
void    draw_floor(t_cube *cube, t_data *data, int floor_color);
void    draw_ceiling(t_cube *cube, t_data *data, int ceiling_color);

//Raycasting
void    calculate_dist(t_player *player, t_ray *ray);
void    DDA(t_data *data, t_player *player, t_ray *ray);
void    wall_render(t_player *player, t_ray *ray);
int     get_direction(t_ray *ray);
void    get_pixel_map(t_data *data, t_ray *ray, int x);

# endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:25:47 by luiberna          #+#    #+#             */
/*   Updated: 2025/01/29 02:08:44 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void get_player_position(t_data *data, t_player *player)
{
    int x;
    int y;
    
    y = 0;
    while (data->map[y]) {
        x = 0;
        while (data->map[y][x]) {
            if (data->map[y][x] == 'N' || data->map[y][x] == 'E' || data->map[y][x] == 'S' || data->map[y][x] == 'W') {
                player->pos_x = x;
                player->pos_y = y;
                return ;
            }
            x++;
        }
        y++;
    }
}

void init_player(t_data *data, t_player *player)
{
    get_player_position(data, player);
    player->angle = PI / 2;

    player->key_up = false;
    player->key_down = false;
    player->key_right = false;
    player->key_left = false;

    player->left_rotate = false;
    player->right_rotate = false;
}

void init_data(t_data *data, char *file)
{
    data->map = get_map(file);
    //print_map(data->map);
    data->map_height = get_map_height(file);
    data->map_width = get_map_width(data);
    data->pixel_map = get_pixel_map(data);
    //data->rff_map = 
    data->textures = get_textures(file);
}

void init_cube(t_cube *cube, char *file)
{
    cube->data = ft_calloc(1, sizeof(t_data));
    init_data(cube->data, file);
    cube->player = ft_calloc(1, sizeof(t_player));
    init_player(cube->data ,cube->player);
    cube->mlx = mlx_init();
    if (!cube->mlx)
        print_error("ERROR: Failed to initialize MLX\n");
    cube->win = mlx_new_window(cube->mlx, SCREEN_W, SCREEN_H, "Cube3D");
    if (!cube->win)
        print_error("ERROR: Failed to create MLX window\n");
    cube->img = ft_calloc(1, sizeof(t_image));
    cube->img->img = mlx_new_image(cube->mlx, SCREEN_W, SCREEN_H);
    if (!cube->img->img)
        print_error("ERROR: Failed to create image\n");
    cube->img->addr = mlx_get_data_addr(cube->img->img, &cube->img->bpp, &cube->img->size_line, &cube->img->endian);
}

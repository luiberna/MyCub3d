/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:25:47 by luiberna          #+#    #+#             */
/*   Updated: 2025/02/07 16:42:43 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void get_player_position(t_data *data, t_player *player)
{
    int x;
    int y;
    
    y = 0;
    while (data->map[y])
    {
        x = 0;
        while (data->map[y][x])
        {
            if (data->map[y][x] == 'N' || data->map[y][x] == 'E' || data->map[y][x] == 'S' || data->map[y][x] == 'W')
            {
                player->looking = data->map[y][x];
                player->pos_x = x + 0.2;
                player->pos_y = y + 0.2;
                return ;
            }
            x++;
        }
        y++;
    }
}

void init_player2(t_player *player)
{
    if (player->looking == 'E')
    {
        player->dir_x = 1.0;
        player->dir_y = 0.0;
        player->plane_x = 0.0;
        player->plane_y = 0.66;
    }
    else if (player->looking == 'W')
    {
        player->dir_x = -1.0;
        player->dir_y = 0.0;
        player->plane_x = 0.0;
        player->plane_y = -0.66;
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
    if (player->looking == 'N')
    {
        player->dir_x = 0.0;
        player->dir_y = -1.0;
        player->plane_x = 0.66;
        player->plane_y = 0.0;
    }
    else if (player->looking == 'S')
    {
        player->dir_x = 0.0;
        player->dir_y = 1.0;
        player->plane_x = -0.66;
        player->plane_y = 0.0;
    }
    init_player2(player);
}

//print_map(data->map);
void init_data(t_cube *cube, t_data *data, char *file)
{
    map_position(data, file);
    data->map = get_map(data, file);
    init_pixel_map(cube, data);
    data->map_height = get_map_height(data, file);
    data->map_width = get_map_width(data);
    data->textures = get_textures(file);
    init_texture_buffer(cube, data);
}

void init_cube(t_cube *cube, char *file)
{
    cube->data = ft_calloc(1, sizeof(t_data));
    init_data(cube, cube->data, file);
    cube->player = ft_calloc(1, sizeof(t_player));
    init_player(cube->data ,cube->player);
    cube->mlx = mlx_init();
    if (!cube->mlx)
        print_error(cube, "ERROR: Failed to initialize MLX\n");
    cube->win = mlx_new_window(cube->mlx, SCREEN_W, SCREEN_H, "Cube3D");
    if (!cube->win)
        print_error(cube, "ERROR: Failed to create MLX window\n");
    cube->img = ft_calloc(1, sizeof(t_image));
    cube->img->img = mlx_new_image(cube->mlx, SCREEN_W, SCREEN_H);
    if (!cube->img->img)
        print_error(cube, "ERROR: Failed to create image\n");
    cube->img->addr = mlx_get_data_addr(cube->img->img, &cube->img->bpp, &cube->img->size_line, &cube->img->endian);
    verify_map(cube, cube->data);
    check_color(cube, file);
    init_color(cube, cube->data, file);
}

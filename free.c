/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:08:27 by luiberna          #+#    #+#             */
/*   Updated: 2025/02/03 23:30:10 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void clear_pixel_map(t_data *data)
{
    int x;
    int y;

    y = 0;
    while(y < SCREEN_H)
    {
        x = 0;
        while (x < SCREEN_W)
        {
            data->pixel_map[y][x] = 0;
            x++;
        }
        y++;
    }
}

void clear_image(t_cube *cube)
{
    int x;
    int y;

    y = 0;
    while (y < SCREEN_H)
    {
        x = 0;
        while (x < SCREEN_W) 
        {
            put_pixel(x, y, 0x000000, cube);
            x++;
        }
        y++;
    }
}

int close_window(t_cube *cube)
{
    free_cube(cube);
    exit(0);
    return 0;
}

void free_cube(t_cube *cube)
{
    int i;

    if (cube->data) {
        if (cube->data->texture_buffer) {
            for (i = 0; i < 4; i++) {
                if (cube->data->texture_buffer[i]) {
                    free(cube->data->texture_buffer[i]);
                }
                cube->data->texture_buffer[i] = NULL;
            }
            free(cube->data->texture_buffer);
            cube->data->texture_buffer = NULL;
        }
        if (cube->data->textures) {
            for (i = 0; i < 4; i++)
                free(cube->data->textures[i]);
            free(cube->data->textures);
        }
        if (cube->data->map) {
            for (i = 0; cube->data->map[i]; i++)
                free(cube->data->map[i]);
            free(cube->data->map);
        }
        if (cube->data->pixel_map) {
            for (i = 0; i < SCREEN_H; i++) {
                if (cube->data->pixel_map[i])
                    free(cube->data->pixel_map[i]);
            }
            free(cube->data->pixel_map);
        }
        free(cube->data);
    }
    if (cube->player)
        free(cube->player);
    if (cube->img) {
        if (cube->img->img)
            mlx_destroy_image(cube->mlx, cube->img->img);
        free(cube->img);
    }
    if (cube->win)
        mlx_destroy_window(cube->mlx, cube->win);
    if (cube->mlx) {
        mlx_destroy_display(cube->mlx);
        free(cube->mlx);
    }
}

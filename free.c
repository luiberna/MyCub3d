/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:08:27 by luiberna          #+#    #+#             */
/*   Updated: 2025/02/05 19:12:28 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void free_texture_buffer(t_data *data)
{
    int i;

    if (data->texture_buffer)
    {
        i = 0;
        while (i < 4)
        {
            if (data->texture_buffer[i])
                free(data->texture_buffer[i]);
            data->texture_buffer[i] = NULL;
            i++;
        }
        free(data->texture_buffer);
        data->texture_buffer = NULL;
    }
}

void free_textures(t_data *data)
{
    int i;

    if (data->textures)
    {
        i = 0;
        while (i < 4)
        {
            free(data->textures[i]);
            i++;
        }
        free(data->textures);
    }
}

void free_map(t_data *data)
{
    int i;

    if (data->map)
    {
        i = 0;
        while (data->map[i])
        {
            free(data->map[i]);
            i++;
        }
        free(data->map);
    }
}

void free_pixel_map(t_data *data)
{
    int i;

    if (data->pixel_map)
    {
        i = 0;
        while (i < SCREEN_H)
        {
            if (data->pixel_map[i])
                free(data->pixel_map[i]);
            i++;
        }
        free(data->pixel_map);
    }
}

void free_cube(t_cube *cube)
{
    if (cube->data)
    {
        free_texture_buffer(cube->data);
        free_textures(cube->data);
        free_map(cube->data);
        free_pixel_map(cube->data);
        free(cube->data);
    }
    if (cube->player)
        free(cube->player);
    if (cube->img)
    {
        if (cube->img->img)
            mlx_destroy_image(cube->mlx, cube->img->img);
        free(cube->img);
    }
    if (cube->win)
        mlx_destroy_window(cube->mlx, cube->win);
    if (cube->mlx)
    {
        mlx_destroy_display(cube->mlx);
        free(cube->mlx);
    }
}

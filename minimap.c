/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:12:53 by luiberna          #+#    #+#             */
/*   Updated: 2025/01/29 02:11:39 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void put_pixel(int x, int y, int color, t_cube *cube) 
{
    if (x >= SCREEN_W || y >= SCREEN_H || x < 0 || y < 0)
        return;
    char *dst = cube->img->addr + (y * cube->img->size_line + x * (cube->img->bpp / 8));
    *(unsigned int *)dst = color;
}

void draw_square(int x, int y, int size, int color, t_cube *cube)
{
    int i;
    int j;

    i = 0;
    while (i < size) 
    {
        j = 0;
        while(j < size)
        {
            put_pixel(x + i, y + j, color, cube);
            j++;
        }
        i++;
    }
}

int draw_minimap(t_cube *cube)
{
    int i;
    int j;
    int tile_size; // Adjust this if needed

    tile_size = 16;
    j = 0;
    mlx_clear_window(cube->mlx, cube->win);
    while (cube->data->map[j])
    {
        i = 0;
        while (cube->data->map[j][i])
        {
            if (cube->data->map[j][i] == '1')
                draw_square(i * tile_size, j * tile_size, tile_size, 0xFFFFFF, cube);
            else if (cube->data->map[j][i] == '0')
                draw_square(i * tile_size, j * tile_size, tile_size, 0x000000, cube);
            i++;
        }
        j++;
    }
    draw_square(cube->player->pos_x * tile_size, cube->player->pos_y * tile_size, tile_size / 2, 0x00FF00, cube);
    mlx_put_image_to_window(cube->mlx, cube->win, cube->img->img, 0, 0);
    return 0;
}



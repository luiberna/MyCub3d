/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:12:53 by luiberna          #+#    #+#             */
/*   Updated: 2025/01/28 21:02:59 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void put_pixel(int x, int y, int color, t_cube *cube) {
    if (x >= SCREEN_W || y >= SCREEN_H || x < 0 || y < 0)
        return;
    int index = y * cube->img->size_line + x * cube->img->bpp / 8;
    cube->img->addr[index] = color & 0xFF;
    cube->img->addr[index + 1] = (color >> 8) & 0xFF;
    cube->img->addr[index + 2] = (color >> 16) & 0xFF;
}

void draw_square(int x, int y, int size, int color, t_cube *cube)
{
    for(int i = 0; i < size; i++)
        put_pixel(x + i, y, color, cube);
    for(int i = 0; i < size; i++)
        put_pixel(x, y + i, color, cube);
    for(int i = 0; i < size; i++)
        put_pixel(x + size, y + i, color, cube);
    for(int i = 0; i < size; i++)
        put_pixel(x + i, y + size, color, cube);
}

int draw_minimap(t_cube *cube) {
    draw_square(cube->player->pos_x, cube->player->pos_y, 10 , 0x00FF00 , cube);
    mlx_put_image_to_window(cube->mlx, cube->win, cube->img, 0, 0);
    return 0;
}
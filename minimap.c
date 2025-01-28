/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:12:53 by luiberna          #+#    #+#             */
/*   Updated: 2025/01/28 15:32:35 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void draw_cube(t_cube *cube, char c, int i, int j) {
    if (c == '1')
        mlx_put_image_to_window(cube->mlx, cube->win, cube->img->img, i * 64, j * 64);
    else
        mlx_put_image_to_window(cube->mlx, cube->win, cube->img->img, i * 64, j * 64);
}

void draw_minimap(t_cube *cube) {
    int i;
    int j;
    j = 0;
    while (cube->data->map[j]) {
        i = 0;
        while (cube->data->map[j][i]) {
            if (cube->data->map[j][i]) {
                draw_cube(cube, cube->data->map[j][i], i, j);
                mlx_put_image_to_window(cube->mlx, cube->win, cube->img->img, cube->player->pos_x, cube->player->pos_y);
            }
            i++;
        }
        j++;
    }
}
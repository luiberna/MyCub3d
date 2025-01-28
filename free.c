/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:08:27 by luiberna          #+#    #+#             */
/*   Updated: 2025/01/28 19:54:09 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void free_cube(t_cube *cube)
{
    int i = 0;
    while (cube->data->map[i]) {
        free(cube->data->map[i]);
        i++;
    }
    free(cube->data->map);
    i = 0;
    while(cube->data->pixel_map[i]) {
        free(cube->data->pixel_map[i]);
        i++;
    }
    i = 0;
    while (i < 4) {
        free(cube->data->textures[i]);
        i++;
    }
    free(cube->data->textures);
    free(cube->data->pixel_map);
    free(cube->player);
    free(cube->mlx);
    free(cube->win);
    free(cube->img);
    free(cube->data);
}

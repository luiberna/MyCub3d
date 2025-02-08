/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:33:50 by luiberna          #+#    #+#             */
/*   Updated: 2025/02/07 17:04:01 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void verify_player(t_cube *cube, t_data *data)
{
    int i;
    int j;
    int flag;

    flag = 0;
    i = 0;
    while (data->map[i])
    {
        j = 0;
        while (data->map[i][j])
        {
            if (data->map[i][j] == 'N' || data->map[i][j] == 'S' || data->map[i][j] == 'E' || data->map[i][j] == 'W')
                flag++;
            j++;
        }
        i++;
    }
    if (flag == 0 || flag > 1)
        print_error(cube, "Error: error on file\n");
}

void verify_closed_map(t_cube *cube, t_data *data)
{
    int i;
    int j;
    char *possible;

    possible = "0NSEW";
    i = 0;
    while (data->map[i])
    {
        j = 0;
        while (data->map[i][j])
        {
            if (ft_strchr(possible, data->map[i][j]))
            {
                if (i == 0 || j == 0 || !data->map[i + 1] || !data->map[i][j + 1] ||
                data->map[i - 1][j] == ' ' || data->map[i + 1][j] == ' ' ||
                data->map[i][j - 1] == ' ' || data->map[i][j + 1] == ' ' ||
                data->map[i - 1][j] == '\0' || data->map[i + 1][j] == '\0' ||
                data->map[i][j - 1] == '\0' || data->map[i][j + 1] == '\0')
                    print_error(cube, "ERROR: Map is not properly closed\n");
            }
            j++;
        }
        i++;
    }
}

void verify_map(t_cube *cube, t_data *data)
{
    int i;
    int j;

    i = 0;
    while (data->map[i])
    {
        j = 0;
        while (data->map[i][j])
        {
            if (data->map[i][j] != '1' && data->map[i][j] != '0' && data->map[i][j] != 'N' &&
                data->map[i][j] != 'S' && data->map[i][j] != 'E' && data->map[i][j] != 'W' &&
                data->map[i][j] != ' ')
                print_error(cube, "ERROR: Invalid map\n");
            j++;
        }
        i++;
    }
    verify_closed_map(cube, data);
    verify_player(cube, data);
}

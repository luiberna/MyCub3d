/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:11:47 by luiberna          #+#    #+#             */
/*   Updated: 2025/02/05 18:12:09 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

int get_map_width(t_data *data)
{
    int i;
    unsigned long len;

    i = 0;
    len = 0;
    while(data->map[i])
    {
        if(ft_strlen(data->map[i]) > len)
            len = ft_strlen(data->map[i]);
        i++;
    }
    return (len);
}

int get_map_height(t_data *data, char *file)
{
    int i;
    char *line;
    int fd;

    i = 0;
    fd = open(file, O_RDONLY);
    line = get_next_line(fd);
    while(i != data->map_position)
    {
        free(line);
        line = get_next_line(fd);
        i++;
    }
    i = 0;
    while (line)
    {
        free(line);
        line = get_next_line(fd);
        i++;
    }
    free(line);
    close(fd);
    return i;
}

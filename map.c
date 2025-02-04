/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 20:16:20 by luiberna          #+#    #+#             */
/*   Updated: 2025/02/04 16:00:27 by luiberna         ###   ########.fr       */
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

char **get_map(t_data *data, char *file)
{
    int i;
    char **map;
    char *line;
    int fd;

    i = get_map_height(data, file);
    map = malloc(sizeof(char *) * (i + 1));
    fd = open(file, O_RDONLY);
    line = get_next_line(fd);
    i = 0;
    while (i != data->map_position)
    {
        free(line);
        line = get_next_line(fd);
        i++;
    }
    i = 0;
    while (line)
    {
        map[i++] = ft_strtrim(line, "\n");
        free(line);
        line = get_next_line(fd);
    }
    free(line);
    map[i] = NULL;
    close(fd);
    return (map);
}

void map_position(t_data *data, char *file)
{
    int flag;
    char *line;
    int fd;
    int count;

    count = 0;
    flag = 0;
    fd = open(file, O_RDONLY);
    while ((line = get_next_line(fd)) && flag < 6)
    {
        if (ft_strncmp(line, "C", 1) == 0)
            flag++;
        else if (ft_strncmp(line, "F", 1) == 0)
            flag++;
        else if (ft_strncmp(line, "NO", 2) == 0)
            flag++;
        else if (ft_strncmp(line, "SO", 2) == 0)
            flag++;
        else if (ft_strncmp(line, "WE", 2) == 0)
            flag++;
        else if (ft_strncmp(line, "EA", 2) == 0)
            flag++;
        count++;
        free(line);
    }
    free(line);
    while ((line = get_next_line(fd)) && ft_strncmp(line, "\n", 1) == 0)
    {
        count++;
        free(line);
    }
    if (line)
        free(line);
    count++;
    close(fd);
    data->map_position = count;
}

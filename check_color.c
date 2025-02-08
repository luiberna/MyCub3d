/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:40:17 by luiberna          #+#    #+#             */
/*   Updated: 2025/02/07 17:29:01 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void check_color5(t_cube *cube, char **color_numbers, char *line, int fd)
{
    int i;
    int flag;
    int j;
    
    i = 0;
    while (color_numbers[i])
    {
        flag = 0;
        j = 0;
        while (color_numbers[i][j])
        {
            if (ft_isdigit(color_numbers[i][j]))
                flag++;
            j++;
        }
        if (flag < 1)
        {
            free(line);
            close(fd);
            free_color(color_numbers);
            print_error(cube, "Error: Color must be a number\n");
        }
        i++;
    }
}

void check_color4(t_cube *cube, char **color_numbers, char *line, int fd)
{
    int i;
    int j;
    
    i = 0;
    j = 0;
    check_color5(cube, color_numbers, line, fd);
    while (color_numbers[i])
    {
        j = 0;
        while (color_numbers[i][j])
        {
            if (!ft_isdigit(color_numbers[i][j]) && color_numbers[i][j] != ' ' && color_numbers[i][j] != '\n')
            {
                free(line);
                close(fd);
                free_color(color_numbers);
                print_error(cube, "Error: Color must be a number\n");
            }
            j++;
        }
        i++;
    }
}

void check_color3(t_cube *cube, char *line, int fd)
{
    int j;
    char **color_numbers;
    
    j = 0;
    color_numbers = ft_split(line + 2, ',');
    check_color4(cube, color_numbers, line, fd);
    while (color_numbers[j])
    {
        if (ft_atoi(color_numbers[j]) < 0 || ft_atoi(color_numbers[j]) > 255)
        {
            free(line);
            close(fd);
            free_color(color_numbers);
            print_error(cube, "Error: Color must be between 0 and 255\n");
        }
        j++;
    }
    if (j != 3)
    {
        free(line);
        close(fd);
        free_color(color_numbers);
        print_error(cube, "Error: Color must have 3 values\n");
    }
    free_color(color_numbers);
}

void check_color2(t_cube *cube, char *line, int fd)
{
    int i;
    int j;
    char **color_numbers;

    i = 0;
    j = 0;
    while (line[i])
    {
        if (line[i] == ',')
            j++;
        i++;
    }
    if (j != 2)
    {
        free(line);
        close(fd);
        print_error(cube, "Error: Color must have 3 values\n");
    }
    check_color3(cube, line, fd);
}

void check_color(t_cube *cube, char *file)
{
    int fd;
    char *line;
    int i;

    i = 0;
    fd = open(file, O_RDONLY);
    while (line = get_next_line(fd))
    {
        if (line[0] == 'C' || line[0] == 'F')
            check_color2(cube, line, fd);
        free(line);
    }
    close(fd);
}

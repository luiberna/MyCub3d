/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:28:38 by luiberna          #+#    #+#             */
/*   Updated: 2025/02/05 19:13:37 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void print_map(char **map)
{
    int i;
    i = 0;
    while (map[i])
    {
        printf("%s\n", map[i]);
        i++;
    }
}

bool check_file(char *str)
{
    int len;

    len = ft_strlen(str);
    if (len > 4 && ft_strncmp(str + len - 4, ".cub", 4) == 0)
        return true;
    return false;
}

void print_error(t_cube *cube, char *str)
{
    printf("%s" ,str);
    free_cube(cube);
    exit(1);
}

void check_errors(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Error: Invalid arguments\n");
        exit(1);
    }
    else if (!check_file(argv[1]))
    {
        printf("Error: Invalid file\n");
        exit(1);
    }
    else if (open(argv[1], O_RDONLY) == -1)
    {
        printf("Error: Can't open file\n");
        exit(1);
    }
}

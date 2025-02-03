/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:28:38 by luiberna          #+#    #+#             */
/*   Updated: 2025/02/01 20:05:01 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

//Test function to print map
void print_map(char **map)
{
    int i = 0;
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

void print_error(char *str)
{
    printf("%s" ,str);
    exit(1);
}

void check_errors(int argc, char **argv)
{
    if (argc != 2)
        print_error("Error: Invalid arguments\n");
    else if (!check_file(argv[1]))
        print_error("Error: Invalid file\n");
    else if (open(argv[1], O_RDONLY) == -1)
        print_error("Error: Can't open file\n");
}

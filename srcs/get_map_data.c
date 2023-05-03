/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:01:49 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/03 23:59:43 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3d.h"

static int	non_specific_chara(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != 'N'
			&& str[i] != 'S' && str[i] != 'E' && str[i] != 'W')
			return (1);
		i++;
	}
	return (0);
}

static char	*check_n(char *str)
{
	int		i;
	char	*res;

	if (ft_strchr(str, '\n'))
		return (str);
	res = (char *)malloc(sizeof(char) * ft_strlen(str) + 2);
	if (!res)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		res[i] = str[i];
		i++;
	}
	res[i++] = '\n';
	res[i] = '\0';
	free(str);
	return (res);
}

static char **map_str_add(char **array, char *new)
{
    char **res;
    int i;
    int vertical;

    vertical = 0;
    while (array && array[vertical] != NULL)
        vertical++;
    res = (char **)malloc(sizeof(char *) * (vertical + 2));
    if (!res)
        print_error("map");
    i = 0;
    while (i < vertical)
    {
        res[i] = array[i];
        i++;
    }
    new = check_n(new);
    if (!new)
        print_error("check_n()");
    res[i++] = new;
    res[i] = NULL;
    free(array);
    return (res);
}

void get_map_data(int fd,t_info *info)
{
    char *str;
    int flag;

    str = get_next_line(fd);
    if (!str)
	{
        print_error("get_next_line");
	}
    flag = 0;
	int i = 0;
    while (str)
    {
        if (non_specific_chara(str) == 1)
            flag = 1;
        info->map->map_data = map_str_add(info->map->map_data,str);
		// printf("info->map->map_data[%d] = %s\n",i,info->map->map_data[i]);
        // info->map->vertical++;
        str = get_next_line(fd);
		i++ ;
    }
	// debug用

    // printf("vertical = %d\n",info->map->vertical);
	// printf("flag = %d\n",flag);
    if (flag == 1)
    {
        free_mapdata(info->map->map_data, info->map->vertical);
        print_error("get_next_line");
    }
}

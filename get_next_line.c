/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 10:49:00 by gduval            #+#    #+#             */
/*   Updated: 2017/01/10 13:55:18 by gduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> //adw
#include "get_next_line.h"
#include <stdio.h> //daw

int                 get_next_line(const int fd, char **line)
{
    char            *buf;
    char            *tmp;
    static char     *overtake = NULL;
    int             ret;
    size_t          i;

    if (fd < 0 || !line)
        return (-1);
    *line = ft_memalloc(1);
    buf = ft_memalloc(sizeof(char) * (400 + 1)); // LEAK
    printf("Overtake -> %s\n", overtake);
    while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
    {
        printf("0 - Buf -> %s\n", buf);
        i = 0;
        buf[ret] = '\0';
        tmp = ft_memalloc(400); // LEAK
        if (overtake)
        {
            buf = ft_strjoin(overtake, buf); // LEAK
            overtake = ft_memalloc(1);
        }
        while (buf[i] != '\n' && buf[i] != '\0')
        {
            tmp[i] = buf[i];
            i++;
        }
        tmp[i] = '\0';
        printf("1 - Buf -> %s\n", buf);
        if (buf[i] == '\n' && i != BUFF_SIZE)
        {
            printf("buf[i + 1] = %c\nlen = %zu\n", buf[i + 1], ft_strlen(buf));
            overtake = ft_strsub(buf, i + 1, ft_strlen(buf) - i);
            *line = ft_strjoin(*line, tmp);
            ft_putendl("0");
            return (1);
        }
        else
        {
            *line = ft_strjoin(*line, tmp);
        }
    }
    if (overtake && ft_strlen(overtake) > 0 && ret == 0)
    {
        i = 0;
        tmp = ft_memalloc(sizeof(char) * ft_strlen(overtake)); // LEAK
        while (overtake[i] != '\n' && overtake[i] != '\0')
        {
            tmp[i] = overtake[i];
            i++;
        }
        i = (overtake[i] == '\n') ? i + 1 : i;
        tmp[i] = '\0';
        overtake = ft_strsub(overtake, i, ft_strlen(overtake) - i);
        *line = tmp;
        if (overtake[0] == '\0')
            overtake = NULL;
        ft_putendl("1");
        return (1);
    }
    if (ret == -1)
        return (ret);
    else if (ret == 0 && ft_strlen(*line) > 0)
    {
        ft_putendl("2");
        return (1);
    }
    ft_putendl("3");
    return (ret == 0) ? 0 : 1;
}
//
// int         main(int argc, char **argv)
// {
//     int     ret;
//     int     fd;
//     char    *line;
//
//     if ((fd = open(argv[1], O_RDONLY)) == -1)
//         return (-1);
//     line = NULL;
//     while ((ret = get_next_line(fd, &line)) > 0)
//     {
//         ft_putendl(line);
//         sleep(3);
//     }
//     return (0);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:52:14 by aogbi             #+#    #+#             */
/*   Updated: 2024/10/14 17:26:26 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

int main(int argc, char **argv)
{
    char *str = malloc(sizeof(char) * 100);
    str[0] = 1;
    printf("%d  %ld\n", argc, ft_strlen(argv[0]));
    return (0);
}
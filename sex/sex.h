/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 05:32:46 by aogbi             #+#    #+#             */
/*   Updated: 2024/10/19 06:28:59 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEX_H
#define SEX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct s_micro t_micro;

struct s_micro
{
    char **cmd;
    int size;
    t_micro *next;
};

#endif // SEX_H
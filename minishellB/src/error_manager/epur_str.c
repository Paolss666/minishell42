/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epur_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeyer <armeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:56:25 by armeyer           #+#    #+#             */
/*   Updated: 2023/12/08 14:25:13 by armeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

char*	epur_str(char *str)
{
	size_t len;
	size_t		i;
	size_t		j;
	int 	spaceFlag;
	char	*result;

	i = 0;
	j = 0;
	spaceFlag = 0;
	if (str == NULL || *str == '\0')
		return (NULL);

	while (ft_isspace((unsigned char)*str))
		str++;

	len = strlen(str);
	result = (char *)malloc((len + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	while (i < len)
	{
		if (isspace((unsigned char)str[i]))
		{
			if (!spaceFlag)
			{
				result[j++] = ' ';
				spaceFlag = 1;
			}
		}
		else
		{
            result[j++] = str[i];
            spaceFlag = 0;
		}
		i++;
	}

    result[j] = '\0';
    return (result);
}

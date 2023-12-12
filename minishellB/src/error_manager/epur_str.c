/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epur_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeyer <armeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:56:25 by armeyer           #+#    #+#             */
/*   Updated: 2023/12/12 13:55:56 by armeyer          ###   ########.fr       */
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

char	*epur_str2(char *str)
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
	return (str);
}

char	*ft_coma(char *str)
{
		int	i;
		int	coma1;
		int flag;

		i = 0;
		flag = 0;
		coma1 = 0;
		while (str[i] != '\0')
		{
			if (str[i] == '"' && flag == 0 && str[i + 1])
			{
				flag = 1;
				coma1 = i;
				i++;
			}
			if (str[i] == '"' && flag == 1)
			{
				str[coma1] = ' ';
				str[i] = ' ';
				flag = 0;
			}
			i++;
		}
		i = 0;
		flag = 0;
		while (str[i] != '\0')
		{
			if (str[i] == 39 && flag == 0 && str[i + 1])
			{
				flag = 1;
				coma1 = i;
				i++;
			}
			if (str[i] == 39 && flag == 1)
			{
				str[coma1] = ' ';
				str[i] = ' ';
				flag = 0;
			}
			i++;
		}
		return (epur_str2(str));
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
    return (ft_coma(result));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 04:55:54 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/17 12:57:52 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns 0 if `s` is NULL. */
int	strlen_null(const char *s)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
		++i;
	return (i);
}

/*
	Return a substring of `s` from `start_idx` to `end_idx` INCLUSIVE.
	Uses allocation so return string must be freed by the caller.
	TODO: clean and exit upon alloc error.
*/
char	*str_sub(char *s, int start_idx, int end_idx)
{
	return (ft_substr(s, start_idx, end_idx - start_idx + 1));
}

/* Return whether string only consists of digits or not. */
int	str_is_numeric(char *str)
{
	size_t	i;
	size_t	len;

	if (str == NULL)
		return (FALSE);
	len = ft_strlen(str);
	if (len == 0)
		return (FALSE);
	i = 0;
	if (str[i] == '-')
	{
		if (len == 1)
			return (FALSE);
		i ++;
	}
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
		++i;
	}
	return (TRUE);
}

/*
	Search `search_char` in `s` starting from index `search_start_idx`.
	Return -1 if not found
*/
int	find_idx_of_nextc(char *s, int search_start_idx, char search_char)
{
	int	i;

	i = search_start_idx;
	while (s[i] != '\0')
	{
		if (s[i] == search_char)
			return (i);
		++i;
	}
	return (-1);
}

/*
	Replace string pointed by `p_str` 
	from `start` index to `end` index inclusive with `replace_with`.
*/
void	str_replace_section(char **p_str, int start, int end, char *replace_with)
{
	// TODO: reconsider if you should use such utility
}

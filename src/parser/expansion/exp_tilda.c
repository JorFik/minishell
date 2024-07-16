/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_tilda.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 00:26:54 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/16 03:07:57 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_eligible_for_exp(char *line, int i, char quote_type)
{
	if (line[i] != '~')
		return (FALSE);
	if (quote_type != NOT_QUOTE)
		return (FALSE);
	if (i > 0 && line[i - 1] != ' ')
		return (FALSE);
	if (line[i + 1] != '\0' && (line[i + 1] != ' ' && line[i + 1] != '/'))
		return (FALSE);
	return (TRUE);
}

void	detect_tilda_expansions(char *line, t_list_int **p_tilda_idxs_to_expand)
{
	char	quote_type;
	int		tilda_idx;
	int		len;
	int		i;
	
	quote_type = NOT_QUOTE;
	tilda_idx = 0;
	len = ft_strlen(line);
	i = 0;
	while (i < len)
	{
		if (quote_type == NOT_QUOTE && (line[i] == '\"' || line[i] == '\''))
			quote_type = line[i];
		else if (line[i] == quote_type)
			quote_type = NOT_QUOTE;
		else if (line[i] == '~')
		{
			if (is_eligible_for_exp(line, i, quote_type))
				list_add(p_tilda_idxs_to_expand, tilda_idx);
			++tilda_idx;
		}
		++i;
	}
}

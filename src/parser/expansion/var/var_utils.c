/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 00:08:46 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/23 02:33:03 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_var_exp_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	is_prev_here_doc(t_token *tok)
{
	if (tok->prev == NULL)
		return (FALSE);
	if (tok->prev->type == HERE_DOC)
		return (TRUE);
	return (FALSE);
}

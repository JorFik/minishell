/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 03:06:31 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/22 08:05:30 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	If env var was not found and previous token was 
	REDIR_TO, REDIR_FROM or APPEND_TO,
	then you should fail
*/
void	handle_if_should_fail(\
t_token *curr_tok, char *env_var_name, char *env_var_result)
{
	if (curr_tok->prev == NULL)
		return ;
	if (env_var_result != NULL)
		return ;
	if (curr_tok->prev->type == REDIR_TO
		|| curr_tok->prev->type == REDIR_FROM
		|| curr_tok->prev->type == APPEND_TO)
	{
		// TODO: freeing stuff
		ft_putstr_fd("minishell: $", 2);
		ft_putstr_fd(env_var_name, 2);
		exit_error(": ambiguous redirect", EXIT_FAILURE);
	}
}

int	handle_if_double_dollar(t_var_exp_vars *v)
{
	char	*minishell_pid;

	if (v->iter->value[v->i + 1] == '$')
	{
		if (!is_prev_here_doc(v->iter))
		{
			minishell_pid = ft_itoa(getpid());
			str_replace_section(&v->iter->value, v->i, v->i + 1, minishell_pid);
			free(minishell_pid);
			v->env_var_val_len = ft_strlen(v->iter->value);
		}
		++(v->idx_idx);
		++(v->var_idx);
		return (TRUE);
	}
	return (FALSE);
}

int	handle_if_dollar_questionmark(t_var_exp_vars *v)
{
	char	*last_proc_exit_code;

	if (v->iter->value[v->i + 1] == '?')
	{
		if (!is_prev_here_doc(v->iter))
		{
			last_proc_exit_code = getenv("LAST_PROCESS_EXIT_CODE");
			handle_if_should_fail(\
			v->iter, "LAST_PROCESS_EXIT_CODE", last_proc_exit_code);
			str_replace_section(&(v->iter->value), v->i, v->i + 1, last_proc_exit_code);
			v->env_var_val_len = ft_strlen(v->iter->value);
		}
		++(v->idx_idx);
		return (TRUE);
	}
	return (FALSE);
}

static void	var_expansion_vars_init(\
t_var_exp_vars *v, t_token *token_list, t_exp_idxs	*exp_idxs)
{
	v->var_idx = 0;
	v->idx_idx = 0;
	v->i = 0;
	v->e = 0;
	v->env_var_name = NULL;
	v->env_var_val = NULL;
	v->env_var_val_len = 0;
	v->iter = token_list;
	v->token_list_head = token_list;
	v->exp_idxs = exp_idxs;
	v->list_size = list_get_size(exp_idxs->var_idxs);
}

void	expand_var(t_token *token_list, t_exp_idxs	*exp_idxs)
{
	t_var_exp_vars v;

	var_expansion_vars_init(&v, token_list, exp_idxs);
	while (v.iter != NULL)
	{
		if (v.iter->type == STRING)
		{
			v.env_var_val_len = ft_strlen(v.iter->value);
			v.i = 0;
			while (v.i < v.env_var_val_len)
			{
				if (v.iter->value[v.i] == '$')
				{
					if (handle_if_double_dollar(&v))
						;
					else if (handle_if_dollar_questionmark(&v))
						;
					else if (v.list_size > v.idx_idx && v.var_idx == list_get_idx(v.exp_idxs->var_idxs, v.idx_idx))
					{
						v.e = v.i + 1;
						while (v.iter->value[v.e] != '\0' && is_valid_var_exp_char(v.iter->value[v.e]))
							++v.e;
						if (!is_prev_here_doc(v.iter))
						{
							v.env_var_name = str_sub(v.iter->value, v.i + 1, v.e - 1);
							v.env_var_val = getenv(v.env_var_name);
							handle_if_should_fail(v.iter, v.env_var_name, v.env_var_val);
							// Sussy wussy (removed -1)
							// str_replace_section(&iter->value, i, e - 1, env_var_val);
							str_replace_section(&(v.iter->value), v.i, v.e - 1, v.env_var_val);
							free(v.env_var_name);
							v.env_var_val_len = ft_strlen(v.iter->value);
						}
						++v.idx_idx;
					}
					++v.var_idx;
				}
				++v.i;
			}
		}
		v.iter = v.iter->next;
	}
}

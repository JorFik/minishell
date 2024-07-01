/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:52:34 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/01 16:57:02 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*lowercase(const char *str)
{
	char	*lower;
	int		i;

	lower = ft_strdup(str);
	if (lower == NULL)
		return (NULL);
	i = -1;
	while (lower[++i])
		lower[i] = ft_tolower(lower[i]);
	return (lower);
}

void	builtins(t_cmd	*cmd)
{
	const char	*all_lowercase = lowercase(cmd->argv[0]);

	set_redir(cmd->redirects);
	if (ft_strnstr(all_lowercase, "cd", 2))
		cd(cmd->argv);
	else if (ft_strnstr(all_lowercase, "echo", 4))
		echo(cmd->argv);
	else if (ft_strnstr(all_lowercase, "env", 3))
		env(cmd->argv);
	else if (ft_strnstr(all_lowercase, "exit", 4))
		exit_bash(cmd);
	// export(input, to_free); Not implemented yet
	else if (ft_strnstr(all_lowercase, "pwd", 3))
		pwd();
	// unset(input, to_free); Not implemented yet
	ft_free_n_null((void **)&all_lowercase);
}
// {
// 	char	*trimmed_input;

// 	trimmed_input = ft_strtrim(input, " ");
// 	if (ft_strlen(trimmed_input) != ft_strlen(input))
// 		input = trimmed_input;
// 	if (ft_strnstr(input, "cd", 2))
// 		cd(input + 2);
// 	else if (ft_strnstr(input, "echo", 4))
// 		echo(input + 4);
// 	else if (ft_strnstr(input, "env", 3))
// 		env(input + 3);
// 	else if (ft_strnstr(input, "exit", 4))
// 		exit_bash(&input);
// 	// export(input, to_free); Not implemented yet
// 	else if (ft_strnstr(input, "pwd", 3))
// 		pwd();
// 	// unset(input, to_free); Not implemented yet
// 	ft_free_n_null((void **)&trimmed_input);
// }

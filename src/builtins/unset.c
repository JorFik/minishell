/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:41:50 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/24 19:35:18 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_key_present(char *key)
{
	extern char	**environ;
	int			i;

	if (getenv(key) != NULL)
		return (true);
	i = -1;
	while (environ[++i])
		if (have_same_key(key, environ[i]) == true)
			return (true);
	return (false);
}

static int	unset_env(char *key)
{
	extern char	**environ;
	const int	environ_size = count_strs_in_array(environ);
	char		**new_environ;
	int			i;

	if (is_key_present(key) == false)
		return (EXIT_SUCCESS);
	new_environ = ft_calloc(sizeof(char *), (environ_size));
	if (new_environ == NULL)
		return (ft_printf_fd(2, ERROR_MSG, "unset", E_ALLOC), EXIT_FAILURE);
	i = -1;
	while (environ[++i] && have_same_key(key, environ[i]) == false)
		new_environ[i] = environ[i];
	ft_free_n_null((void **)&environ[i]);
	while (environ[++i])
		new_environ[i - 1] = environ[i];
	ft_free_n_null((void **)&environ);
	environ = new_environ;
	return (EXIT_SUCCESS);
}

int	unset_builtin(char **args)
{
	int	i;
	int	exit_code;

	i = 0;
	exit_code = EXIT_SUCCESS;
	while (args[++i])
	{
		if (is_key_valid(args[i]) == false || ft_strchr(args[i], '=') != NULL)
		{
			ft_printf_fd(2, ERROR_MSG_PERROR"%s: %s\n", "unset", args[i],
				"not a valid identifier");
			exit_code = EXIT_FAILURE;
		}
		else
			if (unset_env(args[i]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
	}
	return (exit_code);
}

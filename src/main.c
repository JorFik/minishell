/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 08:42:53 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/19 17:58:00 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_minishell(void)
{
	extern char		**environ;
	extern int		errno;
	struct termios	terminal_config;

	errno = 0;
	environ = dup_environ();
	if (environ == NULL)
		return (EXIT_FAILURE);
	tcgetattr(STDIN_FILENO, &terminal_config);
	terminal_config.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal_config);
	return (EXIT_SUCCESS);
}

static char	*get_input(void)
{
	char	*prompt;
	char	*input;

	prompt = get_prompt();
	if (prompt == NULL)
	{
		prompt = ft_strdup("minishell$ ");
		if (prompt == NULL)
			exit_error("minishell: Error allocating memory: malloc",
				EXIT_FAILURE);
	}
	input = readline(prompt);
	ft_free_n_null((void **)&prompt);
	return (input);
}

int	main(void)
{
	char		*input;
	extern int	errno;
	t_token		*token_list;

	if (init_minishell())
	{
		ft_printf_fd(2, ERROR_MSG, "malloc", "Error initializing environment");
		return (EXIT_FAILURE);
	}
	input = NULL;
	while (errno == 0)
	{
		set_signal_handlers_mode(INTERACTIVE);
		input = get_input();
		if (input == NULL)
			return (exit_bash(1, NULL));
		token_list = parse(input);
		if (ft_strlen(input) > 0)
			add_history(input);
		set_signal_handlers_mode(EXECUTION);
		errno = exec(token_list);
		ft_free_n_null((void **)&input);
	}
	return (clean_up(), errno);
}

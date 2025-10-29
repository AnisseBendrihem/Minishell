/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 21:14:57 by abendrih          #+#    #+#             */
/*   Updated: 2025/10/29 09:43:25 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_token	*token;
	t_token	*save_token;

	(void)ac;
	(void)av;
	while (1)
	{
		line = readline("\033[1;91mEl Cancer > \033[0m");
		add_history(line);
		if (!line)
		{
			ft_putstr_fd("exit\n", 2);
			break ;
		}
		token = lexer(line);
		save_token = token;
		free(line);
		simple_exec(&token, env);
		token_free(&save_token);
	}
}

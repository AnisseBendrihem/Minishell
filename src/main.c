/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 21:14:57 by abendrih          #+#    #+#             */
/*   Updated: 2025/10/31 22:33:50 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	has_unclosed_quotes(char *line)
{
	int	count;
	int	count_;
	int	i;

	count_ = 0;
	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '"' && count_ % 2 == 0)
			count++;
		if (line[i] == '\'' && count % 2 == 0)
			count_++;
		i++;
	}
	return ((count + count_) % 2);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_token	*token;
	t_token	*save_token;
	char	*next;
	char	*tmp;

	(void)ac;
	(void)av;
	while (1)
	{
		line = readline("\033[1;91mEl Cancer > \033[0m");
		add_history(line);
		while (has_unclosed_quotes(line))
		{
			printf("DEBUG: line avant readline = [%s]\n", line);
			next = readline("> ");
			add_history(line);
			tmp = ft_strjoin(line, "\n");
			line = ft_strjoin(tmp, next);
			free(next);
			printf("DEBUG: line après concat = [%s]\n", line);
		}
		if (!line)
		{
			ft_putstr_fd("exit\n", 2);
			break ;
		}
		printf("DEBUG: line finale avant lexer = [%s]\n", line);
		token = lexer(line);
		if (token == NULL)
		{
			free(line);
			continue ;
		}
		save_token = token;
		free(line);
		simple_exec(&token, env);
		token_free(&save_token);
	}
}

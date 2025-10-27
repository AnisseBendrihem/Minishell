/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 21:14:57 by abendrih          #+#    #+#             */
/*   Updated: 2025/10/27 06:02:18 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Fonction pour trouver le PATH dans envp
char	*get_path_from_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5); // Retourne après "PATH="
		i++;
	}
	return (NULL);
}

// Fonction pour chercher la commande dans le PATH
char	*find_command(char *cmd, char **envp)
{
	char	*path;
	char	*valid_cmd;
	int		i;
	char	*tmp;

	path = get_path_from_env(envp);
	char **dirs = ft_split(path, ':'); // Split le PATH par ':'
	i = 0;
	while (dirs[i])
	{
		// TODO : construire le chemin complet (dirs[i] + "/" + cmd)
		tmp = ft_strjoin(dirs[i], "/");
		valid_cmd = ft_strjoin(tmp, cmd);
		// TODO : tester avec access()
		if (access(valid_cmd, X_OK) == 0)
		{
			ft_free(&dirs[i + 1]);
			free(dirs);
			return (valid_cmd);
		}
		// TODO : si ça existe, retourner le chemin complet
		free(valid_cmd);
		i++;
	}
	free(dirs);
	return (NULL); // Pas trouvé
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	count_operator(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (is_operator(line[i]))
		{
			count++;
			if (line[i + 1] == line[i])
				i++;
		}
		i++;
	}
	return (count);
}

char	*lexer(char *line)
{
	int		i;
	int		j;
	char	*result;

	if (!line)
		return (NULL);
	result = malloc(ft_strlen(line) + (count_operator(line) * 2) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (is_operator(line[i]))
		{
			result[j++] = ' ';
			result[j++] = line[i];
			if (line[i + 1] == line[i])
				result[j++] = line[++i];
			result[j++] = ' ';
		}
		else
			result[j++] = line[i];
		i++;
	}
	result[j] = '\0';
	return (free(line), result);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	*lexed_line;
	char	**args;
	char	*cmd_path;
	int		id;

	(void)av;
	(void)ac;
	while (1)
	{
		// TODO 1 : lire avec readline() ou scanf
		line = readline("\033[1;91mEl Cancer > \033[0m");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		lexed_line = lexer(line);
		// TODO 2 : split la ligne en motsss
		args = ft_split(lexed_line, ' ');
		if (!args || !args[0])
		{
			ft_free(args);
			free(args);
			continue ;
		}
		// TODO 3 : trouver le chemin complet de la commande
		cmd_path = find_command(args[0], envp);
		if (!cmd_path)
			ft_printf("zsh: command not found: %s\n", args[0]);
		// TODO 4 : fork + execve + wait
		if (cmd_path)
		{
			id = fork();
			if (id == 0)
			{
				execve(cmd_path, args, envp);
				perror("execve");
				exit(1);
			}
			else
				wait(NULL);
			// TODO 5 : free la mémoire
			free(cmd_path);
		}
		ft_free(args);
		free(args);
	}
	return (0);
}

// int	main(int ac, char **av)
// {
// 	int	test;

// 	(void)ac;
// 	test = count_operator(av[1]);
// 	printf("%d", test);
// }

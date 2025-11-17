/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:15:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/11/17 17:15:00 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_var_value(char *var_name, t_shell *shell)
{
	char	*value;
	char	*exit_str;

	if (ft_strcmp(var_name, "?") == 0)
	{
		exit_str = ft_itoa(shell->exit_status);
		return (exit_str);
	}
	value = env_get(shell->env, var_name);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

static char	*extract_var_name(char *str, int *i)
{
	int		start;

	start = *i;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

static char	*append_char(char *str, char c)
{
	char	*new_str;
	char	char_str[2];
	char	*tmp;

	char_str[0] = c;
	char_str[1] = '\0';
	tmp = str;
	new_str = ft_strjoin(str, char_str);
	free(tmp);
	return (new_str);
}

static char	*expand_loop(char *str, t_shell *shell, char *result)
{
	int		i;
	char	*var_name;
	char	*var_value;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (ft_isalnum(str[i + 1])
				|| str[i + 1] == '_' || str[i + 1] == '?'))
		{
			i++;
			var_name = extract_var_name(str, &i);
			var_value = get_var_value(var_name, shell);
			tmp = result;
			result = ft_strjoin(result, var_value);
			free(tmp);
			free(var_name);
			free(var_value);
		}
		else
			(result = append_char(result, str[i]), i++);
	}
	return (result);
}

char	*expand_variables(char *str, t_shell *shell, int in_single_quotes)
{
	char	*result;

	if (in_single_quotes || !str)
		return (ft_strdup(str));
	result = ft_strdup("");
	result = expand_loop(str, shell, result);
	return (result);
}

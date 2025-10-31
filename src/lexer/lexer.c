/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 04:18:54 by abendrih          #+#    #+#             */
/*   Updated: 2025/10/31 19:51:55 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static char	*extract_quoted_word(char *line, int *i, char quote_char)
{
	char	*word;
	int		start;

	start = *i + 1;
	(*i)++;
	while (line[*i] && line[*i] != quote_char)
		(*i)++;
	if (line[*i] == '\0')
	{
		return (NULL);
	}
	word = ft_substr(line, start, *i - start);
	(*i)++;
	return (word);
}

// À ajouter plus tard : guillemets, variables
t_token	*lexer(char *line)
{
	t_token	*head;
	int		i;
	int		start;
	char	*word;

	head = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (!line[i])
			break ;
		if (line[i] == '|')
		{
			token_addback(&head, token_new(TOKEN_PIPE, "|"));
			i++;
		}
		else if (line[i] == '>' || line[i] == '<')
		{
			if (line[i] == '>')
			{
				if (line[i + 1] == line[i])
				{
					token_addback(&head, token_new(TOKEN_APPEND, ">>"));
					i += 2;
				}
				else
				{
					token_addback(&head, token_new(TOKEN_REDIRECT_OUT, ">"));
					i++;
				}
			}
			else if (line[i] == '<')
			{
				if (line[i + 1] == line[i])
				{
					token_addback(&head, token_new(TOKEN_HEREDOC, "<<"));
					i += 2;
				}
				else
				{
					token_addback(&head, token_new(TOKEN_REDIRECT_IN, "<"));
					i++;
				}
			}
		}
		else if (line[i] == '"')
		{
			word = extract_quoted_word(line, &i, '"');
			if (word == NULL)
			{
				ft_putstr_fd("syntax error: unclosed quote\n", 2);
				token_free(&head);
				return (NULL);
			}
			token_addback(&head, token_new(TOKEN_WORD, word));
			free(word);
		}
		else if (line[i] == '\'')
		{
			word = extract_quoted_word(line, &i, '\'');
			if (word == NULL)
			{
				ft_putstr_fd("syntax error: unclosed quote\n", 2);
				token_free(&head);
				return (NULL);
			}
			token_addback(&head, token_new(TOKEN_WORD, word));
			free(word);
		}
		else
		{
			start = i;
			while (line[i] && line[i] != ' ' && !is_operator(line[i]))
				i++;
			word = ft_substr(line, start, i - start);
			token_addback(&head, token_new(TOKEN_WORD, word));
			free(word);
		}
	}
	return (head);
}

// Fonctionne bien pour commandes simples
// Restera utile même avec les pipe
char	**tokens_to_array(t_token **lst)
{
	int		i;
	char	**args;

	i = 0;
	args = malloc(sizeof(char *) * (count_tokens(lst) + 1));
	if (!args)
		return (NULL);
	while (*lst)
	{
		if ((*lst)->type != TOKEN_WORD)
		{
			args[i] = NULL;
			if ((*lst)->next)
				*lst = (*lst)->next;
			return (args);
		}
		args[i] = ft_strdup((*lst)->value);
		i++;
		*lst = (*lst)->next;
	}
	args[i] = NULL;
	return (args);
}

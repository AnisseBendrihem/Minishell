/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 21:47:35 by abendrih          #+#    #+#             */
/*   Updated: 2025/10/29 20:23:44 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

t_token				*lexer(char *line);
t_token				*token_new(t_token_type type, char *value);
void				token_addback(t_token **lst, t_token *new);
int					count_tokens(t_token **lst);
void				token_free(t_token **lst);
char				**tokens_to_array(t_token **lst);

#endif

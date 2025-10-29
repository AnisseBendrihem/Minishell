/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 09:43:50 by abendrih          #+#    #+#             */
/*   Updated: 2025/10/29 09:53:20 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

#ifndef EXECUTOR_H
# define EXECUTOR_H

void	simple_exec(t_token **token, char **envp);

#endif

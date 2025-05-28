/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcouto <jcouto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:38:26 by jcouto            #+#    #+#             */
/*   Updated: 2025/05/27 16:40:57 by jcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Determine operator type and increment
void lexer_operator_type(char *input, int *i, TokenType *type, int *inc)
{
    if (input[*i] == '|')
        *type = TOKEN_PIPE;
    else if (input[*i] == '<' && input[*i + 1] == '<')
    {
        *type = TOKEN_HEREDOC;
        *inc = 1;
    }
    else if (input[*i] == '>' && input[*i + 1] == '>')
    {
        *type = TOKEN_REDIRECT_APPEND;
        *inc = 1;
    }
    else if (input[*i] == '<')
        *type = TOKEN_REDIRECT_IN;
    else if (input[*i] == '>')
        *type = TOKEN_REDIRECT_OUT;
}

// Assign operator token value
TokenNode *lexer_operator_value(TokenNode *tokens, int count, TokenType type)
{
    Token new_token;
    (void)count;
    new_token.type = type;
    new_token.value = NULL;
    tokens = append_token(tokens, new_token);
    if (!tokens)
        return (NULL);
    return (tokens);
}

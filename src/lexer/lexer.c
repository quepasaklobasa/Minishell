/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcouto <jcouto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:35:30 by jcouto            #+#    #+#             */
/*   Updated: 2025/05/27 16:43:00 by jcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Initialize token list
TokenNode *lexer_init(void)
{
    TokenNode *tokens;
    tokens = malloc(sizeof(TokenNode));
    if (!tokens)
        return (NULL);
    tokens->token.type = TOKEN_END;
    tokens->token.value = NULL;
    tokens->next = NULL;
    return (tokens);
}

// Handle operators (<, >, >>, |)
TokenNode *lexer_operator(char *input, int *i, int *count, TokenNode *tokens)
{
    TokenType type;
    int inc;
    type = TOKEN_END;
    inc = 0;
    lexer_operator_type(input, i, &type, &inc);
    tokens = lexer_operator_value(tokens, *count, type);
    if (!tokens)
        return (NULL);
    *count += 1;
    *i += inc;
    return (tokens);
}

// Handle single-quoted strings
TokenNode *lexer_single_quote(char *input, int *i, int *count, TokenNode *tokens)
{
    int start;
    start = *i + 1;
    while (input[*i] && input[*i] != '\'')
        (*i)++;
    if (!input[*i])
        return (free_tokens(tokens), NULL);
    tokens = lexer_word(input, &start, count, tokens);
    if (!tokens)
        return (NULL);
    (*i)++;
    return (tokens);
}

// Handle double-quoted strings
TokenNode *lexer_double_quote(char *input, int *i, int *count, TokenNode *tokens)
{
    int start;
    start = *i + 1;
    while (input[*i] && input[*i] != '"')
        (*i)++;
    if (!input[*i])
    {
        write(2, "minishell: syntax error: unclosed double quote\n", 46);
        free_tokens(tokens);
        return (NULL);
    }
    tokens = lexer_word(input, &start, count, tokens);
    if (!tokens)
        return (NULL);
    (*i)++;
    return (tokens);
}

// Main lexer function
TokenNode *lexer(char *input)
{
    int i;
    int count;
    TokenNode *tokens;
    i = 0;
    count = 0;
    tokens = NULL;
    while (input[i])
    {
        while (input[i] == ' ' || input[i] == '\t')
            i++;
        if (!input[i])
            break;
        tokens = lexer_process(input, &i, &count, tokens);
        if (!tokens)
            return (NULL);
    }
    if (count == 0)
    {
        tokens = lexer_init();
        return (tokens);
    }
    return (tokens);
}

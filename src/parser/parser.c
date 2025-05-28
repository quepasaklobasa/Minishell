/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcouto <jcouto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:19:50 by jcouto            #+#    #+#             */
/*   Updated: 2025/05/27 15:59:08 by jcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Consume a token of expected type
int consume(TokenType type)
{
    if (g_current_token && g_current_token->token.type == type)
    {
        g_current_token = g_current_token->next;
        return (1);
    }
    return (0);
}

// Allocate memory for args array
char **parse_args_alloc(int *arg_count)
{
    TokenNode *temp;
    char **args;
    temp = g_current_token;
    while (temp && (temp->token.type == TOKEN_WORD || temp->token.type == TOKEN_VARIABLE))
    {
        (*arg_count)++;
        temp = temp->next;
    }
    args = malloc((*arg_count + 1) * sizeof(char *));
    if (!args)
        return (NULL);
    return (args);
}

// Process arguments into array
char **parse_args_process(char **args, int *arg_count)
{
    int i;
    i = 0;
    while (g_current_token && (g_current_token->token.type == TOKEN_WORD || 
           g_current_token->token.type == TOKEN_VARIABLE))
    {
        args[i] = ft_strdup(g_current_token->token.value);
        if (!args[i])
        {
            while (i > 0)
                free(args[--i]);
            return (free(args), NULL);
        }
        i++;
        g_current_token = g_current_token->next;
    }
    args[i] = NULL;
    *arg_count = i;
    return (args);
}

// Parse arguments
char **parse_args(int *arg_count)
{
    char **args;
    *arg_count = 0;
    args = parse_args_alloc(arg_count);
    if (!args)
        return (NULL);
    args = parse_args_process(args, arg_count);
    return (args);
}

// Handle redirection type
int parse_redirection_type(Command *cmd, TokenType type)
{
    char *value;
    if (!g_current_token || (g_current_token->token.type != TOKEN_WORD && 
        g_current_token->token.type != TOKEN_VARIABLE))
        return (-1);
    value = ft_strdup(g_current_token->token.value);
    if (!value)
        return (-1);
    g_current_token = g_current_token->next;
    if (type == TOKEN_REDIRECT_IN)
        cmd->redirect_in = value;
    else if (type == TOKEN_REDIRECT_OUT)
        cmd->redirect_out = value;
    else if (type == TOKEN_REDIRECT_APPEND)
        cmd->redirect_append = value;
    else if (type == TOKEN_HEREDOC)
        cmd->heredoc_delim = value;
    return (0);
}

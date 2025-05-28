/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcouto <jcouto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:33:29 by jcouto            #+#    #+#             */
/*   Updated: 2025/05/26 19:33:57 by jcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Execute a single command
int execute_single_command(Command *cmd, t_context *ctx)
{
    int result;
    if (!cmd->cmd)
        return (0);
    setup_fds(cmd);
    if (is_builtin(cmd->cmd))
        result = exec_builtin(cmd, ctx);
    else
        result = exec_external(cmd, ctx);
    return (result);
}

// Execute command list
int execute_command_list(CommandList *cmd_list, t_context *ctx)
{
    CommandList *current;
    int result;
    current = cmd_list;
    while (current)
    {
        result = execute_single_command(current->cmd, ctx);
        if (result != 0)
            return (result);
        current = current->next;
    }
    return (ctx->exit_status);
}
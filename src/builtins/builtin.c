/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcouto <jcouto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:34:10 by jcouto            #+#    #+#             */
/*   Updated: 2025/05/26 19:38:20 by jcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int is_builtin(const char *cmd)
{
    if (!cmd)
        return (0);
    if (ft_strcmp(cmd, "echo") == 0)
        return (1);
    return (0);
}

// Execute built-in command
int exec_builtin(Command *cmd, t_context *ctx)
{
    int i;
    if (ft_strcmp(cmd->cmd, "echo") == 0)
    {
        i = 1;
        while (cmd->args[i])
        {
            write(cmd->out_fd, cmd->args[i], ft_strlen(cmd->args[i]));
            if (cmd->args[i + 1])
                write(cmd->out_fd, " ", 1);
            i++;
        }
        write(cmd->out_fd, "\n", 1);
        ctx->exit_status = 0;
        return (0);
    }
    return (1);
}

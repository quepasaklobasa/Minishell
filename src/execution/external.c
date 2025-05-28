/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcouto <jcouto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:36:08 by jcouto            #+#    #+#             */
/*   Updated: 2025/05/27 16:41:16 by jcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Get path for external command
char *get_command_path(const char *cmd)
{
    char *path;
    path = ft_strjoin("/bin/", cmd);
    if (!path)
           return (NULL);
    return (path);
}

// Execute external command
int exec_external(Command *cmd, t_context *ctx)
{
    char *path;
    pid_t pid;
    int status;
    path = get_command_path(cmd->cmd);
    if (!path)
    {
        ctx->exit_status = 1;
        return (1);
    }
    pid = fork();
    if (pid == 0)
    {
        execve(path, cmd->args, ctx->env);
        write(2, "minishell: command not found\n", 29);
        exit(127);
    }
    else if (pid > 0)
    {
        cmd->pid = pid;
        waitpid(pid, &status, 0);
        ctx->exit_status = WEXITSTATUS(status);
    }
    else
    {
        write(2, "minishell: fork: cannot create process\n", 38);
        ctx->exit_status = 1;
    }
    free(path);
    return (ctx->exit_status);
}

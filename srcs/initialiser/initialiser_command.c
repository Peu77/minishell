#include "../../includes/minishell.h"

char *find_command_in_path(const char *command)
{
    char *env_path;
    char **paths;
    char *full_path;
    int i = 0;

    env_path = getenv("PATH");
    if (!env_path)
    {
        printf("No PATH environment variable found.\n");
        return NULL;
    }
    paths = ft_split(env_path, ':');
    if (!paths)
    {
        printf("Error splitting PATH.\n");
        return NULL;
    }
    while (paths[i])
    {
        full_path = malloc(ft_strlen(paths[i]) + ft_strlen(command) + 2);
        if (!full_path)
        {
            printf("Memory allocation error.\n");
            return NULL;
        }
        strcpy(full_path, paths[i]);
        strcat(full_path, "/");
        strcat(full_path, command);
        if (access(full_path, F_OK) == 0) 
        {
            free(paths);
            return full_path;
        }
        free(full_path); 
        i++;
    }
    free(paths);
    return NULL;
}

static int get_path(t_command **command)
{
    t_command *head;
    char **path;
	char *found_path;
    head = (*command);
    while ((*command))
    {
        path = ft_split((*command)->argument, ' ');
        if (!path)
            return 0;
		((*command)->command_name) = path[0];
        found_path = find_command_in_path((*command)->command_name);
        if (found_path)
        {
            (*command)->path = found_path;
            printf("Command '%s' found at: %s\n", path[0], found_path);
        }
        else
        {
            (*command)->path = NULL;
            printf("Command '%s' not found in PATH.\n", path[0]);
        }
		(*command)->redirection_token = NULL;
		(*command)->redirection = NULL;
        (*command) = (*command)->next;
        free(path);
    }
    (*command) = head;
	return (1);
}

static int create_command_list(char *user_prompt, t_command **command, char **envp)
{
    char **command_split;
    t_command *new_node;
    int i = 0;

    if (!user_prompt || !command)
        return 0;
    command_split = ft_split(user_prompt, '|');
    if (!command_split)
    {
        perror("Failed to split user prompt");
        return 0;
    }
    while (command_split[i])
    {
        if (command_split[i][0] != '\0')
        {
            new_node = create_node(command_split[i], envp);
            if (!new_node)
            {
                perror("Failed to create command node");
                free_command_split(command_split);
                return 0;
            }
            add_node_back(command, new_node);
        }
        i++;
    }
    free_command_split(command_split);
	return (1);
}

int initialise_command(t_command **command, char *user_prompt, char **envp)
{
	if(!create_command_list(user_prompt, command, envp))
		return (0);
	if(!get_path(command))
		return (0);
	
	return (1);
}



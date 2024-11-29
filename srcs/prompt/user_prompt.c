#include "../../includes/minishell.h"

void get_user_prompt(char **user_prompt)
{
{
    size_t len = 0;
    ssize_t nread;

        printf(">>>> Minishell>$ ");
        nread = getline(user_prompt, &len, stdin);
        if (nread == -1)
            pe("Problem with getting line");
        if ((*user_prompt)[nread - 1] == '\n')
            (*user_prompt)[nread - 1] = '\0';
        printf("You entered: %s\n", *user_prompt);
    }
}

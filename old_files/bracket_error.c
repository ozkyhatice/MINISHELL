#include "../include/minishell.h"

int bracket_counter(const char *str, char c)
{
    int i;
    int counter;

    i = 0;
    counter = 0;
    while (str[i] != '\0')
    {
        if(str[i] == c)
            counter++;
        i++;
    }
    return (counter);
}

void control_bracket(const char *str)
{
    int r_bracket;
    int l_bracket;
    int i;

    i = 0;
    r_bracket = bracket_counter(str, ')');
    l_bracket = bracket_counter(str, '(');
    if (r_bracket > l_bracket)
    {
       printf("r>l bracket!\n");
        return ;
    }
    while (str[i] != '(')
    {
        if (str[i] == ')')
        {
            printf("syntax error near unexpected token `)'\n");
            return ;
        }
        i++;
    }
    i = 0;
    while(str[i] != '\0' && str[i+1] != '\0')
    {
        if(str[i] == '(' && str[i+1] == ')')
           printf("errorrr ()\n");
        else if(str[i] == ')' && str[i+1] == '(')
            printf("errorrr )(\n");;
        i++;
    }
}
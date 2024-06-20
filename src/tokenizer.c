#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>

/* Return true (non-zero) if c is a whitespace character ('\t' or ' '). */
int space_char(char c)
{
    return c == ' ' || c == '\t';
}

/* Return true (non-zero) if c is a non-whitespace character (not tab or space). */
int non_space_char(char c)
{
    return !space_char(c) && c != '\0';
}

/* Returns a pointer to the first character of the next space-separated token in zero-terminated str.
   Return a zero pointer if str does not contain any tokens. */
char *token_start(char *str)
{
start_token_start:
    if (non_space_char(*str))
    {
        return str;
    }
    else
    {
        if (*str == '\0')
        {
            return 0; // No more tokens
        }
        str++;
        goto start_token_start;
    }
}

/* Returns a pointer to the character following *token that is a space or terminator character. */
char *token_terminator(char *token)
{
start_token_terminator:
    if (space_char(*token) || *token == '\0')
    {
        return token;
    }
    else
    {
        token++;
        goto start_token_terminator;
    }
}

/* Counts the number of tokens in the string argument. */
int count_tokens(char *str)
{
    int count = 0;
start_count_tokens:
    if (*str == '\0')
    {
        return count; // End of string
    }
    str = token_start(str);
    if (str != 0)
    {
        count++;
    }
    str = token_terminator(str);
    goto start_count_tokens;
}

/* Returns a freshly allocated new zero-terminated string containing <len> chars from <inStr>. */
char *copy_str(char *inStr, short len)
{
    char *newstr = (char *)malloc(sizeof(char) * (len + 1));
    int i = 0;
start_copy_str:
    if (i >= len)
    {
        newstr[len] = '\0'; // 0-terminate the string
        return newstr;
    }
    newstr[i] = inStr[i];
    i++;
    goto start_copy_str;
}

/* Returns a freshly allocated zero-terminated vector of freshly allocated space-separated tokens from zero-terminated str. */
char **tokenize(char *str)
{
    int numtokens = count_tokens(str);
    char **tokens = (char **)malloc(sizeof(char *) * (numtokens + 1));
    int i = 0, strsize = 0;
start_tokenize:
    if (i >= numtokens)
    {
        tokens[numtokens] = 0; // 0-terminate the token array
        return tokens;
    }
    str = token_start(str);
    strsize = token_terminator(str) - str;
    tokens[i] = copy_str(str, strsize);
    str = token_start(str + strsize);
    i++;
    goto start_tokenize;
}

/* Prints all tokens. */
void print_tokens(char **tokens)
{
    int i = 0;
start_print_tokens:
    if (tokens[i] == 0)
    {
        return; // End of token array
    }
    printf("%s\n", tokens[i]);
    i++;
    goto start_print_tokens;
}

/* Frees all tokens and the vector containing them. */
void free_tokens(char **tokens)
{
    int i = 0;
start_free_tokens:
    if (tokens == 0)
    {
        free(tokens); // Free the token array itself
        return;
    }
    if (tokens[i])
        free(tokens[i]);

    i++;
    goto start_free_tokens;
}

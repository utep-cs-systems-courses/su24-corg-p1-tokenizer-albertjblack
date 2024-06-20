#include <stdio.h>
#include "tokenizer.h"
#include "history.h"

#define STRING_MAX_LEN 256

char get_menu_selection();
void clear_input_buffer();
int get_id_from_input(char *input);

int main(int argc, char **argv)
{

    char option;
    List *myList = init_history();
start:
    option = get_menu_selection();
    switch (option)
    {
    case 'a':
        printf("Enter a string to tokenize: (max_length=%d)\n> ", STRING_MAX_LEN);
        char string[STRING_MAX_LEN];
        clear_input_buffer();
        fgets(string, STRING_MAX_LEN, stdin);
        add_history(myList, string);

        char **vec = tokenize(string);
        print_tokens(vec);
        break;
    case 'b':
        print_history(myList);
        break;
    case 'c':
        printf("Enter the id you want to retrieve (ex: !3 retrieves id 3): ");
        char tmp_input[STRING_MAX_LEN];
        scanf("%s", tmp_input);
        int tmp_id = get_id_from_input(tmp_input);
        char *specific_hist = get_history(myList, tmp_id);
        printf("%d: %s\n", tmp_id, specific_hist);
        break;
    default:
        free_tokens(vec);
        free_history(myList);
        goto end;
    }
    goto start;
end:
    return 0;
}

char get_menu_selection()
{
    char option;

menu:
    printf("Please select an option:\n");
    printf("%c) Tokenize\n", 'a');
    printf("%c) Get Entire History\n", 'b');
    printf("%c) Get Item-specific History\n", 'c');
    printf("%c) Quit\n", 'q');
    printf("> ");
    scanf(" %c", &option);

    if (option != 'a' && option != 'b' && option != 'c' && option != 'q')
    {
        printf("Invalid option, please try again.\n");
        goto menu;
    }
    else
    {
        return option;
    }
}

void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int get_id_from_input(char *input)
{
    while (*input != '\0')
    {
        if (*input == '!')
        {
            input++; // Move past '!'
            int id = 0;
            while (*input >= '0' && *input <= '9')
            {
                id = id * 10 + (*input - '0');
                input++;
            }
            return id;
        }
        input++;
    }
    return -1; // Return -1 if no '!' is found
}
#include <stdio.h>
#include <stdlib.h>
#include "history.h"

/* Initialize the linked list to keep the history. */
List *init_history()
{
    List *list = (List *)malloc(sizeof(List));
    list->root = NULL;
    return list;
}

/* Get the length of a string */
int get_str_leng(char *str)
{
    int count = 0;
    while (str[count] != '\0')
    {
        count++;
    }
    return count;
}

/* Copy a string */
char *copy_line(char *inStr, int size)
{
    int str_len = get_str_leng(inStr);
    char *newstr = (char *)malloc(sizeof(char) * (str_len + 1));
    for (int i = 0; i < str_len; i++)
    {
        newstr[i] = inStr[i];
    }
    newstr[str_len] = '\0'; // Correct termination
    return newstr;
}

/* Add a history item to the end of the list */
void add_history(List *list, char *str)
{
    if (list == NULL)
    {
        printf("List not initialized.\n");
        return;
    }
    if (list->root == NULL)
    {
        list->root = (Item *)malloc(sizeof(Item));
        if (list->root == NULL)
        {
            perror("Failed to allocate memory for history item");
            exit(EXIT_FAILURE);
        }
        list->root->id = 0;
        list->root->next = NULL;
        list->root->str = copy_line(str, get_str_leng(str));
    }
    else
    {
        Item *curr = list->root;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        Item *tmp = (Item *)malloc(sizeof(Item));
        tmp->id = curr->id + 1;
        tmp->next = NULL;
        tmp->str = copy_line(str, get_str_leng(str));
        curr->next = tmp;
    }
}

/* Retrieve the string stored in the node where Item->id == id */
char *get_history(List *list, int id)
{
    if (list == NULL || list->root == NULL)
    {
        printf("Empty list. Please type.\n");
        return NULL;
    }
    Item *curr = list->root;
    while (curr != NULL && curr->id != id)
    {
        curr = curr->next;
    }
    if (curr == NULL)
    {
        printf("Id does not exist.\n");
        return NULL;
    }
    else
    {
        return curr->str;
    }
}

/* Print the entire contents of the list */
void print_history(List *list)
{
    if (list == NULL || list->root == NULL)
    {
        printf("Empty list. Please type.\n");
        return;
    }
    Item *curr = list->root;
    while (curr != NULL)
    {
        printf("%s\n", curr->str);
        curr = curr->next;
    }
}

/* Free the history list and the strings it references */
void free_history(List *list)
{
    if (list == NULL || list->root == NULL)
    {
        printf("Empty list. Nothing to free.\n");
        return;
    }
    Item *curr = list->root;
    while (curr != NULL)
    {
        Item *tmp = curr->next;
        free(curr->str);
        free(curr);
        curr = tmp;
    }
    free(list);
}

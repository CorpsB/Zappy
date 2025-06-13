/*
** EPITECH PROJECT, 2025
** B-NWP-400-STG-4-1-myftp-noe.carabin
** File description:
** str_to_array2
*/

#include "include/include.h"

static int memory_size(char *str, char separator)
{
    int count = 1;

    if (!str)
        return 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] == separator)
            count++;
    }
    return count;
}

static char **allocate_result(int count)
{
    char **result = malloc((count + 1) * sizeof(char *));

    if (!result)
        return NULL;
    result[count] = NULL;
    return result;
}

static int fill_result(char **result, char *str, char *separator)
{
    char *temp = strdup(str);
    int index = 0;
    char *token;

    if (!temp)
        return 0;
    token = strtok(temp, separator);
    while (token) {
        result[index] = strdup(token);
        if (!result[index]) {
            free(temp);
            return 0;
        }
        index++;
        token = strtok(NULL, separator);
    }
    free(temp);
    return 1;
}

char **str_to_array(char *str, char *separator)
{
    int count = memory_size(str, separator[0]);
    char **result = allocate_result(count);

    if (!str)
        return NULL;
    if (!result)
        return NULL;
    if (!fill_result(result, str, separator)) {
        for (int i = 0; result[i]; i++)
            free(result[i]);
        free(result);
        return NULL;
    }
    return result;
}

void free_table(char **table)
{
    if (!table)
        return;
    for (int i = 0; table[i] != NULL; i++)
        free(table[i]);
    free(table);
}

void remove_newline(char *str)
{
    size_t len = strlen(str);

    if (!str)
        return;
    if (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r'))
        str[len - 1] = '\0';
    if (len > 1 && (str[len - 2] == '\r'))
        str[len - 2] = '\0';
}
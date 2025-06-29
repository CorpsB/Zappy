/*
** EPITECH PROJECT, 2025
** B-NWP-400-STG-4-1-myftp-noe.carabin
** File description:
** str_to_array2
*/

#include "include/include.h"

/**
 * @brief Count the number of tokens in a string based on a separator.
 * @param str The input string to analyze.
 * @param separator The character used as a separator.
 * @return The number of tokens in the string.
*/
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

/**
 * @brief Allocate memory for a NULL-terminated array of strings.
 * @param count The number of elements to allocate.
 * @return A pointer to the allocated array, or NULL on failure.
*/
static char **allocate_result(int count)
{
    char **result = malloc((count + 1) * sizeof(char *));

    if (!result)
        return NULL;
    result[count] = NULL;
    return result;
}

/**
 * @brief Fill a string array with tokens extracted from a string.
 * @param result The array to fill.
 * @param str The source string to tokenize.
 * @param separator The separator used to split the string.
 * @return 1 on success, 0 on failure.
*/
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

int table_size(char **table)
{
    int i = 0;

    for (; table[i] != NULL; i++);
    return i;
}

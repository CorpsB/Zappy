/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** density_table
*/

#ifndef DENSITY_TABLE_H_
    #define DENSITY_TABLE_H_

typedef struct density_s {
    const char *name;
    float density;
    unsigned int repartition_value;
} density_t;

extern const density_t density_table[];

#endif /* !DENSITY_TABLE_H_ */

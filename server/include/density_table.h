/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** density_table
*/

/**
 * @file density_table.h
 * @brief Defines resource spawn densities for the Zappy server
 * map generation logic.
 * @author Noé Carabin
 * @version 1.0
 * @date 2025-06
 * @details
 * This file declares the structure describing a resource's spawn density
 * and its repartition value. The constant array defines the parameters
 * used to control how resources are distributed across the game map.
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

/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** include
*/

/**
 * @file include.h
 * @brief Central header regrouping all required includes for the Zappy
 * server project compilation units.
 * @author Noé Carabin
 * @version 1.0
 * @date 2025-06
 * @details
 * This file contains all necessary standard and system includes
 * used throughout
 * the project. It simplifies the inclusion process for source files and
 * ensures consistency in dependencies.
*/

#ifndef INCLUDE_H_
    #define INCLUDE_H_

    #define _GNU_SOURCE
    #define _POSIX_C_SOURCE 199309L
    //All the poll and server include needed by the project
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <string.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <poll.h>
    #include <math.h>
    #include <errno.h>

    //Write include
    #include <unistd.h>
    #include <string.h>

    //bool
    #include <stdbool.h>

    #include <stdlib.h>
    //printf
    #include <stdio.h>
    //time -> srand -> random
    #include <time.h>

    //log (open, perm, ...)
    #include <fcntl.h>    // pour open() et les flags O_*
    #include <sys/types.h> // recommandé pour certains types comme mode_t
    #include <sys/stat.h>  // pour les permissions (ex: 0644)
    #include <unistd.h>    // pour close(), write(), etc.

    #include <limits.h>
    #include <ctype.h>
    #include <time.h>
    #include <sys/types.h> // parfois nécessaire selon la plateforme
    #include <sys/time.h>


#endif /* !INCLUDE_H_ */

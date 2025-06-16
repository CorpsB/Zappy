/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** include
*/

#ifndef INCLUDE_H_
    #define INCLUDE_H_

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

#endif /* !INCLUDE_H_ */

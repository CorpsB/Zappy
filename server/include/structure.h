/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** structure
*/

#ifndef STRUCTURE_H_
    #define STRUCTURE_H_

/**
 * @file structure.h
 * @brief Core data structures for the Zappy server project.
 *
 * This file defines all primary types and structures used throughout
 * the Zappy server implementation, including the server controller,
 * players, teams, map resources, and egg management.
 *
 * It also declares the direction enumeration used to manage
 * player orientation on the map.
 *
 * @author
 * Noé Carabin
 *
 * @date
 * 2025
 *
 * @version
 * 1.0
 *
 * @defgroup Structures
 * @{
 * @struct server_t     Represents the global server configuration and world
 * state.
 * @struct resources_t  Represents the resources stored on a tile or in a
 * player's inventory.
 * @struct teams_t      Represents a team in the game, along with its players
 * and eggs.
 * @struct player_t     Represents a player, their position, direction,
 * inventory and socket.
 * @struct eggs_t       Represents an egg laid by a player for future
 * connections.
 * @enum direction_t    Represents the cardinal direction a player is facing.
 * @}
 *
 * @see server_t
 * @see player_t
 * @see teams_t
 * @see eggs_t
 * @see resources_t
 * @see direction_t
 */

    #include "include.h"

// Forward declarations
typedef struct server server_t;
typedef struct resources resources_t;
typedef struct teams teams_t;
typedef struct player player_t;
typedef struct eggs eggs_t;
typedef struct client client_t;
typedef struct poll poll_t;

/**
 * @enum direction_t
 * @brief Represents the direction a player is facing on the map.
 *
 * The direction determines the player's orientation, which is
 * used for movement and field of vision.
 *
 * These values match the protocol specifications:
 * - NORTH = 1
 * - EAST = 2
 * - SOUTH = 3
 * - WEST = 4
 */
typedef enum direction {
    NORTH = 1, /**< Facing up on the map (north). */
    EAST = 2,  /**< Facing right on the map (east). */
    SOUTH = 3, /**< Facing down on the map (south). */
    WEST = 4   /**< Facing left on the map (west). */
} direction_t;

typedef enum whoAmI {
    PLAYER,
    GUI,
    LISTEN
} whoAmI_t;

struct poll {
    int socket;
    struct sockaddr_in sockaddr;
    int client_index;
    struct pollfd *pollfds;
    client_t *client_list;
};

/**
 * @struct server_t
 * @brief Represents the global configuration and state of the Zappy
 * server.
 *
 * The server structure stores configuration parameters such as map size,
 * maximum allowed connections per team, and frequency of game ticks.
 * It also maintains the game world state, including the map of resources
 * and the list of teams (which in turn contain players and eggs).
 */
struct server {
    /// Maximum number of players per team (including pending eggs).
    unsigned int max_connections_per_team;
    /// Number of game ticks per second. Used to control action timing.
    unsigned int frequency;
    /// TCP port used to listen for incoming client connections.
    unsigned int port;
    /// Width of the game map in number of tiles.
    unsigned int width;
    /// Height of the game map in number of tiles.
    unsigned int height;

    /// Total number of eggs present in the game world.
    unsigned int eggs_count;
    /// Total number of active players currently in the game.
    unsigned int player_count;
    /// Total number of active teams currently in the game.
    unsigned int teams_count;

    /// Enables or disables debug mode. When true, logs are written to a file.
    bool debug;
    /// File descriptor used to write debug logs when debug mode is enabled.
    int debug_fd;

    poll_t poll;

    /// 2D array representing the game map, each tile containing resources.
    resources_t **map;
    /// Linked list of all teams participating in the game.
    teams_t *teams;
};

/**
 * @struct resources_t
 * @brief Represents a collection of resources on a map tile or in a
 * player's inventory.
 *
 * Each type of resource is used for different game mechanics such as survival,
 * elevation (leveling up), and crafting. This structure can be used both for
 * map tiles and for players' inventories.
 */
struct resources {
    /// Used to survive; consumed periodically to prevent death.
    unsigned int food;
    /// Required for player elevation (leveling).
    unsigned int linemate;
    /// Required for player elevation.
    unsigned int deraumere;
    /// Required for player elevation.
    unsigned int sibur;
    /// Required for player elevation.
    unsigned int mendiane;
    /// Required for player elevation.
    unsigned int phiras;
    /// Required for the final level (level 8 elevation).
    unsigned int thystame;
};


/**
 * @struct teams_t
 * @brief Represents a team in the Zappy game, including its players and eggs.
 *
 * Each team has a unique name and ID, and maintains lists of its current
 * players and laid eggs. The number of used slots reflects how many player
 * connections
 * (including unhatched eggs) are currently active for this team.
 */
struct teams {
    /// Name of the team (as received in the server's arguments).
    char *name;
    /// Unique identifier for the team.
    int id;

    /// Number of currently used slots (players + unhatched eggs).
    int slots_used;

    /// Whether this team has achieved victory (level 8 incantation).
    bool win;
    /// Whether this team has lost (no players or eggs remaining).
    bool eliminated;

    /// Linked list of the team's unhatched eggs.
    eggs_t *egg;
    /// Linked list of the team's active players.
    player_t *player;

    /// Pointer to the next team in the linked list.
    struct teams *next;
};

/**
 * @struct player_t
 * @brief Represents a connected player in the Zappy world.
 *
 * Each player is tied to a specific team and has a position on the map,
 * an inventory of resources, a direction, and a level. Players consume
 * food over time and can perform various actions such as movement,
 * incantations, and resource collection.
 */
struct player {
    /// Unique identifier for the player (often sequentially assigned).
    unsigned int id;

    /// Position of the player on the map, as [x, y] coordinates.
    unsigned int position[2];
    /// Current level of the player (starts at 1, max is 8).
    unsigned int lvl;
    /// Remaining cycles before the player dies without eating.
    unsigned int cycle_before_death;

    /// Orientation of the player on the map (NORTH, EAST, SOUTH, WEST).
    direction_t direction;
    /// File descriptor of the player's TCP connection.
    int socket_fd;
    /// Pointer to the team this player belongs to.
    teams_t *team;
    /// Player's personal inventory of resources.
    resources_t inventory;

    /// Pointer to the next player in the linked list (same team).
    struct player *next;
};

/**
 * @struct eggs_t
 * @brief Represents an egg laid by a player, used for future player spawns.
 *
 * Eggs are created when a player uses the `Fork` command. Each egg corresponds
 * to a future player connection (until it hatches). The egg is associated with
 * the team that laid it, and remains inactive until a client connects using
 * that team name.
 */
struct eggs {
    /// Unique identifier for the egg.
    unsigned int id;
    /// ID of the player who laid the egg (used for logging/debug).
    unsigned int creator_id;
    /// Position of the egg on the map, as [x, y] coordinates.
    unsigned int position[2];

    /// Pointer to the next egg in the team's linked list.
    struct eggs *next;
};

struct client {
    player_t *player;
    whoAmI_t whoAmI;
};

#endif /* !STRUCTURE_H_ */

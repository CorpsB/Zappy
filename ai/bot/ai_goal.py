##
## EPITECH PROJECT, 2025
## B-YEP-400-STG-4-1-zappy-noe.carabin
## File description:
## ai_goal
##

import ai_moves as am
from helper import find_item as fi
from .. import ai_print as ap
from ..network import ai_socket as aso

ELEVATION_RECIPES = [
    {'player': 1, 'linemate': 1, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0},
    {'player': 2, 'linemate': 1, 'deraumere': 1, 'sibur': 1, 'mendiane': 0, 'phiras': 0, 'thystame': 0},
    {'player': 2, 'linemate': 2, 'deraumere': 0, 'sibur': 1, 'mendiane': 0, 'phiras': 2, 'thystame': 0},
    {'player': 4, 'linemate': 1, 'deraumere': 1, 'sibur': 2, 'mendiane': 0, 'phiras': 1, 'thystame': 0},
    {'player': 4, 'linemate': 1, 'deraumere': 2, 'sibur': 1, 'mendiane': 3, 'phiras': 0, 'thystame': 0},
    {'player': 6, 'linemate': 1, 'deraumere': 2, 'sibur': 3, 'mendiane': 0, 'phiras': 1, 'thystame': 0},
    {'player': 6, 'linemate': 2, 'deraumere': 2, 'sibur': 2, 'mendiane': 2, 'phiras': 2, 'thystame': 1},
]

def has_enough_rock(level, inventory, rock):
    """Determines if the bot's has enough of one precise rock."""

    return inventory.get(rock, 0) >= ELEVATION_RECIPES[level - 1][rock]

def has_enough_rocks(level, inventory):
    """Determines if the bot's has all the rocks required to level up."""

    if (has_enough_rock(level, inventory, 'linemate') and
    has_enough_rock(level, inventory, 'deraumere') and
    has_enough_rock(level, inventory, 'sibur') and
    has_enough_rock(level, inventory, 'mendiane') and
    has_enough_rock(level, inventory, 'phiras') and
    has_enough_rock(level, inventory, 'thystame')):
        return True
    return False

def determine_rarest_missing_stone(level, inventory):
    """Determines the bot's next stone to gather. Since rarest stones are the most hard to find, we search them in priority."""

    if not has_enough_rock(level, inventory, 'thystame'):
        return 'thystame'
    if not has_enough_rock(level, inventory, 'phiras'):
        return 'phiras'
    if not has_enough_rock(level, inventory, 'mendiane'):
        return 'mendiane'
    if not has_enough_rock(level, inventory, 'sibur'):
        return 'sibur'
    if not has_enough_rock(level, inventory, 'deraumere'):
        return 'deraumere'
    return 'linemate'

def determine_goal(level, food_level, inventory, last_heard_meetup_k):
    """Determines the bot's next goal based on its state."""

    if food_level < 6.0: #FOOD_THRESHOLD = 6.0
        return 'FOOD'
    if level == 8:
        return 'WANDER'
    if has_enough_rocks(level, inventory) and last_heard_meetup_k != -1:
        return 'MEETUP'
    return 'GATHER'

def handle_goal(goal, sock, reader, look_str, bot_spiral_state, thread_name):
    """
    Attempts to find and take a resource. If the resource not seen, executes a spiral move.
    Uses and potentially updates bot_spiral_state.
    Returns True if action was successful, False otherwise.
    """
    res_tile_idx = fi.find_item_in_look(look_str, goal, thread_name)

    if res_tile_idx == 0:
        ap.safe_print(f"[{thread_name}] {goal} on current tile. Taking.")
        return aso.do_action(sock, reader, f"Take {goal}", thread_name) != "dead"
    elif res_tile_idx > 0:
        moves = am.get_moves_to_tile_level1_vision(res_tile_idx)
        if moves:
            ap.safe_print(f"[{thread_name}] {goal} on tile {res_tile_idx}. Moving to take.")
            if not am.execute_moves(sock, reader, moves, thread_name):
                return False
            return aso.do_action(sock, reader, f"Take {goal}", thread_name) != "dead"
        else:
            ap.safe_print(f"[{thread_name}] {goal} at tile {res_tile_idx}, path complex or too far for simple moves. Defaulting to spiral.")
            return am.execute_spiral_move(sock, reader, bot_spiral_state, thread_name)
    else:
        if "CRITICAL" in look_str and "PARSE ERROR" in look_str:
            ap.safe_print(f"[{thread_name}] Halting {goal} goal due to look parse error.")
            return False
        ap.safe_print(f"[{thread_name}] {goal} not seen. Executing spiral move.")
        return am.execute_spiral_move(sock, reader, bot_spiral_state, thread_name)

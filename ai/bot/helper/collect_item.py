##
## EPITECH PROJECT, 2025
## B-YEP-400-STG-4-1-zappy-noe.carabin
## File description:
## collect_item
##

from . import find_item as fi
from ...network import ai_socket as aso

def collect_item(look_string, item_name, sock, reader, food_level, inventory, level,
    recipes, thread_name = "UnknownThread"):
    """Take an item if founded on current tile and not too present in inventory."""

    if fi.find_item_in_look(look_string, item_name, thread_name) == 0:
        if ((item_name == 'food' and food_level >= 12.0) or level == 8 or (item_name != 'food' and
        inventory.get(item_name, 0) >= recipes[level - 1][item_name] * 2 + 1)):
            return True
        return aso.do_action(sock, reader, f"Take {item_name}", thread_name) != "dead"
    return True

def collect_all_items(look_string, sock, reader, food_level, inventory, level, recipes, thread_name = "UnknownThread"):
    """Try to take all the items on the current tile."""

    return (collect_item(look_string, 'food', sock, reader, food_level, inventory, level, recipes, thread_name) and
    collect_item(look_string, 'linemate', sock, reader, food_level, inventory, level, recipes, thread_name) and
    collect_item(look_string, 'deraumere', sock, reader, food_level, inventory, level, recipes, thread_name) and
    collect_item(look_string, 'sibur', sock, reader, food_level, inventory, level, recipes, thread_name) and
    collect_item(look_string, 'mendiane', sock, reader, food_level, inventory, level, recipes, thread_name) and
    collect_item(look_string, 'phiras', sock, reader, food_level, inventory, level, recipes, thread_name) and
    collect_item(look_string, 'thystame', sock, reader, food_level, inventory, level, recipes, thread_name))

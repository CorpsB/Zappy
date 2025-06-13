##
## EPITECH PROJECT, 2025
## B-YEP-400-STG-4-1-zappy-noe.carabin
## File description:
## ai_elevate
##

import time
from ..network import ai_socket as aso
from .. import ai_print as ap

def set_stones_for_incantation(sock, reader, inventory, level, recipes, thread_name):
    """Sets the required stones on the tile for incantation."""
    stones_to_set = []

    for stone, req_qty in recipes[level - 1].items():
        if stone == 'player' or req_qty == 0:
            continue
        if inventory.get(stone, 0) < req_qty:
            return False
        for _ in range(req_qty):
            stones_to_set.append(stone)
    for stone_to_set in stones_to_set:
        if aso.do_action(sock, reader, f"Set {stone_to_set}", thread_name) == "dead":
            ap.safe_print(f"[{thread_name}] Failed to set {stone_to_set} during L{level} prep.")
            return False
        time.sleep(0.1)
    return True

def launch_incantation(sock, reader, level, inventory, recipes, thread_name):
    """Attempts incantation process after ensuring players and stones."""

    ap.safe_print(f"[{thread_name}] Attempting L{level + 1} Incantation.")
    if not set_stones_for_incantation(sock, reader, inventory, level, recipes, thread_name):
        ap.safe_print(f"[{thread_name}] L{level + 1} stone setting phase failed.")
        return False
    time.sleep(0.2)

    if not aso.send_command(sock, "Incantation", thread_name):
        return False
    response_elev = reader.receive_line(level)
    if response_elev == "dead":
        return False

    if "Elevation underway" in response_elev:
        response_level = reader.receive_line(level, timeout = 350.0)
        if response_level == "dead":
            return False
        if f"Current level: {level + 1}" in response_level:
            ap.safe_print(f"[{thread_name}] L{level + 1} ELEVATION SUCCESS! Now Level {level + 1}.")
            return True
        else:
            ap.safe_print(f"[{thread_name}] L{level + 1} Elevation failed or unexpected response: {response_level}.")
    else:
        ap.safe_print(f"[{thread_name}] L{level + 1} Incantation start failed: {response_elev}.")
    return False

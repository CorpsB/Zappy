##
## EPITECH PROJECT, 2025
## B-YEP-400-STG-4-1-zappy-noe.carabin
## File description:
## ai_moves
##

import time
from ..network import ai_socket as aso
from .. import ai_print as ap
from .. import ai_threads as at

ACTION_DELAY = 0.2

def get_moves_to_tile_level1_vision(tile_index):
    """Returns a basic move list for level 1 vision (tiles 0-3)."""

    match tile_index:
        case 0:
            return []
        case 1:
            return ["Forward", "Left", "Forward"]
        case 2:
            return ["Forward"]
        case 3:
            return ["Forward", "Right", "Forward"]
        case _:
            return None

def get_moves_towards_sound_direction(k_direction):
    """
    Generates a list of moves towards a sound direction K.
    K is relative to player's current facing.
    K=0: current tile, K=1: front, K=2: front-left, ..., K=8: front-right.
    """

    match k_direction:
        case 0:
            return []
        case 1:
            return ["Forward"]
        case 2:
            return ["Forward", "Left", "Forward"]
        case 3:
            return ["Left", "Forward"]
        case 4:
            return ["Left", "Left", "Forward"]
        case 5:
            return ["Left", "Left", "Forward"]
        case 6:
            return ["Right", "Right", "Forward"]
        case 7:
            return ["Right", "Forward"]
        case 8:
            return ["Forward", "Right", "Forward"]
        case _:
            return ["Forward"]

def execute_moves(sock, reader, moves, thread_name):
    """Executes a list of moves, checking for 'dead' after each."""

    for move in moves:
        if at.EXIT_EVENT.is_set():
            return False
        response = aso.do_action(sock, reader, move, thread_name)
        if response == "dead":
            return False
        time.sleep(ACTION_DELAY)
    return True

def execute_spiral_move(sock, reader, bot_spiral_state, thread_name):
    """
    Executes the next step in a spiral pattern for food searching.
    Updates bot_spiral_state.
    Returns True if the action was successful (not "dead"), False otherwise.
    """
    action_to_take = ""

    if bot_spiral_state["leg_steps_taken"] < bot_spiral_state["leg_max_steps"]:
        action_to_take = "Forward"
        bot_spiral_state["leg_steps_taken"] += 1
    else:
        action_to_take = "Left"
        bot_spiral_state["leg_steps_taken"] = 0
        bot_spiral_state["legs_completed_at_current_length"] += 1

        if bot_spiral_state["legs_completed_at_current_length"] >= 2:
            bot_spiral_state["leg_max_steps"] += 1
            bot_spiral_state["legs_completed_at_current_length"] = 0

    ap.safe_print(f"[{thread_name}] Food Search Spiral: Action: {action_to_take}. State: {bot_spiral_state}")
    return aso.do_action(sock, reader, action_to_take, thread_name) != "dead"

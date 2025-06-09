##
## EPITECH PROJECT, 2025
## B-YEP-400-STG-4-1-zappy-noe.carabin
## File description:
## goal
##

def handle_food_goal(sock, reader, look_str, bot_spiral_state, thread_name):
    """
    Attempts to find and take food. If food not seen, executes a spiral move.
    Uses and potentially updates bot_spiral_state.
    Returns True if action was successful, False otherwise.
    """
    food_tile_idx = find_item_in_look(look_str, 'food', thread_name)

    if food_tile_idx == 0:
        safe_print(f"[{thread_name}] Food on current tile. Taking.")
        return do_action(sock, reader, "Take food", thread_name) != "dead"
    elif food_tile_idx > 0:
        moves = get_moves_to_tile_level1_vision(food_tile_idx)
        if moves:
            safe_print(f"[{thread_name}] Food on tile {food_tile_idx}. Moving to take.")
            if not execute_moves(sock, reader, moves, thread_name): return False
            return do_action(sock, reader, "Take food", thread_name) != "dead"
        else:
            safe_print(f"[{thread_name}] Food at tile {food_tile_idx}, path complex or too far for simple moves. Defaulting to spiral.")
            return _execute_spiral_move(sock, reader, bot_spiral_state, thread_name)
    else:
        if "CRITICAL" in look_str and "PARSE ERROR" in look_str :
            safe_print(f"[{thread_name}] Halting food goal due to look parse error.")
            return False
        safe_print(f"[{thread_name}] Food not seen. Executing spiral move.")
        return _execute_spiral_move(sock, reader, bot_spiral_state, thread_name)

def determine_bot_goal(level, food_level, current_goal, last_heard_meetup_k):
    """Determines the bot's next goal based on its state."""
    if food_level < FOOD_THRESHOLD:
        return 'FOOD'

    if current_goal == 'FOOD':
        if level == 1: return 'GATHER_L1_LINEMATE'
        if level == 2: return 'GATHER_L2_STONES'
        return 'WANDER'

    if level == 2 and last_heard_meetup_k != -1:
        if food_level >= FOOD_THRESHOLD:
            return 'MEETUP_L3'
        else:
            return 'FOOD'

    if current_goal == 'GATHER_L1_LINEMATE' and level > 1:
        safe_print(f"[{threading.current_thread().name}] Correcting L1 goal at Lvl {level}. Food: {food_level}.")
        if level == 2: return 'GATHER_L2_STONES'
        return 'WANDER'

    if (current_goal == 'GATHER_L2_STONES' or current_goal == 'MEETUP_L3') and level != 2 :
        safe_print(f"[{threading.current_thread().name}] Correcting L2/L3 goal at Lvl {level}. Food: {food_level}.")
        if level == 1: return 'GATHER_L1_LINEMATE'
        return 'WANDER'

    return current_goal

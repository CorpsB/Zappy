##
## EPITECH PROJECT, 2025
## B-YEP-400-STG-4-1-zappy-noe.carabin
## File description:
## moves
##

def get_moves_to_tile_level1_vision(tile_index):
    """Returns a basic move list for level 1 vision (tiles 0-3)."""
    if tile_index == 0: return []
    if tile_index == 1: return ["Forward", "Left", "Forward"]
    if tile_index == 2: return ["Forward"]
    if tile_index == 3: return ["Forward", "Right", "Forward"]
    return None

def get_moves_towards_sound_direction(k_direction):
    """
    Generates a list of moves towards a sound direction K.
    K is relative to player's current facing.
    K=0: current tile, K=1: front, K=2: front-left, ..., K=8: front-right.
    """
    if k_direction == 0: return []
    if k_direction == 1: return ["Forward"]
    if k_direction == 2: return ["Forward", "Left", "Forward"]
    if k_direction == 3: return ["Left", "Forward"]
    if k_direction == 4: return ["Left", "Left", "Forward"]
    if k_direction == 5: return ["Left", "Left", "Forward"]
    if k_direction == 6: return ["Right", "Right", "Forward"]
    if k_direction == 7: return ["Right", "Forward"]
    if k_direction == 8: return ["Forward", "Right", "Forward"]
    return ["Forward"]

def execute_moves(sock, reader, moves, thread_name):
    """Executes a list of moves, checking for 'dead' after each."""
    for move in moves:
        if exit_event.is_set(): return False
        response = do_action(sock, reader, move, thread_name)
        if response == "dead": return False
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

    safe_print(f"[{thread_name}] Food Search Spiral: Action: {action_to_take}. State: {bot_spiral_state}")
    return do_action(sock, reader, action_to_take, thread_name) != "dead"

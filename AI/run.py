##
## EPITECH PROJECT, 2025
## B-YEP-400-STG-4-1-zappy-noe.carabin
## File description:
## run
##

def handle_starvation_check(food_level, thread_name):
    """Checks if the bot has starved."""
    if food_level == 0:
        safe_print(f"[{thread_name}] Died from starvation!")
        return False
    return True

def perform_wander_action(sock, reader, thread_name, preferred_moves=None):
    """Performs a wander action, either random or from a preferred list."""
    action = ""
    if preferred_moves and isinstance(preferred_moves, list) and len(preferred_moves) > 0:
        action = random.choice(preferred_moves)
    elif random.random() < WANDER_CHANCE:
        action = "Left"
    else:
        action = "Forward"
    safe_print(f"[{thread_name}] Wandering: {action}.")
    return do_action(sock, reader, action, thread_name) != "dead"

def run_ai_bot(team_name, host, port, bot_id):
    """Main lifecycle for a single AI bot."""
    thread_name = f"Bot-{bot_id}"
    threading.current_thread().name = thread_name
    safe_print(f"[{thread_name}] Starting...")

    client_socket, reader, connected = _initialize_bot_connection(team_name, host, port, thread_name)
    if not connected:
        trigger_exit(f"{thread_name} ConnectionFailed")
        return

    level = 1
    current_goal = 'FOOD'

    bot_spiral_state = {
        "leg_max_steps": 1,
        "leg_steps_taken": 0,
        "legs_completed_at_current_length": 0,
    }
    inventory = {} # Initialize inventory to prevent error in finally block if loop doesn't run

    try:
        while not exit_event.is_set():
            inventory, food_level = _get_inventory_and_food(client_socket, reader, thread_name)
            if inventory is None:
                if not exit_event.is_set(): trigger_exit(f"{thread_name} InvError")
                break

            if not _handle_starvation_check(food_level, thread_name):
                if not exit_event.is_set(): trigger_exit(f"{thread_name} Starvation")
                break

            last_k_for_decision = reader.last_heard_meetup_k
            reader.last_heard_meetup_k = -1

            current_goal = _determine_bot_goal(level, food_level, current_goal, last_k_for_decision)
            safe_print(f"[{thread_name}] Tick: Lvl:{level}, Food:{food_level}, Goal:{current_goal}, HeardK:{last_k_for_decision}, Inv:{inventory.get('linemate',0)}Li,{inventory.get('deraumere',0)}De,{inventory.get('sibur',0)}Si")

            look_str = do_action(client_socket, reader, "Look", thread_name)
            if look_str == "dead":
                if not exit_event.is_set(): trigger_exit(f"{thread_name} LookDead")
                break

            action_ok = True
            action_taken_this_turn = False

            if current_goal == 'FOOD':
                action_ok = _handle_food_goal(client_socket, reader, look_str, bot_spiral_state, thread_name)
                action_taken_this_turn = True
            elif current_goal == 'GATHER_L1_LINEMATE' and level == 1:
                new_level, action_ok = _handle_l1_gather_and_elevate(client_socket, reader, inventory, look_str, thread_name)
                if new_level > level:
                    level = new_level
                    current_goal = 'GATHER_L2_STONES'
                    bot_spiral_state = { "leg_max_steps": 1, "leg_steps_taken": 0, "legs_completed_at_current_length": 0 }
                action_taken_this_turn = True
            elif (current_goal == 'GATHER_L2_STONES' or current_goal == 'MEETUP_L3') and level == 2:
                new_level, new_goal, action_ok = _handle_l2_l3_logic(
                    client_socket, reader, inventory, look_str,
                    current_goal, last_k_for_decision, bot_id, thread_name
                )
                if new_level > level:
                    level = new_level
                    bot_spiral_state = { "leg_max_steps": 1, "leg_steps_taken": 0, "legs_completed_at_current_length": 0 }
                current_goal = new_goal
                action_taken_this_turn = True
            else:
                safe_print(f"[{thread_name}] No specific action for current goal '{current_goal}' (Lvl {level}). Wandering.")
                action_ok = _perform_wander_action(client_socket, reader, thread_name)
                action_taken_this_turn = True

            if not action_ok :
                if not exit_event.is_set():
                    safe_print(f"[{thread_name}] Action failed or led to 'dead' state. Terminating.")
                    trigger_exit(f"{thread_name} ActionFailure")
                break

            if exit_event.is_set(): break
            time.sleep(ACTION_DELAY)

    except Exception as e:
        safe_print(f"[{thread_name}] CRITICAL EXCEPTION in main loop: {e}")
        safe_print(traceback.format_exc())
        trigger_exit(f"{thread_name} UnhandledException")
    finally:
        if client_socket: client_socket.close()
        safe_print(f"[{thread_name}] Connection closed. Final state: Level {level}, Goal {current_goal}, Food {inventory.get('food', 'N/A')}.")

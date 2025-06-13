##
## EPITECH PROJECT, 2025
## B-YEP-400-STG-4-1-zappy-noe.carabin
## File description:
## run
##

import random
import threading
import time
import traceback
from . import ai_threads as at
from . import ai_print as ap
from .network import ai_socket as aso
from .network import ai_initialize as ain
from .bot import ai_goal as ag
from .bot import ai_inventory as aiv
from .bot import ai_moves as am
from .bot import ai_elevate as ae

def handle_starvation_check(food_level, thread_name):
    """Checks if the bot has starved."""

    if food_level == 0:
        ap.safe_print(f"[{thread_name}] Died from starvation!")
        return False
    return True

def perform_wander_action(sock, reader, thread_name, preferred_moves=None):
    """Performs a wander action, either random or from a preferred list."""
    action = ""

    if preferred_moves and isinstance(preferred_moves, list) and len(preferred_moves) > 0:
        action = random.choice(preferred_moves)
    elif random.random() < 0.3: # WANDER_CHANCE = 0.3
        action = "Left"
    else:
        action = "Forward"

    ap.safe_print(f"[{thread_name}] Wandering: {action}.")
    return aso.do_action(sock, reader, action, thread_name) != "dead"

def perform_action_goal(current_goal, level, food_level, inventory, client_socket, reader, look_str, bot_spiral_state, thread_name):
    """Perform an action based on the current goal."""

    if current_goal == 'FOOD':
        return ag.handle_goal('food', client_socket, reader, look_str, bot_spiral_state, thread_name, food_level, inventory, level, ag.ELEVATION_RECIPES)

    if current_goal == 'GATHER':
        rarest_missing_stone = ag.determine_rarest_missing_stone(level, inventory)
        return ag.handle_goal(rarest_missing_stone, client_socket, reader, look_str, bot_spiral_state, thread_name, food_level, inventory, level, ag.ELEVATION_RECIPES)

    if current_goal == 'EVOLVE':
        if aso.do_action(client_socket, reader, f"Broadcast EVOLVE_{level + 1}", thread_name) == "dead":
            return False
        player_dir = am.get_moves_towards_sound_direction(reader.last_heard_meetup_k)
        return am.execute_moves(look_str, client_socket, reader, food_level, inventory, level, ag.ELEVATION_RECIPES, player_dir, thread_name)

    if current_goal == 'MEETUP':
        ap.safe_print(f"[{thread_name}] Sending everyone a meetup request for level {level + 1}.")
        if aso.do_action(client_socket, reader, f"Broadcast MEETUP_{level + 1}", thread_name) == "dead":
            return False
        if reader.last_heard_player_k != -1:
            player_dir = am.get_moves_towards_sound_direction(reader.last_heard_player_k)
            return am.execute_moves(look_str, client_socket, reader, food_level, inventory, level, ag.ELEVATION_RECIPES, player_dir, thread_name)
        return ag.handle_goal('food', client_socket, reader, look_str, bot_spiral_state, thread_name, food_level, inventory, level, ag.ELEVATION_RECIPES)

    if current_goal == 'INCANT':
        return ae.launch_incantation(client_socket, reader, level, inventory, ag.ELEVATION_RECIPES, thread_name)

    ap.safe_print(f"[{thread_name}] No specific action for current goal '{current_goal}' (Lvl {level}). Wandering.")
    return perform_wander_action(client_socket, reader, thread_name)

def run_ai(team_name, host, port, bot_id):
    """Main lifecycle for a single AI bot."""
    thread_name = f"Bot-{bot_id}"
    threading.current_thread().name = thread_name
    ap.safe_print(f"[{thread_name}] Starting...")

    client_socket, reader, connected = ain.initialize_connection(team_name, host, port, thread_name)
    if not connected:
        at.trigger_exit(f"{thread_name} ConnectionFailed")
        return

    level = 1
    current_goal = 'FOOD'
    bot_spiral_state = {
        "leg_max_steps": 1,
        "leg_steps_taken": 0,
        "legs_completed_at_current_length": 0,
    }
    inventory = aiv.create_inventory() # Initialize inventory to prevent error in finally block if loop doesn't run

    try:
        while not at.EXIT_EVENT.is_set():
            inventory, food_level = aiv.get_inventory_and_food(client_socket, reader, thread_name)
            if inventory is None:
                if not at.EXIT_EVENT.is_set():
                    at.trigger_exit(f"{thread_name} InvError")
                break
            if not handle_starvation_check(food_level, thread_name):
                if not at.EXIT_EVENT.is_set():
                    at.trigger_exit(f"{thread_name} Starvation")
                break

            last_k_for_decision = reader.last_heard_meetup_k
            reader.last_heard_meetup_k = -1

            look_str = aso.do_action(client_socket, reader, "Look", thread_name)
            if look_str == "dead":
                if not at.EXIT_EVENT.is_set():
                    at.trigger_exit(f"{thread_name} LookDead")
                break

            current_goal = ag.determine_goal(level, food_level, inventory, last_k_for_decision, look_str, thread_name, ag.ELEVATION_RECIPES)
            ap.safe_print(f"[{thread_name}] Tick: Lvl:{level}, Food:{food_level}, Goal:{current_goal}, HeardK:{last_k_for_decision}, Inv:{inventory.get('linemate',0)}Li,{inventory.get('deraumere',0)}De,{inventory.get('sibur',0)}Si")

            if not perform_action_goal(current_goal, level, food_level, inventory, client_socket, reader, look_str, bot_spiral_state, thread_name):
                if not at.EXIT_EVENT.is_set():
                    ap.safe_print(f"[{thread_name}] Action failed or led to 'dead' state. Terminating.")
                    at.trigger_exit(f"{thread_name} ActionFailure")
                break
            if at.EXIT_EVENT.is_set():
                break
            if current_goal == 'INCANT':
                level += 1
            time.sleep(0.2) #ACTION_DELAY = 0.2
            reader.last_heard_player_k = -1
    except Exception as e:
        ap.safe_print(f"[{thread_name}] CRITICAL EXCEPTION in main loop: {e}")
        ap.safe_print(traceback.format_exc())
        at.trigger_exit(f"{thread_name} UnhandledException")
    finally:
        if client_socket:
            client_socket.close()
        ap.safe_print(f"[{thread_name}] Connection closed. Final state: Level {level}, Goal {current_goal}, Food {inventory.get('food', 'N/A')}.")

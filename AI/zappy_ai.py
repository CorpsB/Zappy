#!/usr/bin/env python3
##
## EPITECH PROJECT, 2025
## B-YEP-400-STG-4-1-zappy-noe.carabin
## File description:
## Refactored
##

import socket
import argparse
import sys
import time
import random
import threading
import re
import collections
import atexit
import traceback

# --- Configuration ---
FOOD_THRESHOLD = 6
WANDER_CHANCE = 0.3
SOCKET_TIMEOUT = 180.0
ACTION_DELAY = 0.2
L2_STONES_NEEDED_NAMES = ['linemate', 'deraumere', 'sibur']
L3_ELEVATION_REQUIREMENTS = {'player': 2, 'linemate': 1, 'deraumere': 1, 'sibur': 1, 'mendiane': 0, 'phiras': 0, 'thystame': 0}
LOG_BUFFER_SIZE = 100

# --- Global Flags & Shared Resources ---
print_lock = threading.Lock()
exit_event = threading.Event()
log_buffer = collections.deque(maxlen=LOG_BUFFER_SIZE)
DEBUG_MODE = False

# --- Shutdown & Logging ---
def trigger_exit(reason="Unknown"):
    """Sets the global exit event to signal all threads to terminate."""
    if not exit_event.is_set():
        safe_print(f"[Main] CRITICAL ERROR DETECTED ({reason}). Signaling exit...")
        exit_event.set()

def print_log_buffer():
    """Prints the log buffer if not in debug mode."""
    if not DEBUG_MODE and log_buffer:
        print("\n--- Last Log Messages ---", flush=True)
        with print_lock:
            for msg in list(log_buffer):
                print(msg, flush=True)
        print("--- End Log Messages ---\n", flush=True)

atexit.register(print_log_buffer)

def safe_print(message):
    """Prints or buffers a message based on DEBUG_MODE."""
    with print_lock:
        if DEBUG_MODE:
            print(message, flush=True)
        else:
            log_buffer.append(message)

# --- Main Startup ---
def _setup_arg_parser():
    """Configures and returns the argument parser."""
    parser = argparse.ArgumentParser(description="Zappy AI Heuristic Client", add_help=False)
    parser.add_argument('--help', action='help', default=argparse.SUPPRESS, help='Show this help message and exit')
    parser.add_argument("-p", "--port", type=int, required=True, help="Port number")
    parser.add_argument("-n", "--name", type=str, required=True, help="Name of the team")
    parser.add_argument("-h", "--host", type=str, default="localhost", help="Name of the machine")
    parser.add_argument("-c", "--count", type=int, default=1, help="Number of bots to run (default: 1)")
    parser.add_argument("-d", "--debug", action='store_true', help="Enable debug mode (print all logs immediately)")
    return parser

def _initialize_global_settings(args):
    """Initializes global settings based on parsed arguments."""
    global DEBUG_MODE
    DEBUG_MODE = args.debug
    if DEBUG_MODE:
        safe_print("[Main] Debug mode ENABLED.")
    else:
        safe_print("[Main] Debug mode DISABLED. Logs will print on exit or error.")

    if args.count < 1:
        print("Error: Bot count must be at least 1.", file=sys.stderr)
        sys.exit(84)

def _launch_bot_threads(args):
    """Creates, starts, and returns a list of bot threads."""
    threads = []
    for i in range(args.count):
        safe_print(f"[Main] Launching Bot {i+1} for team {args.name}...")
        thread = threading.Thread(
            target=run_ai_bot,
            args=(args.name, args.host, args.port, i+1),
            daemon=True
        )
        threads.append(thread)
        thread.start()
        time.sleep(0.1)
    return threads

def _await_threads_completion(bot_threads):
    """Waits for all bot threads to complete or for an exit signal."""
    try:
        while any(t.is_alive() for t in bot_threads) and not exit_event.is_set():
            time.sleep(1)

        if exit_event.is_set():
            safe_print("[Main] Exit event received. Waiting for bots to shut down.")
        else:
            safe_print("[Main] All bots seem to have finished their tasks.")

    except KeyboardInterrupt:
        safe_print("\n[Main] Ctrl+C received. Signaling all bots to exit.")
        trigger_exit("Ctrl+C")
    finally:
        for t_idx, t in enumerate(bot_threads):
            if t.is_alive():
                safe_print(f"[Main] Attempting to join Bot thread {t_idx+1}...")
                t.join(timeout=5.0)
                if t.is_alive():
                    safe_print(f"[Main] Bot thread {t_idx+1} did not terminate cleanly after 5s.")
                else:
                    safe_print(f"[Main] Bot thread {t_idx+1} joined.")
        safe_print("[Main] Shutdown sequence complete.")


def main():
    """Parses command-line arguments and launches AI bot threads."""
    parser = _setup_arg_parser()
    args = parser.parse_args()

    _initialize_global_settings(args)
    bot_threads = _launch_bot_threads(args)
    _await_threads_completion(bot_threads)

if __name__ == "__main__":
    main()

##
## EPITECH PROJECT, 2025
## B-YEP-400-STG-4-1-zappy-noe.carabin
## File description:
## print
##

import atexit
import collections
import threading

LOG_BUFFER = collections.deque(maxlen = 100) # LOG_BUFFER_SIZE = 100
DEBUG_MODE = False
PRINT_LOCK = threading.Lock()

def init_debug_mode(args):
    """Initializes DEBUG_MODE using args.debug"""
    global DEBUG_MODE

    DEBUG_MODE = args.debug
    if DEBUG_MODE:
        safe_print("[Main] Debug mode ENABLED.")
    else:
        safe_print("[Main] Debug mode DISABLED. Logs will print on exit or error.")

def print_log_buffer():
    """Prints the log buffer if not in DEBUG_MODE."""

    if not DEBUG_MODE and LOG_BUFFER:
        print("\n--- Last Log Messages ---", flush=True)
        with PRINT_LOCK:
            for msg in list(LOG_BUFFER):
                print(msg, flush=True)
        print("--- End Log Messages ---\n", flush=True)

def safe_print(message):
    """Prints or buffers a message based on DEBUG_MODE."""

    with PRINT_LOCK:
        if DEBUG_MODE:
            print(message, flush=True)
        else:
            LOG_BUFFER.append(message)

atexit.register(print_log_buffer)

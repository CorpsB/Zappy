##
## EPITECH PROJECT, 2025
## B-YEP-400-STG-4-1-zappy-noe.carabin
## File description:
## threads
##

import threading
import time
import ai_print as ap
import ai_run as ar

EXIT_EVENT = threading.Event()

def trigger_exit(reason = "Unknown"):
    """Sets the global exit event to signal all threads to terminate."""

    if not EXIT_EVENT.is_set():
        ap.safe_print(f"[Main] CRITICAL ERROR DETECTED ({reason}). Signaling exit...")
        EXIT_EVENT.set()

def await_threads_join(bot_threads):
    """Waits for all bot threads to complete or for an exit signal."""

    try:
        while any(t.is_alive() for t in bot_threads) and not EXIT_EVENT.is_set():
            time.sleep(1)
        if EXIT_EVENT.is_set():
            ap.safe_print("[Main] Exit event received. Waiting for bots to shut down.")
        else:
            ap.safe_print("[Main] All bots seem to have finished their tasks.")
    except KeyboardInterrupt:
        ap.safe_print("\n[Main] Ctrl+C received. Signaling all bots to exit.")
        trigger_exit("Ctrl+C")
    finally:
        for t_idx, t in enumerate(bot_threads):
            if t.is_alive():
                ap.safe_print(f"[Main] Attempting to join Bot thread {t_idx + 1}...")
                t.join(timeout = 5.0)
                if t.is_alive():
                    ap.safe_print(f"[Main] Bot thread {t_idx + 1} did not terminate cleanly after 5s.")
                else:
                    ap.safe_print(f"[Main] Bot thread {t_idx + 1} joined.")
        ap.safe_print("[Main] Shutdown sequence complete.")

def init_threads(args):
    """Creates, starts, and returns a list of bot threads."""
    threads = []

    for i in range(args.count):
        ap.safe_print(f"[Main] Launching Bot {i + 1} for team {args.name}...")
        thread = threading.Thread(
            target = ar.run_ai,
            args = (args.name, args.host, args.port, i + 1),
            daemon = True
        )
        threads.append(thread)
        thread.start()
        time.sleep(0.1)
    return threads

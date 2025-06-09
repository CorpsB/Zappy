##
## EPITECH PROJECT, 2025
## B-YEP-400-STG-4-1-zappy-noe.carabin
## File description:
## count_player
##

from ... import ai_print as ap
from ... import ai_threads as at

def count_players_on_tile(look_string, tile_index, thread_name="UnknownThread"):
    """Counts players on a specific tile from look results. Returns -1 on error."""

    if not look_string or not look_string.startswith('[') or not look_string.endswith(']'):
        ap.safe_print(f"[{thread_name}] CRITICAL PARSE ERROR: Bad Look string for player count: '{look_string}'")
        at.trigger_exit(f"{thread_name} PlayerCountParseFormat")
        return -1

    try:
        tiles = look_string.strip('[]').split(',')
        if 0 <= tile_index < len(tiles):
            return tiles[tile_index].split().count('player')
        ap.safe_print(f"[{thread_name}] WARN: Tile index {tile_index} out of bounds for look string.")
        return 0
    except Exception as e:
        ap.safe_print(f"[{thread_name}] CRITICAL PARSE ERROR: Failed counting players in look string '{look_string}': {e}")
        at.trigger_exit(f"{thread_name} PlayerCountException")
        return -1

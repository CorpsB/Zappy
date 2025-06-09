##
## EPITECH PROJECT, 2025
## B-YEP-400-STG-4-1-zappy-noe.carabin
## File description:
## find_item
##

def find_item_in_look(look_string, item_name, thread_name="UnknownThread"):
    """Finds an item in look results and returns its tile index. Returns -1 if not found or error."""
    if not look_string or not look_string.startswith('[') or not look_string.endswith(']'):
        safe_print(f"[{thread_name}] CRITICAL PARSE ERROR: Bad Look string format: '{look_string}'")
        trigger_exit(f"{thread_name} LookParseFormat")
        return -1
    try:
        tiles = look_string.strip('[]').split(',')
        for i, tile_content in enumerate(tiles):
            if item_name in tile_content.split(): return i
        return -1
    except Exception as e:
        safe_print(f"[{thread_name}] CRITICAL PARSE ERROR: Failed parsing Look string '{look_string}': {e}")
        trigger_exit(f"{thread_name} LookParseException")
        return -1

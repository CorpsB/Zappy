##
## EPITECH PROJECT, 2025
## B-YEP-400-STG-4-1-zappy-noe.carabin
## File description:
## inventory
##

def parse_inventory(inv_string, thread_name="UnknownThread"):
    """Parses an inventory string and returns a dictionary."""
    inventory = {'food': 0, 'linemate': 0, 'deraumere': 0, 'sibur': 0,
                 'mendiane': 0, 'phiras': 0, 'thystame': 0}
    if not inv_string or not inv_string.startswith('[') or not inv_string.endswith(']'):
        safe_print(f"[{thread_name}] CRITICAL PARSE ERROR: Received non-inventory: '{inv_string}'")
        trigger_exit(f"{thread_name} InvParseFormat")
        return None
    try:
        items = inv_string.strip('[]').split(',')
        for item in items:
            item = item.strip()
            if item:
                parts = item.split()
                if len(parts) == 2:
                    resource, quantity_str = parts
                    if resource in inventory:
                        inventory[resource] = int(quantity_str)
        return inventory
    except ValueError as e:
        safe_print(f"[{thread_name}] CRITICAL PARSE ERROR: Inventory ValueError for '{inv_string}': {e}")
        trigger_exit(f"{thread_name} InvParseValueError")
        return None
    except Exception as e:
        safe_print(f"[{thread_name}] CRITICAL PARSE ERROR: Inventory generic Exception for '{inv_string}': {e}")
        trigger_exit(f"{thread_name} InvParseException")
        return None

def get_inventory_and_food(sock, reader, thread_name):
    """Fetches and parses inventory, returns inventory dict and food level."""
    inv_str = do_action(sock, reader, "Inventory", thread_name)
    if inv_str == "dead": return None, 0
    inventory = parse_inventory(inv_str, thread_name)
    if inventory is None: return None, 0
    return inventory, inventory.get('food', 0)

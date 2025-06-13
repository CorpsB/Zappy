##
## EPITECH PROJECT, 2025
## B-YEP-400-STG-4-1-zappy-noe.carabin
## File description:
## initialize
##

import socket
from . import ai_socket as ais
from .. import ai_print as ap

def initialize_connection(team_name, host, port, thread_name):
    """Establishes connection and performs initial handshake with the server."""
    client_socket = None

    try:
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client_socket.connect((host, port))
        reader = ais.SocketReader(client_socket, thread_name)
        welcome_msg = reader.receive_line(1)

        if welcome_msg == "dead":
            raise ConnectionError("Failed at welcome message.")
        ap.safe_print(f"[{thread_name}] Server: {welcome_msg}")
        if not ais.send_command(client_socket, team_name, thread_name):
            raise ConnectionError("Failed to send team name.")

        client_num_str = reader.receive_line(1)
        if client_num_str == "dead":
            raise ConnectionError("Failed receiving client slot info.")
        if "ko" in client_num_str:
            raise ConnectionError(f"Team name rejected or team full: {client_num_str}")

        try:
            _ = int(client_num_str)
            ap.safe_print(f"[{thread_name}] Client slots available/msg: {client_num_str}")
        except ValueError:
            raise ConnectionError(f"Expected client slots (number) or 'ko', got '{client_num_str}'")

        world_size_str = reader.receive_line(1)
        if world_size_str == "dead":
            raise ConnectionError("Failed to receive world size.")
        ap.safe_print(f"[{thread_name}] Connected. World Size: {world_size_str}")
        return client_socket, reader, True

    except (socket.error, ConnectionError) as e:
        ap.safe_print(f"[{thread_name}] Connection setup failed: {e}")
        if client_socket:
            client_socket.close()
        return None, None, False

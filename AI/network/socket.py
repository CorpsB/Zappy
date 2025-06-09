##
## EPITECH PROJECT, 2025
## B-YEP-400-STG-4-1-zappy-noe.carabin
## File description:
## socket
##

class SocketReader:
    """Manages a socket and its read buffer for line-based reading."""
    def __init__(self, sock, thread_name):
        self.sock = sock
        self.buffer = b""
        self.thread_name = thread_name
        self.last_heard_meetup_k = -1

    def _handle_buffered_data(self):
        """Processes the current buffer to extract one line."""
        if b'\n' in self.buffer:
            line, self.buffer = self.buffer.split(b'\n', 1)
            return line.decode().strip()
        return None

    def _receive_data_from_socket(self, timeout):
        """Receives data from the socket, handling timeouts and errors."""
        self.sock.settimeout(timeout)
        start_time = time.time()
        while b'\n' not in self.buffer:
            if exit_event.is_set(): return "dead"
            if time.time() - start_time > timeout:
                safe_print(f"[{self.thread_name}] Socket receive timeout ({timeout}s).")
                return "dead"
            try:
                data = self.sock.recv(1024)
                if not data:
                    safe_print(f"[{self.thread_name}] Server disconnected.")
                    return "dead"
                self.buffer += data
            except socket.timeout:
                safe_print(f"[{self.thread_name}] Socket recv call timed out waiting for more data.")
                return "dead"
            except socket.error as e:
                safe_print(f"[{self.thread_name}] Socket error during recv: {e}")
                return "dead"
        return "ok"

    def _process_server_message(self, decoded_line):
        """Handles server-initiated messages like broadcasts or ejections."""
        if decoded_line == "dead":
            safe_print(f"[{self.thread_name}] Explicitly Received 'dead'.")
            return "dead", True

        msg_match = re.match(r"message (\d+), (.+)", decoded_line)
        if msg_match:
            k = int(msg_match.group(1))
            text = msg_match.group(2).strip()
            safe_print(f"[{self.thread_name}] Heard broadcast (K={k}): {text}")
            if "MEETUP_L3" in text:
                self.last_heard_meetup_k = k
            return "broadcast", False

        if decoded_line.startswith("eject:"):
            safe_print(f"[{self.thread_name}] Got ejected! {decoded_line}")
            return "eject", False

        return decoded_line, True

    def receive_line(self, timeout=SOCKET_TIMEOUT):
        """Receives data until a newline, handling buffering, broadcasts, and timeouts."""
        if exit_event.is_set(): return "dead"

        status = self._receive_data_from_socket(timeout)
        if status == "dead":
            return "dead"

        decoded_line = self._handle_buffered_data()
        if decoded_line is None:
            safe_print(f"[{self.thread_name}] Error: No line after successful receive.")
            return "dead"

        processed_message, is_final = self._process_server_message(decoded_line)
        if processed_message == "dead":
            return "dead"
        if not is_final:
            return self.receive_line(timeout)

        return processed_message

def send_command(sock, command, thread_name):
    """Sends a command to the server thread-safely."""
    if exit_event.is_set(): return False
    safe_print(f"[{thread_name}] SND: {command}")
    try:
        sock.sendall(f"{command}\n".encode())
        return True
    except socket.error as e:
        safe_print(f"[{thread_name}] Socket error while sending '{command}': {e}")
        trigger_exit(f"{thread_name} SendError")
        return False

def do_action(sock, reader, command, thread_name):
    """Sends a command and reads its single response."""
    if not send_command(sock, command, thread_name): return "dead"
    return reader.receive_line()

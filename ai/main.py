#!/usr/bin/env python3
##
## EPITECH PROJECT, 2025
## B-YEP-400-STG-4-1-zappy-noe.carabin
## File description:
## main
##

import argparse
import sys
from . import ai_threads as at
from . import ai_print as ap

def init_parser():
    """Configures and returns the argument parser."""
    parser = argparse.ArgumentParser(description="Zappy AI Heuristic Client", add_help=False)
    parser.add_argument('--help', action='help', default=argparse.SUPPRESS, help='Show this help message and exit')
    parser.add_argument("-p", "--port", type=int, required=True, help="Port number")
    parser.add_argument("-n", "--name", type=str, required=True, help="Name of the team")
    parser.add_argument("-h", "--host", type=str, default="localhost", help="Name of the machine")
    parser.add_argument("-c", "--count", type=int, default=1, help="Number of bots to run (default: 1)")
    parser.add_argument("-d", "--debug", action='store_true', help="Enable debug mode (print all logs immediately)")
    return parser

def main():
    """Parses command-line arguments and launches AI bot threads."""

    parser = init_parser()
    args = parser.parse_args()

    if args.count < 1:
        print("Error: Bot count must be at least 1.", file=sys.stderr)
        sys.exit(84)
    if args.name == "GRAPHIC":
        print("Error: GRAPHIC team name is reserved to gui.", file=sys.stderr)
        sys.exit(84)

    ap.init_debug_mode(args)
    bot_threads = at.init_threads(args)
    at.await_threads_join(bot_threads)

if __name__ == "__main__":
    main()

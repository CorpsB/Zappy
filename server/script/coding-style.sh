#!/bin/bash
##
## EPITECH PROJECT, 2023
## New
## File description:
## conding_style.sh
##

clear
make fclean
while true; do
    /coding-style-checker-main/coding-style.sh . .
    clear
    cat coding-style-reports.log | grep MAJOR
    cat coding-style-reports.log | grep MINOR
    cat coding-style-reports.log | grep INFO
    echo "Retry ? (y/n)"
    read response
    if [ "$response" == "y" ]; then
        echo "Retry ..."
    else
        clear
        rm coding-style-reports.log
        echo "y"
        break
    fi
done
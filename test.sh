#!/bin/bash

NAME=minishell
LOGS=logs

run_test () {
    make > /dev/null
    while IFS= read -r line; do
        local cmd="$line"
        ms_output=$(./$NAME -c "$cmd" 2> /dev/null)
        local ms_ret=$?
        bash_output=$($cmd 2> /dev/null)
        local bash_ret=$?
        if [ "$ms_ret" -eq 0 ] && [ "$bash_ret" -eq 0 ]; then
            if [ "$ms_output" = "$bash_output" ]; then
                printf "\e[32m%s\n" "[OK]"
            else
                printf "\e[31m%s\n" "[KO]"
                printf "\033[0m"
                printf "desired output %s\nreturn value: [%d]\n" "$bash_output" "$bash_ret"
                printf "received output %s\nreturn value: [%d]\n" "$ms_output" "$ms_ret"
            fi
            printf "\033[0m"
        else
            if [ "$ms_ret" -eq "$bash_ret" ]; then
                printf "\e[32m%s\n" "[OK]"
                printf "\033[0m"
            else
                printf "\e[31m%s\n" "[KO]"
                printf "\033[0m"
                printf "desired output %s\nreturn value: [%d]\n" "$bash_output" "$bash_ret"
                printf "received output %s\nreturn value: [%d]\n" "$ms_output" "$ms_ret"
            fi
            printf "\033[0m"
        fi
    done < $1
}

run_test test_cmd.txt

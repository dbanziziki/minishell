#!/bin/bash

NAME=minishell
LOGS=logs
BASH_OUT=bash_outfile
MS_CMD=""
BASH_CMD=""

run_simple_test () {
    local cmd=$1
    ms_output=$(./$NAME -c "$cmd" 2> /dev/null)
    local ms_ret=$?
    bash_output=$(eval "$cmd" 2> /dev/null)
    local bash_ret=$?
    if [ "$ms_ret" -eq 0 ] && [ "$bash_ret" -eq 0 ]; then
        if [ "$ms_output" = "$bash_output" ]; then
            printf "%s\n\e[32m%s\n" "$cmd" "[OK]"
        else
            printf "\e[31m%s\n" "[KO]"
            printf "\033[0m"
            printf "desired output %s\nreturn value: [%d]\n" "$bash_output" "$bash_ret"
            printf "received output %s\nreturn value: [%d]\n" "$ms_output" "$ms_ret"
        fi
        printf "\033[0m"
    else
        if [ "$ms_ret" -eq "$bash_ret" ]; then
            printf "%s\n\e[32m%s\n" "$cmd" "[OK]"
            printf "\033[0m"
        else
            printf "\e[31m%s\n" "[KO]"
            printf "\033[0m"
            printf "desired output %s\nreturn value: [%d]\n" "$bash_output" "$bash_ret"
            printf "received output %s\nreturn value: [%d]\n" "$ms_output" "$ms_ret"
        fi
        printf "\033[0m"
    fi
}

test_redirections () {
    make > /dev/null
    ./$NAME -c "cat < Makefile > outfile" 2> /dev/null
    local ms_ret=$?
    cat < Makefile > bash_outfile
    diff outfile bash_outfile
    local bash_ret=$?
    if [ "$ms_ret" -eq 0 ] && [ "$bash_ret" -eq 0 ]; then
        printf ""
    fi
}

run_tests () {
    make > /dev/null
    while IFS= read -r line; do
        run_simple_test "$line"
    done < $1
}

run_tests test_cmd.txt
#test_redirections

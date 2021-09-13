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
    local ms_outfile="$LOGS/ms_outfile"
    local ms_full_cmd="$1 $ms_outfile"
    local bash_outfile="$LOGS/bash_outfile"
    local bash_full_cmd="$1 $bash_outfile"
    make > /dev/null
    ./$NAME -c "$ms_full_cmd" 2> $LOGS/ms.log
    local ms_ret=$?
    eval $bash_full_cmd  2> $LOGS/bash.log
    local bash_ret=$?
    if [ "$bash_ret" -eq "$ms_ret" ]; then
        diff $ms_outfile $bash_outfile
        local cmp_res=$?
        if [ "$cmp_res" -eq 0 ]; then
            printf "%s\n\e[32m%s\n" "$ms_full_cmd" "[OK]"
            printf "\033[0m"
        else
            printf "\e[31m%s\n" "[KO]"
            printf "\033[0m"
            local expected=$(cat "$bash_outfile")
            local received=$(cat "$ms_outfile")
            printf "Expected %s\n" "$expected"
            printf "Got %s\n" "$received"
        fi
    else
        printf "\e[31m%s\n" "[KO]"
        printf "\033[0m"
        printf "Wrong exit status: expected [%d] and got [%d]\n" "$bash_ret" "$ms_ret"
    fi
}

clean_up() {
    make fclean > /dev/null
    rm -f $bash_outfile $ms_outfile
}

run_tests () {
    printf "Compiling minishell...\n"
    make > /dev/null
    printf "\033[0;35m--------%s-------------\n" "Testing simple commands"
    printf "\033[0m"
    while IFS= read -r line; do
        run_simple_test "$line"
    done < $1
    printf "\033[0;35m--------%s-------------\n" "Testing redirections"
    printf "\033[0m"
    while IFS= read -r line; do
       test_redirections "$line" 
    done < test_redir.txt
    #clean_up
}


run_tests test_cmd.txt
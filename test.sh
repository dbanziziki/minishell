#!/bin/bash

NAME=minishell

run_test () {
    make
    echo "$@"
   ./$NAME -c "$@"
}

cmd="ls -la"
run_test $cmd

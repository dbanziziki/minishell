#!/bin/bash

NAME=minishell

run_test () {
    make
   ./$minishell -c $1 
}

run_test "ls -la"
#!/bin/bash

./build
gdb -q --command=debug_commands.gdb ../bin/analyzer 


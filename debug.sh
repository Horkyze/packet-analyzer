#!/bin/bash

./build
gdb --command=debug_commands.gdb ../bin/analyzer 


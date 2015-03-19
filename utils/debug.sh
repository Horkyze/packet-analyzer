#!/bin/bash

cd ..
make
cd utils
gdb -q --command=debug_commands.gdb ../bin/analyzer 


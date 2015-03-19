HEADERS = eth_parser.h functions.h

default: analyzer

analyzer: main.c
	clang -lpcap -g main.c -o bin/analyzer 

debug:
	gdb -q --command=debug_commands.gdb bin/analyzer 

clean:
	-rm -f bin/analyzer 

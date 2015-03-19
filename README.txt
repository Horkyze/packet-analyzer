A simple packet analyzer utility using pcap library.

Run 
$ make 
to create a binary inside bin folder.

Optionaly run
$ make debug
to open gdb

Example:

$ ./analyzer -i wlan1    (may need sudo)
$ ./analyzer -f ../capture/capture.pcap

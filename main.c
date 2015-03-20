/**
	A simple packet analyzer utility using pcap library.
	Created as a school assigment for Computer Networks curse.
	Matej Bellus

**/


#include <pcap.h>
#include <arpa/inet.h>
#include <getopt.h>
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

// custom includes
#include "functions.h"
#include "hash_table.h"
#include "eth_parser.h"
#include "ip_parser.h"



void print_usage(){
	printf("A simple packet analyzer utility using pcap library by Matej Bellus (c) \n");
	printf("Usage: <prog> [-i interface] [-f file.pcap] \n\n");
}

int main(int argc, char *argv[])
{	
	int option = 0;
 	char * interface = 0, * file = 0;

    //Specifying the expected options
    //The two options l and b expect numbers as argument
    while ((option = getopt(argc, argv,"i:f:")) != -1) {
        switch (option) {
             case 'i' : interface = optarg;
                 break;
             case 'f' : file = optarg;
                 break;
             default: print_usage(); 
                 exit(EXIT_FAILURE);
        }
    }

    

	pcap_t *handle;			/* Session handle */
	char *dev;			/* The device to sniff on */
	char errbuf[PCAP_ERRBUF_SIZE];	/* Error string */
	struct bpf_program fp;		/* The compiled filter */
	char filter_exp[] = ""; //"ether src 5c:51:4f:73:3d:d6 and ether dst 00:00:00:00:11:22";	/* The filter expression */
	bpf_u_int32 mask;		/* Our netmask */
	bpf_u_int32 net;		/* Our IP */
	struct pcap_pkthdr header;	/* The header that pcap gives us */
	const u_char *packet;		/* The actual packet */

	/* Define the device */
	dev = pcap_lookupdev(errbuf);
	if (dev == NULL) {
		fprintf(stderr, "Couldn't find default device: %s\n", errbuf);
		return(2);
	}
	/* Find the properties for the device */
	if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1) {
		fprintf(stderr, "Couldn't get netmask for device %s: %s\n", dev, errbuf);
		net = 0;
		mask = 0;
	}

	if (file){
    	handle = pcap_open_offline(file, errbuf); 
    } else if (interface){
    	/* Open the session in promiscuous mode */
    	handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    }
	
	if (handle == NULL) {
		fprintf(stderr, "Couldn't open device %s: %s\n", "somedev", errbuf);
		return(2);
	}
	/* Compile and apply the filter */
	if (pcap_compile(handle, &fp, filter_exp, 0, net) == -1) {
		fprintf(stderr, "Couldn't parse filter %s: %s\n", filter_exp, pcap_geterr(handle));
		return(2);
	}
	if (pcap_setfilter(handle, &fp) == -1) {
		fprintf(stderr, "Couldn't install filter %s: %s\n", filter_exp, pcap_geterr(handle));
		return(2);
	}

	int packet_number = 1;
	while(1){

		packet = pcap_next(handle, &header);
		if ( packet == NULL){
			break;
		} else {		
			add_frame(packet, header.len);
		}
		
	}

	print_frames();
	parse_packets();
	
	pcap_close(handle);
	return(0);
}

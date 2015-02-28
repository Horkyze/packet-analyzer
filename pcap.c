#include <pcap.h>
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "eth.h"






int is_print(char c){
	return (c > 31 && c <= 127);
}
void dump(const unsigned char * p, int len){
	int i, k = 0;
	char buff[16];
	for (i = 1; i < len + 1; ++i)
	{
		printf("%02x ", p[i-1]);

		buff[k++] = (is_print(p[i-1]))? p[i-1] : '.';

		if (i % 8 == 0 && i) {
			printf(" ");
		}


		if (i % 16 == 0 && i){

			printf(" | %s \n", buff);
			memset(buff, 0, 16);
			k = 0;
		} 

		
	}
	printf("\n\n");
}

	 int main(int argc, char *argv[])
	 {
		pcap_t *handle;			/* Session handle */
		char *dev;			/* The device to sniff on */
		char errbuf[PCAP_ERRBUF_SIZE];	/* Error string */
		struct bpf_program fp;		/* The compiled filter */
		char filter_exp[] = "tcp port 80";	/* The filter expression */
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
		/* Open the session in promiscuous mode */
		handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
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

		while(1){

		
			/* Grab a packet */
			packet = pcap_next(handle, &header);
			if ( packet == NULL){
				continue;
			} else {
			
				printf("Jacked a packet with length of [%d]\n", header.len);
				
				dump(packet, header.len);
				parse_eth(packet);
			}
			
		}
		/* And close the session */
			pcap_close(handle);
			return(0);
	 }

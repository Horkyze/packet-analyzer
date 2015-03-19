#define IPv4 ((ipv4_h*)f->network_header)

typedef	struct ipv4_h
{
	u_char version_ihl;
	u_char dscp_enc;
	u_short length;
	u_short identification;
	u_short flags_fragment_offset;
	u_char ttl;
	u_char protocol;
	u_short header_chksm;
	u_int src_ip_addr;
	u_int dst_ip_addr;
	u_int options; // if ihl > 5

}ipv4_h;


char * ip_to_string(u_int ip){
	char * s;
	s = (char *) malloc(20);
    u_char bytes[4];
    bytes[0] = ip & 0xFF;
    bytes[1] = (ip >> 8) & 0xFF;
    bytes[2] = (ip >> 16) & 0xFF;
    bytes[3] = (ip >> 24) & 0xFF;	
    sprintf(s, "%d.%d.%d.%d", bytes[0], bytes[1], bytes[2], bytes[3]);  
    return s;      
}

// create packets linked list 
void parse_packets(){

	Hash_table * ht = init_hash_table(1000);

	Frame * f;
	Item * curr;
	curr = frames_ll->head;

	while(curr) {		
		f = curr->data; // frame struct
		                
		printf("eth type: %04x\n", get_eth_type( f->eth_header ));
		if (  get_eth_type( f->eth_header ) == ARP_TYPE  ){
			printf("arp\n");
		} else {
			f->network_header = f->data + 14;
			printf("SRC IP address: %s\n", ip_to_string(IPv4->src_ip_addr));
		}
		

		//printf("\t: %u bytes\n", );
		//insert_h(ht, IPv4->src_ip_addr, 10);
		
	    curr = curr->next; // next item in LL
	}
}
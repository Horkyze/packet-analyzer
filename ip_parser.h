// macro for referencing ipv4 header
#define IPv4 ((ipv4_h*)f->network_header)

// macro for referencing eth II header
#define EthII ((eth_2_h*)f->eth_header)

// Hash table size
#define HT_SIZE (frames_ll->number_of_items*3)

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

#define ARP_REQUEST 1   /* ARP Request             */ 
#define ARP_REPLY 2     /* ARP Reply               */ 
typedef struct arp_h { 
    u_int16_t htype;    /* Hardware Type           */ 
    u_int16_t ptype;    /* Protocol Type           */ 
    u_char hlen;        /* Hardware Address Length */ 
    u_char plen;        /* Protocol Address Length */ 
    u_int16_t oper;     /* Operation Code          */ 
    u_char sha[6];      /* Sender hardware address */ 
    u_int spa[4];      	/* Sender IP address       */ 
    u_char tha[6];      /* Target hardware address */ 
    u_int tpa[4];      	/* Target IP address       */ 
}arp_h; 


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

// prints all ip addrs from hash table
void print_all_h(Hash_table * ht){
	int i;

	for (i = 0; i < ht->n; ++i){
		if ( (ht->table[i]).ip != 0){
			printf("Src ip: %s \t bytes send: %u\n", ip_to_string(ht->table[i].ip), ht->table[i].bytes_send);
		}
	}
}

void print_max_h(Hash_table * ht){
	u_int max = 0;
	u_int max_ip = 0;
	int i;
	for (i = 0; i < ht->n; ++i){
		if ( (ht->table[i]).ip != 0){
			if (ht->table[i].bytes_send > max){
				max = ht->table[i].bytes_send;
				max_ip = ht->table[i].ip;
			}
		}
	}
	printf("\nMost data send from ip: %s \t bytes send: %u\n", ip_to_string(max_ip), max);

}

void parse_packets(){

	Hash_table * ht = init_hash_table(HT_SIZE);

	Frame * f;
	Item * curr;
	curr = frames_ll->head;

	// for each frame in linked list
	while(curr) {		
		// set current frame f
		f = curr->data; 
		
		// if given frame is not ETH II, dont analyze it
		if (! f->parseble){
	    	curr = curr->next; 
			continue;
		}                

		// if we have IPv4
		if (  get_eth_type( f->eth_header ) == IP4_TYPE  ){

			f->network_header = f->data + 14;

			insert_h(ht, IPv4->src_ip_addr, (f->length < 60)? 64 : f->length+4);
		}

		// if we have ARP
		if (  get_eth_type( f->eth_header ) == ARP_TYPE  ){

			//f->network_header = f->data + 14;

			
		}
		
	    curr = curr->next; // next item in LL
	}
	print_all_h(ht);
	print_max_h(ht);
	printf("Parsed %u frames :)\n", frames_ll->number_of_items);
}
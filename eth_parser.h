/*=======================================
=            Ethernet Parser            =
=======================================*/






/*==========  Variables / Constants  ==========*/

const u_char eth_max[] = {0x06, 0x00}; // 1536 

// link layer codes
const u_char arp[]  =  {0x08, 0x06};
const u_char ipv4[] =  {0x08, 0x00};

// Linked list of all frames
LL * frames_ll;


/*==========  Ethernet Headers Definitions  ==========*/


                                       
typedef	struct eth_2_h
{
	u_char dst_addr[6];
	u_char src_addr[6];
	u_char eth_type[2];
	u_char extra[2]; // just for parsing purposes
}Eth_II_hdr;

typedef	struct eth_raw_h
{
	u_char dst_addr[6];
	u_char src_addr[6];
	u_char length[2];
	u_char ipx_hdr[3];

}eth_raw_h;

typedef	struct eth_llc_h
{
	u_char dst_addr[6];
	u_char src_addr[6];
	u_char length[2];
	u_char dsap[1];
	u_char ssap[1];
	u_char control[1];
}eth_llc_h;


typedef	struct eth_llc_snap_h
{
	u_char dst_addr[6];
	u_char src_addr[6];
	u_char length[2];
	u_char dsap[1];
	u_char ssap[1];
	u_char control[1];
	u_char vendor[3];
	u_char eth_type[2];
}eth_llc_snap_h;


/*-----  End of Ethernet Header Declaration  ------*/


void parse_eth(u_char * data, int length, int index){

	struct eth_2_h * hdr = data;

	printf("\n------------------------------------------\nFrame #%i\n", index);


	printf("Dst Addr : "); 
	print_hex(hdr->dst_addr, 6);

	printf("Src Addr : "); 
	print_hex(hdr->src_addr, 6);

	printf("Length / type : "); 
	print_hex(hdr->eth_type, 2);


	int k = memcmp(hdr->eth_type, eth_max, 2);
	//printf("cmp: %i\n", k);
	if ( k >= 0){
		
		printf("Ethernet II\n");



	
	} else {
		// dont perform more analysis than this 
		if (hdr->extra[0] == 0xFF && hdr->extra[1] == 0xFF)
		{
			printf("Ethernet RAW\n");
		} else if (hdr->extra[0] == 0xAA && hdr->extra[1] == 0xAA)
		{
			printf("Ethernet LLC/SNAP\n");
		} else {
			printf("Ethernet LLC\n");
		}
	}
	dump(data, length);
}






typedef struct Frame {
	unsigned int number;
	unsigned int length;
	void * eth_header;
	void * data;
} Frame;

void add_frame(u_char * data, int length){

	if(frames_ll == 0) {
		frames_ll = LL_init();
	}

	Frame * frame = malloc(sizeof(Frame));
	frame->length = length;
	frame->data = malloc(length);
	memcpy ( frame->data, data, length);
	frame->number = frames_ll->number_of_items+1;
	LL_add(frames_ll, frame);
}

void print_frames(){
	int i = 0;
	Frame * f;
	Item * curr;
	curr = frames_ll->head;
	while(curr) {
	
		
		f = curr->data;
		parse_eth(f->data, f->length, f->number);

	    curr = curr->next;
	}
}




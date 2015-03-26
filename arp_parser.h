#define ARP(x) ((arp_h*)((x)->network_header))

#define PASRABLE 0x01
#define ARP_ALREADY_PARSED 0x02

#define ARP_REQUEST 0x0100   // ARP Request
#define ARP_REPLY 	0x0200   // ARP Reply


typedef struct arp_h { 
    u_short htype;    /* Hardware Type           */ 
    u_short ptype;    /* Protocol Type           */ 
    u_char hlen;        /* Hardware Address Length */ 
    u_char plen;        /* Protocol Address Length */ 
    u_short oc;     /* Operation Code          */ 

    u_char sha[6];      /* Sender hardware address */ 
    u_long spa;      	/* Sender IP address       */ 

    u_char tha[6];      /* Target hardware address */ 
    u_long tpa;      	/* Target IP address       */ 
}arp_h; 
//#pragma options align=reset

LL * arp_frames_ll = 0;


void add_arp_frame(Frame * f){
	if (arp_frames_ll == 0){
		arp_frames_ll = LL_init();
	}
	LL_add(arp_frames_ll, f);
}

Frame * get_next_request(){
	Frame * next_request = 0;
	Frame * f;
	Item * curr;
	curr = arp_frames_ll->head;

	// for each frame in linked list
	while(curr) {		
		// set current frame f
		f = curr->data; 
		
		if ( f->parseble && f->parseble != ARP_ALREADY_PARSED && ARP(f)->oc == ARP_REQUEST){
	    	next_request = f;
			printf("GOT ARP REQUEST\n");

			f->parseble = ARP_ALREADY_PARSED;
			return next_request;
		}
		
		curr = curr->next; // next item in LL
	}

	return 0;
}

Frame * find_arp_reply(Frame * request){
	Frame * next_reply = 0;
	Frame * f;
	Item * curr;
	curr = arp_frames_ll->head;

	printf("\nFinding reply for: \n");
	dump(request->data, request->length);
	printf("diff \t= %u\n", (void*)&(ARP(request)->tpa) - (void*)(ARP(request)) );
	printf("htype \t= %04x\n", ARP(request)->htype );
	printf("ptype \t= %04x\n", ARP(request)->ptype );
	printf("hlen \t= %02x\n", ARP(request)->hlen );
	printf("plen \t= %02x\n", ARP(request)->plen );
	printf("oc \t= %04x\n", ARP(request)->oc );

	printf("sha \t= ");
	print_hex(ARP(request)->sha, 6);

	printf("spa \t= ");
	print_hex(&ARP(request)->spa, 4);

	printf("tha \t= ");
	print_hex(ARP(request)->tha, 6);

	printf("tpa \t= ");
	print_hex(&ARP(request)->tpa, 4);


	printf("Sender IP: %s\nTarget IP: %s\n", ip_to_string(ARP(request)->spa), ip_to_string(ARP(request)->tpa));


	// for each frame in linked list
	while(curr) {		
		// set current frame f
		f = curr->data; 
		
		if ( /*f->parseble && f->parseble != ARP_ALREADY_PARSED &&*/ ARP(f)->oc == ARP_REPLY){
			
			//printf("Is this the reply??\n");

			
				    	
	    	next_reply = f;
			//dump(request->data, request->length);
			//dump(next_reply->data, next_reply->length);

			print_hex(&ARP(next_reply)->spa, 4);
			print_hex(&ARP(next_reply)->tpa, 4);
			
	    	if ( //ARP(request)->sha == ARP(next_reply)->tha && 1
	    		 ARP(request)->spa == ARP(next_reply)->tpa && 1
	    		 //ARP(request)->tpa == ARP(next_reply)->spa    
	    		 ){
	    		printf("Found ARP pair\n");
	    		f->parseble = ARP_ALREADY_PARSED;
	    		return next_reply;
	    	}	
		
		}
		
		curr = curr->next; // next item in LL
	}

	return 0;
}

void find_arp_pairs(){
	Frame * request;
	Frame * reply;
	while( request = get_next_request() ){
		reply = find_arp_reply(request);

	}
}
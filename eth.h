
/*===================================================
=            Ethernet Header Declaration            =
===================================================*/

typedef	struct eth_2_h
{
	u_char dst_addr[6];
	u_char src_addr[6];
	u_char eth_type[2];
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

void print(u_char * data, int len){
	int i;
	for (i = 0; i < len; ++i)
	{
		printf("%x", data[i]);
	}
	printf("\n");
}

void parse_eth(u_char * data){
	struct eth_2_h * hdr = data;

	printf("Destiation Addr: "); 
	print(hdr->dst_addr, 6);

	printf("Source Addr: "); 
	print(hdr->src_addr, 6);

	printf("Length: "); 
	print(hdr->eth_type, 2);

	// ipv4
	if (hdr->eth_type == 0x8000)
	{
		parse_ipv4();
	}

}
int is_print(u_char c){
	return (c > 31 && c <= 127);
}

void print(u_char * data, int len){
	int i;
	for (i = 0; i < len; ++i)
	{
		printf("%02x", data[i]);
	}
	printf("\n");
}

void print_hex(const char *s)
{
  while(*s)
    printf("%02x", (unsigned int) *s++);
}


void dump(const unsigned char * p, int len){
	int i, k = 0;
	u_char buff[17];
	for (i = 1; i < len + 1; ++i)
	{
		printf("%02x ", p[i-1]);

		buff[(i-1)%16] = (is_print(p[i-1]))? p[i-1] : '.';

		if (i % 8 == 0 && i) {
			printf(" ");
		}


		if (i % 16 == 0 && i){

			printf(" | %s \n", buff);
			memset(buff, 0, 17);
			k = 0;
		} 

		
	}
	printf("\n\n");
}

/*==================================
=            HASH TABLE            =
==================================*/

typedef struct Item_h{
	u_long ip;
	//u_char ip[4]; //ip addr has 4 bytes
	int bytes_send;
}Item_h;

typedef struct Hash_table{
  Item_h * table;	// array of Item_h 
  int n;
}Hash_table;

int insert(Hash_table * ht, int x);

Hash_table * init_hash_table(int size){

	Hash_table * h = 0;
	h = (Hash_table*) malloc(sizeof(Hash_table)); 

	h->n = size;
	h->table  = 0;

	h->table  = (Item_h *) malloc(sizeof(Item_h) * size); 
	memset(h->table , 0, sizeof(Item_h) * size);

	return h;
}

int hash(u_int a){
	a ^= (a << 13);
	a ^= (a >> 17);
	a ^= (a << 5);
	return a;   
}

// insert into hash table ht value x

int insert_h(Hash_table * ht, u_int x, int bytes)
{

	unsigned long h = hash(x) % ht->n;
	(ht->table[h]).bytes_send += bytes;

	return 1;
}


// search in hash table ht for value x
// return 1 if found
int search_h(Hash_table * ht, u_int x)
{
	u_long h = hash(x) % ht->n;

	return ht->table[h].bytes_send;

  
}

/*-----  End of HASH TABLE  ------*/

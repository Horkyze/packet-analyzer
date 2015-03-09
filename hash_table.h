
// /*==================================
// =            HASH TABLE            =
// ==================================*/

// typedef struct Item{
// 	u_char ip[4]; //ip addr has 4 bytes
// 	int bytes_send;
// }Item;

// typedef struct Hash_table{
//   Item * table;	// array of strings 
//   int n;
// }Hash_table;

// int insert(Hash_table * ht, int x);

// Hash_table * init_hash_table(int size){

// 	Hash_table * h = 0;
// 	h = (Hash_table*) malloc(sizeof(Hash_table)); 

// 	h->n = size;
// 	h->table  = 0;

// 	h->table  = (Item *) malloc(sizeof(Item) * size); 
// 	memset(h->table , 0, sizeof(Item) * size);

// 	return h;
// }

// // from http://www.cse.yorku.ca/~oz/hash.html
// unsigned long hash(char * str)
// {
// 	unsigned long hash = 5381;
// 	int c;
// 	while (c = *str++)
// 		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

// 	return hash;
// }

// // insert into hash table ht value x

// int insert_h(Hash_table * ht, u_char * x, int size)
// {

// 	unsigned long h = hash(x) % ht->n;
// 	while( (ht->table[h]).name ){
// 		h = (h < ht->n) ? h + 1 : 0;
// 	}

// 	// //printf("Inserting value %i to ht[%i]\n", x, h);
// 	// ht->table[h].name = (char*) malloc(sizeof(char) * (strlen(x) + 1) );
// 	// strcpy(ht->table[h].name, x);
// 	// ht->table[h].tree_root_prt = 0;

// 	return 1;
// }


// // search in hash table ht for value x
// // return 1 if found
// Page * search_h(Hash_table * ht, char * x)
// {
// 	unsigned long h = hash(x) % ht->n;

// 	while( ht->table[h].name != 0 ){
// 		if ( strcmp(ht->table[h].name, x) == 0 ){
// 			return &(ht->table[h]);  //  a[i] == *(a + i)
// 		}
// 		h = (h < ht->n) ? h + 1 : 0;
// 	}
// 	return 0;
  
// }

// /*-----  End of HASH TABLE  ------*/

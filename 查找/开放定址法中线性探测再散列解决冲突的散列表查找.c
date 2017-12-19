#define SUCCESS 1
#define DUPLICATE -1
#define NULLKEY -2
#define FULL -3
#define EQ(a,b) ((a)==(b))
typedef int KeyType;
int hashsize[];
typedef struct
{
	KeyType *elem;
	int count;
	int sizeindex;
}HashTable;
int hash_search(KeyType v, HashTable t) // v是查找的给定值，t为散列表
{
	int c, sup;
	c = 0;
	sup = hashsize[t.sizeindex] / 2;
	int *p = v % hashsize[t.sizeindex];
	while (1)
	{
		if (t.elem[*p] == NULLKEY)
			return NULLKEY;
		else if (EQ(t.elem[*p], v))
			return DUPLICATE;
		else if (++c == sup)
			return FULL;
		else
			*p = (*p + 1) % hashsize[t.sizeindex];
	}
}
#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))
#define LQ(a,b) ((a)<=(b))

void heap_sort(int a[], int n)
{
	int i;
	int tmp;
	for (i = n / 2; i > 0; i--)
		HeapAdjust(a, i, n);
	for (i = n; i > 1; i--)
	{
		tmp = a[1];
		a[1] = a[i];
		a[i] = tmp;
		HeapAdjust(a, 1, i - 1);
	}
}

void HeapAdjust(int a[], int s, int m)
{
	int j;
	int rc;
	rc = a[s];
	for (j = 2*s;j <= m;j *= 2)
	{
		if (j < m && LT(a[j], a[j + 1]))
			j++;
		if (!LT(rc, a[j]) )
			break;
		a[s] = a[j];
		s = j;
	}
	a[s] = rc;
}
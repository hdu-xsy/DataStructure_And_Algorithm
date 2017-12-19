#define LT(a,b) ((a)<(b))
void insert_sort(int a[], int n)
{
	int i, j;
	for (i = 2; i <= n; i++)
	{
		if (LT(a[i], a[i - 1]))
		{
			a[0] = a[i];
			a[i] = a[i - 1];
			for (j = i - 1; LT(a[0], a[j]); --j)
				a[j + 1] = a[j];
			a[j + 1] = a[0];
		}
	}
}
void quick_sort(int a[], int n)
{
	int pivotkey;
	int low = 1;
	int high = n;
	a[0] = a[low];
	pivotkey = a[low];
	while (low < high)
	{
		while (low < high && a[high] >= pivotkey)
			high--;
		a[low] = a[high];
		while (low < high && a[low] <= pivotkey)
			low++;
		a[high] = a[low];
	}
	a[low] = a[0];
	return low;
}

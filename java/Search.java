public class Search {

    public static int sequenceSearch(int a[],int key) {
        int i = a.length-1;
        a[0] = key;
        while(a[i] != key)
            i--;
        return i;
    }

    public static int binarySearch(int a[],int key) {
        int low = 0,high = a.length-1,mid;
        while (low <= high) {
            mid = (low + high)/2;
            if(a[mid] == key) return mid;
            else if(a[mid] > key) high = mid-1;
            else low = mid +1 ;
        }
        return -1;
    }

}

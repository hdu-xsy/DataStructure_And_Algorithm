import org.junit.Test;

import java.util.Arrays;

public class SortTest {

    @Test
    public void insertSortTest() {
        int[] i = new int[]{0,2,5,4,3,6,7,9,8};
        Sort.insertSort(i);
        System.out.println(Arrays.toString(i));
    }

    @Test
    public void shellSortTest() {
        int[] i = new int[]{0,2,5,4,3,6,7,9,8};
        Sort.shellSort(i);
        System.out.println(Arrays.toString(i));
    }

    @Test
    public void bubbleSortTest() {
        int[] i = new int[]{10,2,5,4,3,6,7,9,8};
        Sort.bubbleSort(i);
        System.out.println(Arrays.toString(i));
    }

    @Test
    public void quickSortTest() {
        int[] i = new int[]{10,2,5,4,3,6,7,9,8};
        Sort.quickSort(i,0,8);
        System.out.println(Arrays.toString(i));
    }

    @Test
    public void selectSortTest() {
        int[] i = new int[]{10,2,5,4,3,6,7,9,8};
        Sort.selectSort(i);
        System.out.println(Arrays.toString(i));
    }

    @Test
    public void heapSortTest() {
        int[] i = new int[]{0,2,5,4,3,6,7,9,8};
        Sort.heapSort(i);
        System.out.println(Arrays.toString(i));
    }

    @Test
    public void mergeSortTest() {
        int[] i = new int[]{0,2,5,4,3,6,7,9,8};
        Sort.mergeSort(i,0,i.length-1);
        System.out.println(Arrays.toString(i));
    }
}

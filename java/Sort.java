public class Sort {

    private static boolean LT(int a,int b) {
        if(a < b) return true;
        else return false;
    }

    private static boolean RT(int a,int b) {
        if(a > b) return true;
        else return false;
    }


    public static void insertSort(int[] SqList) {
        /*
        伪代码
         void InsertSort(SqlList &L) {
           for(i=2;i<L.Length;++i)
               if(LT(L.r[i].key,L.r[i-1].key)) {
                L.r[0] = L.r[i];    //复制为哨兵
                L.r[i] = L.r[i-1];
                for(j=i-2;LT(L.r[0].key,L.r[j].key);--j)
                    L.r[j+1] = L.r[j];  //记录后移
                L.r[j+1] = L.r[0];  //插入到正确位置
               }
         }
        */
        if(SqList == null) return;
        for (int i = 2; i < SqList.length; i++) {
            SqList[0] = SqList[i];
            for (int j = i-1; LT(SqList[0],SqList[j]); j--) {
                SqList[j+1] = SqList[j];
                SqList[j] = SqList[0];
            }
        }
    }


    public static void shellSort(int[] L) {
        int i,j,n=L.length-1;
        for (int dk = n / 2; dk >= 1; dk = dk / 2)  //初始长度为总长度的一般
            for (i = dk + 1; i <= n; i++)   //最后一次为1
                if (L[i] < L[i - dk]) {
                    L[0] = L[i];    //暂存在0
                    for (j = i - dk; j > 0 && L[0] < L[j]; j -= dk)
                        L[j + dk] = L[j];
                    L[j + dk] = L[0];
                }
    }

    public static void bubbleSort(int[] L) {
        for (int i = 0; i < L.length-1; i++) {
            boolean flag = false;
            for (int j = L.length-1; j > i; j--)    //一趟冒泡过程
                if(L[j-1] > L[j]) {
                    int temp = L[j-1];
                    L[j-1] = L[j];
                    L[j] = temp;
                    flag = true;
                }
            if(flag == false) return;
        }
    }

    private static int Partition(int[] L,int low,int high) {   //low是当前待排序的序列出事下标,high是末尾下标
        int pivot = L[low]; //第一个元素作为枢轴
        while(low < high) {
            while(low < high && L[high] >= pivot) --high;   //第一个比枢轴小元素
            L[low] = L[high];   //替换
            while(low < high && L[low] <= pivot) ++low; //第一个比枢轴大的元素
            L[high] = L[low];   //替换
        }
        L[low] = pivot;
        return low;
    }

    public static void quickSort(int[] L,int low,int high) {
        if(low < high) {
            int pivopos = Partition(L,low,high);
            quickSort(L,low,pivopos-1);
            quickSort(L,pivopos+1,high);
        }
    }

    public static void selectSort(int[] L) {
        int min;
        for (int i = 0; i < L.length-1; i++) {  //依次从后面选择当前当前最小元素作为第i个元素,最后一个元素不需要排序
            min = i;    //当前最小元素所在的小标,初值设为第i个
            for (int j = i+1; j < L.length; j++)   //从第i个元素往后找,一直找到最后一个元素
                if(L[j] < L[min]) min = j;
            if(min != i) {
                int temp = L[i];
                L[i] = L[min];
                L[min] = temp;
            }
        }
    }

    private static void buildMaxHeap(int[] L,int len) {
        for (int i = len/2; i > 0; i--)  adjustDown(L,i,len);
    }

    private static void adjustDown(int[] L,int k,int len) { //k是要检查的结点下标
        L[0] = L[k];
        for (int i = 2 * k; i <= len; i*=2) {  //左孩子开始往下比较
            if(i < len && L[i] < L[i+1]) i++;    //如果发生交换,对交换过的结点继续和它的孩子比较
            if(L[0]>=L[i]) break;   //如果这个结点的值不小于它的较大孩子节点值,则不交换
            else {
                L[k] = L[i];
                k = i;
            }
        }
        L[k] = L[0];
    }

    public static void heapSort(int[] L) {
        int len = L.length-1;
        buildMaxHeap(L,len);
        for (int i = len; i > 1; i--) {
            //输出堆顶元素
            int temp = L[i];
            L[i] = L[1];
            L[1] = temp;
            adjustDown(L,1,i-1);
        }
    }

    private static void merge(int[] a, int low, int mid, int high) {
        int[] temp = new int[high-low+1];
        int i= low;
        int j = mid+1;
        int k=0;
        // 把较小的数先移到新数组中
        while(i<=mid && j<=high){
            if(a[i]<a[j]){
                temp[k++] = a[i++];
            }else{
                temp[k++] = a[j++];
            }
        }
        // 把左边剩余的数移入数组
        while(i<=mid){
            temp[k++] = a[i++];
        }
        // 把右边边剩余的数移入数组
        while(j<=high){
            temp[k++] = a[j++];
        }
        // 把新数组中的数覆盖nums数组
        for(int x=0;x<temp.length;x++){
            a[x+low] = temp[x];
        }
    }

    public static void mergeSort(int[] L,int low,int high) {
        int mid = (low+high)/2;
        if(low<high){
            mergeSort(L,low,mid);
            mergeSort(L,mid+1,high);
            //左右归并
            merge(L,low,mid,high);
        }
    }

}

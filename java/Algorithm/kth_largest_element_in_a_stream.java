package Algorithm;

import java.util.Arrays;
import java.util.PriorityQueue;

/**
 * 设计一个找到数据流中第K大元素的类（class）。注意是排序后的第K大元素，不是第K个不同的元素。
 *
 * 你的 KthLargest 类需要一个同时接收整数 k 和整数数组nums 的构造器，它包含数据流中的初始元素。每次调用 KthLargest.add，返回当前数据流中第K大的元素。
 *
 * 示例:
 *
 * int k = 3;
 * int[] arr = [4,5,8,2];
 * KthLargest kthLargest = new KthLargest(3, arr);
 * kthLargest.add(3);   // returns 4
 * kthLargest.add(5);   // returns 5
 * kthLargest.add(10);  // returns 5
 * kthLargest.add(9);   // returns 8
 * kthLargest.add(4);   // returns 8
 * */
public class kth_largest_element_in_a_stream {

    /**
     * 维护含k个元素的小顶堆
     * */

    class KthLargest {

        private int k = 0;

        private PriorityQueue<Integer> priorityQueue;

        public KthLargest(int k, int[] nums) {
            this.k = k;
            priorityQueue = new PriorityQueue<Integer>(k);
            for(int i : nums) add(i);
        }

        public int add(int val) {
            if(priorityQueue.size() < k) priorityQueue.add(val);
            else if (val >= priorityQueue.peek()) {
                priorityQueue.poll();
                priorityQueue.add(val);
            }
            return priorityQueue.peek();
        }

    }
}
/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest obj = new KthLargest(k, nums);
 * int param_1 = obj.add(val);
 */

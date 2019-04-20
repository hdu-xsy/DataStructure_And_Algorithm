package Algorithm;

import java.util.*;

/**
给定一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？找出所有满足条件且不重复的三元组。

注意：答案中不可以包含重复的三元组。

例如, 给定数组 nums = [-1, 0, 1, 2, -1, -4]，

满足要求的三元组集合为：
[
  [-1, 0, 1],
  [-1, -1, 2]
]
*/

public class ThreeSum {
    /**
     * 1.暴力循环 O(N^3)
     * 2.使用Set O(N^2)
     * 3.先排序O(Nlog(N)),后查找,枚举一个数,另外两个数从后面的数组两边往中间夹 O(N^2)
     * */

    public List<List<Integer>> threeSum(int[] nums) {
        Set<List<Integer>> set = new HashSet<>();
        Arrays.sort(nums);
        int length = nums.length;
        for (int i = 0; i < length-2; i++) {
            if (i != 0 && nums[i-1] == nums[i]) continue;
            int min = i + 1;
            int max = length-1;
            while(min != max) {
                if(nums[i] + nums[min] + nums[max] == 0) {
                    set.add(Arrays.asList(nums[i], nums[min], nums[max]));
                    min = min + 1;
                } else if(nums[i] + nums[min] + nums[max] < 0)
                    min = min + 1;
                else max = max - 1;
            }
        }
        return new ArrayList<>(set);
    }
}

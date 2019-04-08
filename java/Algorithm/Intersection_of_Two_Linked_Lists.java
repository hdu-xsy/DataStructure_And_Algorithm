package Algorithm;

/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) {
 *         val = x;
 *         next = null;
 *     }
 * }
 */

/**
 * 编写一个程序，找到两个单链表相交的起始节点。
 * 输入：intersectVal = 8, listA = [4,1,8,4,5], listB = [5,0,1,8,4,5], skipA = 2, skipB = 3
 * 输出：Reference of the node with value = 8
 * 输入解释：相交节点的值为 8 （注意，如果两个列表相交则不能为 0）。从各自的表头开始算起，链表 A 为 [4,1,8,4,5]，链表 B 为 [5,0,1,8,4,5]。在 A 中，相交节点前有 2 个节点；在 B 中，相交节点前有 3 个节点。
 */

public class Intersection_of_Two_Linked_Lists {

    /**
     * 先判断是否相交
     * 计算两者长度
     * 长度差即两者头节点距离公共交点的距离差
     * */
    private class ListNode {
        int val;
        ListNode next;
        ListNode(int x) {
            val = x;
            next = null;
        }
    }

    public ListNode getIntersectionNode(ListNode headA, ListNode headB) {
        if(headA == null || headB == null) return null;
        ListNode pA = headA;
        ListNode pB = headB;
        int lenA = 1;
        int lenB = 1;
        while (pA.next != null) {
            pA = pA.next;
            lenA++;
        }
        while (pB.next != null) {
            pB = pB.next;
            lenB++;
        }
        if(pA != pB) return null;
        ListNode tA = headA;
        ListNode tB = headB;
        if(lenA > lenB) {
            int d = lenA - lenB;
            while(d!=0) {
                tA = tA.next;
                d--;
            }
        }else {
            int d = lenB - lenA;
            while (d!=0) {
                tB = tB.next;
                d--;
            }
        }
        while(tA != tB) {
            tA = tA.next;
            tB = tB.next;
        }
        return tA;
    }
}

/**
 *         if(headA == null || headB == null) return null;
 *         ListNode pA = headA, pB = headB;
 *         while(pA != pB) {
 *             pA = pA == null ? headB : pA.next;
 *             pB = pB == null ? headA : pB.next;
 *         }
 *         return pA;
 */


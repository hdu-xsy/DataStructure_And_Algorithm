package Algorithm;

import java.util.Stack;

/**
 * 使用栈实现队列的下列操作：
 *
 * push(x) -- 将一个元素放入队列的尾部。
 * pop() -- 从队列首部移除元素。
 * peek() -- 返回队列首部的元素。
 * empty() -- 返回队列是否为空。
 * 示例:
 *
 * MyQueue queue = new MyQueue();
 *
 * queue.push(1);
 * queue.push(2);
 * queue.peek();  // 返回 1
 * queue.pop();   // 返回 1
 * queue.empty(); // 返回 false
 * */
public class Implement_Queue_Using_Stacks {

    /**
     * 进队列时入栈1
     * 出队列时若站栈2不为空则出栈,否则栈1全部元素入栈2
     * */
    public class MyQueue {

        private Stack<Integer> stackIn = new Stack<Integer>();
        private Stack<Integer> stackOut = new Stack<Integer>();

        /** Initialize your data structure here. */
        public MyQueue() {

        }

        /** Push element x to the back of queue. */
        public void push(int x) {
            stackIn.push(x);
        }

        /** Removes the element from in front of queue and returns that element. */
        public int pop() {
            if(stackOut.empty()) {
                while (!stackIn.empty()) {
                    stackOut.push(stackIn.pop());
                }
            }
            return stackOut.pop();
        }

        /** Get the front element. */
        public int peek() {
            if(stackOut.empty()) {
                while (!stackIn.empty()) {
                    stackOut.push(stackIn.pop());
                }
            }
            return stackOut.peek();
        }

        /** Returns whether the queue is empty. */
        public boolean empty() {
            return stackIn.empty() && stackOut.empty();
        }
    }

}

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue obj = new MyQueue();
 * obj.push(x);
 * int param_2 = obj.pop();
 * int param_3 = obj.peek();
 * boolean param_4 = obj.empty();
 */


import java.util.Stack;

public class Tree {

    private class Node {
        public int data;

        public Node left;

        public Node right;

        public Node(){}

        public Node(int data) {
            this.data = data;
            this.left = null;
            this.right = null;
        }
    }

    private Node root;

    public Tree() {
        root = null;
    }

    //后序遍历递归
    public void postOrder(Node localRoot) {
        postOrder(localRoot.left);
        postOrder(localRoot.right);
        System.out.print(localRoot.data + " ");
    }

    public void postOrder() {
        Stack<Node> s = new Stack<>();
        Node current;   //当前结点
        Node pre = null;    //前一次访问的结点

        s.push(this.root);
        while(false == s.empty()) {
            current = s.peek();
            if((null == current.left && null == current.right) ||
                    (null != pre && ( pre == current.left || pre == current.right))) {
                System.out.println(current.data + " ");  //如果当前结点没有孩子结点或者孩子节点都已被访问过
                s.pop();
                pre = current;
            } else {
                if(null != current.right) s.push(current.right);
                if(null != current.left) s.push(current.left);
            }
        }
    }

    public void initTree(int[] preOrder,int[] inOrder) {
        this.root = this.initTree(preOrder,0,preOrder.length-1,inOrder,0,inOrder.length-1);
    }

    public Node initTree(int[] preOrder,int start1,int end1,int[] inOrder,int start2,int end2) {
        if(start1 > end1 || start2 > end2) return null;
        int rootData = preOrder[start1];
        Node head = new Node(rootData);
        int rootIndex = findIndexInArray(inOrder,rootData,start2,end2);
        int offSet = rootIndex - start2 -1;
        Node left = initTree(preOrder,start1+1,start1+1+offSet,inOrder,start2,start2+offSet);
        Node right = initTree(preOrder,start1+offSet+2,end1,inOrder,rootIndex+1,end2);
        head.left = left;
        head.right = right;
        return head;
    }

    public int findIndexInArray(int[] a,int x,int begin,int end) {
        for (int i = begin; i <= end; i++) {
            if(a[i] == x) return i;
        }
        return -1;
    }




}

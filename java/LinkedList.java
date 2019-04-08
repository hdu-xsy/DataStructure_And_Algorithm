import java.util.Hashtable;

public class LinkedList {

    private Node head = null;

    public Node getHead() {
        return head;
    }

    public LinkedList add(int data) {
        Node node = new Node(data);
        if(head == null) {
            head = node;
            return this;
        }
        Node tmp = head;
        while(tmp.next != null) {
            tmp = tmp.next;
        }
        tmp.next = node;
        return this;
    }

    public void print() {
        Node tmp = head;
        if (tmp == null) return;
        while(tmp.next != null) {
            System.out.print(tmp.data + ",");
            tmp = tmp.next;
        }
        System.out.println(tmp.data);
    }

    public int length() {
        Node tmp = head;
        int i = 1;
        while(tmp.next != null) {
            tmp = tmp.next;
            i++;
        }
        return i;
    }

    public void remove(int i) {
        if (i==0) {
            head = head.next;
            return;
        }
        if (i >= length()) {
            throw new IllegalArgumentException("越界");
        }
        Node tmp = head;
        int n = 0;
        while(head.next != null && n < i - 1) {
            tmp = tmp.next;
            n++;
        }
        if(tmp.next == null)
            tmp.next = null;
        else
            tmp.next = tmp.next.next;
    }

    public void deleteDuplecate() {
        Hashtable<Integer,Integer> hashtable = new Hashtable<Integer, Integer>();
        Node tmp = head;
        Node pre = null;
        while(tmp != null) {
            if(hashtable.containsKey(tmp.data)) {
                pre.next = tmp.next;
                tmp = tmp.next;
            }
            else {
                hashtable.put(tmp.data,1);
                pre = tmp;
                tmp = tmp.next;
            }
        }
    }

    public void reverseIteratively() {
        //非递归
        Node pRecersedHead = head;
        Node pNode = head;
        Node pPrev = null;
        while(pNode != null) {
            Node pNext = pNode.next;
            if(pNext == null) pRecersedHead = pNode;
            pNode.next = pPrev;
            pPrev = pNode;
            pNode = pNext;
        }
        this.head = pRecersedHead;
    }

    public Node reverseIteratively(Node head) {
        //递归
        if(head == null || head.next == null) return head;
        else {
            Node newHead = reverseIteratively(head.next);
            head.next.next = head;
            head.next = null;
            if(head == this.head) this.head = newHead;
            return newHead;
        }
    }

    public void printListReversely(Node node) {
        if(node != null) {
            printListReversely(node.next);
            System.out.print(node.data);
        }

    }

    public Node getMid() {
        Node p = head;
        Node q = head;
        while(p != null && p.next != null && p.next.next != null) {
            p = p.next.next;
            q = q.next;
        }
        return q;
    }

}

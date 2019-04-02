public class LinkedList {

    private Node head = null;

    public void add(int data) {
        Node node = new Node(data);
        if(head == null) {
            head = node;
            return;
        }
        Node tmp = head;
        while(tmp.next != null) {
            tmp = tmp.next;
        }
        tmp.next = node;
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
}

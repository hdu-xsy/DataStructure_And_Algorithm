import org.junit.Test;

public class LinkedListTest {

    @Test
    public void addTest() {
        LinkedList linkedList = new LinkedList();
        linkedList.add(1);
        linkedList.add(2);
        linkedList.add(3);
        linkedList.add(4);
        linkedList.add(5);
        System.out.println(linkedList.length());
        linkedList.print();
        linkedList.remove(3);
        System.out.println(linkedList.length());
        linkedList.print();
        linkedList.add(555);
        linkedList.print();
    }
}

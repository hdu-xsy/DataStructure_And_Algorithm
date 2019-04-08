package Algorithm;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
/**
 * 平时哲学家围坐在圆桌交替进行思考和进餐，饥饿时试图分别取两侧筷子，只有两只筷子都拿到后才能进餐
 * 死锁解决：
 * 1.限制最多拿筷子的哲学家数量，至少保证一个哲学家拿到两个筷子
 * 2.只有左右筷子都可拿时才允许拿
 * 3.规定奇数先取左侧偶数先取右侧
 * */
public class Philosopher implements Runnable{

    private int times = 20;

    private final int philosophers = 3;

    private int id;

    private int left;

    private int right;

    private Lock lock; //= new ReentrantLock();

    private Condition[] locks;// = new Condition[philosophers];

    private boolean[] chop;// = new boolean[philosophers];

    Philosopher(int id,Lock lock,Condition[] conditions,boolean[] chop) {
        this.lock = lock;
        this.locks = conditions;
        this.chop = chop;
        this.id = id;
        this.left = id;
        this.right = (id+1) % philosophers;
    }

    private void eating() throws InterruptedException{
        lock.lock();
        try {
            while(!chop[left] || !chop[right]) {
                System.out.println(id + "等待筷子");
                locks[id].await();
            }
            chop[left] = false;
            chop[right] = false;
        } finally {
            lock.unlock();
        }
        System.out.println(id+"开始吃饭");
        Thread.sleep(1000);
    }

    private void sleeping() throws InterruptedException{
        lock.lock();
        try {
            chop[left] = true;
            chop[right] = true;
            System.out.println(id + "开始睡觉");
            if(chop[(left+philosophers-1) % philosophers]) locks[(left+philosophers-1)%philosophers].signal();
            if(chop[(right+1) % philosophers]) locks[(right+1) % philosophers].signal();
        } finally {
            lock.unlock();
        }
        Thread.sleep(1000);
    }

    public void run() {
        try {
            while (times >= 0) {
                eating();
                sleeping();
                times--;
            }
        }catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

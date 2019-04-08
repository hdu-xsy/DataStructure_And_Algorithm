package Algorithm;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 * 一位理发师、一把理发椅、n把等候椅
 * 第一个顾客叫醒理发师，后来的若有空位则等待
 * 没有顾客时理发师睡觉
 * */
public class BarberShop {

    private static final int MAX_CUSTOMER = 3;

    private static int waiting = 0;

    private static Lock lock = new ReentrantLock();

    private static Condition cust_ready = lock.newCondition(); //理发椅是否有顾客

    private static boolean is_cust_ready = false;

    private static Condition finished = lock.newCondition();   //是否完成理发

    private static Lock mutex = new ReentrantLock(); //互斥访问waiting

    private static Lock chair = new ReentrantLock();  //椅子是否空闲

    private static void cut_hair() {
        System.out.println("开始理发");
    }

    private static void exit_barbershop(int i) {
        System.out.println("当前人数:" + waiting + " "+ i +" 离开理发店");
    }

    private static void sit_in_chair(int i) {
        System.out.println(i + "在等待椅坐下");
    }

    private static void stand_from_chair(int i) {
        System.out.println(i + "从椅子站起");
    }
    public static void barber () {
        lock.lock();
        try {
            while (true) {
                if(!is_cust_ready) {
                    System.out.println("等待顾客");
                    cust_ready.await();
                }
                cut_hair();
                Thread.sleep(1000);
                is_cust_ready = false;
                finished.signal();
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            lock.unlock();
        }
        /**
         * do {
         *  wait(cust_ready);
         *  cut_hair;
         *  signal(finished);
         * }while(1);
         * */
    }

    public static void customer(int i) {
        mutex.lock();
        if (waiting < MAX_CUSTOMER) {
            waiting = waiting + 1;
            mutex.unlock();
        } else {
            mutex.unlock();
            exit_barbershop(i);
            return;
        }
        chair.lock();
        sit_in_chair(i);
        mutex.lock();
        waiting = waiting + 1;
        mutex.unlock();
        lock.lock();
        try {
            is_cust_ready = true;
            cust_ready.signal();
            finished.await();
            stand_from_chair(i);
            waiting = waiting - 1;
            chair.unlock();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            lock.unlock();
        }
        /**
         * wait(mutex);
         * if(waiting < n) {
         *  waiting = waiting +1;
         *  signal(mutex);
         * } else {
         *  signal(mutex)
         *  exit_barbershop
         *  return;
         * }
         * wait(chair)
         * sit_in_chair
         * wait(mutex)
         * waiting = waiting -1
         * signal(mutex)
         * signal(cust_ready)
         * get_haircut
         * wait(finished)
         * stand_from_chair
         * signal(chair)
         * */
    }
}

/**
 * private static class Barber implements Runnable{
 *         public void run() {
 *             BarberShop.barber();
 *         }
 *     }
 *
 *     private static class Customer implements Runnable {
 *
 *         private int i;
 *
 *         public Customer(int i) {
 *             this.i = i;
 *         }
 *
 *         public void run() {
 *             BarberShop.customer(i);
 *         }
 *     }
 *
 *     @Test
 *     public void  barber() throws Exception{
 *         Thread[] customers = new Thread[10];
 *         Thread t1 = new Thread(new Barber());
 *         t1.start();
 *         for (int i = 0; i < 10; i++) {
 *             int time = (int)(Math.random() * 1000);
 *             Thread.sleep(time);
 *             customers[i] = new Thread(new Customer(i));
 *             customers[i].start();
 *         }
 *         for (int i = 0; i < 10; i++) {
 *             customers[i].join();
 *         }
 *         t1.join();
 *     }
 * */
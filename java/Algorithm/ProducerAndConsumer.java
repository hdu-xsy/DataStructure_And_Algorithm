package Algorithm;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
/**
 * m个生产者和n个消费者　共享k个缓冲池区的循环缓冲池
 * 生产者不能从一个空缓冲区中取产品，生产者不能向一个已装满的缓冲池投放产品
 * */
public class ProducerAndConsumer {

    private static final int k = 10;

    private static int cons = 0;

    private static int[] buffer = new int[k];

    private static int in = 0;

    private static int out = 0;

    private static int num = 0;

    private static int nums = 100;

    private static Lock mutex = new ReentrantLock();

    private static Condition emptyLock = mutex.newCondition();

    private static Condition fullLock = mutex.newCondition();

    public static void produce() throws InterruptedException{
        do {
            mutex.lock();
            try {
                if (cons >= k) fullLock.await();
                num++;
                buffer[in] = num;
                in = (in + 1) % k;
                cons++;
                System.out.println("produce : cons = " + cons);
                if (cons > 0) emptyLock.signal();
            }finally {
                mutex.unlock();
            }
            /**
             * produce
             * wait(empty)
             * wait(mutex)
             * buffer(in) = num;
             * in = (in+1) mod k
             * signal(mutex)
             * signal(full)
             */
        }while (num < nums);
    }

    public static void consumer() throws InterruptedException{
        do {
            mutex.lock();
            try {
                if (cons <= 0) emptyLock.await();
                System.out.println("get " + buffer[out]);
                buffer[out] = -1;
                out = (out + 1) % k;
                cons--;
                System.out.println("consumer : cons = " + cons);
                if (cons < k) fullLock.signal();
            } finally {
                mutex.unlock();
            }
            /**
             * wait(full)
             * wait(mutex)
             * num = buffer(out);
             * out = (out+1) mod k
             * signal(mutex)
             * signal(empty)
             * consumer
             */
        }while (num <= nums);
    }
}

/**
 * @Test
 *     public void ProducerAndConsumerTest() throws Exception{
 *         Thread t1 = new Thread(new Producer());
 *         Thread t2 = new Thread(new Consumer());
 *         t1.start();
 *         t2.start();
 *         t1.join();
 *         t2.join();
 *     }
 *
 *     private class Producer implements Runnable {
 *         public void run() {
 *             try {
 *                 ProducerAndConsumer.produce();
 *             } catch (Exception e) {
 *                 e.printStackTrace();
 *             }
 *         }
 *     }
 *
 *     private class Consumer implements Runnable {
 *         public void run() {
 *             try {
 *                 ProducerAndConsumer.consumer();
 *             } catch (Exception e) {
 *                 e.printStackTrace();
 *             }
 *         }
 *     }
 * */

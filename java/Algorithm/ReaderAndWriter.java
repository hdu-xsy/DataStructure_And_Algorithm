package Algorithm;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

/**
 * 任意多个Reader可以读
 * 只能有一个Writer可以写
 * 写的时候不能读
 * */
public class ReaderAndWriter {

    private static int text = 0;

    private static ReentrantReadWriteLock rwl = new ReentrantReadWriteLock();

    public static void read() {
        try {
            rwl.readLock().lock();
            Thread.sleep(300);
            System.out.println("read " + text);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            rwl.readLock().unlock();
        }
    }

    public static void write() {
        try {
            rwl.writeLock().lock();
            int num = (int) (Math.random() * 1000);
            System.out.println("writing");
            text = num;
            Thread.sleep(2000);
            System.out.println("write " + num);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            rwl.writeLock().unlock();
        }
    }
}

/**
 * private class Writer implements Runnable {
 *         public void run() {
 *             while (true)
 *                 if(((int)(Math.random()*100000))%3333 == ((int)(Math.random()*100000))%3333)
 *                     ReaderAndWriter.write();
 *         }
 *     }
 *
 *     private class Reader implements Runnable {
 *         public void run() {
 *             while (true)
 *                 ReaderAndWriter.read();
 *         }
 *     }
 *
 *     @Test
 *     public void ReaderAndWriterTest() throws Exception{
 *         Thread[] readerThreads = new Thread[4];
 *         Thread[] writerThreads = new Thread[2];
 *
 *         for (int i = 0; i < 2; i++) {
 *             writerThreads[i] = new Thread(new Writer());
 *             writerThreads[i].start();
 *         }
 *
 *         for (int i = 0; i < 4; i++) {
 *             readerThreads[i] = new Thread(new Reader());
 *             readerThreads[i].start();
 *         }
 *
 *         for (int i = 0; i < 4; i++) {
 *             writerThreads[i].join();
 *         }
 *
 *         for (int i = 0; i < 2; i++) {
 *             writerThreads[i].join();
 *         }
 *
 *     }
 * */
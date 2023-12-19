
import java.util.Random;
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class boundedBuffer {
    private final String[] buffer;
    private final int capacity;

    private int front;
    private int rear;
    private int count;

    private final Lock lock = new ReentrantLock();

    private final Condition notFull = lock.newCondition();
    private final Condition notEmpty = lock.newCondition();

    public boundedBuffer(int capacity) {
        super();

        this.capacity = capacity;

        buffer = new String[capacity];
    }

    public void deposit(String data) throws InterruptedException {
        lock.lock();

        try {
            while (count == capacity) {
                notFull.await();
            }

            buffer[rear] = data;
            rear = (rear + 1) % capacity;
            count++;

            notEmpty.signal();
        } finally {
            lock.unlock();
        }
    }

    public String fetch() throws InterruptedException {
        lock.lock();

        try {
            while (count == 0) {
                notEmpty.await();
            }

            String result = buffer[front];
            front = (front + 1) % capacity;
            count--;

            notFull.signal();

            return result;
        } finally {
            lock.unlock();
        }
    }
    public static void main(String[] args) throws InterruptedException {
        boundedBuffer buffer = new boundedBuffer(100);


        Thread t1 = new Thread(new Runnable() {
            Random random = ThreadLocalRandom.current();
            @Override
            public void run() {
                for (int i = 0; i < 30; i++) {
                    try {
                        buffer.deposit(String.format("%d-%05d", Thread.currentThread().getId(), random.nextInt(100000)));
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        });
        Thread t2 = new Thread(new Runnable() {
            Random random = ThreadLocalRandom.current();
            @Override
            public void run() {
                for (int i = 0; i < 30; i++) {
                    try {
                        buffer.deposit(String.format("%d-%05d", Thread.currentThread().getId(), random.nextInt(100000)));
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        });
        Thread t3 = new Thread(new Runnable() {
            Random random = ThreadLocalRandom.current();
            @Override
            public void run() {
                for (int i = 0; i < 30; i++) {
                    try {
                        buffer.deposit(String.format("%d-%05d", Thread.currentThread().getId(), random.nextInt(100000)));
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        });
        Thread t4 = new Thread(new Runnable() {

            @Override
            public void run() {
                for (int i = 0; i < 90; i++) {
                    try {
                        System.out.println(buffer.fetch());
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        });


        t1.start();
        t2.start();
        t3.start();
        t4.start();

        t1.join();
        t2.join();
        t3.join();
        t4.join();

    }

}






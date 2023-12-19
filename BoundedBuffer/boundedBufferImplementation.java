import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class boundedBufferImplementation {
    private final String[] buffer;
    private final int capacity;

    private int front;
    private int rear;
    private int count;

    private final Lock lock = new ReentrantLock();

    private final Condition notFull = lock.newCondition();
    private final Condition notEmpty = lock.newCondition();

    public boundedBufferImplementation(int capacity) {
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
        boundedBufferImplementation buffer = new boundedBufferImplementation(3);


        Thread producer = new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    buffer.deposit("Hello");
                    buffer.deposit("World");
                    buffer.deposit("!");
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        });



        Thread consumer = new Thread(new Runnable() {
            @Override
            public void run() {
                try{
                    System.out.println(buffer.fetch());
                    System.out.println(buffer.fetch());
                    System.out.println(buffer.fetch());
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        });



        producer.start();
        consumer.start();

        producer.join();
        consumer.join();

    }
}






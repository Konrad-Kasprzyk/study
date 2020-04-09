package l4z1;

import org.junit.Assert;
import org.junit.Test;

public class SingletonTest {
    @Test
    public void ProcessSingleton_UniqueTest(){
        ProcessSingleton s1 = ProcessSingleton.Instance();
        ProcessSingleton s2 = ProcessSingleton.Instance();
        Assert.assertEquals(s1, s2);
    }

    static int s1_hash = 0, s2_hash = 0;
    @Test
    public void ThreadSingleton_UniqueTest() throws InterruptedException {
        for (int i=0; i<10; i++){
            Thread thread = new Thread(new Runnable()
            {
                @Override
                public void run()
                {
                    ThreadSingleton s1 = ThreadSingleton.Instance();
                    ThreadSingleton s2 = ThreadSingleton.Instance();
                    s1_hash = s1.hashCode();
                    s2_hash = s2.hashCode();
                }
            });
            thread.start();
            thread.join();
            Assert.assertEquals(s1_hash, s2_hash);
        }
    }

    @Test
    public void ThreadSingleton_UniqueTest2() throws InterruptedException {
        for (int i=0; i<10; i++){
            Thread thread = new Thread(new Runnable()
            {
                @Override
                public void run()
                {
                    ThreadSingleton s1 = ThreadSingleton.Instance();
                    s1_hash = s1.hashCode();
                }
            });
            thread.start();
            thread.join();
            int thread1_singleton = s1_hash;
            thread = new Thread(new Runnable()
            {
                @Override
                public void run()
                {
                    ThreadSingleton s1 = ThreadSingleton.Instance();
                    s1_hash = s1.hashCode();
                }
            });
            thread.start();
            thread.join();
            int thread2_singleton = s1_hash;
            Assert.assertNotEquals(thread1_singleton, thread2_singleton);
        }
    }

    @Test
    public void FiveSecondsSingleton_UniqueTest1(){
        FiveSecondsSingleton s1 = FiveSecondsSingleton.Instance();
        FiveSecondsSingleton s2 = FiveSecondsSingleton.Instance();
        Assert.assertEquals(s1, s2);
    }

    @Test
    public void FiveSecondsSingleton_UniqueTest2(){
        FiveSecondsSingleton s1 = FiveSecondsSingleton.Instance();
        long start = System.currentTimeMillis();
        long curr = System.currentTimeMillis();
        while(curr - start < FiveSecondsSingleton.MinTimeInterval() - 1000){
            curr = System.currentTimeMillis();
        }
        FiveSecondsSingleton s2 = FiveSecondsSingleton.Instance();
        Assert.assertEquals(s1, s2);
    }

    @Test
    public void FiveSecondsSingleton_UniqueTest3(){
        FiveSecondsSingleton s1 = FiveSecondsSingleton.Instance();
        long start = System.currentTimeMillis();
        long curr = System.currentTimeMillis();
        while(curr - start < FiveSecondsSingleton.MinTimeInterval()){
            curr = System.currentTimeMillis();
        }
        FiveSecondsSingleton s2 = FiveSecondsSingleton.Instance();
        Assert.assertNotEquals(s1, s2);
    }
}

package l4z1;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Main {
    public static void main(String[] args){
    }
}

class ProcessSingleton{
    private static ProcessSingleton _instance;
    private static Lock lock = new ReentrantLock();
    public static ProcessSingleton Instance(){
        if ( _instance == null ){
            lock.lock();
            try {
                if ( _instance == null )
                    _instance = new ProcessSingleton();
            } finally {
                lock.unlock();
            }
        }
        return _instance;
    }
}

class ThreadSingleton{
    private static ThreadLocal<ThreadSingleton> _threadLocal =
            ThreadLocal.withInitial(() -> new ThreadSingleton());
    public static ThreadSingleton Instance() {
        return _threadLocal.get();
    }
}

class FiveSecondsSingleton{
    public static long lastDeployedTime = System.currentTimeMillis();
    private static long minTimeInterval = 5000;
    private static FiveSecondsSingleton _instance;
    private static Lock lock = new ReentrantLock();
    public static FiveSecondsSingleton Instance(){
        if ( _instance == null || System.currentTimeMillis() - lastDeployedTime > minTimeInterval){
            lock.lock();
            try {
                if ( _instance == null || System.currentTimeMillis() - lastDeployedTime > minTimeInterval){
                    _instance = new FiveSecondsSingleton();
                    lastDeployedTime = System.currentTimeMillis();
                }
            } finally {
                lock.unlock();
            }
        }
        return _instance;
    }
    public static long MinTimeInterval(){
        return minTimeInterval;
    }
}

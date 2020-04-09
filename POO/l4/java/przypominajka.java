class ThreadSingleton{
    private static Map<Integer, ThreadSingleton> mapSingleton = new HashMap<Integer, ThreadSingleton>();
    private static ArrayList<Integer> listThreads = new ArrayList<Integer>();
    public static ArrayList<Entry<Integer, Integer>> releasedSingleton =
            new ArrayList<Entry<Integer, Integer>>();
    public static ThreadSingleton Instance() {
        Integer curr_thread_hash = currentThread().hashCode();
        //System.out.println(curr_thread.getName());
        if (!listThreads.contains(curr_thread_hash)){
            ThreadSingleton instance = new ThreadSingleton();
            listThreads.add(curr_thread_hash);
            mapSingleton.put(curr_thread_hash, instance);
        }
        Entry<Integer, Integer> entry = new AbstractMap.SimpleEntry<Integer, Integer>
                (curr_thread_hash, mapSingleton.get(curr_thread_hash).hashCode());
        releasedSingleton.add(entry);
        return mapSingleton.get(curr_thread_hash);
    }

}


    @Test
    public void ThreadSingleton_UniqueTest() throws InterruptedException {
        int j = 5;
        Thread[] threads = new Thread[j];
        int[] threads_hashes = new int[j];
        for (int i=0; i<j; i++){
            ThreadTest threadTest = new ThreadTest();
            Thread thread = new Thread(threadTest);
            threads[i] = thread;
            threads_hashes[i] = thread.hashCode();
            thread.start();
        }
        for (Thread t: threads) {
            System.out.println(t.hashCode());
            t.join();
        }
        for (int i=0; i<j; i++) {
            int s1 = 0, s2 = 0;
            boolean first = true;
            for (Map.Entry<Integer, Integer> entry : ThreadTest.releasedSingleton) {
                if (threads_hashes[i] == entry.getKey()) {
                    if (first) {
                        s1 = entry.getValue();
                        first = false;
                    } else{
                        s2 = entry.getValue();
                    }
                }
                if (i==0){
                    System.out.println("Thread " + entry.getKey() + " singleton: " +  entry.getValue());
                }
            }
            System.out.println("s1: " + s1 + " s2: " +  s2);
            Assert.assertEquals(s1, s2);
        }
    }


class ThreadTest implements Runnable{
    public static volatile ArrayList<Map.Entry<Integer, Integer>> releasedSingleton =
            new ArrayList<Map.Entry<Integer, Integer>>();

    public void run(){
        ThreadSingleton s1 = ThreadSingleton.Instance();
        ThreadSingleton s2 = ThreadSingleton.Instance();
        Map.Entry<Integer, Integer> entry = new AbstractMap.SimpleEntry<Integer, Integer>
                (currentThread().hashCode(), s1.hashCode());
        releasedSingleton.add(entry);
        entry = new AbstractMap.SimpleEntry<Integer, Integer>
                (currentThread().hashCode(), s2.hashCode());
        releasedSingleton.add(entry);
        //Assert.assertNotEquals(s1, s2);
    }
}
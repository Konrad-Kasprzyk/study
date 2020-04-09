// Wyjaśnienie w osobnym pliku l3z1 (PDF)
package l3;

import static java.lang.System.*;

public class l3z1 {
    public static void main(String[] args) {
        TestController testController = new TestController();
        testController.makeTest("IntAddTest", 1000000000);
        testController.makeTest("IntObjAddTest", 1000000000);
        testController.makeTest("DoubleMultTest", 1000000000);
        testController.makeTest("DoubleObjMultTest", 1000000000);
    }
}

class TestController{

    public void makeTest(String testName, int how_many_times){
        Test test;
        long time;
        switch (testName){
            case "IntAddTest":
                test = new IntAddTest();
                time = measureTime(test, how_many_times);
                System.out.println("Test " + testName + " zajął " + time + " ms");
                break;
            case "IntObjAddTest":
                test = new IntObjAddTest();
                time = measureTime(test, how_many_times);
                System.out.println("Test " + testName + " zajął " + time + " ms");
                break;
            case "DoubleMultTest":
                test = new DoubleMultTest();
                time = measureTime(test, how_many_times);
                System.out.println("Test " + testName + " zajął " + time + " ms");
                break;
            case "DoubleObjMultTest":
                test = new DoubleObjMultTest();
                time = measureTime(test, how_many_times);
                System.out.println("Test " + testName + " zajął " + time + " ms");
                break;
            default:
                System.out.println("Nie rozpoznano testu");
        }
    }

    long measureTime(Test test, int how_many_times){
        long nano_startTime = nanoTime();
        test.makeTest(how_many_times);
        long nano_endTime = nanoTime();
        return (nano_endTime - nano_startTime) / 1000000;
    }
}

interface Test{
    public void makeTest(int how_many_times);
}

class IntAddTest implements Test{
    private int a, b = 1;

    @Override
    public void makeTest(int j){
        for(int i=0; i<j; i++){
            a += b;
        }
    }
}

class IntObjAddTest implements Test{
    private Integer a = 1, b = 1;

    @Override
    public void makeTest(int j){
        for(int i=0; i<j; i++){
            a += b;
        }
    }
}

class DoubleMultTest implements Test{
    private double a=2.0, b=1.1;

    @Override
    public void makeTest(int j){
        for(int i=0; i<j; i++){
            a *= b;
        }
    }
}

class DoubleObjMultTest implements Test{
    private Double a=2.0, b=1.1;

    @Override
    public void makeTest(int j){
        for(int i=0; i<j; i++){
            a *= b;
        }
    }
}
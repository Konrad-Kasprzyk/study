// Wyjaśnienie w osobnym pliku l3z4 (PDF)
package l3;

public class l3z4 {

    public static void main(String[] args) {
        int w = 4, h = 5;
        Square rect = new Rectangle(w, h);
        AreaCalculator calc = new AreaCalculator();
        System.out.println("prostokąt o wymiarach " + w + " na " + h
                + " ma pole " + calc.CalculateArea(rect));
    }
}

class Square{
    int width;
    int height;

    public Square(int w, int h){
        SetWidth(w);
        SetHeight(h);
    }

    public int Width(){
        return this.width;
    }
    public void SetWidth(int val){
        this.height = this.width = val;
    }
    public int Height(){
        return this.height;
    }
    public void SetHeight(int val){
        this.height = this.width = val;
    }
}

class Rectangle extends Square{

    public Rectangle(int w, int h){
        super(w, h);
    }

    @Override
    public void SetWidth(int val){
        this.width = val;
    }
    @Override
    public void SetHeight(int val){
        this.height = val;
    }
}

class AreaCalculator{
    public int CalculateArea( Square square ){
        return square.Height() * square.Width();
    }
}

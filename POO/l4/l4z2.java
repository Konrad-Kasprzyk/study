package l4z2;

import java.util.ArrayList;

public class Main {
    public static void main(String[] args){
    }
}

class ShapeFactory{
    ArrayList<IShapeFactoryWorker> _workers = new ArrayList<IShapeFactoryWorker>();

    public ShapeFactory(){
        this._workers.add(new SquareFactoryWorker());
    }

    public void RegisterWorker( IShapeFactoryWorker worker ){
        _workers.add(worker);
    }

    public IShape CreateShape( String shapeName, double ...params){
        for(var worker: _workers){
            if (worker.AcceptsParameters(shapeName))
                return worker.Create(params);
        }
        throw new IllegalArgumentException();
    }
}

interface IShapeFactoryWorker{
    boolean AcceptsParameters(String parameter);

    IShape Create(double ...params);
}

class SquareFactoryWorker implements IShapeFactoryWorker{
    public boolean AcceptsParameters(String parameter){
        return parameter == "Square";
    }

    public IShape Create(double ...params){
        if (params.length != 1){
            throw new IllegalArgumentException();
        }
        return new Square(params[0]);
    }
}

interface IShape{
    double Area();
}

class Square implements IShape{
    private double side;
    public Square(double side){
        this.side = side;
    }
    public double Area(){
        return side*side;
    }
}
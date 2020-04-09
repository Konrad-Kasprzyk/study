package l4z2;

import org.junit.Assert;
import org.junit.Test;

public class ShapeFactoryTest {
    class Rectangle implements IShape{
        private double width, height;
        public Rectangle(double width, double height){
            this.width = width;
            this.height = height;
        }
        public double Area(){
            return width*height;
        }
    }

    class RectangleFactoryWorker implements IShapeFactoryWorker{
        public boolean AcceptsParameters(String parameter){
            return parameter == "Rectangle";
        }

        public IShape Create(double ...params){
            if (params.length != 2){
                throw new IllegalArgumentException();
            }
            return new Rectangle(params[0], params[1]);
        }
    }

    @Test
    public void TestNewWorker(){
        ShapeFactory factory = new ShapeFactory();
        factory.RegisterWorker( new RectangleFactoryWorker() );
        IShape rect1 = factory.CreateShape("Rectangle", 3, 5);
        IShape rect2 = factory.CreateShape("Rectangle", 5, 3);
        Assert.assertNotNull(rect1);
        Assert.assertNotNull(rect2);
        Assert.assertEquals(rect1.Area(), rect2.Area(), 0.1);
    }

    @Test
    public void TestFactory(){
        ShapeFactory factory = new ShapeFactory();
        IShape square1 = factory.CreateShape("Square", 5 );
        IShape square2 = factory.CreateShape("Square", 5 );
        Assert.assertNotNull(square1);
        Assert.assertNotNull(square2);
        Assert.assertEquals(square1.Area(),square2.Area(), 0.1);
    }
}
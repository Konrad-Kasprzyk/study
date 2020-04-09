package l4z3;

import java.util.ArrayList;

public class Main {
    public static void main(String[] args){
    }
}

class PlanePool{
    private ArrayList<APlanePoolWorker> poolWorkers = new ArrayList<>();

    public PlanePool(int economic, int business){
        poolWorkers.add(new EconomicPlanePoolWorker(economic));
        poolWorkers.add(new BusinessPlanePoolWorker(business));
    }

    public Plane AcquireReusable(Class planeClass){
        for (var poolWorker: poolWorkers){
            if(poolWorker.correctPool(planeClass))
                return poolWorker.AcquireReusable();
        }
        throw new IllegalArgumentException();
    }

    public void ReleaseReusable( Plane plane ){
        for (var poolWorker: poolWorkers){
            if(poolWorker.correctPool(plane.getClass()))
                poolWorker.ReleaseReusable(plane);
        };
    }
}

abstract class APlanePoolWorker{
    private int _capacity;
    private ArrayList<Plane> ready = new ArrayList<>();
    private ArrayList<Plane> released = new ArrayList<>();
    abstract public boolean correctPool(Class planeClass);
    abstract protected Plane NewPlane();
    public final Plane AcquireReusable(){
        if ( released.size() == this._capacity){
            throw new IllegalArgumentException();
        }
        if ( ready.size() == 0){
            Plane newPlane = NewPlane();
            ready.add(newPlane);
        }
        var reusable = ready.get(0);
        ready.remove(reusable);
        released.add(reusable);
        return reusable;
    }
    public final void ReleaseReusable( Plane reusable ){
        if ( !released.contains(reusable)){
            throw new IllegalArgumentException();
        }
        released.remove(reusable);
        ready.add(reusable);
    }
    public APlanePoolWorker(int capacity){
        if(capacity <= 0){
            throw new IllegalArgumentException();
        }
        this._capacity = capacity;
    }
}

class EconomicPlanePoolWorker extends APlanePoolWorker{
    @Override
    protected Plane NewPlane(){
        return new EconomicPlane();
    }

    @Override
    public boolean correctPool(Class planeClass){
        return planeClass.equals(EconomicPlane.class);
    }

    public EconomicPlanePoolWorker(int capacity){
        super(capacity);
    }
}

class BusinessPlanePoolWorker extends APlanePoolWorker{
    @Override
    protected Plane NewPlane(){
        return new BusinessPlane();
    }

    @Override
    public boolean correctPool(Class planeClass){
        return planeClass.equals(BusinessPlane.class);
    }

    public BusinessPlanePoolWorker(int capacity){
        super(capacity);
    }
}

interface Plane{
}

class EconomicPlane implements Plane{
}

class BusinessPlane implements Plane{
}

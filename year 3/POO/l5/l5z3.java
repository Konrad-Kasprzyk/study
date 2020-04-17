package l5z3;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.logging.Logger;

public class l5z3 {
    public static void main(String[] args){
        PlanePoolProxyLogger pool = new PlanePoolProxyLogger(2, 1);
        Plane economic1 = pool.AcquireReusable(EconomicPlane.class);
        Plane economic2 = pool.AcquireReusable(EconomicPlane.class);
        Plane business1 = pool.AcquireReusable(BusinessPlane.class);
        pool.ReleaseReusable(business1);
        System.out.println(pool.LOGGER.toString());
    }
}


class PlanePoolProxyLogger{
    private PlanePool planePool;
    public Logger LOGGER;

    public PlanePoolProxyLogger(int economic, int business){
        this.planePool = new PlanePool(economic, business);
        LOGGER = Logger.getLogger(Logger.GLOBAL_LOGGER_NAME);
    }

    public Plane AcquireReusable(Class planeClass){
        String message = "arg: " + planeClass.toString();
        Plane plane = planePool.AcquireReusable(planeClass);
        message += "\t\tret: " + plane.toString();
        LOGGER.info(message);
        return plane;
    }

    public void ReleaseReusable( Plane plane ){
        String message = "arg: " + plane.toString();
        planePool.ReleaseReusable(plane);
        message += "\t\tret: void";
        LOGGER.info(message);
    }
}


class PlanePoolProxyBlocker{
    private PlanePool planePool;

    public PlanePoolProxyBlocker(int economic, int business){
        this.planePool = new PlanePool(economic, business);
    }

    private boolean CheckTime() throws ParseException {
        SimpleDateFormat parser = new SimpleDateFormat("HH:mm");
        Date eight = parser.parse("8:00");
        Date ten = parser.parse("22:00");
        Calendar now = Calendar.getInstance();
        int hour = now.get(Calendar.HOUR_OF_DAY);
        int minute = now.get(Calendar.MINUTE);
        Date current = parser.parse(Integer.toString(hour) + ":" + Integer.toString(minute));
        if (current.before(eight) || current.after(ten))
            return false;
        return true;
    }

    public Plane AcquireReusable(Class planeClass) throws ParseException {
        if (!CheckTime())
            throw new IllegalArgumentException();
        return planePool.AcquireReusable(planeClass);
    }

    public void ReleaseReusable( Plane plane ) throws ParseException {
        if (!CheckTime())
            throw new IllegalArgumentException();
        planePool.ReleaseReusable(plane);
    }
}


class PlanePool{
    protected ArrayList<APlanePoolWorker> poolWorkers = new ArrayList<>();

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

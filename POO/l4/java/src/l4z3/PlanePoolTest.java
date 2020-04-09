package l4z3;

import org.junit.Assert;
import org.junit.Test;

import static org.junit.jupiter.api.Assertions.*;

public class PlanePoolTest {
    @Test
    public void InvalidCapacity(){
        assertThrows(IllegalArgumentException.class, () -> {
            PlanePool pool = new PlanePool(0, 2);
        });
        assertThrows(IllegalArgumentException.class, () -> {
            PlanePool pool = new PlanePool(2, 0);
        });
    }

    @Test
    public void ValidCapacity(){
        PlanePool pool = new PlanePool(1, 1);
        Plane reusable = pool.AcquireReusable(EconomicPlane.class);
        Assert.assertNotNull(reusable);
        Plane reusable2 = pool.AcquireReusable(BusinessPlane.class);
        Assert.assertNotNull(reusable2);
    }

    @Test
    public void CapacityDepleted(){
        PlanePool pool = new PlanePool(1, 1);
        Plane reusable = pool.AcquireReusable(EconomicPlane.class);
        assertThrows(IllegalArgumentException.class, () -> {
            Plane reusable2 = pool.AcquireReusable(EconomicPlane.class);
        });
        reusable = pool.AcquireReusable(BusinessPlane.class);
        assertThrows(IllegalArgumentException.class, () -> {
            Plane reusable2 = pool.AcquireReusable(BusinessPlane.class);
        });
    }

    @Test
    public void ReusedObject(){
        PlanePool pool = new PlanePool(1, 1);
        Plane reusable = pool.AcquireReusable(EconomicPlane.class);
        pool.ReleaseReusable(reusable);
        Plane reusable2 = pool.AcquireReusable(EconomicPlane.class);
        Assert.assertEquals(reusable, reusable2);
        reusable = pool.AcquireReusable(BusinessPlane.class);
        pool.ReleaseReusable(reusable);
        reusable2 = pool.AcquireReusable(BusinessPlane.class);
        Assert.assertEquals(reusable, reusable2);
    }

    @Test
    public void ReleaseInvalidReusable(){
        PlanePool pool = new PlanePool(1, 1);
        EconomicPlane reusable = new EconomicPlane();
        assertThrows(IllegalArgumentException.class, () -> {
            pool.ReleaseReusable(reusable);
        });
        BusinessPlane reusable2 = new BusinessPlane();
        assertThrows(IllegalArgumentException.class, () -> {
            pool.ReleaseReusable(reusable2);
        });
    }
}
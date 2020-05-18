from Dostawa_Domain.Model.Package.Package import Package, DELIVERY_SUCCESS_STATUS, DELIVERY_FAILURE_STATUS
from Dostawa_Domain.Model.Package.ValueObjects.Pickup import Pickup
from Dostawa_Domain.Model.Package.ValueObjects.Return import Return
from Dostawa_Domain.Model.Package.ValueObjects.Status import Status

class PackageObjectMother:

    def CreatePackageNoPickupsNoReturn(self):
        return Package(City = "Wrocław", PostalCode="51-152", StreetAddress= "Piłsudskiego 7",
                       ClientId=1, DeliveryType="Standard", DeclaredValue=100)

    def CreatePackageManyPickupNoReturn(self):
        package = Package(City="Wrocław", PostalCode="51-152", StreetAddress="Piłsudskiego 7",
                       ClientId=1, DeliveryType="Standard", DeclaredValue=100)
        package.AddDeliveryProduct("Pan Tadeusz", 1)
        package.AddDeliveryProduct("Biblia", 3)
        package.AddDeliveryProduct(".net oczami developera", 1)
        package.GetStatus().Name="Pakowanie"
        return package

    def CreatePackageManyPickupPackedNoReturn(self):
        package = Package(City="Wrocław", PostalCode="51-152", StreetAddress="Piłsudskiego 7",
                       ClientId=1, DeliveryType="Standard", DeclaredValue=100)
        package.AddDeliveryProduct("Pan Tadeusz", 1)
        package.AddDeliveryProduct("Biblia", 3)
        package.AddDeliveryProduct(".net oczami developera", 1)
        package.MarkPackedProduct("Pan Tadeusz")
        package.MarkPackedProduct("Biblia")
        package.MarkPackedProduct(".net oczami developera")
        package.GetStatus().Name = "Wysłane"
        return package

    def CreatePackageManyPickupPackedWithUnconfirmedReturn(self):
        package = Package(City="Wrocław", PostalCode="51-152", StreetAddress="Piłsudskiego 7",
                       ClientId=1, DeliveryType="Standard", DeclaredValue=100)
        package.AddDeliveryProduct("Pan Tadeusz", 1)
        package.AddDeliveryProduct("Biblia", 3)
        package.AddDeliveryProduct(".net oczami developera", 1)
        package.MarkPackedProduct("Pan Tadeusz")
        package.MarkPackedProduct("Biblia")
        package.MarkPackedProduct(".net oczami developera")
        package.MakeReturn("Odbiorca twierdzi, że niczego nie zamawiał. Nie przyjął przesyłki.")
        package.GetStatus().Name = DELIVERY_FAILURE_STATUS
        return package

    def CreatePackageManyPickupPackedWithConfirmedReturn(self):
        package = Package(City="Wrocław", PostalCode="51-152", StreetAddress="Piłsudskiego 7",
                       ClientId=1, DeliveryType="Standard", DeclaredValue=100)
        package.AddDeliveryProduct("Pan Tadeusz", 1)
        package.AddDeliveryProduct("Biblia", 3)
        package.AddDeliveryProduct(".net oczami developera", 1)
        package.MarkPackedProduct("Pan Tadeusz")
        package.MarkPackedProduct("Biblia")
        package.MarkPackedProduct(".net oczami developera")
        package.MakeReturn("Odbiorca twierdzi, że niczego nie zamawiał. Nie przyjął przesyłki.")
        package.GetStatus().Name = "Wysłane"
        return package

    def CreateUnpackedPickups(self):
        package = Package(City="Wrocław", PostalCode="51-152", StreetAddress="Piłsudskiego 7",
                       ClientId=1, DeliveryType="Standard", DeclaredValue=100)
        package.AddDeliveryProduct("Pan Tadeusz", 1)
        package.AddDeliveryProduct("Biblia", 3)
        package.AddDeliveryProduct(".net oczami developera", 1)
        return package.GetPackageProducts()

    def CreatePackedPickups(self):
        package = Package(City="Wrocław", PostalCode="51-152", StreetAddress="Piłsudskiego 7",
                       ClientId=1, DeliveryType="Standard", DeclaredValue=100)
        package.AddDeliveryProduct("Pan Tadeusz", 1)
        package.AddDeliveryProduct("Biblia", 3)
        package.AddDeliveryProduct(".net oczami developera", 1)
        package.MarkPackedProduct("Pan Tadeusz")
        package.MarkPackedProduct("Biblia")
        package.MarkPackedProduct(".net oczami developera")
        return package.GetPackageProducts()

    def CreateUnconfirmedReturn(self):
        package = Package(City="Wrocław", PostalCode="51-152", StreetAddress="Piłsudskiego 7",
                       ClientId=1, DeliveryType="Standard", DeclaredValue=100)
        package.AddDeliveryProduct("Pan Tadeusz", 1)
        package.AddDeliveryProduct("Biblia", 3)
        package.AddDeliveryProduct(".net oczami developera", 1)
        package.MarkPackedProduct("Pan Tadeusz")
        package.MarkPackedProduct("Biblia")
        package.MarkPackedProduct(".net oczami developera")
        package.MakeReturn("Odbiorca twierdzi, że niczego nie zamawiał. Nie przyjął przesyłki.")
        return package.GetReturn()
from Dostawa_Domain.Model.Package.Package import Package, DELIVERY_SUCCESS_STATUS, DELIVERY_FAILURE_STATUS
from Dostawa_Domain.Model.Package.ValueObjects.Pickup import Pickup
from Dostawa_Domain.Model.Package.ValueObjects.Return import Return
from Dostawa_Domain.Model.Package.ValueObjects.Status import Status


class PackageObjectMother:

    @staticmethod
    def CreatePackageNoPickupsNoReturn():
        return Package(City="Wrocław", PostalCode="51-152", StreetAddress= "Piłsudskiego 7",
                       ClientId=1, DeliveryType="Standard", DeclaredValue=100)

    @staticmethod
    def CreatePackageManyPickupNoReturn():
        package = Package(City="Wrocław", PostalCode="51-152", StreetAddress="Piłsudskiego 7",
                       ClientId=1, DeliveryType="Standard", DeclaredValue=100)
        package.AddDeliveryProduct("Pan Tadeusz", 1)
        package.AddDeliveryProduct("Biblia", 3)
        package.AddDeliveryProduct(".net oczami developera", 1)
        # Status == Pakowanie
        package.GetStatus().NextDeliveryStep()
        return package

    @staticmethod
    def CreatePackageManyPickupPackedNoReturn():
        package = Package(City="Wrocław", PostalCode="51-152", StreetAddress="Piłsudskiego 7",
                       ClientId=1, DeliveryType="Standard", DeclaredValue=100)
        package.AddDeliveryProduct("Pan Tadeusz", 1)
        package.AddDeliveryProduct("Biblia", 3)
        package.AddDeliveryProduct(".net oczami developera", 1)
        package.GetStatus().NextDeliveryStep()
        package.MarkPackedProduct("Pan Tadeusz")
        package.MarkPackedProduct("Biblia")
        package.MarkPackedProduct(".net oczami developera")
        # Status == Wysłane
        package.GetStatus().NextDeliveryStep()
        return package

    @staticmethod
    def CreateDeliveredPackageManyPickupPackedNoReturn():
        package = Package(City="Wrocław", PostalCode="51-152", StreetAddress="Piłsudskiego 7",
                       ClientId=1, DeliveryType="Standard", DeclaredValue=100)
        package.AddDeliveryProduct("Pan Tadeusz", 1)
        package.AddDeliveryProduct("Biblia", 3)
        package.AddDeliveryProduct(".net oczami developera", 1)
        package.GetStatus().NextDeliveryStep()
        package.MarkPackedProduct("Pan Tadeusz")
        package.MarkPackedProduct("Biblia")
        package.MarkPackedProduct(".net oczami developera")
        package.GetStatus().NextDeliveryStep()
        # Status == Dostarczone
        package.GetStatus().NextDeliveryStep()
        return package

    @staticmethod
    def CreatePackageManyPickupPackedUnconfirmedReturn():
        package = Package(City="Wrocław", PostalCode="51-152", StreetAddress="Piłsudskiego 7",
                       ClientId=1, DeliveryType="Standard", DeclaredValue=100)
        package.AddDeliveryProduct("Pan Tadeusz", 1)
        package.AddDeliveryProduct("Biblia", 3)
        package.AddDeliveryProduct(".net oczami developera", 1)
        package.GetStatus().NextDeliveryStep()
        package.MarkPackedProduct("Pan Tadeusz")
        package.MarkPackedProduct("Biblia")
        package.MarkPackedProduct(".net oczami developera")
        package.GetStatus().NextDeliveryStep()
        package.GetStatus().NextDeliveryStep()
        package.MakeReturn("Odbiorca twierdzi, że niczego nie zamawiał. Nie przyjął przesyłki.")
        # Status == Problem z Dostawą
        package.GetStatus().NextDeliveryStep()
        return package

    @staticmethod
    def CreatePackageManyPickupPackedConfirmedReturn():
        package = Package(City="Wrocław", PostalCode="51-152", StreetAddress="Piłsudskiego 7",
                       ClientId=1, DeliveryType="Standard", DeclaredValue=100)
        package.AddDeliveryProduct("Pan Tadeusz", 1)
        package.AddDeliveryProduct("Biblia", 3)
        package.AddDeliveryProduct(".net oczami developera", 1)
        package.GetStatus().NextDeliveryStep()
        package.MarkPackedProduct("Pan Tadeusz")
        package.MarkPackedProduct("Biblia")
        package.MarkPackedProduct(".net oczami developera")
        package.GetStatus().NextDeliveryStep()
        package.GetStatus().NextDeliveryStep()
        package.MakeReturn("Odbiorca twierdzi, że niczego nie zamawiał. Nie przyjął przesyłki.")
        # Status == Problem z Dostawą
        package.GetStatus().NextDeliveryStep()
        package.GetReturn().Accept()
        return package

    @staticmethod
    def CreateUnpackedPickups():
        package = Package(City="Wrocław", PostalCode="51-152", StreetAddress="Piłsudskiego 7",
                       ClientId=1, DeliveryType="Standard", DeclaredValue=100)
        package.AddDeliveryProduct("Pan Tadeusz", 1)
        package.AddDeliveryProduct("Biblia", 3)
        package.AddDeliveryProduct(".net oczami developera", 1)
        return package.GetPackageProducts()

    @staticmethod
    def CreatePackedPickups():
        package = Package(City="Wrocław", PostalCode="51-152", StreetAddress="Piłsudskiego 7",
                       ClientId=1, DeliveryType="Standard", DeclaredValue=100)
        package.AddDeliveryProduct("Pan Tadeusz", 1)
        package.AddDeliveryProduct("Biblia", 3)
        package.AddDeliveryProduct(".net oczami developera", 1)
        package.MarkPackedProduct("Pan Tadeusz")
        package.MarkPackedProduct("Biblia")
        package.MarkPackedProduct(".net oczami developera")
        return package.GetPackageProducts()

    @staticmethod
    def CreateUnconfirmedReturn():
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

    @staticmethod
    def CreateConfirmedReturn():
        package = Package(City="Wrocław", PostalCode="51-152", StreetAddress="Piłsudskiego 7",
                       ClientId=1, DeliveryType="Standard", DeclaredValue=100)
        package.AddDeliveryProduct("Pan Tadeusz", 1)
        package.AddDeliveryProduct("Biblia", 3)
        package.AddDeliveryProduct(".net oczami developera", 1)
        package.MarkPackedProduct("Pan Tadeusz")
        package.MarkPackedProduct("Biblia")
        package.MarkPackedProduct(".net oczami developera")
        package.MakeReturn("Odbiorca twierdzi, że niczego nie zamawiał. Nie przyjął przesyłki.")
        package.GetReturn().Accept()
        return package.GetReturn()
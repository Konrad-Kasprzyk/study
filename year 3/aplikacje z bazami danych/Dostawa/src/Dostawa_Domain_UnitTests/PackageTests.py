from unittest import TestCase
from datetime import datetime
from Dostawa_Domain.Model.Package.Package import Package, DELIVERY_SUCCESS_STATUS,\
    DELIVERY_FAILURE_STATUS, RETURN_STARTING_STATUS
from Dostawa_ObjectMothers.PackageObjectMother import PackageObjectMother

class PackageTests(TestCase):

    def test_UniquePackageCodes(self):
        packages = []
        for i in range(1000):
            packages.append(PackageObjectMother.CreatePackageNoPickupsNoReturn())

        self.assertEqual(len(packages), len(set(packages)))

    def test_ChangePickupsState(self):
        package = PackageObjectMother.CreatePackageManyPickupNoReturn()

        pickups = package.GetPackageProducts()
        for pickup in pickups:
            package.MarkPackedProduct(pickup.Name)

        pickups = package.GetPackageProducts()
        for pickup in pickups:
            self.assertEqual(pickup.IsPacked, True)

    def test_ChangingPackageStatuses(self):
        # DeliveryStep = 0, first status
        package = PackageObjectMother.CreatePackageNoPickupsNoReturn()
        package2 = PackageObjectMother.CreatePackageNoPickupsNoReturn()
        statuses = Package.FindAllPackageStatuses()

        for status in statuses:
            package.GetStatus().Name = status.Name
            self.assertEqual(package.GetStatus().Name, package2.GetStatus().Name)
            self.assertEqual(package.GetStatus().DeliveryStep, package2.GetStatus().DeliveryStep)
            package2.GetStatus().NextDeliveryStep()

    def test_DeliveryFailureMakeReturn(self):
        package = PackageObjectMother.CreatePackageManyPickupPackedNoReturn()

        package.MakeReturn("Odbiorca twierdzi, że niczego nie zamawiał. Nie przyjął przesyłki.")
        package.GetStatus().Name = DELIVERY_FAILURE_STATUS

        self.assertEqual(package.GetReturn().Sum, package.DeclaredValue)
        self.assertEqual(package.GetReturn().Status, RETURN_STARTING_STATUS)
        self.assertEqual(package.GetReturn().ReportDate.date(), datetime.now().date())
        self.assertEqual(package.GetReturn().Accepted, False)
        self.assertEqual(package.GetReturn().Description,
                         "Odbiorca twierdzi, że niczego nie zamawiał. Nie przyjął przesyłki.")

    def test_AllDeliveryStepsDuringSuccessfulDelivery(self):
        package = PackageObjectMother.CreatePackageNoPickupsNoReturn()

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
        package.DeliveryDate = datetime.now()

        self.assertEqual(package.GetReturn(), None)
        self.assertEqual(package.GetStatus().Name, DELIVERY_SUCCESS_STATUS)
        self.assertEqual(package.DeliveryDate.date(), datetime.now().date())

    def test_AddPickupsCheckNotPacked(self):
        package = PackageObjectMother.CreatePackageNoPickupsNoReturn()

        package.AddDeliveryProduct("Pan Tadeusz", 1)
        package.AddDeliveryProduct("Biblia", 3)
        package.AddDeliveryProduct(".net oczami developera", 1)

        pickups = package.GetPackageProducts()
        for pickup in pickups:
            self.assertEqual(pickup.IsPacked, False)

    def test_MakeReturnWithDifferentValueThanDeclared(self):
        package = PackageObjectMother.CreatePackageManyPickupPackedNoReturn()

        package.MakeReturn("Odbiorca twierdzi, że niczego nie zamawiał. Nie przyjął przesyłki.", 123)
        package.GetStatus().Name = DELIVERY_FAILURE_STATUS

        self.assertEqual(package.GetReturn().Sum, 123)

    def test_ChangeReturnDescription(self):
        return_ = PackageObjectMother.CreateUnconfirmedReturn()

        return_.Description = "qwerty"

        self.assertEqual(return_.Description, "qwerty")

    def test_AcceptReturn(self):
        return_ = PackageObjectMother.CreateUnconfirmedReturn()

        return_.Accept()

        self.assertEqual(return_.Accepted, True)


    def test_AllReturnStatuses(self):
        return_ = PackageObjectMother.CreateConfirmedReturn()

        statuses = Package.FindAllReturnStatuses()

        for status in statuses:
            return_.Status = status
            self.assertEqual(return_.Status, status)

    def test_CreateAllObjectsFromObjectMother(self):
        p = PackageObjectMother.CreatePackageNoPickupsNoReturn()
        p = PackageObjectMother.CreatePackageManyPickupNoReturn()
        p = PackageObjectMother.CreatePackageManyPickupPackedNoReturn()
        p = PackageObjectMother.CreateDeliveredPackageManyPickupPackedNoReturn()
        p = PackageObjectMother.CreatePackageManyPickupPackedUnconfirmedReturn()
        p = PackageObjectMother.CreatePackageManyPickupPackedConfirmedReturn()
        p = PackageObjectMother.CreateUnpackedPickups()
        p = PackageObjectMother.CreatePackedPickups()
        p = PackageObjectMother.CreateUnconfirmedReturn()
        p = PackageObjectMother.CreateConfirmedReturn()

    def test_BadPackingInputRaisesException(self):
        package = PackageObjectMother.CreatePackageManyPickupPackedNoReturn()
        pickup = package.GetPackageProducts()[0]

        with self.assertRaises(ValueError):
            package.MarkPackedProduct("")

        with self.assertRaises(ValueError):
            package.MarkPackedProduct("nieistniejacy produkt")

        with self.assertRaises(ValueError):
            package.AddDeliveryProduct(pickup.Name, 1)

        with self.assertRaises(ValueError):
            package.AddDeliveryProduct("", 1)

        with self.assertRaises(ValueError):
            package.AddDeliveryProduct("książka", 0)

    def test_BadMakingReturnInputRaisesException(self):
        package = PackageObjectMother.CreatePackageManyPickupPackedNoReturn()

        with self.assertRaises(ValueError):
            package.MakeReturn("")

        with self.assertRaises(ValueError):
            package.MakeReturn(17)

        with self.assertRaises(ValueError):
            package.MakeReturn("opis szkody", -100)

    def test_BadPackageStateChangeRaisesException(self):
        package = PackageObjectMother.CreatePackageManyPickupPackedNoReturn()

        with self.assertRaises(ValueError):
            package.GetStatus().Name = 14

        with self.assertRaises(ValueError):
            package.GetStatus().Name = ""

        with self.assertRaises(ValueError):
            package.GetStatus().Name = "nieistniejący stan przesyłki"

    def test_BadReturnStateChangeRaisesException(self):
        return_ = PackageObjectMother.CreateConfirmedReturn()

        with self.assertRaises(ValueError):
            return_.Status = ""

        with self.assertRaises(ValueError):
            return_.Status = 13

        with self.assertRaises(ValueError):
            return_.Status = "zły stan, nie ma go"
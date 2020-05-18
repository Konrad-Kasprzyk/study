from unittest import TestCase
from Dostawa_Domain.Model.Package.Package import Package
from Dostawa_ObjectMothers.PackageObjectMother import PackageObjectMother

class PackageTests(TestCase):
    def test_PackingPickupsChangeTheirState(self):
        package = PackageObjectMother.CreatePackageManyPickupNoReturn()

        pickups = package.GetPackageProducts()
        for pickup in pickups:
            package.MarkPackedProduct(pickup.Name)

        pickups = package.GetPackageProducts()
        for pickup in pickups:
            self.assertEqual(pickup.IsPacked, True)

    def test_ChangingPackageStatusesEqualDeliveryStep (self):
        # DeliveryStep = 0, first status
        package = PackageObjectMother.CreatePackageNoPickupsNoReturn()
        package2 = PackageObjectMother.CreatePackageNoPickupsNoReturn()
        statuses = Package.FindAllPackageStatuses()

        for status in statuses:
            package.GetStatus().Name = status.Name
            self.assertEqual(package.GetStatus().Name, package2.GetStatus().Name)
            self.assertEqual(package.GetStatus().DeliveryStep, package2.GetStatus().DeliveryStep)
            package2.GetStatus().NextDeliveryStep()
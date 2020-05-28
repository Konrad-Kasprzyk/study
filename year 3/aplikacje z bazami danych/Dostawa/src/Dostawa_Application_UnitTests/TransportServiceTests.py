from unittest import TestCase
from unittest.mock import patch
from Dostawa_Application.TransportService import TransportService
from Dostawa_Infrastructure.Repositories.FakePackageRepository import FakePackageRepository as PackageRepository
from Dostawa_ObjectMothers.PackageObjectMother import PackageObjectMother
from Dostawa_Domain.Model.Package.Package import Package, DELIVERY_SUCCESS_STATUS,\
    DELIVERY_FAILURE_STATUS, RETURN_STARTING_STATUS

class TransportServiceTests(TestCase):

    def test_GetLimitedPackageRepoReturnsNone(self):
        with patch.object(PackageRepository, 'Find', return_value=None):
            transportService = TransportService()

            package = transportService.GetLimitedPackage(32423)

            self.assertEqual(None, package)

    def test_GetLimitedPackageRepoReturnsPackageWithWrongStatus(self):
        with patch.object(PackageRepository, 'Find',
                          return_value=PackageObjectMother.CreatePackageNoPickupsNoReturn()):
            transportService = TransportService()

            package = transportService.GetLimitedPackage(32423)

            self.assertEqual(None, package)

    def test_GettingLimitedPackagesRepoReturnsStatusValidPackages(self):
        transportService = TransportService()
        statuses = Package.FindAllLimitedPackageStatuses()
        package = PackageObjectMother.CreatePackageNoPickupsNoReturn()

        for status in statuses:
            package.GetStatus().Name = status.Name
            with patch.object(PackageRepository, 'Find', return_value=package):
                self.assertEqual(package, transportService.GetLimitedPackage(32423))

    def test_GetAllLimitedPackages(self):
        with patch.object(PackageRepository, 'Find', return_value=[
            PackageObjectMother.CreatePackageManyPickupNoReturn(),
            PackageObjectMother.CreatePackageManyPickupNoReturn(),
            PackageObjectMother.CreatePackageManyPickupPackedNoReturn(),
            PackageObjectMother.CreatePackageManyPickupPackedNoReturn(),
            PackageObjectMother.CreatePackageManyPickupPackedUnconfirmedReturn(),
            PackageObjectMother.CreatePackageManyPickupPackedUnconfirmedReturn(),
            PackageObjectMother.CreateDeliveredPackageManyPickupPackedNoReturn(),
            PackageObjectMother.CreateDeliveredPackageManyPickupPackedNoReturn(),
        ]):
            transportService = TransportService()
            statuses_obj = Package.FindAllLimitedPackageStatuses()
            statuses = [status.Name for status in statuses_obj]

            packages = transportService.GetAllLimitedPackages()

            for package in packages:
                self.assertIn(package.GetStatus().Name, statuses)

    def test_AccomplishDeliveryProperChangePackageStatus(self):
        transportService = TransportService()
        package = PackageObjectMother.CreatePackageManyPickupPackedNoReturn()

        transportService.AccomplishDelivery(package)

        self.assertEqual(package.GetStatus().Name, DELIVERY_SUCCESS_STATUS)

    def test_DeliveryFailureProperChangePackageStatus(self):
        transportService = TransportService()
        package = PackageObjectMother.CreatePackageManyPickupPackedNoReturn()

        transportService.DeliveryFailure(package, "Odmówienie odbioru przesyłki")
        return_ = package.GetReturn()

        self.assertEqual(package.GetStatus().Name, DELIVERY_FAILURE_STATUS)
        self.assertEqual(return_.Status, RETURN_STARTING_STATUS)

    def test_PackProductPackAllProducts(self):
        transportService = TransportService()
        package = PackageObjectMother.CreatePackageManyPickupNoReturn()
        products = package.GetPackageProducts()

        for product in products:
            transportService.PackProduct(package, product.Name)

        packedPackage = PackageObjectMother.CreatePackageManyPickupPackedNoReturn()
        packedStatus = packedPackage.GetStatus()
        products = package.GetPackageProducts()
        for product in products:
            self.assertEqual(product.IsPacked, True)
        self.assertEqual(package.GetStatus().Name, packedStatus.Name)

    def test_PackProductInvalidProductName(self):
        transportService = TransportService()
        package = PackageObjectMother.CreatePackageManyPickupNoReturn()

        with self.assertRaises(ValueError):
            transportService.PackProduct(package, "invalid product name")

    def test_GetLimitedPackageStatusesReturnsValidSortedStatuses(self):
        transportService = TransportService()
        validStatuses = Package.FindAllLimitedPackageStatuses()
        validStatusNames = [status.Name for status in validStatuses]

        statuses = transportService.GetLimitedPackageSatuses()

        for status in statuses:
            self.assertIn(status.Name, validStatusNames)
        for i in range(len(statuses) - 1):
            self.assertLess(statuses[i].DeliveryStep, statuses[i+1].DeliveryStep)

    def test_UndoPackingProductChangeStatusProperly(self):
        transportService = TransportService()
        package = PackageObjectMother.CreatePackageManyPickupPackedNoReturn()
        products = package.GetPackageProducts()

        for product in products:
            transportService.UndoPackingProduct(package, product.Name)

        unpackedPackage = PackageObjectMother.CreatePackageManyPickupNoReturn()
        unpackedStatus = unpackedPackage.GetStatus()
        products = package.GetPackageProducts()
        for product in products:
            self.assertEqual(product.IsPacked, False)
        self.assertEqual(package.GetStatus().Name, unpackedStatus.Name)


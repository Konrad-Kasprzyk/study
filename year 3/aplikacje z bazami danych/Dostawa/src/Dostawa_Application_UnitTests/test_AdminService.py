from unittest import TestCase
from unittest.mock import patch
from Dostawa_Application.AdminService import AdminService
from Dostawa_Infrastructure.Repositories.FakePackageRepository \
    import FakePackageRepository as PackageRepository
from Dostawa_Infrastructure.Repositories.FakeDeliveryTypeRepository \
    import FakeDeliveryTypeRepository as DeliveryTypeRepository
from Dostawa_ObjectMothers.PackageObjectMother import PackageObjectMother
from Dostawa_Domain.Model.Package.Package import Package


class AdminServiceTests(TestCase):

    def test_GetAllPackagesUseProperRepositoryMethod(self):
        with patch.object(PackageRepository, 'FindAll'):
            adminService = AdminService()

            adminService.GetAllPackages()

            PackageRepository.FindAll.assert_called_once()

    def test_GetPackageUseProperRepositoryMethod(self):
        with patch.object(PackageRepository, 'Find'):
            adminService = AdminService()

            adminService.GetPackage(222222)

            PackageRepository.Find.assert_called_once()

    def test_GetAllPackageStatusesUseProperRepositoryMethod(self):
        with patch.object(Package, 'FindAllPackageStatuses'):
            adminService = AdminService()

            adminService.GetAllPackageStatuses()

            Package.FindAllPackageStatuses.assert_called_once()

    def test_ChangePackageStatusUseProperRepositoryMethod(self):
        adminService = AdminService()
        package = PackageObjectMother.CreatePackageManyPickupNoReturn()
        statuses = adminService.GetAllPackageStatuses()

        with patch.object(Package, 'GetStatus'):
            adminService.ChangePackageStatus(package, statuses[-1].Name)

            Package.GetStatus.assert_called_once()

    def test_ChangePackageStatusRaiseProperException(self):
        adminService = AdminService()
        package = PackageObjectMother.CreatePackageManyPickupNoReturn()

        with self.assertRaises(ValueError):
            adminService.ChangePackageStatus(package, "valid status name")

    def test_ChangePackageStatusProperlyChangeStatus(self):
        adminService = AdminService()
        package = PackageObjectMother.CreatePackageManyPickupNoReturn()
        statuses = adminService.GetAllPackageStatuses()

        adminService.ChangePackageStatus(package, statuses[-1].Name)

        assert package.GetStatus().Name == statuses[-1].Name

    def test_GetAllDeliveryMethodsUseProperRepositoryMethod(self):
        adminService = AdminService()

        with patch.object(DeliveryTypeRepository, 'FindAll'):
            adminService.GetAllDeliveryMethods()

            DeliveryTypeRepository.FindAll.assert_called_once()

    def test_GetDeliveryMethodUseProperRepositoryMethod(self):
        adminService = AdminService()

        with patch.object(DeliveryTypeRepository, 'Find'):
            adminService.GetDeliveryMethod("proper delivery type name")

            DeliveryTypeRepository.Find.assert_called_once()

    def test_GetAllReturnsProperlyPullsOutAllReturns(self):
        adminService = AdminService()
        packages = \
            [PackageObjectMother.CreatePackageManyPickupNoReturn(),
             PackageObjectMother.CreatePackageManyPickupNoReturn(),
             PackageObjectMother.CreatePackageManyPickupPackedNoReturn(),
             PackageObjectMother.CreatePackageManyPickupPackedNoReturn(),
             PackageObjectMother.CreatePackageManyPickupPackedUnconfirmedReturn(),
             PackageObjectMother.CreatePackageManyPickupPackedUnconfirmedReturn(),
             PackageObjectMother.CreateDeliveredPackageManyPickupPackedNoReturn(),
             PackageObjectMother.CreateDeliveredPackageManyPickupPackedNoReturn()
             ]
        packageReturns = [package.GetReturn() for package in packages]

        with patch.object(PackageRepository, 'FindAll', return_value=packages):
            servicePackageReturns = adminService.GetAllReturns()
            for return_ in servicePackageReturns:
                assert return_ in packageReturns

    def test_UpdateReturnUseProperRepositoryMethod(self):
        adminService = AdminService()
        package = PackageObjectMother.CreatePackageManyPickupPackedUnconfirmedReturn()
        return_ = package.GetReturn()

        with patch.object(PackageRepository, 'Update'):
            adminService.UpdateReturn(package, return_)

            PackageRepository.Update.assert_called_with(package)

    def test_UpdateReturnRaiseExceptionWhenPackageDoesntHaveReturn(self):
        adminService = AdminService()
        package = PackageObjectMother.CreatePackageManyPickupNoReturn()

        with patch.object(PackageRepository, 'Update'):
            return_ = package.GetReturn()

            with self.assertRaises(ValueError):
                adminService.UpdateReturn(package, return_)

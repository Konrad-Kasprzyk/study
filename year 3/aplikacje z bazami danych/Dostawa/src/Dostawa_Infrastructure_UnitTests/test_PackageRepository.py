from unittest import TestCase
from django.test import TestCase
from Dostawa_ObjectMothers.PackageObjectMother import PackageObjectMother
from Dostawa_Infrastructure.Repositories.PackageRepository import PackageRepository as PackageRepository
from datetime import datetime


class PackageRepositoryTests(TestCase):

    def test_FindInsertedPackages(self):
        packageRepository = PackageRepository()
        package = PackageObjectMother.CreatePackageManyPickupNoReturn()
        package2 = PackageObjectMother.CreatePackageManyPickupNoReturn()
        package3 = PackageObjectMother.CreatePackageManyPickupNoReturn()

        packageRepository.Insert(package)
        packageRepository.Insert(package2)
        packageRepository.Insert(package3)

        assert package.PackageCode == packageRepository.Find(package.PackageCode).PackageCode
        assert package2.PackageCode == packageRepository.Find(package2.PackageCode).PackageCode
        assert package3.PackageCode == packageRepository.Find(package3.PackageCode).PackageCode

    def test_FindInsertedPackageInFindAll(self):
        packageRepository = PackageRepository()
        insertedPackage = PackageObjectMother.CreatePackageManyPickupNoReturn()

        packageRepository.Insert(insertedPackage)
        packages = packageRepository.FindAll()
        foundInsertedPackage = False
        for package in packages:
            if insertedPackage.PackageCode == package.PackageCode:
                foundInsertedPackage = True
                break

        assert foundInsertedPackage == True

    def test_FindUpdatedPackageReturnsSamePackage(self):
        packageRepository = PackageRepository()
        packageRepository.Insert(PackageObjectMother.CreatePackageNoPickupsNoReturn())
        packageRepository.Insert(PackageObjectMother.CreatePackageManyPickupNoReturn())
        packageRepository.Insert(PackageObjectMother.CreatePackageManyPickupPackedNoReturn())
        packageRepository.Insert(PackageObjectMother.CreateDeliveredPackageManyPickupPackedNoReturn())
        packageRepository.Insert(PackageObjectMother.CreatePackageManyPickupPackedUnconfirmedReturn())
        packageRepository.Insert(PackageObjectMother.CreatePackageManyPickupPackedConfirmedReturn())
        packages = packageRepository.FindAll()
        package = packages[0]

        package.DeliveryDate = datetime(2018, 12, 30)
        package.GetStatus().NextDeliveryStep()
        return_ = package.GetReturn()
        if not return_:
            package.MakeReturn("Sample text")
        else:
            return_.Description = "Sample text"
        packageRepository.Update(package)
        packageAfterInsert = packageRepository.Find(package.PackageCode)

        assert packageAfterInsert.PackageCode == package.PackageCode
        assert packageAfterInsert.DeliveryDate == datetime(2018, 12, 30).date()
        assert packageAfterInsert.GetReturn().Description == "Sample text"


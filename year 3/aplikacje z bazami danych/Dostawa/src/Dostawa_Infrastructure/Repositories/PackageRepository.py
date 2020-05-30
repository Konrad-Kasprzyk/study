from interface import implements
from Dostawa_Domain.Model.Package.Repositories.IPackageRepository import IPackageRepository
from Dostawa_Infrastructure.models.Package.PackageModel import PackageModel


class PackageRepository(implements(IPackageRepository)):

    def Insert(self, package):
        ORMPackage = PackageModel()
        ORMPackage._CityField = package.City
        ORMPackage._PostalCodeField = package.PostalCode
        ORMPackage._StreetAddressField = package.StreetAddress
        ORMPackage._ClientIdField = package.ClientId
        ORMPackage._DeclaredValueField = package.DeclaredValue
        ORMPackage._AcceptDateField = package.AcceptDate
        ORMPackage._DeliveryDateField = package.DeliveryDate
        ORMPackage._PackageCodeField = str(package.PackageCode)
        status = package.GetStatus()
        ORMPackage._StatusNameField = status.Name
        ORMPackage._StatusDeliveryStepField = status.DeliveryStep
        ORMPackage.save()

    def Find(self, package_code):
        package = PackageModel.objects.get(_PackageCodeField=package_code)
        package._restore()
        return package

    def FindFilter(self, filter_):
        pass

    def FindAll(self):
        packages = list(PackageModel.objects.all())
        for package in packages:
            package._restore()
        return packages

    def Update(self, package):
        if package._ReturnForeignKey:
            package._ReturnForeignKey.save()
        package.save()

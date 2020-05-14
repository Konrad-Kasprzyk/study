from interface import implements
from Dostawa_Domain.Model.Package.Repositories import IPackageRepository
from Dostawa_Domain.Model.Package import Package
from Dostawa_Domain.Model.Package.ValueObjects.Status import DELIVERY_SUCCESS_STATUS, DELIVERY_FAILURE_STATUS,\
    DELIVERY_STARTING_STATUS
from Dostawa_Domain.Model.Package.ValueObjects.Return import RETURN_STARTING_STATUS
from Dostawa_Domain.Model.Package.ValueObjects import Status


class PackageRepository(implements(IPackageRepository)):

    def __init__(self):
        self._packages = []
        self._packages.append(Package(City = "Wrocław", PostalCode = "50-043", StreetAddress = "Ruska 38",
                                      ClientId = 1, DeliveryMethod = "Ekonomiczny", DeclaredValue=100))
        self._packages.append(Package(City = "Wrocław", PostalCode = "51-152", StreetAddress = "Piłsudskiego 7",
                                      ClientId = 2, DeliveryMethod = "Standard"))
        self._packages.append(Package(City="Wrocław", PostalCode="53-659", StreetAddress="Sikorskiego 10",
                                      ClientId = 3, DeliveryMethod= "Standard", DeclaredValue = 50))
        self._packages.append(Package(City="Wrocław", PostalCode="53-609", StreetAddress="Fabryczna 12",
                                      ClientId=4, DeliveryMethod="Ekonomiczny", DeclaredValue=200))
    def Insert(self, package):
        self._packages.append(package)

    def Find(self, package_code):
        for package in self._packages:
            if package.Code == package_code:
                return package
        return None

    def FindFilter(self, filter_):
        matched = []
        for package in self._packages:
            match = True
            for key in filter_:
                if not getattr(package, key, None) == filter_[key]:
                    match = False
                    break
            if match:
                matched.append(package)
        return matched

    def FindAll(self):
        return self._packages

    def Update(self, package):
        for i in range(len(self._packages)):
            if self._packages[i].Code == package.Code:
                self._packages[i] = package

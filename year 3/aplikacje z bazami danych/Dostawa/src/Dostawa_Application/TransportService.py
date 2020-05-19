from interface import implements
from .TransportInterface import TransportInterface
from Dostawa_Infrastructure.Repositories.PackageRepository import PackageRepository
from Dostawa_Domain.Model.Package.Package import Package, DELIVERY_SUCCESS_STATUS, DELIVERY_FAILURE_STATUS


class TransportService(implements(TransportInterface)):

    def __init__(self):
        self.packageRepository = PackageRepository()

    def GetLimitedPackage(self, package_code):
        package = self.packageRepository.Find(package_code)
        if not package:
            return None
        valid_statuses_obj = Package.FindAllLimitedPackageStatuses()
        valid_statuses = []
        for status_obj in valid_statuses_obj:
            valid_statuses.append(status_obj.Name)
        if package.GetStatus().Name in valid_statuses:
            return package
        return None

    def GetLimitedPackagesFilter(self, filter_):
        packages = self.packageRepository.FindFilter(filter_)
        valid_statuses_obj = Package.FindAllLimitedPackageStatuses()
        valid_statuses = []
        for status_obj in valid_statuses_obj:
            valid_statuses.append(status_obj.Name)
        matched = []
        for package in packages:
            if package.GetStatus().Name in valid_statuses:
                matched.append(package)
        return matched

    def GetAllLimitedPackages(self):
        packages = self.packageRepository.FindAll()
        valid_statuses_obj = Package.FindAllLimitedPackageStatuses()
        valid_statuses = []
        for status_obj in valid_statuses_obj:
            valid_statuses.append(status_obj.Name)
        matched = []
        for package in packages:
            if package.GetStatus().Name in valid_statuses:
                matched.append(package)
        return matched

    def AccomplishDelivery(self, package):
        package.GetStatus().Name = DELIVERY_SUCCESS_STATUS
        self.packageRepository.Update(package)

    def DeliveryFailure(self, package, description):
        package.MakeReturn(description, package.DeclaredValue)
        package.GetStatus().Name = DELIVERY_FAILURE_STATUS
        self.packageRepository.Update(package)

    def PackProduct(self, package, product_name):
        package.MarkPackedProduct(product_name)
        products = package.GetPackageProducts()
        allPacked = True
        for product in products:
            if product.IsPacked == False:
                allPacked = False
                break
        if allPacked:
            package.GetStatus().NextDeliveryStep()
        self.packageRepository.Update(package)

    def GetLimitedPackageSatuses(self):
        return Package.FindAllLimitedPackageStatuses()

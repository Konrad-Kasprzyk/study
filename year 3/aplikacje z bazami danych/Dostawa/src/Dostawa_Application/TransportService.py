from interface import implements
from . import TransportInterface
from Dostawa_Infrastructure.Repositories import PackageRepository, DeliveryTypeRepository
from Dostawa_Domain.Model.Package.ValueObjects.Status import DELIVERY_SUCCESS_STATUS, DELIVERY_FAILURE_STATUS


class TransportService(implements(TransportInterface)):

    def __init__(self):
        self.packageRepository = PackageRepository()
        self.deliveryTypeRepository = DeliveryTypeRepository()

    def GetlimitedPackage(self, package_code):
        package = self.packageRepository.Find(package_code)
        if not package:
            return None
        valid_statuses_obj = self.packageRepository.FindAllLimitedPackageStatuses()
        valid_statuses = []
        for status_obj in valid_statuses_obj:
            valid_statuses.append(status_obj.Name)
        if package.GetStatus().Name in valid_statuses:
            return package
        return None

    def GetLimitedPackagesFilter(self, filter_):
        packages = self.packageRepository.FindFilter(filter_)
        valid_statuses_obj = self.packageRepository.FindAllLimitedPackageStatuses()
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
        valid_statuses_obj = self.packageRepository.FindAllLimitedPackageStatuses()
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
        self.packageRepository.MakePersistent(package)

    def DeliveryFailure(self, package, description):
        package.MakeReturn(description, package.DeclaredValue)
        package.GetStatus().Name = DELIVERY_FAILURE_STATUS
        self.packageRepository.MakePersistent(package)

    def PackProduct(self, package, product_name):
        try:
            package.MarkPackedProduct(product_name)
        except ValueError as err:
            print("PackProduct error:", err)
        else:
            self.packageRepository.MakePersistent(package)

    def GetLimitedPackageSatuses(self):
        return self.packageRepository.FindAllLimitedPackageStatuses()

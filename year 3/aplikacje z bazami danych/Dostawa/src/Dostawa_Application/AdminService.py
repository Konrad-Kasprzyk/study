from interface import implements
from . import AdminInterface
from Dostawa_Infrastructure.Repositories import PackageRepository


class AdminService(implements(AdminInterface)):

    def __init__(self):
        self.packageRepository = PackageRepository()

    def GetAllPackages(self):
        return self.packageRepository.FindAll()

    def GetPackagesFilter(self, filter_):
        return self.packageRepository.FindFilter(filter_)

    def GetPackage(self, package_code):
        return self.packageRepository.Find(package_code)

    def GetPackagePickups(self, package_code):
        package = self.packageRepository.Find(package_code)
        return package.GetPackageProducts()

    def GetPackageStatuses(self):
        return self.packageRepository.FindAllPackageStatuses()

    def ChangePackageStatus(self, package_code, new_status):
        package = self.packageRepository.Find(package_code)
        package_status = package.GetStatus()
        try:
            package_status.Name = new_status
        except


    def GetDeliveryMethods(self):
        pass

    def ChangeDeliveryMethod(self, name, new_value):
        pass

    def AddDeliveryMethod(self, name, value):
        pass

    def DeleteDeliveryMethod(self, name, value):
        pass

    def GetAllReturns(self):
        pass

    def GetReturnsFilter(self, filter):
        pass

    def GetReturn(self, package_code):
        pass

    def AcceptReturn(self, package_code, value):
        pass

    def DeclineReturn(self, package_code, description):
        pass
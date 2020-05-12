from interface import implements
from . import AdminInterface
from Dostawa_Infrastructure.Repositories import PackageRepository, DeliveryTypeRepository


class AdminService(implements(AdminInterface)):

    def __init__(self):
        self.packageRepository = PackageRepository()
        self.deliveryTypeRepository = DeliveryTypeRepository()

    def GetAllPackages(self):
        return self.packageRepository.FindAll()

    def GetPackagesFilter(self, filter_):
        return self.packageRepository.FindFilter(filter_)

    def GetPackage(self, package_code):
        return self.packageRepository.Find(package_code)

    def GetPackagePickups(self, package):
        return package.GetPackageProducts()

    def GetPackageStatuses(self):
        return self.packageRepository.FindAllPackageStatuses()

    def ChangePackageStatus(self, package, new_status):
        package_status = package.GetStatus()
        try:
            package_status.Name = new_status
        except ValueError as err:
            print("ChangePackageStatus error:", err)
        else:
            self.packageRepository.MakePersistent(package)

    def GetDeliveryMethods(self):
        return self.deliveryTypeRepository.FindAll()

    def GetDeliveryMethod(self, name):
        return self.deliveryTypeRepository.Find(name)

    def AddDeliveryMethod(self, new_deliveryMethod):
        self.deliveryTypeRepository.Insert(new_deliveryMethod)

    def DeleteDeliveryMethod(self, name):
        self.deliveryTypeRepository.Delete(name)

    def ChangeDeliveryMethod(self, name, new_deliveryMethod):
        deliveryMethod = self.deliveryTypeRepository.Find(name)
        if not deliveryMethod:
            print("ChangeDeliveryMethod error: name not found")
            return
        self.DeleteDeliveryMethod(name)
        self.AddDeliveryMethod(new_deliveryMethod)

    def GetAllReturns(self):
        packages = self.packageRepository.FindAll()
        returns = []
        for package in packages:
            return_ = package.GetReturn()
            if return_:
                returns.append(return_)
        return returns

    def GetReturnsFilter(self, filter_):
        returns = self.GetAllReturns()
        matched = []
        for return_ in returns:
            match = True
            for key in filter_:
                if not getattr(return_, key, None) == filter_[key]:
                    match = False
                    break
            if match:
                matched.append(return_)
        return matched

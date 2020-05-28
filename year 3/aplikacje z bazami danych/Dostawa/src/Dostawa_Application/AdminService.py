from Dostawa_Infrastructure.Repositories.FakePackageRepository \
    import FakePackageRepository as PackageRepository
from Dostawa_Infrastructure.Repositories.FakeDeliveryTypeRepository \
    import FakeDeliveryTypeRepository as DeliveryTypeRepository
from Dostawa_Domain.Model.Package.Package import Package


class AdminService():

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

    def GetAllPackageStatuses(self):
        return Package.FindAllPackageStatuses()

    """
        Raises ValueError when valid new_status_name
    """
    def ChangePackageStatus(self, package, new_status_name):
        package_status = package.GetStatus()
        package_status.Name = new_status_name
        self.packageRepository.Update(package)

    def GetAllDeliveryMethods(self):
        return self.deliveryTypeRepository.FindAll()

    def GetDeliveryMethod(self, name):
        return self.deliveryTypeRepository.Find(name)

    def AddDeliveryMethod(self, new_deliveryMethod):
        self.deliveryTypeRepository.Insert(new_deliveryMethod)

    def DeleteDeliveryMethod(self, delivery_type):
        self.deliveryTypeRepository.Delete(delivery_type)

    def UpdateDeliveryMethod(self, deliveryMethod):
        self.deliveryTypeRepository.Update(deliveryMethod)

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

    def GetReturn(self, package):
        return package.GetReturn()

    def GetAllReturnStatuses(self):
        return Package.FindAllReturnStatuses()

    def UpdateReturn(self, package, return_):
        if not package.GetReturn():
            raise ValueError("Package doesnt have return. Make return first")
        currReturn = package.GetReturn()
        currReturn.Status = return_.Status
        currReturn.Description = return_.Description
        if return_.Accepted:
            currReturn.Accept()
        self.packageRepository.Update(package)

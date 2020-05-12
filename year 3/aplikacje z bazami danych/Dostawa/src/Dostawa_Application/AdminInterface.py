from interface import Interface


class AdminInterface(Interface):

    def GetAllPackages(self):
        pass

    def GetPackagesFilter(self, filter):
        pass

    def GetPackage(self, package_code):
        pass

    def GetPackagePickups(self, package_code):
        pass

    def GetPackageStatuses(self):
        pass

    def ChangePackageStatus(self, package_code, new_status):
        pass

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



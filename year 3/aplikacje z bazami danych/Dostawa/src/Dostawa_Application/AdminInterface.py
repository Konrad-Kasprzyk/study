from interface import Interface


class AdminInterface(Interface):

    def GetAllPickups(self, package_code):
        pass

    def AcceptReturn(self, package_code, value):
        pass

    def DeclineReturn(self, package_code, description):
        pass

    def ShowPackageInfo(self, package_code):
        pass

    def ChangePackageStatus(self, package_code, new_status):
        pass

    def ShowDeliveryMethods(self):
        pass

    def ChangeDeliveryMethod(self, name, new_value):
        pass

    def AddDeliveryMethod(self, name, value):
        pass

    def ShowPackages(self, filter):
        pass

    def ShowReturns(self, filter):
        pass

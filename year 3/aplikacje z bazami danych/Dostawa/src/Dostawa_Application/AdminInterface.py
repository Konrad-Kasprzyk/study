from interface import Interface


class AdminInterface(Interface):

    def GetAllPickups(self, package_code):
        pass

    def MakeReturn(self, package_code, value):
        pass

    def ShowPackageInfo(self, package_code):
        pass

    def ChangePackageStatus(self, package_code, new_status):
        pass

    def NewDelivery(self, client_id, delivery_method, address, value, items):
        pass

    def ShowDeliveryMethods(self):
        pass

    def ShowPackages(self):
        pass

    def ShowReturns(self):
        pass

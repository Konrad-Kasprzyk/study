from interface import Interface


class TransportInterface(Interface):

    def GetlimitedPackage(self, package_code):
        pass

    def GetLimitedPackagesFilter(self, filter):
        pass

    def GetAllLimitedPackages(self):
        pass

    def AccomplishDelivery(self, package_code):
        pass

    def DeliveryFailure(self, package_code, description):
        pass

    def PackProduct(self, package_code, product_name):
        pass

    def GetLimitedPackageSatuses(self):
        pass
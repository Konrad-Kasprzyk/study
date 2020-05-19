from interface import Interface


class TransportInterface(Interface):

    def GetLimitedPackage(self, package_code):
        pass

    def GetLimitedPackagesFilter(self, filter_):
        pass

    def GetAllLimitedPackages(self):
        pass

    def AccomplishDelivery(self, package):
        pass

    def DeliveryFailure(self, package, description):
        pass

    def PackProduct(self, package, product_name):
        pass

    def GetLimitedPackageSatuses(self):
        pass
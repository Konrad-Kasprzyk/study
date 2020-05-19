from interface import Interface


class ShopInterface(Interface):

    def GetPackageInfo(self, package_code):
        pass

    def NewDelivery(self, city, postalCode, streetAddress, client_id, delivery_method, value, items):
        pass

    def GetPackageStatus(self, package_code):
        pass
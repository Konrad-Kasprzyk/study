from interface import Interface


class ShopInterface(Interface):

    def GetAllPackageInfo(self, client_id):
        pass

    def NewDelivery(self, client_id, delivery_method, address, value, items):
        pass

    def GetPackageStatus(self, client_id):
        pass
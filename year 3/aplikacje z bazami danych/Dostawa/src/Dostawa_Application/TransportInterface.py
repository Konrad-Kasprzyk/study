from interface import Interface


class TransportInterface(Interface):

    def ShowPackages(self, filter):
        pass

    def AccomplishDelivery(self, package_code):
        pass

    def DeliveryFailure(self, package_code, description):
        pass

    def PackProduct(self, package_code, product_name):
        pass
from interface import Interface


class TransportInterface(Interface):

    # Transport może ustawić tylko określone statusy przesyłki, nie może np. anulować jej
    def ChangePackageStatus(self, package_code, new_status):
        pass

    def AccomplishDelivery(self, package_code):
        pass

    def DeliveryFailure(self, package_code, description):
        pass

    def PackProduct(self, package_code, product_name, quantity):
        pass
class Package:

    @property
    def Address(self):
        pass

    @Address.setter
    def Address(self):
        pass

    @property
    def Value(self):
        pass

    @Value.setter
    def Value(self):
        pass

    @property
    def Code(self):
        pass

    @property
    def ClientId(self):
        pass

    @property
    def AcceptDate(self):
        pass

    @AcceptDate.setter
    def AcceptDate(self):
        pass

    @property
    def DeliveryDate(self):
        pass

    @DeliveryDate.setter
    def DeliveryDate(self):
        pass

    @property
    def Status(self):
        pass

    @Status.setter
    def Status(self):
        pass

    # Użyj do tworzenia obiektu przesylki
    def AddDeliveryProduct(self, product_name, quantity):
        pass

    # Użyj przy wkładaniu pobranych produktów z magazynu do przesyłki
    def MarkPackedProduct(self, product_name, quantity, packing_date):
        pass

    # Zwraca zawartość przesyłki
    def GetPackageProducts(self):
        pass

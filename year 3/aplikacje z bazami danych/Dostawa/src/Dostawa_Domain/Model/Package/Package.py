from datetime import datetime
from .Repositories import Status


class Package:

    def __init__(self, City, PostalCode, StreetAddress, ClientId, DeliveryMethod, DeclaredValue=0):
        self._City = City
        self._PostalCode = PostalCode
        self._StreetAddress = StreetAddress
        self._ClientId = ClientId
        self._DeliveryMethod = DeliveryMethod
        self._DeclaredValue = DeclaredValue
        self._AcceptDate = datetime.now()
        self._pickups = []
        self._Status = Status()

    @property
    def City(self):
        return self.City

    @property
    def PostalCode(self):
        pass

    @property
    def StreetAddress(self):
        pass

    @property
    def DeclaredValue(self):
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

    @property
    def DeliveryMethod(self):
        pass

    @property
    def DeliveryDate(self):
        pass

    @DeliveryDate.setter
    def DeliveryDate(self):
        pass

    @property
    def Status(self):
        return self._Status.Name

    @Status.setter
    def Status(self, value):
        self._Status.Name = value

    # Użyj do tworzenia obiektu przesylki
    def AddDeliveryProduct(self, product_name, quantity):
        pass

    # Użyj przy wkładaniu pobranych produktów z magazynu do przesyłki
    def MarkPackedProduct(self, product_name, packing_date):
        pass

    # Zwraca zawartość przesyłki
    def GetPackageProducts(self):
        pass

    def MakeReturn(self, description, sum_=DeclaredValue):
        pass

    def GetReturn(self):
        pass

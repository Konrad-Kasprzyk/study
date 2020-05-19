from datetime import datetime
import uuid
from .ValueObjects.Status import Status
from .ValueObjects.Pickup import Pickup
from .ValueObjects.Return import Return
from Dostawa_Infrastructure.Repositories.DeliveryTypeRepository import DeliveryTypeRepository


DELIVERY_SUCCESS_STATUS = "Dostarczone"
DELIVERY_FAILURE_STATUS = "Problem z Dostawą"
DELIVERY_STARTING_STATUS = "Przyjęte"
RETURN_STARTING_STATUS = "Niepotwierdzone"

class Package:

    def __init__(self, City, PostalCode, StreetAddress, ClientId, DeliveryType, DeclaredValue=0):
        self._City = City
        self._PostalCode = PostalCode
        self._StreetAddress = StreetAddress
        self._ClientId = ClientId
        self._DeclaredValue = DeclaredValue
        self._AcceptDate = datetime.now()
        self._Pickups = []
        self._Status = Status()
        self._DeliveryDate = None
        self._Return = None
        self._PackageCode = int(uuid.uuid4())
        repo = DeliveryTypeRepository()
        allDeliveryTypes = repo.FindAll()
        for repo_deliveryType in allDeliveryTypes:
            if repo_deliveryType.Name == DeliveryType:
                self._DeliveryType = DeliveryType
                return
        raise ValueError("DeliveryType not found in available delivery type names")

    @property
    def City(self):
        return self._City

    @property
    def PostalCode(self):
        return self._PostalCode

    @property
    def StreetAddress(self):
        return self._StreetAddress

    @property
    def DeclaredValue(self):
        return self._DeclaredValue

    @property
    def PackageCode(self):
        return self._PackageCode

    @property
    def ClientId(self):
        return self._ClientId

    @property
    def AcceptDate(self):
        return self._AcceptDate

    @property
    def DeliveryType(self):
        return self._DeliveryType

    @property
    def DeliveryDate(self):
        return self._DeliveryDate

    @DeliveryDate.setter
    def DeliveryDate(self, value):
        if isinstance(value, datetime):
            self._DeliveryDate = value
        else:
            raise ValueError("DeliveryDate must be a datetime object")

    def GetStatus(self):
        return self._Status

    # Użyj do tworzenia obiektu przesylki
    def AddDeliveryProduct(self, product_name, quantity):
        if not isinstance(product_name, str) or not isinstance(quantity, int) \
                or not product_name or quantity < 1:
            raise ValueError("Bad input while putting products to deliver")
        for pickup in self._Pickups:
            if pickup.Name == product_name:
                raise ValueError("while putting products to deliver product duplication occurred")
        self._Pickups.append(Pickup(Name=product_name, Amount=quantity))

    # Użyj przy wkładaniu pobranych produktów z magazynu do przesyłki
    def MarkPackedProduct(self, product_name):
        for pickup in self._Pickups:
            if pickup.Name == product_name:
                pickup.IsPacked = True
                pickup.PackingDate = datetime.now()
                return
        raise ValueError("Product name not found while packing product")

    # Zwraca zawartość przesyłki
    def GetPackageProducts(self):
        return self._Pickups

    def MakeReturn(self, description, sum_=None):
        if not sum_:
            sum_=self._DeclaredValue
        if not isinstance(description, str) or not isinstance(sum_, int)\
                or not description or sum_ < 0:
            raise ValueError("Bad input while making return")
        self._Return = Return(description, sum_)

    def GetReturn(self):
        return self._Return

    # Keep sorted by DeliveryStep!
    @staticmethod
    def FindAllPackageStatuses():
        statuses = []
        statuses.append(Status(DeliveryStep=0, Name=DELIVERY_STARTING_STATUS))
        statuses.append(Status(DeliveryStep=1, Name="Pakowanie"))
        statuses.append(Status(DeliveryStep=2, Name="Wysłane"))
        statuses.append(Status(DeliveryStep=3, Name=DELIVERY_SUCCESS_STATUS))
        statuses.append(Status(DeliveryStep=4, Name=DELIVERY_FAILURE_STATUS))
        statuses.append(Status(DeliveryStep=5, Name="Anulowane"))
        return statuses

    # dla transportu, np. transport nie może ustawić statusu paczki na anulowane
    # Keep sorted!
    @staticmethod
    def FindAllLimitedPackageStatuses():
        statuses = []
        statuses.append(Status(DeliveryStep=1, Name="Pakowanie"))
        statuses.append(Status(DeliveryStep=2, Name="Wysłane"))
        statuses.append(Status(DeliveryStep=3, Name=DELIVERY_SUCCESS_STATUS))
        statuses.append(Status(DeliveryStep=4, Name=DELIVERY_FAILURE_STATUS))
        return statuses

    @staticmethod
    def FindAllReturnStatuses():
        statuses = []
        statuses.append(RETURN_STARTING_STATUS)
        statuses.append("Zwrot pieniędzy")
        statuses.append("Wysłane ponownie")
        return statuses

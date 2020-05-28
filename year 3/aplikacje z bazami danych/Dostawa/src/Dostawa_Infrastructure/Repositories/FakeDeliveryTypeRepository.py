from interface import implements
from Dostawa_Domain.Model.DeliveryType.Repositories.IDeliveryTypeRepository import IDeliveryTypeRepository
from Dostawa_Domain.Model.DeliveryType.DeliveryType import DeliveryType

class FakeDeliveryTypeRepository(implements(IDeliveryTypeRepository)):

    def __init__(self):
        self._deliveryTypes = []
        self._deliveryTypes.append(DeliveryType(Name="Ekonomiczny", Price=12, DeliveryTime="3-5 dni roboczych"))
        self._deliveryTypes.append(DeliveryType(Name="Standard", Price=15, DeliveryTime="2-3 dni roboczych"))
        self._deliveryTypes.append(DeliveryType(Name="Ekspres", Price=20, DeliveryTime="1-2 dni roboczych"))

    def Insert(self, delivery_type):
        self._deliveryTypes.append(delivery_type)

    def Find(self, name):
        for delivery_type in self._deliveryTypes:
            if delivery_type.Name == name:
                return delivery_type
        return None

    def Delete(self, delivery_type):
        self._deliveryTypes.remove(delivery_type)

    def FindAll(self):
        return self._deliveryTypes

    def Update(self, delivery_type):
        pass
from interface import implements
from Dostawa_Domain.Model.DeliveryType.Repositories import IDeliveryTypeRepository
from Dostawa_Domain.Model.DeliveryType import DeliveryType

class DeliveryTypeRepository(implements(IDeliveryTypeRepository)):

    def __init__(self):
        self._deliveryTypes = []
        self._deliveryTypes.append(DeliveryType(Name="Ekonomiczny", Price=12, DeliveryType="3-5 dni roboczych"))
        self._deliveryTypes.append(DeliveryType(Name="Standard", Price=15, DeliveryType="2-3 dni roboczych"))
        self._deliveryTypes.append(DeliveryType(Name="Ekspres", Price=20, DeliveryType="1-2 dni roboczych"))

    def Insert(self, delivery_type):
        self._deliveryTypes.append(delivery_type)

    def Find(self, name):
        for delivery_type in self._deliveryTypes:
            if delivery_type.Name == name:
                return delivery_type
        return None

    def Delete(self, name):
        self._deliveryTypes.remove(name)

    def FindAll(self):
        return self._deliveryTypes

    def MakePersistent(self, delivery_type):
        for i in range(len(self._deliveryTypes)):
            if self._deliveryTypes[i].Name == delivery_type.Name:
                self._deliveryTypes[i] = delivery_type
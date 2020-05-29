from interface import implements
from Dostawa_Domain.Model.DeliveryType.Repositories.IDeliveryTypeRepository import IDeliveryTypeRepository
from Dostawa_Infrastructure.models.DeliveryType.DeliveryType import DeliveryType


class DeliveryTypeRepository(implements(IDeliveryTypeRepository)):

    def Insert(self, delivery_type):
        ORMDeliveryType = DeliveryType()
        ORMDeliveryType.Name = delivery_type.Name
        ORMDeliveryType.Price = delivery_type.Price
        ORMDeliveryType.DeliveryTime = delivery_type.DeliveryTime
        ORMDeliveryType.save()

    def Find(self, name):
        delivery_type = DeliveryType.objects.get(_NameField=name)
        delivery_type._restore()
        return delivery_type

    def Delete(self, delivery_type):
        delivery_type.delete()

    def FindAll(self):
        DeliveryTypes = list(DeliveryType.objects.all())
        for delivery_type in DeliveryTypes:
            delivery_type._restore()
        return DeliveryTypes
        #return [delivery_type._restore() for delivery_type in list(DeliveryType.objects.all())]

    def Update(self, delivery_type):
        delivery_type.save()

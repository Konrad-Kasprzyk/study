from interface import implements
from Dostawa_Domain.Model.DeliveryType.Repositories.IDeliveryTypeRepository import IDeliveryTypeRepository
from Dostawa_Infrastructure.models.DeliveryType.DeliveryTypeModel import DeliveryTypeModel


class DeliveryTypeRepository(implements(IDeliveryTypeRepository)):

    def Insert(self, delivery_type):
        ORMDeliveryType = DeliveryTypeModel()
        ORMDeliveryType.Name = delivery_type.Name
        ORMDeliveryType.Price = delivery_type.Price
        ORMDeliveryType.DeliveryTime = delivery_type.DeliveryTime
        ORMDeliveryType.save()

    def Find(self, name):
        delivery_type = DeliveryTypeModel.objects.get(_NameField=name)
        delivery_type._restore()
        return delivery_type

    def Delete(self, delivery_type):
        delivery_type.delete()

    def FindAll(self):
        DeliveryTypes = list(DeliveryTypeModel.objects.all())
        for delivery_type in DeliveryTypes:
            delivery_type._restore()
        return DeliveryTypes

    def Update(self, delivery_type):
        delivery_type.save()

from Dostawa_Domain.Model.DeliveryType.DeliveryType import DeliveryType


class DeliveryTypeObjectMother:

    @staticmethod
    def CreateDeliveryType():
        return DeliveryType(Name="Standard", Price=12, DeliveryTime="3-5 dni roboczych")
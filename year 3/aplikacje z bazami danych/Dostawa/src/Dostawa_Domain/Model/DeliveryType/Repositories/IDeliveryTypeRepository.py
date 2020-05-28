from interface import Interface


class IDeliveryTypeRepository(Interface):

    def Insert(self, delivery_type):
        pass

    def Find(self, name):
        pass

    def Delete(self, delivery_type):
        pass

    def FindAll(self):
        pass

    def Update(self, delivery_type):
        pass
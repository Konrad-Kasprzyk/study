class DeliveryTpe:

    def __init__(self, Name, Price, DeliveryTime):
        self._Name = Name
        self._Price = Price
        self._DeliveryTime = DeliveryTime

    @property
    def Name(self):
        return self._Name

    @Name.setter
    def Name(self, value):
        if isinstance(value, str):
            self._Name = value
        else:
            raise ValueError("Name must be a string")

    @property
    def Price(self):
        return self._Price

    @Price.setter
    def Price(self, value):
        if isinstance(value, int):
            self._Price = value
        else:
            raise ValueError("Price must be an integer")

    @property
    def DeliveryTime(self):
        return self._DeliveryTime

    @DeliveryTime.setter
    def DeliveryTime(self, value):
        if isinstance(value, int):
            self._DeliveryTime = value

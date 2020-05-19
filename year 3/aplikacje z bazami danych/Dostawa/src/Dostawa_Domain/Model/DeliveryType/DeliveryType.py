class DeliveryType:

    def __init__(self, Name, Price, DeliveryTime):
        self._Name = Name
        self._Price = Price
        self._DeliveryTime = DeliveryTime

    @property
    def Name(self):
        return self._Name

    @Name.setter
    def Name(self, value):
        if value and isinstance(value, str):
            self._Name = value
        else:
            raise ValueError("Name must be a non empty string")

    @property
    def Price(self):
        return self._Price

    @Price.setter
    def Price(self, value):
        if isinstance(value, int) and value > 0:
            self._Price = value
        else:
            raise ValueError("Price must be a postitive integer")

    @property
    def DeliveryTime(self):
        return self._DeliveryTime

    @DeliveryTime.setter
    def DeliveryTime(self, value):
        if value and isinstance(value, str):
            self._DeliveryTime = value
        else:
            raise ValueError("DeliveryTime must be a non empty string")

from datetime import datetime


class PickUp:

    def __init__(self, ProductName, Amount = 1):
        self._IsPacked = False
        self._Productname = ProductName
        self._Amount = Amount
        self._PackingDate = None

    @property
    def Productname(self):
        return self._Productname

    @property
    def Amount(self):
        return self._Amount

    @property
    def IsPacked(self):
        return self._IsPacked

    @IsPacked.setter
    def IsPacked(self, value):
        if isinstance(value, bool):
            self._IsPacked = value
        else:
            raise ValueError("IsPacked must be a bool")

    @property
    def PackingDate(self):
        return self._PackingDate

    @PackingDate.setter
    def PackingDate(self, value):
        if isinstance(value, datetime):
            self._PackingDate = value
        else:
            raise ValueError("PackingDate must be a datetime object")
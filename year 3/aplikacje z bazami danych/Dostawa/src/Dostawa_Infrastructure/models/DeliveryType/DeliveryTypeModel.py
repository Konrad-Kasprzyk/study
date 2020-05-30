from Dostawa_Domain.Model.DeliveryType.DeliveryType import DeliveryType
from django.db import models


class DeliveryTypeModel(DeliveryType, models.Model):
    _NameField = models.CharField(max_length=200)
    _PriceField = models.PositiveIntegerField()
    _DeliveryTimeField = models.CharField(max_length=200)

    def __init__(self, *args, **kwargs):
        models.Model.__init__(self, *args, **kwargs)

    def _restore(self):
        super(DeliveryTypeModel, type(self)).Name.fset(self, self._NameField)
        super(DeliveryTypeModel, type(self)).Price.fset(self, self._PriceField)
        super(DeliveryTypeModel, type(self)).DeliveryTime.fset(self, self._DeliveryTimeField)

    @property
    def Name(self):
        return super().Name

    @Name.setter
    def Name(self, value):
        super(DeliveryTypeModel, type(self)).Name.fset(self, value)
        self._NameField = value

    @property
    def Price(self):
        return super().Price

    @Price.setter
    def Price(self, value):
        super(DeliveryTypeModel, type(self)).Price.fset(self, value)
        self._PriceField = value

    @property
    def DeliveryTime(self):
        return super().DeliveryTime

    @DeliveryTime.setter
    def DeliveryTime(self, value):
        super(DeliveryTypeModel, type(self)).DeliveryTime.fset(self, value)
        self._DeliveryTimeField = value

from Dostawa_Domain.Model.Package.ValueObjects.Pickup import Pickup
import Dostawa_Infrastructure.models.Package.PackageModel as PackageModelFile
from django.db import models


class PickupModel(Pickup, models.Model):
    _NameField = models.CharField(max_length=200)
    _AmountField = models.PositiveIntegerField(default=1)
    _IsPackedField = models.BooleanField(default=False)
    _PackingDateField = models.DateField(default=None, null=True)
    _PackageForeignKey = models.ForeignKey(PackageModelFile.PackageModel, on_delete=models.CASCADE)

    def __init__(self, *args, **kwargs):
        models.Model.__init__(self, *args, **kwargs)

    def _restore(self):
        super(PickupModel, type(self)).Name.fset(self, self._NameField)
        self._Amount = self._AmountField
        super(PickupModel, type(self)).IsPacked.fset(self, self._IsPackedField)
        super(PickupModel, type(self)).PackingDate.fset(self, self._PackingDateField)

    @property
    def Name(self):
        return super().Name

    @property
    def Amount(self):
        return super().Amount

    @property
    def IsPacked(self):
        return super().IsPacked

    @IsPacked.setter
    def IsPacked(self, value):
        super(PickupModel, type(self)).IsPacked.fset(self, value)
        self._IsPackedField = value

    @property
    def PackingDate(self):
        return super().PackingDate

    @PackingDate.setter
    def PackingDate(self, value):
        super(PickupModel, type(self)).PackingDate.fset(self, value)
        self._PackingDateField = value

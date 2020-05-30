from Dostawa_Domain.Model.Package.Package import Package
from Dostawa_Domain.Model.Package.ValueObjects.Status import Status
import Dostawa_Infrastructure.models.Package.PickupModel as PickupModelFile
from Dostawa_Infrastructure.models.Package.ReturnModel import ReturnModel
from django.db import models
from datetime import datetime


class PackageModel(Package, models.Model):
    _CityField = models.CharField(max_length=50)
    _PostalCodeField = models.CharField(max_length=20)
    _StreetAddressField = models.CharField(max_length=200)
    _ClientIdField = models.PositiveIntegerField()
    _DeclaredValueField = models.PositiveIntegerField()
    _AcceptDateField = models.DateField()
    _DeliveryDateField = models.DateField(null=True)
    _PackageCodeField = models.CharField(max_length=200)
    _StatusNameField = models.CharField(max_length=100)
    _StatusDeliveryStepField = models.PositiveSmallIntegerField()
    _ReturnForeignKey = models.ForeignKey(ReturnModel, on_delete=models.CASCADE, default=None, null=True)

    def __init__(self, *args, **kwargs):
        models.Model.__init__(self, *args, **kwargs)

    def _restore(self):
        self._City = self._CityField
        self._PostalCode = self._PostalCodeField
        self._StreetAddress = self._StreetAddressField
        self._ClientId = self._ClientIdField
        self._DeclaredValue = self._DeclaredValueField
        self._AcceptDate = self._AcceptDateField
        self._DeliveryDate = self._DeliveryDateField
        self._PackageCode = int(self._PackageCodeField)
        self._Status = Status(self._StatusDeliveryStepField, self._StatusNameField)

    @property
    def City(self):
        return super().City

    @property
    def PostalCode(self):
        return super().PostalCode

    @property
    def StreetAddress(self):
        return super().StreetAddress

    @property
    def DeclaredValue(self):
        return super().DeclaredValue

    @property
    def PackageCode(self):
        return super().PackageCode

    @property
    def ClientId(self):
        return super().ClientId

    @property
    def AcceptDate(self):
        return super().AcceptDate

    @property
    def DeliveryType(self):
        return super().DeliveryType

    @property
    def DeliveryDate(self):
        return super().DeliveryDate

    @DeliveryDate.setter
    def DeliveryDate(self, value):
        super(PackageModel, type(self)).DeliveryDate.fset(self, value)
        self._DeliveryDateField = value

    def GetStatus(self):
        return self._Status

    def AddDeliveryProduct(self, product_name, quantity):
        super().AddDeliveryProduct(product_name, quantity)
        PickupModelFile.PickupModel.objects.create(_NameField=product_name, _AmountField=quantity,
                                                   _IsPackedField=False, _PackageForeignKey=self)

    def MarkPackedProduct(self, product_name):
        pickup = PickupModelFile.PickupModel.objects.filter(_NameField=product_name, _PackageForeignKey=self).first()
        if not pickup:
            raise ValueError("Product name not found while packing product")
        pickup._IsPackedField = True
        pickup._PackingDateField = datetime.now()
        pickup.save()

    def UndoMarkPackedProduct(self, product_name):
        pickup = PickupModelFile.PickupModel.objects.filter(_NameField=product_name, _PackageForeignKey=self).first()
        if not pickup:
            raise ValueError("Product name not found while packing product")
        pickup._IsPackedField = False
        pickup._PackingDateField = None
        pickup.save()

    def GetPackageProducts(self):
        pickups = list(PickupModelFile.PickupModel.objects.filter(_PackageForeignKey=self))
        for pickup in pickups:
            pickup._restore()
        return pickups

    def MakeReturn(self, description, sum_=None):
        super().MakeReturn(description, sum_)
        return_ = super().GetReturn()
        self._ReturnForeignKey = ReturnModel.objects.create(_DescriptionField=return_.Description,
                                                            _SumField=return_.Sum, _ReportDateField=return_.ReportDate,
                                                            _StatusField=return_.Status)

    def GetReturn(self):
        return_ = self._ReturnForeignKey
        if return_:
            return_._restore()
        return return_

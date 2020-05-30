from Dostawa_Domain.Model.Package.ValueObjects.Return import Return
from django.db import models


class ReturnModel(Return, models.Model):
    _DescriptionField = models.CharField(max_length=200)
    _SumField = models.PositiveIntegerField()
    _ReportDateField = models.DateField()
    _AcceptedField = models.BooleanField(default=False)
    _StatusField = models.CharField(max_length=100)

    def __init__(self, *args, **kwargs):
        models.Model.__init__(self, *args, **kwargs)

    def _restore(self):
        super(ReturnModel, type(self)).Description.fset(self, self._DescriptionField)
        self._Sum = self._SumField
        self._ReportDate = self._ReportDateField
        self._Accepted = self._AcceptedField
        super(ReturnModel, type(self)).Status.fset(self, self._StatusField)

    @property
    def Status(self):
        return super().Status

    @Status.setter
    def Status(self, value):
        super(ReturnModel, type(self)).Status.fset(self, value)
        self._StatusField = value

    @property
    def Sum(self):
        return super().Sum

    @property
    def ReportDate(self):
        return super().ReportDate

    @property
    def Accepted(self):
        return super().Accepted

    def Accept(self):
        super().Accept()
        self._AcceptedField = True

    @property
    def Description(self):
        return super().Description

    @Description.setter
    def Description(self, value):
        super(ReturnModel, type(self)).Description.fset(self, value)
        self._DescriptionField = value

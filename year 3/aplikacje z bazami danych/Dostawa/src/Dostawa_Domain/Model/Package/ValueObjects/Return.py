from datetime import datetime
import Dostawa_Domain.Model.Package.Package as PackageFile


class Return:

    def __init__(self, Description, Sum = 0):
        self._Description = Description
        self._Sum = Sum
        self._ReportDate = datetime.now()
        self._Accepted = False
        self._Status = PackageFile.RETURN_STARTING_STATUS

    @property
    def Status(self):
        return self._Status

    @Status.setter
    def Status(self, value):
        returnStatuses = PackageFile.Package.FindAllReturnStatuses()
        if value in returnStatuses:
            self._Status = value

    @property
    def Sum(self):
        return self._Sum

    @property
    def ReportDate(self):
        return self._ReportDate

    @property
    def ReturnDate(self):
        return self._ReturnDate

    @ReturnDate.setter
    def ReturnDate(self, value):
        if isinstance(value, datetime):
            self._ReturnDate = value
        else:
            raise ValueError("ReturnDate must be a datetime object")

    @property
    def Accepted(self):
        return self._Accepted

    def Accept(self):
        self._Accepted = True

    @property
    def Description(self):
        return self._Description

    @Description.setter
    def Description(self, value):
        if isinstance(value, str):
            self._Description = value
        else:
            raise ValueError("Description must be a string")

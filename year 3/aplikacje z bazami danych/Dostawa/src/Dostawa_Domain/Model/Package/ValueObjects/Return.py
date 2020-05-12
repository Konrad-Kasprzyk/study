from datetime import datetime


class Return:

    def __init__(self, Description, Sum = 0):
        self._Description = Description
        self._Sum = Sum
        self._ReportDate = datetime.now()
        self._Accepted = False

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

    @Accepted.setter
    def Accepted(self, value):
        if isinstance(value, bool):
            self._Accepted = value
        else:
            raise ValueError("Accepted must be a bool")

    @property
    def Description(self):
        return self._Description

    @Description.setter
    def Description(self, value):
        if isinstance(value, str):
            self._Description = value
        else:
            raise ValueError("Description must be a string")

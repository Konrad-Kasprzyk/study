from datetime import datetime


class Return:

    def __init__(self, Description, Sum = 0):
        self._Description = Description
        self._Sum = Sum
        self._ReportDate = datetime.now()

    @property
    def Sum(self):
        pass

    @property
    def ReportDate(self):
        pass

    @property
    def ReturnDate(self):
        pass

    @ReturnDate.setter
    def ReturnDate(self):
        pass

    @property
    def Accepted(self):
        pass

    @Accepted.setter
    def Accepted(self):
        pass

    @property
    def Description(self):
        pass

    @Description.setter
    def Description(self):
        pass

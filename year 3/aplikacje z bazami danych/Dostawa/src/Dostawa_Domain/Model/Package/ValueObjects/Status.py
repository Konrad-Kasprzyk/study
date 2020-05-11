from Dostawa_Infrastructure.Repositories import PackageRepository

class Status:

    _startStatus = "Przyjete"

    def __init__(self, Name = _startStatus):
        self._Name = Name

    @property
    def Name(self):
        return self._Name

    @Name.setter
    def Name(self, value):
        repo = PackageRepository()
        if value in repo.GetAllPackageStatuses():
            self._Name = value
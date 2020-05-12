from interface import Interface


class IPackageRepository(Interface):

    def Insert(self, package):
        pass

    def Find(self, package_code):
        pass

    def FindFilter(self, filter_):
        pass

    def FindAll(self):
        pass

    def MakePersistent(self, package):
        pass

    def FindAllPackageStatuses(self):
        pass

    # dla transportu, np. transport nie może ustawić statusu paczki na anulowane
    def FindAllLimitedPackageStatuses(self):
        pass

    def FindAllReturnStatuses(self):
        pass
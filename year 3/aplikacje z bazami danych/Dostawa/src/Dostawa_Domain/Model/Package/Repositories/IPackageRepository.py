from interface import Interface


class IPackageRepository(Interface):

    def Insert(self, package):
        pass

    def Find(self, package_code):
        pass

    def FindFilter(self, filter):
        pass

    def FindAll(self):
        pass

    def MakePersistent(self, package):
        pass

    def GetAllPackageStatuses(self):
        pass
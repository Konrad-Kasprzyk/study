import Dostawa_Domain.Model.Package.Package as PackageFile


class Status:

    def __init__(self, DeliveryStep = -1, Name = None):
        if DeliveryStep < 0 or not Name:
            self._DeliveryStep = 0
            self._Name = PackageFile.DELIVERY_STARTING_STATUS
        else:
            self._DeliveryStep = DeliveryStep
            self._Name = Name

    @property
    def DeliveryStep(self):
        return self._DeliveryStep

    @property
    def Name(self):
        return self._Name

    @Name.setter
    def Name(self, value):
        for status in PackageFile.Package.FindAllPackageStatuses():
            if status.Name == value:
                self._Name = value
                self._DeliveryStep = status.DeliveryStep
                return
        raise ValueError("Status name not found in available statuses")

    def NextDeliveryStep(self):
        allStatuses = PackageFile.Package.FindAllPackageStatuses()
        if allStatuses[-1].DeliveryStep <= self._DeliveryStep:
            return
        self._DeliveryStep += 1
        for status in allStatuses:
            if status.DeliveryStep == self._DeliveryStep:
                self._Name = status.Name

    def PrevDeliveryStep(self):
        allStatuses = PackageFile.Package.FindAllPackageStatuses()
        if allStatuses[0].DeliveryStep >= self._DeliveryStep:
            return
        self._DeliveryStep -= 1
        for status in allStatuses:
            if status.DeliveryStep == self._DeliveryStep:
                self._Name = status.Name
from unittest import TestCase
from Dostawa_ObjectMothers.DeliveryTypeObjectMother import DeliveryTypeObjectMother
from Dostawa_Infrastructure.Repositories.FakeDeliveryTypeRepository import \
    FakeDeliveryTypeRepository as DeliveryTypeRepository


class DeliveryTypeRepositoryTests(TestCase):

    def test_FindInsertedDeliveryTypes(self):
        deliveryTypeRepository = DeliveryTypeRepository()
        deliveryType = DeliveryTypeObjectMother.CreateDeliveryType()
        deliveryType2 = DeliveryTypeObjectMother.CreateDeliveryType()
        deliveryType3 = DeliveryTypeObjectMother.CreateDeliveryType()
        deliveryType.Name = "Sample name"
        deliveryType2.Name = "Sample name2"
        deliveryType3.Name = "Sample name3"
        deliveryType.DeliveryTime = "Sample delivery time"
        deliveryType2.DeliveryTime = "Sample delivery time2"
        deliveryType3.DeliveryTime = "Sample delivery time3"

        deliveryTypeRepository.Insert(deliveryType)
        deliveryTypeRepository.Insert(deliveryType2)
        deliveryTypeRepository.Insert(deliveryType3)

        assert "Sample delivery time" == deliveryTypeRepository.Find("Sample name").DeliveryTime
        assert "Sample delivery time2" == deliveryTypeRepository.Find("Sample name2").DeliveryTime
        assert "Sample delivery time3" == deliveryTypeRepository.Find("Sample name3").DeliveryTime

    def test_FindInsertedDeliveryTypeInFindAll(self):
        deliveryTypeRepository = DeliveryTypeRepository()
        insertedDeliveryType = DeliveryTypeObjectMother.CreateDeliveryType()
        insertedDeliveryType.Name = "Sample name"
        insertedDeliveryType.DeliveryTime = "Sample delivery time"
        deliveryTypes = deliveryTypeRepository.FindAll()

        deliveryTypeRepository.Insert(insertedDeliveryType)
        foundInsertedDeliveryType = False
        for deliveryType in deliveryTypes:
            if deliveryType.Name == insertedDeliveryType.Name and \
                    deliveryType.Price == insertedDeliveryType.Price and \
                    deliveryType.DeliveryTime == insertedDeliveryType.DeliveryTime:
                foundInsertedDeliveryType = True
                break

        assert foundInsertedDeliveryType == True

    def test_FindUpdatedDeliveryTypeReturnsSamePackage(self):
        deliveryTypeRepository = DeliveryTypeRepository()
        deliveryTypes = deliveryTypeRepository.FindAll()
        deliveryType = deliveryTypes[0]

        deliveryType.Name = "Sample name"
        deliveryType.Price = 1
        deliveryType.DeliveryTime = "Sample delivery time"
        deliveryTypeRepository.Update(deliveryType)
        deliveryTypeAfterInsert = deliveryTypeRepository.Find(deliveryType.Name)

        assert deliveryTypeAfterInsert.Name == deliveryType.Name
        assert deliveryTypeAfterInsert.Price == deliveryType.Price
        assert deliveryTypeAfterInsert.DeliveryTime == deliveryType.DeliveryTime


    def test_Deleting(self):
        deliveryTypeRepository = DeliveryTypeRepository()
        deliveryTypes = deliveryTypeRepository.FindAll()
        deletedDeliveryType = deliveryTypes[0]

        deliveryTypeRepository.Delete(deletedDeliveryType)
        deliveryTypes = deliveryTypeRepository.FindAll()
        foundDeletedDeliveryType = False
        for deliveryType in deliveryTypes:
            if deliveryType.Name == deletedDeliveryType.Name and \
                    deliveryType.Price == deletedDeliveryType.Price and \
                    deliveryType.DeliveryTime == deletedDeliveryType.DeliveryTime:
                foundDeletedDeliveryType = True
                break

        assert foundDeletedDeliveryType == False

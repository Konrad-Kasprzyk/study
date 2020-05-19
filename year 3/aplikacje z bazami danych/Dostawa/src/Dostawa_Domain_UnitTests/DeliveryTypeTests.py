from unittest import TestCase
from Dostawa_ObjectMothers.DeliveryTypeObjectMother import DeliveryTypeObjectMother


class DeliveryTypeTests(TestCase):

    def test_ChangingDeliveryTypeProperties(self):
        type = DeliveryTypeObjectMother.CreateDeliveryType()

        type.Name = "qwerty"
        type.DeliveryTime = "w kilka godzin"
        type.Price = 17

        self.assertEqual(type.Name, "qwerty")
        self.assertEqual(type.DeliveryTime, "w kilka godzin")
        self.assertEqual(type.Price, 17)

    def test_BadChangesRaisesException(self):
        type = DeliveryTypeObjectMother.CreateDeliveryType()

        with self.assertRaises(ValueError):
            type.Name = ""

        with self.assertRaises(ValueError):
            type.Name = 17

        with self.assertRaises(ValueError):
            type.DeliveryTime = ""

        with self.assertRaises(ValueError):
            type.DeliveryTime = 17

        with self.assertRaises(ValueError):
            type.Price = "drogo"


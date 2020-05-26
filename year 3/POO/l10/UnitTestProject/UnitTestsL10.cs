using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using l10;

namespace UnitTestProject
{
    [TestClass]
    public class UnitTestsL10
    {
        [TestMethod]
        public void TestRegisterInstanceReturnsSameInstance()
        {
            SimpleContainer container = new SimpleContainer();

            ClassInheritsClass object1 = new ClassInheritsClass();
            container.RegisterInstance<ClassInheritsClass>(object1);
            ClassInheritsClass object2 = container.Resolve<ClassInheritsClass>();

            Assert.AreEqual(object1, object2);
        }

        [TestMethod]
        public void TestManyAttributeConstrucorsThrowException()
        {
            SimpleContainer container = new SimpleContainer();

            Assert.ThrowsException<MemberAccessException>(() =>
            {
                ManyAttributeConstrucors object1 =
                container.Resolve<ManyAttributeConstrucors>();
            });
        }

        [TestMethod]
        public void TestManyConstructorsOneAttributeConstrucotrUseAttributeConstrucotr()
        {
            SimpleContainer container = new SimpleContainer();

            container.RegisterType<Interface, ClassInheritsAbstractClass>(false);
            var object1 = container.Resolve<ManyConstructorsOnlyAttributeConstrucotrDoesntThrowException>();
        }

        [TestMethod]
        public void TestLongestConstrucotIsUsed()
        {
            SimpleContainer container = new SimpleContainer();

            container.RegisterType<Interface, ClassInheritsAbstractClass>(false);
            var object1 = container.Resolve<ManyConstructorsOnlyLongestConstructorDoesntThrowException>();
        }

        [TestMethod]
        public void TestManySameLengthConstructorsProperlyCreateObject()
        {
            SimpleContainer container = new SimpleContainer();

            container.RegisterType<Interface, ClassInheritsAbstractClass>(false);
            var object1 = container.Resolve<ManySameLengthConstructors>();
        }

        [TestMethod]
        public void TestConstructorWithManyDifferentParametersProperlyCreateObject()
        {
            SimpleContainer container = new SimpleContainer();

            container.RegisterType<Interface, ClassInheritsAbstractClass>(false);
            var object1 = container.Resolve<ConstructorRequireManyDifferentParameters>();
        }

        [TestMethod]
        public void TestConstructorWithoutRegisteringSimpleTypesThrowsException()
        {
            SimpleContainer container = new SimpleContainer();

            Assert.ThrowsException<MissingMethodException>(() =>
            {
                var object1 = container.Resolve<ConstructorRequireRegisteringStringAndInt>();
            });
        }

        [TestMethod]
        public void TestConstructorWithRegisteringSimpleTypesCreatesProperly()
        {
            SimpleContainer container = new SimpleContainer();
            container.RegisterInstance<string>("string");
            container.RegisterInstance<int>(13);

            var object1 = container.Resolve<ConstructorRequireRegisteringStringAndInt>();
        }

        [TestMethod]
        public void TestResolveConstructorParametersCreatingCycleThrowsException()
        {
            SimpleContainer container = new SimpleContainer();
            container.RegisterType<Interface, ClassInheritsAbstractClass>(false);

            Assert.ThrowsException<MemberAccessException>(() =>
            {
                var object1 = container.Resolve<ConstructorParametersCreateResolveCycle>();
            });
        }
    }
}

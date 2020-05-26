using Microsoft.VisualStudio.TestTools.UnitTesting;
using l9z1;
using System;

namespace l9z1TestProject
{
    [TestClass]
    public class UnitTests
    {
        [TestMethod]
        public void TestRegisteringClassAsSingletonAreEqual()
        {
            SimpleContainer container = new SimpleContainer();

            container.RegisterType<ClassInheritsAbstractClass>(true);
            ClassInheritsAbstractClass object1 = container.Resolve<ClassInheritsAbstractClass>();
            ClassInheritsAbstractClass object2 = container.Resolve<ClassInheritsAbstractClass>();

            Assert.AreEqual(object1, object2);
        }

        [TestMethod]
        public void TestUnregisteredClassResolveNotEqual()
        {
            SimpleContainer container = new SimpleContainer();

            ClassInheritsAbstractClass object1 = container.Resolve<ClassInheritsAbstractClass>();
            ClassInheritsAbstractClass object2 = container.Resolve<ClassInheritsAbstractClass>();

            Assert.AreNotEqual(object1, object2);
        }

        [TestMethod]
        public void TestInterfaceResolveThrowingErrorNoEmptyConstructor()
        {
            SimpleContainer container = new SimpleContainer();

            Assert.ThrowsException<MissingMethodException>(() =>
            {
                Interface interface1 = container.Resolve<Interface>();
            });
        }

        [TestMethod]
        public void TestAbstractClassResolveThrowingErrorNoEmptyConstructor()
        {
            SimpleContainer container = new SimpleContainer();

            Assert.ThrowsException<MissingMethodException>(() =>
            {
                AbstractClassNoConstrucotrImplementingInterface abstractObject1 =
                container.Resolve<AbstractClassNoConstrucotrImplementingInterface>();
            });
        }

        [TestMethod]
        public void TestAbstractClassResolveThrowingErrorCannotCreateAbstractClass()
        {
            SimpleContainer container = new SimpleContainer();

            Assert.ThrowsException<MemberAccessException>(() =>
            {
                AbstractClassImplementingInterface abstractObject1 =
                container.Resolve<AbstractClassImplementingInterface>();
            });
        }

        [TestMethod]
        public void TestClassResolveThrowingErrorNoEmptyConstructor()
        {
            SimpleContainer container = new SimpleContainer();

            Assert.ThrowsException<MissingMethodException>(() =>
            {
                ClassNoEmptyConstructorInheritsAbstractClass object1 =
                container.Resolve<ClassNoEmptyConstructorInheritsAbstractClass>();
            });
        }

        [TestMethod]
        public void TestRegisteringInterfaceWithSingletonAreEqual()
        {
            SimpleContainer container = new SimpleContainer();

            container.RegisterType<Interface, ClassInheritsAbstractClass>(true);
            var object1 = container.Resolve<Interface>();
            var object2 = container.Resolve<Interface>();

            Assert.AreEqual(object1, object2);
        }

        [TestMethod]
        public void TestRegisteringSingletonAfterInterfaceAreEqual()
        {
            SimpleContainer container = new SimpleContainer();

            container.RegisterType<Interface, ClassInheritsAbstractClass>(false);
            container.RegisterType<ClassInheritsAbstractClass>(true);
            var object1 = container.Resolve<Interface>();
            var object2 = container.Resolve<Interface>();

            Assert.AreEqual(object1, object2);
        }

        [TestMethod]
        public void TestInterfaceImplementing()
        {
            SimpleContainer container = new SimpleContainer();

            container.RegisterType<Interface, ClassInheritsAbstractClass>(false);
            var object1 = container.Resolve<Interface>();

            Assert.AreEqual(object1.GetType(), typeof(ClassInheritsAbstractClass));
        }

        [TestMethod]
        public void TestAbstractClassImplementing()
        {
            SimpleContainer container = new SimpleContainer();

            container.RegisterType<AbstractClassImplementingInterface, ClassInheritsAbstractClass>(false);
            var object1 = container.Resolve<AbstractClassImplementingInterface>();

            Assert.AreEqual(object1.GetType(), typeof(ClassInheritsAbstractClass));
        }

        [TestMethod]
        public void TestAnotherClassInheritance()
        {
            SimpleContainer container = new SimpleContainer();

            container.RegisterType<ClassInheritsAbstractClass, ClassInheritsClass>(false);
            var object1 = container.Resolve<ClassInheritsAbstractClass>();

            Assert.AreEqual(object1.GetType(), typeof(ClassInheritsClass));
        }

        [TestMethod]
        public void TestChangingRegisterType()
        {
            SimpleContainer container = new SimpleContainer();

            container.RegisterType<Interface, ClassInheritsAbstractClass>(false);
            var object1 = container.Resolve<Interface>();
            container.RegisterType<Interface, ClassInheritsClass>(false);
            var object2 = container.Resolve<Interface>();

            Assert.AreEqual(object1.GetType(), typeof(ClassInheritsAbstractClass));
            Assert.AreEqual(object2.GetType(), typeof(ClassInheritsClass));
        }

        [TestMethod]
        public void TestMultipleResolving()
        {
            SimpleContainer container = new SimpleContainer();

            container.RegisterType<Interface, AbstractClassImplementingInterface>(false);
            container.RegisterType<AbstractClassImplementingInterface, ClassInheritsAbstractClass>(false);
            container.RegisterType<ClassInheritsAbstractClass, ClassInheritsClass>(false);
            var object1 = container.Resolve<Interface>();

            Assert.AreEqual(object1.GetType(), typeof(ClassInheritsClass));
        }

        [TestMethod]
        public void TestMultipleResolvingNoEmptyConstructorThrowError()
        {
            SimpleContainer container = new SimpleContainer();

            Assert.ThrowsException<MissingMethodException>(() =>
            {
                container.RegisterType<Interface, AbstractClassImplementingInterface>(false);
                container.RegisterType<AbstractClassImplementingInterface, ClassInheritsAbstractClass>(false);
                container.RegisterType<ClassInheritsAbstractClass,
                    ClassNoEmptyConstructorInheritsAbstractClass>(false);
                var object1 = container.Resolve<Interface>();
            });
        }

        [TestMethod]
        public void TestMultipleResolvingOneSingleton()
        {
            SimpleContainer container = new SimpleContainer();

            container.RegisterType<Interface, AbstractClassImplementingInterface>(false);
            container.RegisterType<AbstractClassImplementingInterface, ClassInheritsAbstractClass>(true);
            container.RegisterType<ClassInheritsAbstractClass, ClassInheritsClass>(false);
            var object1 = container.Resolve<Interface>();
            var object2 = container.Resolve<Interface>();

            Assert.AreEqual(object1, object2);
        }

        [TestMethod]
        public void TestMultipleResolvingAllSingletons()
        {
            SimpleContainer container = new SimpleContainer();

            container.RegisterType<Interface, AbstractClassImplementingInterface>(true);
            container.RegisterType<AbstractClassImplementingInterface, ClassInheritsAbstractClass>(true);
            container.RegisterType<ClassInheritsAbstractClass, ClassInheritsClass>(true);
            var object1 = container.Resolve<Interface>();
            var object2 = container.Resolve<Interface>();

            Assert.AreEqual(object1, object2);
        }

        [TestMethod]
        public void TestRevertSingleton()
        {
            SimpleContainer container = new SimpleContainer();

            container.RegisterType<Interface, ClassInheritsAbstractClass>(true);
            container.RegisterType<ClassInheritsClass>(true);
            var object1 = container.Resolve<Interface>();
            var object2 = container.Resolve<ClassInheritsClass>();
            container.RegisterType<Interface, ClassInheritsAbstractClass>(false);
            container.RegisterType<ClassInheritsClass>(false);
            var object3 = container.Resolve<Interface>();
            var object4 = container.Resolve<ClassInheritsClass>();

            Assert.AreNotEqual(object1, object3);
            Assert.AreNotEqual(object2, object4);
        }
    }

    public interface Interface
    {
        public void foo();
    }

    public abstract class AbstractClassNoConstrucotrImplementingInterface : Interface
    {
        public abstract void foo();
    }

    public abstract class AbstractClassImplementingInterface : Interface
    {
        public AbstractClassImplementingInterface() { }
        public abstract void foo();
    }

    public class ClassInheritsAbstractClass : AbstractClassImplementingInterface
    {
        public override void foo() { }
    }

    public class ClassNoEmptyConstructorInheritsAbstractClass : ClassInheritsAbstractClass
    {
        public ClassNoEmptyConstructorInheritsAbstractClass(int nothing) { }
        public override void foo() { }
    }

    public class ClassInheritsClass : ClassInheritsAbstractClass
    {

    }
}

using System;
using Unity;

namespace UnitTestProject
{
    public class ManyAttributeConstrucors
    {
        [InjectionConstructor]
        public ManyAttributeConstrucors() { }

        [InjectionConstructor]
        public ManyAttributeConstrucors(int i) { }

        [InjectionConstructor]
        public ManyAttributeConstrucors(int i, int j) { }
    }

    public class ManyConstructorsOnlyAttributeConstrucotrDoesntThrowException
    {
        public ManyConstructorsOnlyAttributeConstrucotrDoesntThrowException() 
        {
            throw new Exception("Constructor with InjectionConstructor attribute should be used");
        }

        [InjectionConstructor]
        public ManyConstructorsOnlyAttributeConstrucotrDoesntThrowException(Interface i) { }

        public ManyConstructorsOnlyAttributeConstrucotrDoesntThrowException(Interface i, Interface j) 
        {
            throw new Exception("Constructor with InjectionConstructor attribute should be used");
        }
    }

    public class ManyConstructorsOnlyLongestConstructorDoesntThrowException
    {
        public ManyConstructorsOnlyLongestConstructorDoesntThrowException()
        {
            throw new Exception("Constructor with most parameters should be used");
        }

        public ManyConstructorsOnlyLongestConstructorDoesntThrowException(Interface i)
        {
            throw new Exception("Constructor with most parameters should be used");
        }

        public ManyConstructorsOnlyLongestConstructorDoesntThrowException(Interface i, Interface j)
        {
            throw new Exception("Constructor with most parameters should be used");
        }

        public ManyConstructorsOnlyLongestConstructorDoesntThrowException(Interface i, Interface j, Interface k) { }
    }

    public class ManySameLengthConstructors
    {
        public ManySameLengthConstructors(Interface i, Interface j) { }

        public ManySameLengthConstructors(AbstractClassImplementingInterface i, Interface j) { }
        public ManySameLengthConstructors(AbstractClassImplementingInterface i,
            AbstractClassImplementingInterface j) { }
    }

    public class ConstrucotrParametersHaveManyConstructorParameters
    {
        public ConstrucotrParametersHaveManyConstructorParameters(ManySameLengthConstructors a,
            ManyConstructorsOnlyAttributeConstrucotrDoesntThrowException b, ConstructorRequireManyDifferentParameters c) { }
    }

    public class ConstructorRequireManyDifferentParameters
    {
        public ConstructorRequireManyDifferentParameters(ClassInheritsClass a,
            ClassInheritsAbstractClass b, Interface c) { }
    }

    public class ConstructorRequireRegisteringStringAndInt
    {
        public ConstructorRequireRegisteringStringAndInt(string a, int b) { }
    }

    public class ConstructorParametersCreateResolveCycle
    {
        public ConstructorParametersCreateResolveCycle(
            ConstrucotrParametersHaveManyConstructorParameters a, RequireCycleHelper b) { }
    }

    public class RequireCycleHelper
    {
        public RequireCycleHelper(ConstructorParametersCreateResolveCycle a) { }
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

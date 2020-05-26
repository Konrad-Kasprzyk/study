using System;
using System.Collections.Generic;
using System.Reflection;

namespace l9z1
{
    public class SimpleContainer
    {
        private Dictionary<Type, Resolver> registeredTypes = new Dictionary<Type, Resolver>();

        public SimpleContainer()
        {
            Resolver.container = this;
        }

        public void RegisterType<T>(bool Singleton) where T : class
        {
            if (registeredTypes.ContainsKey(typeof(T)))
            {
                registeredTypes.Remove(typeof(T));
            }
            if (Singleton)
            {
                registeredTypes.Add(typeof(T), new SingletonResolver(typeof(T)));
            }
        }
        public void RegisterType<From, To>(bool Singleton) where To : From
        {
            if (registeredTypes.ContainsKey(typeof(From)))
            {
                registeredTypes.Remove(typeof(From));
            }
            if (Singleton)
            {
                registeredTypes.Add(typeof(From), new SingletonResolver(typeof(To)));
            }
            else
            {
                registeredTypes.Add(typeof(From), new Resolver(typeof(To)));
            }
        }
        public T Resolve<T>()
        {
            if (registeredTypes.ContainsKey(typeof(T)))
            {
                return (T)registeredTypes[typeof(T)].Create();
            }
            else
            {
                return (T) Create(typeof(T));
            }
        }

        private object Create(Type ToType)
        {
            ConstructorInfo emptyConstructor = ToType.GetConstructor(Type.EmptyTypes);
            if (emptyConstructor == null)
                throw new MissingMethodException("SimpleContainer.Resolve<T> error: No empty constructor." +
                    " Resolve generic parameter must have a constructor without arguments");
            try
            {
                return emptyConstructor.Invoke(null);
            }
            catch (MemberAccessException err)
            {
                throw new MemberAccessException("SimpleContainer.Resolve<T> error: " + err.Message);
            }
        }

        private class Resolver
        {
            public static SimpleContainer container;
            public Type ToType;
            public Resolver(Type ToType)
            {
                this.ToType = ToType;
            }
            public virtual object Create()
            {
                if (container.registeredTypes.ContainsKey(ToType))
                {
                    Resolver nextResolver = container.registeredTypes[ToType];
                    if (nextResolver != this)
                    {
                        return nextResolver.Create();
                    }
                    else
                    {
                        return container.Create(ToType);
                    }
                }
                return container.Create(ToType);
            }
        }

        private class SingletonResolver : Resolver
        {
            public SingletonResolver(Type ToType) : base(ToType) { }
            private object _instance;
            private object _lock = new object();
            public override object Create()
            {
                if (_instance == null)
                {
                    lock (_lock)
                    {
                        if (_instance == null)
                        {
                            _instance = base.Create();
                        }
                    }
                }
                return _instance;
            }
        }
    }
}

using System;
using System.Collections.Generic;
using System.Reflection;
using Unity;

namespace l10
{
    public class SimpleContainer
    {
        private Dictionary<Type, Resolver> registeredTypes = new Dictionary<Type, Resolver>();
        private List<Type> markedConstructors = new List<Type>();

        public SimpleContainer()
        {
            Resolver.container = this;
        }

        public void RegisterInstance<T>(T instance)
        {
            if (registeredTypes.ContainsKey(typeof(T)))
            {
                registeredTypes.Remove(typeof(T));
            }
            registeredTypes.Add(typeof(T), new InstanceResolver(typeof(T), instance));
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
            markedConstructors.Clear();
            if (registeredTypes.ContainsKey(typeof(T)))
            {
                return (T)registeredTypes[typeof(T)].Create();
            }
            else
            {
                return (T)Create(typeof(T));
            }
        }

        private object Create(Type ToType)
        {
            ConstructorInfo targetConstructor = null;
            var constructors = ToType.GetConstructors();
            foreach (ConstructorInfo constructor in constructors)
            {
                Attribute atrybut = constructor.GetCustomAttribute(typeof(InjectionConstructorAttribute));
                if (atrybut != null)
                {
                    if (targetConstructor != null)
                    {
                        throw new MemberAccessException("SimpleContainer.Resolve<T> error: " +
                           "Only one constructor can have InjectionConstructor attribute");
                    }                   
                    targetConstructor = constructor;
                }
            }
            if (targetConstructor == null)
            {
                int maxParameters = 0;
                foreach (var constructor in constructors)
                {
                    if (constructor.GetParameters().Length > maxParameters)
                    {
                        maxParameters = constructor.GetParameters().Length;
                        targetConstructor = constructor;
                    }
                }

            }
            if (targetConstructor != null)
            {
                var parameters = targetConstructor.GetParameters();
                object[] parametersInstances = new object[parameters.Length];
                foreach (var paramater in parameters)
                {
                    if (markedConstructors.Contains(paramater.ParameterType))
                    {
                        throw new MemberAccessException("SimpleContainer.Resolve<T> error: " +
                            $"Constructors create resolve cycle. {ToType} Created cycle.");
                    }
                }
                for (int i=0; i<parameters.Length; i++)
                {
                    Type parameterType = parameters[i].ParameterType;
                    if (!markedConstructors.Contains(parameterType))
                    {
                        markedConstructors.Add(parameterType);
                    }   
                    if (registeredTypes.ContainsKey(parameterType))
                    {
                        parametersInstances[i] = registeredTypes[parameterType].Create();
                    }
                    else
                    {
                        parametersInstances[i] = Create(parameterType);
                    }
                }
                return targetConstructor.Invoke(parametersInstances);
            }

            ConstructorInfo emptyConstructor = ToType.GetConstructor(Type.EmptyTypes);
            if (emptyConstructor == null)
                throw new MissingMethodException("SimpleContainer.Resolve<T> error: No empty constructor." +
                    " Resolve generic parameter must have a constructor without arguments or other" +
                    " valid constructor that is with attribute InjectionConstructor or have most parameters." +
                    $" {ToType} created error");
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

        private class InstanceResolver : Resolver
        {
            private object _instance;
            public InstanceResolver(Type ToType, object _instance) : base(ToType)
            {
                this._instance = _instance;
            }
            
            public override object Create()
            {
                return _instance;
            }
        }
    }
}

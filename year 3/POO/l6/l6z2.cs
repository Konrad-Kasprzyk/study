using System;
using System.Collections.Generic;

namespace Lista6
{
    class l6z2
    {
        public static void Main_z2()
        {
            Console.WriteLine("Lista 6, zadanie 2");

            Context context = new Context();
            context.SetValue("x", false);
            context.SetValue("y", true);
            AbstractExpression exp = new UnaryExpression()
            {
                Operator = "!",
                Expression = new BinaryExpression() {
                    Operator = "|",
                    Left = new ConstExpression("x"),
                    Right = new ConstExpression("y")}
            };
            bool Value = exp.Interpret(context);
            Console.WriteLine(Value);
            Console.ReadLine();
        }
    }

    public class Context
    {
        private Dictionary<string, bool> _localVariables =
            new Dictionary<string, bool>();

        public bool GetValue(string variableName)
        {
            if (_localVariables.ContainsKey(variableName))
            {
                return _localVariables[variableName];
            }
            else
            {
                throw new ArgumentException();
            }
        }

        public void SetValue(string variableName, bool value)
        {
            if (_localVariables.ContainsKey(variableName))
            {
                _localVariables.Remove(variableName);
            }
            _localVariables.Add(variableName, value);
        }
    }

    public abstract class AbstractExpression
    {
        public abstract bool Interpret(Context context);
    }
    public class ConstExpression : AbstractExpression
    {
        public string variableName;

        public ConstExpression(string variableName)
        {
            this.variableName = variableName;
        }
        public override bool Interpret(Context context)
        {
            return context.GetValue(variableName);
        }
    }
    public class BinaryExpression : AbstractExpression
    {
        public AbstractExpression Left;
        public AbstractExpression Right;

        public string Operator;

        public override bool Interpret(Context context)
        {
            switch (Operator)
            {
                case "|":
                    return
                    this.Left.Interpret(context) |
                    this.Right.Interpret(context);
                case "&":
                    return
                    this.Left.Interpret(context) &
                    this.Right.Interpret(context);
                default:
                    throw new ArgumentException();
            }
        }

    }
    public class UnaryExpression : AbstractExpression
    {
        public AbstractExpression Expression;

        public string Operator;

        public override bool Interpret(Context context)
        {
            switch (Operator)
            {
                case "!":
                    return !Expression.Interpret(context);
                default:
                    throw new ArgumentException();
            }
        }
    }
}

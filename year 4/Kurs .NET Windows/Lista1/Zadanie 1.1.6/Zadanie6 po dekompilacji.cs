// Zadanie_1._1._6.Calculate
using Zadanie_1._1._6;

internal static class Calculate
{
	public static event Operator Operators;

	public static void PerformCalculations(int x, int y)
	{
		Calculate.Operators?.Invoke(x, y);
	}
}

// Zadanie_1._1._6.Maths
using System;

public class Maths
{
	public static void StaticPrintSum(int x, int y)
	{
		Console.WriteLine(x + y);
	}

	public void PrintDiff(int x, int y)
	{
		Console.WriteLine(x - y);
	}
}

// Zadanie_1._1._6.Numbers
using System.Linq;

public class Numbers
{
	private readonly int[] _numbers;

	public int publicNumber = 42;

	public int this[int i]
	{
		get
		{
			return _numbers[i];
		}
		set
		{
			_numbers[i] = value;
		}
	}

	public int NumberOfElements => _numbers.Length;

	public Numbers(int publicNumber)
	{
		this.publicNumber = publicNumber;
	}

	public Numbers(params int[] input)
	{
		_numbers = new int[input.Length];
		for (int i = 0; i < input.Length; i++)
		{
			_numbers[i] = input[i];
		}
	}

	public int Sum()
	{
		return _numbers.Sum();
	}
}

// Zadanie_1._1._6.Operator
public delegate void Operator(int x, int y);

// Zadanie_1._1._6.Zadanie6
using System;
using Zadanie_1._1._6;

internal static class Zadanie6
{
	public static void Main(string[] args)
	{
		Numbers numbers = new Numbers(13);
		Console.WriteLine($"public number {numbers.publicNumber}");
		numbers = new Numbers(1, 2, 3, 4, 5, 6);
		Console.WriteLine(numbers.publicNumber);
		numbers.publicNumber = 99;
		numbers[2] = numbers.publicNumber;
		Console.WriteLine(numbers[2]);
		Console.WriteLine("Sum of elements equals " + numbers.Sum());
		Console.WriteLine(numbers.NumberOfElements);
		Maths @object = new Maths();
		Calculate.Operators += Maths.StaticPrintSum;
		Calculate.Operators += @object.PrintDiff;
		Calculate.PerformCalculations(4, 2);
		for (int i = 0; i < 3; i++)
		{
			Console.WriteLine(i);
		}
		for (int num = 3; num >= 0; num--)
		{
			Console.WriteLine(num);
		}
		bool flag = true;
		Console.WriteLine(value: true);
		switch (1)
		{
		case 1:
			Console.WriteLine("Case 1");
			break;
		case 2:
			Console.WriteLine("Case 2");
			break;
		case 3:
			Console.WriteLine("Case 3");
			break;
		default:
			Console.WriteLine("Case default");
			break;
		}
		Console.ReadKey();
	}
}

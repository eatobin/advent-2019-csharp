namespace App;

public class Intcode(int pointer, int[] memory)
{
    public int Pointer { get; set; } = pointer;
    public int[] Memory { get; } = memory;
}

internal static class Program
{
    public static void Main()
    {
        var ic = new Intcode(1, [11]);
        Console.WriteLine($"{ic.Pointer}");
        Console.WriteLine($"{ic.Memory[0]}");

        ic.Pointer = 2;
        ic.Memory[0] = 222;

        Console.WriteLine($"{ic.Pointer}");
        Console.WriteLine($"{ic.Memory[0]}");

        // // Create  struct instance and initialize by using "new".
        // // Memory is allocated on thread stack.
        // var p1 = new Person("Alex", 9);
        // Console.WriteLine($"p1 Name = {p1.Name} Age = {p1.Age}");
        //
        // // Create  new struct object. Note that struct can be initialized
        // // without using "new".
        // var p2 = p1;
        //
        // // Assign values to p2 members.
        // p2.Name = "Spencer";
        // p2.Age = 7;
        // Console.WriteLine($"p2 Name = {p2.Name} Age = {p2.Age}");
        //
        // // p1 values remain unchanged because p2 is  copy.
        // Console.WriteLine($"p1 Name = {p1.Name} Age = {p1.Age}");
        //
        // var p9 = new Person("Me", 99);
        // Console.WriteLine($"p9 Name = {p9.Name} Age = {p9.Age}");
        // p9.Speak();
    }
}

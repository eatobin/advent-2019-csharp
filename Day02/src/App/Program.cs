namespace App;

public class Intcode
{
    public int Pointer;
    public readonly int[] Memory = [1, 0, 0, 3, 99];

    public int Add(int y)
    {
        return Pointer + y;
    }

    public int opcode()
    {
        var action = Memory[Pointer];
        var address1 = Memory[Pointer + 1];
        var address2 = Memory[Pointer + 2];
        var address3 = Memory[Pointer + 3];

        switch (action)
        {
            case 1:
                Memory[address3] = Memory[address1] + Memory[address2];
                Pointer += 4;
                return 1;
            case 2:
                Memory[address3] = Memory[address1] * Memory[address2];
                Pointer += 4;
                return 1;
            default:
                return 0;
        }
    }
}

internal static class Program
{
    public static void Main()
    {
        var ic = new Intcode();

        Console.WriteLine($"{ic.Pointer}");
        Console.WriteLine($"{ic.Memory[0]}");

        ic.Pointer = 1;
        ic.Memory[0] = 999;

        Console.WriteLine($"{ic.Pointer}");
        Console.WriteLine($"{ic.Memory[0]}");

        ic.Memory[4] = 888;
        Console.WriteLine($"{ic.Memory[3]}");
        Console.WriteLine($"{ic.Memory[4]}");

        var xx = ic.Add(33);
        Console.WriteLine($"{xx}");

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

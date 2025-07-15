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

    public void updatedMemory(int noun, int verb)
    {
        Memory[1] = noun;
        Memory[2] = verb;
    }
}

internal static class Program
{
    public static void Main()
    {
        var ic = new Intcode();


    }
}

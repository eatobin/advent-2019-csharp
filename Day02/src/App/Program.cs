namespace App;

public class Intcode
{
    public int Pointer;

    public readonly int[] Memory =
    [
        1, 0, 0, 3, 1, 1, 2, 3, 1, 3, 4, 3, 1, 5, 0, 3, 2, 10, 1, 19, 2, 9, 19, 23, 2, 13, 23,
        27, 1, 6, 27, 31, 2, 6, 31, 35, 2, 13, 35, 39, 1, 39, 10, 43, 2, 43, 13, 47, 1, 9, 47,
        51, 1, 51, 13, 55, 1, 55, 13, 59, 2, 59, 13, 63, 1, 63, 6, 67, 2, 6, 67, 71, 1, 5, 71,
        75, 2, 6, 75, 79, 1, 5, 79, 83, 2, 83, 6, 87, 1, 5, 87, 91, 1, 6, 91, 95, 2, 95, 6, 99,
        1, 5, 99, 103, 1, 6, 103, 107, 1, 107, 2, 111, 1, 111, 5, 0, 99, 2, 14, 0, 0
    ];
}

public static class Opcode
{
    public static int OpcodeRun(Intcode intcode)
    {
        var action = intcode.Memory[intcode.Pointer];
        var address1 = intcode.Memory[intcode.Pointer + 1];
        var address2 = intcode.Memory[intcode.Pointer + 2];
        var address3 = intcode.Memory[intcode.Pointer + 3];

        switch (action)
        {
            case 1:
                intcode.Memory[address3] = intcode.Memory[address1] + intcode.Memory[address2];
                intcode.Pointer += 4;
                return 1;
            case 2:
                intcode.Memory[address3] = intcode.Memory[address1] * intcode.Memory[address2];
                intcode.Pointer += 4;
                return 1;
            default:
                return 0;
        }
    }

    public static void UpdatedMemory(Intcode intcode, int noun, int verb)
    {
        intcode.Memory[1] = noun;
        intcode.Memory[2] = verb;
    }

    public static int NounVerb()
    {
        for (var noun = 0; noun < 100; noun++)
        {
            for (var verb = 0; verb < 100; verb++)
            {
                var intcode = new Intcode();
                UpdatedMemory(intcode, noun, verb);

                var icReturn = 1;
                while (icReturn == 1)
                {
                    icReturn = OpcodeRun(intcode);
                }

                var candidate = intcode.Memory[0];

                if (candidate == 19690720)
                {
                    return 100 * noun + verb;
                }
            }
        }

        return -1;
    }
}

internal static class Program
{
    public static void Main()
    {
        var intcode = new Intcode();
        var icReturn = 1;

        Opcode.UpdatedMemory(intcode, 12, 2);

        while (icReturn == 1)
        {
            icReturn = Opcode.OpcodeRun(intcode);
        }

        Console.WriteLine($"\nPart A answer: {intcode.Memory[0]}, correct: 2890696");
        Console.WriteLine($"Part B answer: {Opcode.NounVerb()}, correct: 8226\n");
    }
}

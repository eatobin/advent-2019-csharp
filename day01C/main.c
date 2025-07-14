#include <stdio.h>

int fuelValue(int mass);
int recFuelValue(int mass);

const int INPUT[100] = {68958, 82218, 54333, 59177, 51874, 100259, 95468, 124006, 75078, 113631, 90315, 147580, 68233, 81025, 133084, 90959, 81196, 92443, 124832, 65871, 57704, 140203, 113053, 76337, 72195, 115917, 87843, 131768, 105816, 131153, 59714, 94107, 50933, 139545, 94969, 149463, 60042, 66028, 111190, 63257, 50020, 88783, 81428, 73977, 149240, 137152, 74738, 55067, 128829, 56465, 81962, 67242, 94121, 92303, 68477, 88595, 64324, 82527, 134717, 140344, 132026, 137558, 95643, 79010, 146346, 86246, 52341, 147564, 89159, 66456, 83190, 128675, 130658, 122857, 134538, 122151, 133900, 117462, 117791, 139254, 86366, 66165, 92897, 121218, 135962, 143061, 129220, 114623, 98257, 76722, 121014, 77713, 137858, 133282, 103595, 118981, 149137, 101141, 70765, 141113};

int main(void) {
    int mass;
    int tot_fuel = 0;
    int tot_fuel_rec = 0;

    for (int i = 0; i < 100; ++i) {
        mass = INPUT[i];
        tot_fuel += fuelValue(mass);
    }

    printf("\nPart a: %i\n", tot_fuel);// 3337766

    for (int i = 0; i < 100; ++i) {
        mass = INPUT[i];
        tot_fuel_rec += recFuelValue(mass);
    }

    printf("Part b: %i\n\n", tot_fuel_rec);// 5003788

    return 0;
}

int fuelValue(int mass) {
    return (mass / 3) - 2;
}

int recFuelValue(int mass) {
    int sum = 0;
    int fuel = fuelValue(mass);

    while (fuel > 0) {
        sum += fuel;
        fuel = fuelValue(fuel);
    }

    return sum;
}

#include "simulator.h"
#include "argument_parser.h"

#include <string>
#include <iostream>

std::string getUsageMessage() {
    return {
        "\n"
        "Usage:\n"
        "    elevator filename [milliseconds]\n"
        "\n"
        "filename:\n"
        "    The input file containing simulation parameters and inputs.\n"
        "\n"
        "    The first line contains: number of elevators, number of floors, weight capacity.\n"
        "    The second line contains: number of passengers.\n"
        "    The following x lines, where x is the number of passengers, contains: passenger id, passenger weight.\n"
        "    The remaining lines contain: time, passenger id, starting floor, ending floor.\n"
        "\n"
        "    Example:\n"
        "        1 30 500\n"
        "        2\n"
        "        0 64\n"
        "        1 75\n"
        "        0 0 0 10\n"
        "        6 1 0 8\n"
        "\n"
        "    This will simulate 1 elevator with 30 floors and a weight capacity of 500kg.\n"
        "    There are 2 passengers:\n"
        "        Passenger 0 weighs 64kg.\n"
        "        Passenger 1 weighs 75kg.\n"
        "    At time 0, passenger 0 will request an elevator from the 0th floor for the 10th floor.\n"
        "    At time 6, passenger 1 will request an elevator from the 0th floor for the 8th floor.\n"
        "\n"
        "milliseconds:\n"
        "    Optional. Adds a delay in milliseconds to each step of the simulation."
        "\n"
    };
}

int main(int argc, char **argv) {
    try {
        ArgumentParser argParser { argc, argv, getUsageMessage() };
        const auto filename { argParser.get<std::string>() };
        const auto millisecondsDelay { argParser.getOptional<int>(0) };

        Simulator simulator { millisecondsDelay };
        simulator.initializeFromFile(filename);
        simulator.run();
    } catch (const std::runtime_error& exception) {
        std::cout << exception.what() << std::endl;
    }
}
#pragma once
#include <vector>
#include <iostream>

namespace AOC::IntcodeComputer {

int Run(std::vector<int> memory, int input1, int input2)
{
	memory[1] = input1;
	memory[2] = input2;

	int offset = 0;
	while (memory[offset] != 99) {
		int opcode = memory[offset];
		int arg0_offset = memory[offset + 1];
		int arg1_offset = memory[offset + 2];
		int write_offset = memory[offset + 3];

		if (opcode == 1)
			memory[write_offset] = memory[arg0_offset] +
			                       memory[arg1_offset];

		else if (opcode == 2)
			memory[write_offset] = memory[arg0_offset] *
			                       memory[arg1_offset];

		offset += 4;
	}

	return memory[0];
}

}

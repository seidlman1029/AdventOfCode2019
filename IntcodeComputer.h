#pragma once
#include <vector>
#include <queue>
#include <iostream>
#include <thread>

namespace AOC::IntcodeComputer {

constexpr int position_mode = 0;
constexpr int immediate_mode = 1;

inline int GetMinOpCode(int full_op_code)
{
	return full_op_code % 100;
}

inline int GetParamValue(const std::vector<int>& memory,
                         int full_op_code,
                         int param_number,
                         int raw_param_value)
{
	switch (GetDigitAtPos(full_op_code, 2 + param_number)) {
	case position_mode:
		return memory[raw_param_value];
	case immediate_mode:
		return raw_param_value;
	default:
		throw std::exception("aaa");
	}
}

inline void Op1(std::vector<int>& memory,
                int& offset)
{
	int full_op_code = memory[offset++];
	int param0 = GetParamValue(memory, full_op_code, 0, memory[offset++]);
	int param1 = GetParamValue(memory, full_op_code, 1, memory[offset++]);
	int param2 = memory[offset++];

	memory[param2] = param0 + param1;
}

inline void Op2(std::vector<int>& memory,
                int& offset)
{
	int full_op_code = memory[offset++];
	int param0 = GetParamValue(memory, full_op_code, 0, memory[offset++]);
	int param1 = GetParamValue(memory, full_op_code, 1, memory[offset++]);
	int param2 = memory[offset++];

	memory[param2] = param0 * param1;
}

inline void Op3(std::vector<int>& memory,
                int& offset,
                std::queue<int>& inputs)
{
	int full_op_code = memory[offset++];
	int param0 = memory[offset++];

	memory[param0] = inputs.front();
	inputs.pop();
}

inline void Op4(std::vector<int>& memory,
                int& offset,
                std::queue<int>& outputs)
{
	int full_op_code = memory[offset++];

	outputs.emplace(GetParamValue(memory, full_op_code, 0, memory[offset++]));
}

inline void Op5(std::vector<int>& memory,
                int& offset)
{
	int full_op_code = memory[offset++];
	int param0 = GetParamValue(memory, full_op_code, 0, memory[offset++]);
	int param1 = GetParamValue(memory, full_op_code, 1, memory[offset++]);

	if (param0 != 0)
		offset = param1;
}

inline void Op6(std::vector<int>& memory,
                int& offset)
{
	int full_op_code = memory[offset++];
	int param0 = GetParamValue(memory, full_op_code, 0, memory[offset++]);
	int param1 = GetParamValue(memory, full_op_code, 1, memory[offset++]);

	if (param0 == 0)
		offset = param1;
}

inline void Op7(std::vector<int>& memory,
                int& offset)
{
	int full_op_code = memory[offset++];
	int param0 = GetParamValue(memory, full_op_code, 0, memory[offset++]);
	int param1 = GetParamValue(memory, full_op_code, 1, memory[offset++]);
	int param2 = memory[offset++];

	memory[param2] = param0 < param1 ? 1 : 0;
}

inline void Op8(std::vector<int>& memory,
                int& offset)
{
	int full_op_code = memory[offset++];
	int param0 = GetParamValue(memory, full_op_code, 0, memory[offset++]);
	int param1 = GetParamValue(memory, full_op_code, 1, memory[offset++]);
	int param2 = memory[offset++];

	memory[param2] = param0 == param1 ? 1 : 0;
}

inline int Run(std::vector<int> memory, std::queue<int>& inputs, std::queue<int>& outputs)
{
	int offset = 0;
	while (memory[offset] != 99) {
		switch (GetMinOpCode(memory[offset])) {
		case 1:
			Op1(memory, offset);
			break;
		case 2:
			Op2(memory, offset);
			break;
		case 3:
			Op3(memory, offset, inputs);
			break;
		case 4:
			Op4(memory, offset, outputs);
			break;
		case 5:
			Op5(memory, offset);
			break;
		case 6:
			Op6(memory, offset);
			break;
		case 7:
			Op7(memory, offset);
			break;
		case 8:
			Op8(memory, offset);
			break;
		default:
			throw std::exception("Oh god the cpu is on fire");
		}
	}

	return memory[0];
}

}

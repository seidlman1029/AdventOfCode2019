#pragma once
#include <vector>
#include <queue>
#include <iostream>
#include <thread>
#include <cstdint>

namespace AOC {

class IntcodeComputer {
private:
	constexpr static int position_mode = 0;
	constexpr static int immediate_mode = 1;
	constexpr static int relative_mode = 2;

	std::vector<int64_t> memory_;
	int64_t offset_;
	int64_t relative_base_;
	std::shared_ptr<std::queue<int64_t>> inputs_;
	std::shared_ptr<std::queue<int64_t>> outputs_;
	bool terminated_;

public:
	IntcodeComputer(std::vector<int64_t> memory,
	                std::shared_ptr<std::queue<int64_t>> inputs,
	                std::shared_ptr<std::queue<int64_t>> outputs)
	  : memory_{std::move(memory)},
	    offset_{0},
	    relative_base_{0},
	    inputs_{std::move(inputs)},
	    outputs_{std::move(outputs)},
	    terminated_{false}
	{}

	bool IsTerminated();

	int64_t GetMinOpCode(int64_t full_op_code);

	int64_t GetInputParamValue(int64_t full_op_code,
	                  int64_t param_number,
	                  int64_t raw_param_value);

	int64_t GetOutputParamPosition(int64_t full_op_code,
	                         int64_t param_number,
	                         int64_t raw_param_value);

	void Op1();

	void Op2();

	bool Op3();

	void Op4();

	void Op5();

	void Op6();

	void Op7();

	void Op8();

	void Op9();

	void Run();
};


inline bool IntcodeComputer::IsTerminated() {
	return terminated_;
}

inline int64_t IntcodeComputer::GetMinOpCode(int64_t full_op_code)
{
	return full_op_code % 100;
}

inline int64_t IntcodeComputer::GetInputParamValue(int64_t full_op_code,
                                              int64_t param_number,
                                              int64_t raw_param_value)
{
	switch (GetDigitAtPos(full_op_code, 2 + param_number)) {
	case position_mode:
		return memory_[raw_param_value];
	case relative_mode:
		return memory_[relative_base_ + raw_param_value];
	case immediate_mode:
		return raw_param_value;
	default:
		throw std::exception("aaa");
	}
}

inline int64_t IntcodeComputer::GetOutputParamPosition(int64_t full_op_code,
                                                 int64_t param_number,
                                                 int64_t raw_param_value)
{
	switch (GetDigitAtPos(full_op_code, 2 + param_number)) {
	case position_mode:
		return raw_param_value;
	case relative_mode:
		return relative_base_ + raw_param_value;
	case immediate_mode: // shouldnt happen
	default:
		throw std::exception("aaa");
	}
}

inline void IntcodeComputer::Op1()
{
	int64_t full_op_code = memory_[offset_++];
	int64_t param0 = GetInputParamValue(full_op_code, 0, memory_[offset_++]);
	int64_t param1 = GetInputParamValue(full_op_code, 1, memory_[offset_++]);
	int64_t param2 = GetOutputParamPosition(full_op_code, 2, memory_[offset_++]);

	memory_[param2] = param0 + param1;
}

inline void IntcodeComputer::Op2()
{
	int64_t full_op_code = memory_[offset_++];
	int64_t param0 = GetInputParamValue(full_op_code, 0, memory_[offset_++]);
	int64_t param1 = GetInputParamValue(full_op_code, 1, memory_[offset_++]);
	int64_t param2 = GetOutputParamPosition(full_op_code, 2, memory_[offset_++]);

	memory_[param2] = param0 * param1;
}

inline bool IntcodeComputer::Op3()
{
	if (inputs_->empty())
		return false;

	int64_t full_op_code = memory_[offset_++];
	int64_t param0 = GetOutputParamPosition(full_op_code, 0, memory_[offset_++]);

	memory_[param0] = inputs_->front();
	inputs_->pop();
	return true;
}

inline void IntcodeComputer::Op4()
{
	int64_t full_op_code = memory_[offset_++];

	outputs_->emplace(GetInputParamValue(full_op_code, 0, memory_[offset_++]));
}

inline void IntcodeComputer::Op5()
{
	int64_t full_op_code = memory_[offset_++];
	int64_t param0 = GetInputParamValue(full_op_code, 0, memory_[offset_++]);
	int64_t param1 = GetInputParamValue(full_op_code, 1, memory_[offset_++]);

	if (param0 != 0)
		offset_ = param1;
}

inline void IntcodeComputer::Op6()
{
	int64_t full_op_code = memory_[offset_++];
	int64_t param0 = GetInputParamValue(full_op_code, 0, memory_[offset_++]);
	int64_t param1 = GetInputParamValue(full_op_code, 1, memory_[offset_++]);

	if (param0 == 0)
		offset_ = param1;
}

inline void IntcodeComputer::Op7()
{
	int64_t full_op_code = memory_[offset_++];
	int64_t param0 = GetInputParamValue(full_op_code, 0, memory_[offset_++]);
	int64_t param1 = GetInputParamValue(full_op_code, 1, memory_[offset_++]);
	int64_t param2 = GetOutputParamPosition(full_op_code, 2, memory_[offset_++]);

	memory_[param2] = param0 < param1 ? 1 : 0;
}

inline void IntcodeComputer::Op8()
{
	int64_t full_op_code = memory_[offset_++];
	int64_t param0 = GetInputParamValue(full_op_code, 0, memory_[offset_++]);
	int64_t param1 = GetInputParamValue(full_op_code, 1, memory_[offset_++]);
	int64_t param2 = GetOutputParamPosition(full_op_code, 2, memory_[offset_++]);

	memory_[param2] = param0 == param1 ? 1 : 0;
}

inline void IntcodeComputer::Op9()
{
	int64_t full_op_code = memory_[offset_++];
	int64_t param0 = GetInputParamValue(full_op_code, 0, memory_[offset_++]);

	relative_base_ += param0;
}

inline void IntcodeComputer::Run()
{
	if (terminated_)
		return;

	while (memory_[offset_] != 99) {
		switch (GetMinOpCode(memory_[offset_])) {
		case 1:
			Op1();
			break;
		case 2:
			Op2();
			break;
		case 3:
			if (!Op3()) // waiting on input, must manually restart
				return;
			break;
		case 4:
			Op4();
			break;
		case 5:
			Op5();
			break;
		case 6:
			Op6();
			break;
		case 7:
			Op7();
			break;
		case 8:
			Op8();
			break;
		case 9:
			Op9();
			break;
		default:
			throw std::exception("Oh god the cpu is on fire");
		}
	}

	terminated_ = true;
}

}

#pragma once

#include "parallel_group/details.hpp"

namespace cango::parallel_group {
	/// @brief group 提示词，开始组合任务，使用 + 连接任务
	inline constexpr details::group_mark group;

	/// @brief parallel 提示词，并行执行任务组，使用 << 连接任务组
	inline constexpr details::parallel_mark parallel;
}
#pragma once

#include <thread>
#include <list>

namespace cango::parallel_group::details {
	/// @brief 线程列表
	using thread_list = std::list<std::thread>;

	/// @brief 组合后的任务，内部含有两个指向任务的引用
	template<typename old_task_type, typename new_task_type>
	class task_pair {
		using this_task_type = task_pair;

	public:
		old_task_type& old_task;
		new_task_type& new_task;

		/// @brief 组合任务
		template<typename target_task_type>
		task_pair<this_task_type, target_task_type> operator +(target_task_type& target_task) {
			return { *this, target_task };
		}

		/// @brief 将任务添加到线程列表
		void emplace_back_at(thread_list& threads) const {
			old_task.emplace_back_at(threads);
			threads.emplace_back(new_task);
		}
	};

	/// @brief 组合后的任务，内部含有一个指向任务的引用，为任务组的第一个任务
	template<typename new_task_type>
	class task_pair<void, new_task_type>
	{
		using this_task_type = task_pair;

	public:
		new_task_type& new_task;

		/// @brief 组合任务
		template<typename target_task_type>
		task_pair<this_task_type, target_task_type> operator +(target_task_type& target_task) {
			return { *this, target_task };
		}

		/// @brief 将任务添加到线程列表
		void emplace_back_at(thread_list& threads) const {
			threads.emplace_back(new_task);
		}
	};

	/// @brief 用于标记任务组的提示词，提供连接任务的 + 操作符
	struct group_mark {
		template<typename target_task_type>
		task_pair<void, target_task_type> operator +(target_task_type& target) const {
			return { target };
		}
	};

	/// @brief 用于并行执行任务组的提示词，提供执行任务组的 << 操作符
	struct parallel_mark {
		template<typename old_task_type, typename new_task_type>
		void operator<<(const task_pair<old_task_type, new_task_type>& tasks) const {
			thread_list threads;
			tasks.emplace_back_at(threads);
			for (auto& thread : threads)
				thread.join();
		}
	};
}

#include <iostream>
#include <sstream>

#include <cango/parallel_group.hpp>

namespace {
	auto generate_task(const int value) {
		return [value] {
			std::ostringstream stream{};
			stream << "Task" << value << "\n";
			std::cout << stream.str();
		};
	}
}

int main() {
	auto task1 = generate_task(1);
	auto task2 = generate_task(2);
	auto task3 = generate_task(3);

	using namespace cango::parallel_group;
	parallel << group + task1 + task2 + task3;

	return 0;
}
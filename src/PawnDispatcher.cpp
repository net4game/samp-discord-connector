#include "PawnDispatcher.hpp"

#include <chrono>
#include <vector>

void PawnDispatcher::Configure(unsigned int max_time_ms, unsigned int max_tasks)
{
	m_MaxTimeMs.store(max_time_ms, std::memory_order_relaxed);
	m_MaxTasks.store(max_tasks, std::memory_order_relaxed);
}

void PawnDispatcher::Dispatch(Function_t &&func)
{
	std::lock_guard<std::mutex> lock_guard(m_QueueMtx);
	m_Queue.push(std::move(func));
}

void PawnDispatcher::Process()
{
	using clock = std::chrono::steady_clock;

	unsigned int const max_time_ms = m_MaxTimeMs.load(std::memory_order_relaxed);
	unsigned int const max_tasks = m_MaxTasks.load(std::memory_order_relaxed);
	bool const unlimited = (max_time_ms == 0 && max_tasks == 0);

	auto const deadline = unlimited
		? clock::time_point::max()
		: (clock::now() + std::chrono::milliseconds(max_time_ms));

	size_t processed = 0;
	std::vector<Function_t> batch;
	batch.reserve(64);

	while (unlimited || (processed < max_tasks && clock::now() < deadline))
	{
		batch.clear();
		{
			std::lock_guard<std::mutex> lock_guard(m_QueueMtx);
			for (size_t i = 0; i < 64 && !m_Queue.empty(); ++i)
			{
				batch.push_back(std::move(m_Queue.front()));
				m_Queue.pop();
			}
		}

		if (batch.empty())
			return;

		for (auto &fn : batch)
		{
			fn();
			++processed;

			if (!unlimited)
			{
				if (processed >= max_tasks)
					return;
				if (clock::now() >= deadline)
					return;
			}
		}
	}
}
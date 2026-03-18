#pragma once

#include "Singleton.hpp"

#include <queue>
#include <mutex>
#include <functional>
#include <atomic>

#include "types.hpp"


class PawnDispatcher : public Singleton<PawnDispatcher>
{
	friend class Singleton<PawnDispatcher>;
public: //type definitions
	using Function_t = std::function<void()>;

private: //constructor / destructor
	PawnDispatcher() = default;
	~PawnDispatcher() = default;

private: //variables
	std::queue<Function_t> m_Queue;
	std::mutex m_QueueMtx;
	std::atomic<unsigned int> m_MaxTimeMs{ 2 };
	std::atomic<unsigned int> m_MaxTasks{ 1000 };

public: //functions
	// Limits to avoid long stalls on the main server thread.
	// If both are 0, Process() drains the entire queue.
	void Configure(unsigned int max_time_ms, unsigned int max_tasks);
	void Dispatch(Function_t &&func);
	void Process();

};
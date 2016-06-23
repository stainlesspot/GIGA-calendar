#pragma once

#include <string>
#include <memory>

#include "DateTime.h"

//	Task is an activity which should be finished before a deadline.
//	For example homework is a kind of task.
//	There could also be repetitive tasks, which repeat after given time.
//	For example paying your bills is a kind of task which reapeats every month.
class Task {
private:
	DateTime deadline;
	std::string name;
	std::unique_ptr<std::string> description;
	uint8_t completionPerCent;
	
public:
	Task();
	Task(const std::string& name, const std::string& description, const DateTime& deadline);

	Task(const Task&) = default;
	Task(Task&&) = default;
	~Task() = default;

	Task& setDeadldine(const DateTime&);
	Task& setCompletion(const uint8_t);

	DateTime getDeadline() const;
	DateTime getName() const;
	uint8_t getCompletion() const;

	
};
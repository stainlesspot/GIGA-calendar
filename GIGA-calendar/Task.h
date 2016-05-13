#pragma once
#include "Activity.h"

//	Task is an activity which should be finished before a deadline.
//	For example homework is a kind of task.
//	There could also be repetitive tasks, which repeat after given time.
//	For example paying your bills is a kind of task which reapeats every month.
class Task : public Activity {
private:
	Timestamp deadline;	//		the date at which the task should be done,
						//		cannot be set in the past or present,
						//		default = tomorrow;
	unsigned char completion;//	represents how much of the work is done, measured in precents,
						//		ranges from 0 to 100, default = 0;
	
public:
	Task();
	Task(const std::string& description, const Timestamp& deadline);
	Task(const Task&);
	~Task();

	Task& setDeadldine(const Timestamp&);
	Task& setCompletion(const unsigned char);

	Timestamp getDeadline() const;
	unsigned char getCompletion() const;

	Date getAsociatedDate() const;
	unsigned char getStatus() const;// returns:
	//	0 = {to be done: completion != 100, deadline in the future or present};
	//	1 = {overdue: completion != 100, deadline in the past};
	//	2 = {done: completion == 100}

};
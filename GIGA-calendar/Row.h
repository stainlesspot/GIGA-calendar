#pragma once
#include "Cell.h"
#include <array>

//	A row represents a week in the calendar and thus is made up of seven cells,
//	each with ascending dates. The row is used in scrolling the calendar,
//	in order to move the cells together. The row with the currently selected
//	cell is also highlighted
class Row {
private:
	std::array<Cell, 7> s;
	
public:
	Row();
	Row(const std::array<Cell, 7>& );
	Row(const Row&);
	Row(Row&&);
	~Row();

	Row& setHeight(const float);
	Row& move(const float height);

};
#include "set.hpp"

set::set(searchable_bag& bag) : _bag(bag) {}
set::~set() {}

searchable_bag& set::get_bag()
{
	return _bag;
}

void set::insert(int item)
{
	if (!has(item))
		_bag.insert(item);
}

void set::insert (int *items, int count)
{
	for (int i = 0; i < count; i++)
		insert(items[i]);
}

void set::print() const
{
	_bag.print();
}

void set::clear()
{
	_bag.clear();
}

bool set::has(int value) const
{
	return _bag.has(value);
}


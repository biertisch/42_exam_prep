#pragma once

#include "bag.hpp"
#include "searchable_bag.hpp"
#include "array_bag.hpp"
#include "tree_bag.hpp"
#include "searchable_array_bag.hpp"
#include "searchable_tree_bag.hpp"

class set
{
	private:
		searchable_bag& _bag;

	public:
		set() = delete;
		set(const set& other) = delete;
		set(searchable_bag& bag);
		~set();

		set& operator=(const set& other) = delete;

		searchable_bag& get_bag();

		void insert(int item);
		void insert (int *items, int count);
		void print() const;
		void clear();
		bool has(int value) const;
};
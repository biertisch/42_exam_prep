#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag() : tree_bag() {}

searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag& other) : tree_bag(other) {}

searchable_tree_bag::~searchable_tree_bag() {}

searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag& other)
{
	if (this != &other)
		tree_bag::operator=(other);
	return *this;
}

bool searchable_tree_bag::search(node *node, int value) const
{
	if (!node)
		return false;
	if (node->value == value)
		return true;
	return (search(node->l, value) || search(node->r, value));
}

bool searchable_tree_bag::has(int value) const
{
	return search(tree, value);
}
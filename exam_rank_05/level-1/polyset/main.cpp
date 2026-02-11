#include "searchable_bag.hpp"
#include "searchable_tree_bag.hpp"
#include "searchable_array_bag.hpp"
#include "set.hpp"

#include <iostream>
#include <cstdlib>

int main(int argc, char **argv)
{
	// if (argc == 1)
	// 	return 1;
	// searchable_bag *t = new searchable_tree_bag;
	// searchable_bag *a = new searchable_array_bag;

	// for (int i = 1; i < argc; i++) {
	// 	t->insert(atoi(argv[i]));
	// 	a->insert(atoi(argv[i]));
	// }
	// t->print();
	// a->print();

	// for (int i = 1; i < argc; i++)
	// {
	// 	std::cout << t->has(atoi(argv[i])) << std::endl;
	// 	std::cout << a->has(atoi(argv[i])) << std::endl;
	// 	std::cout << t->has(atoi(argv[i]) - 1) << std::endl;
	// 	std::cout << a->has(atoi(argv[i]) - 1) << std::endl;
	// }

	// t->clear();
	// a->clear();

	// const searchable_array_bag tmp(static_cast<searchable_array_bag &>(*a));
	// tmp.print();
	// tmp.has(1);

	// set sa(*a);
	// set st(*t);
	// for (int i = 1; i < argc; i++)
	// {
	// 	st.insert(atoi(argv[i]));
	// 	sa.insert(atoi(argv[i]));

	// 	sa.has(atoi(argv[i]));
	// 	sa.print();
	// 	sa.get_bag().print();
	// 	st.print();
	// 	sa.clear();

	// 	int array[] = { 1, 2, 3, 4, };
	// 	sa.insert(array, 4);
	// 	std::cout << std::endl;
	// }

	searchable_bag* t = new searchable_tree_bag;
	searchable_bag* a = new searchable_array_bag;

	t->insert(1);
	t->insert(2);
	t->insert(3);
	a->insert(1);
	a->insert(2);
	a->insert(3);

	t->print();
	a->print();

	std::cout << "\nSETS\n";
	set st(*t);
	set sa(*a);
	st.print();
	sa.print();

	std::cout << "\nAdding 4\n";
	st.insert(4);
	sa.insert(4);
	st.print();
	sa.print();

	std::cout << "\nAdding 4 again\n";
	st.insert(4);
	sa.insert(4);
	st.print();
	sa.print();

	std::cout << "\nBags themselves\n";
	st.get_bag().print();
	sa.get_bag().print();

	return (0);
}
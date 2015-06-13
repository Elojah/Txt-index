#include "Trie.hpp"
#include <iostream>

Trie::Trie(void) {
	_root.create();
}

Trie::Trie(Trie const &src) {
	if (this != &src)
		*this = src;
}

Trie::~Trie(void) {
}

Trie		&Trie::operator=(Trie const &rhs) {
	if (this != &rhs) {
		;
	}
	return (*this);
}

void	Trie::addValue(char const *s, char *filename) {
	_root.addValue(s, filename);
}

void	Trie::searchValue(std::string &s) {
	Node const	*node;

	if ((node = _root.getSNode(&(s[0]))) != NULL) {
		node->display();
	} else {
		std::cout << "No results found" << std::endl;
	}
}

#include "Node.hpp"
#include <iostream>
#include <stddef.h>

Node::Node(void) :
	_children(NULL),
	_files(NULL),
	_last(NULL) {
}

Node::Node(Node const &src) {
	if (this != &src)
		*this = src;
}

Node::~Node(void) {
	if (_files != NULL) {
		_files->remove();
		delete _files;
	}
	if (_children != NULL) {
		delete[] _children;
	}
}

Node		&Node::operator=(Node const &rhs) {
	if (this != &rhs) {
		;
	}
	return (*this);
}

/*
**Create children nodes when needed: if (children == NULL) => NOT INIT
*/
void		Node::create(void) {
	_children = new Node[MAX_CHARS_ASCII];
}

void		Node::addValue(char const *s, char *value) {
	int		n;
	sList	*tmp;

	if (!s) {
		return ;
	}
	n = static_cast<int>(*s);
	if (*s == '\0') {
		if (_last != NULL) {
			tmp = _last->addLst(value);
			if (tmp != NULL) {
				_last = tmp;
			}
		} else {
			_files = new sList;
			_files->create(value);
			_last = _files;
		}
	} else if (Node::isValidChar(n)) {
		if (_children[n]._children == NULL) {
			_children[n].create();
		}
		_children[n].addValue(s + 1, value);
	}
}

Node		*Node::getSNode(char *s) {
	int		n;

	n = static_cast<int>(*s);
	if (*s == '\0') {
		return (this);
	} else if (Node::isValidChar(n) && _children[n]._children != NULL) {
		return (_children[n].getSNode(s + 1));
	} else {
		return (NULL);
	}
}

bool		Node::isValidChar(int n) {
	/*n >= 0 && n < MAX_CHARS_ASCII is MANDATORY*/
	return (n >= 0 && n < MAX_CHARS_ASCII);
}

/*
**To improve by replacing with operator<< ?
*/
void		Node::display(void) {
	if (_files != NULL) {
		_files->display();
	} else {
		std::cout << "No results found" << std::endl;
	}
}

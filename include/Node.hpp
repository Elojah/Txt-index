#ifndef NODE_H
# define NODE_H

# define MAX_CHARS_ASCII 128
# include "List.hpp"

class Node
{
public:
	Node(void);
	~Node(void);

	void		create(void);
	void		addValue(char const *s, char *value);
	Node const	*getSNode(char *s) const;
	void		display(void) const;

protected:
private:

	Node(Node const &src);
	Node&	operator=(Node const &rhs);
	static bool	isValidChar(int n);

	Node		*_children;
	sList		*_files;
	sList		*_last;
};

#endif

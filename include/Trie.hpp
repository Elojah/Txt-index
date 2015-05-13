#ifndef TRIE_H
# define TRIE_H

# include <string>
# include "Node.hpp"

class Trie
{
public:
	Trie(void);
	~Trie(void);
	void	addValue(char const *value, char *filename);
	void	searchValue(std::string &s);
protected:
private:
	Trie(Trie const &src);
	Trie&	operator=(Trie const &rhs);

	Node			_root;
};

#endif

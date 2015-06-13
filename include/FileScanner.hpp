#ifndef FILE_SCANNER_H
# define FILE_SCANNER_H

# define NB_EXT 4
# define NB_SEP 17

# include <string>
# include "List.hpp"
# include "Trie.hpp"
class Trie;

class FileScanner
{
public:
	FileScanner(void);
	~FileScanner(void);
	FileScanner(FileScanner const &src);
	FileScanner&	operator=(FileScanner const &rhs);

	void			scan(char *path);
	void			ask(void);
protected:
private:

	bool			isScannableFile(char const *name);
	void			scanChildren(char *path);
	void			scanFile(char *filename);

	static const char			_separators[NB_SEP];
	static const char			_extension[NB_EXT][5];
	static const unsigned int	_lenExt[NB_EXT];

	Trie			_t;
	sList			_files;
	unsigned int	_countFiles;
};

#endif

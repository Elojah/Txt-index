#include "FileScanner.hpp"
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

const char			FileScanner::_separators[NB_SEP] = " \t(){}#;,.:*_/\"";
const char			FileScanner::_extension[NB_EXT][5] = {".c", ".h", ".cpp", ".hpp"};
const unsigned int	FileScanner::_lenExt[NB_EXT] = {2, 2, 4, 4};


FileScanner::FileScanner(void) :
	_countFiles(0) {
	_files.create(NULL);
}

FileScanner::FileScanner(FileScanner const &src) {
	if (this != &src)
		*this = src;
}

FileScanner::~FileScanner(void) {
	std::cout << "Destructing saved values, please wait a few seconds ..." << std::endl;
	_files.freeValues();
	_files.remove();
}

FileScanner		&FileScanner::operator=(FileScanner const &rhs) {
	if (this != &rhs) {
		;
	}
	return (*this);
}

bool			FileScanner::isScannableFile(char const *name) {
	unsigned int				len;
	bool						result;

	result = false;
	if (!name) {
		return (false);
	}
	len = strlen(name);
	for (unsigned int i = 0; i < 4; ++i) {
		bool						tmp(false);
		if (len < _lenExt[i]) {
			continue ;
		}
		for (unsigned int j = 0; j < _lenExt[i]; ++j) {
			if (name[len - _lenExt[i] + j] != _extension[i][j]) {
				tmp = true;
				break ;
			}
		}
		if (tmp) {
			continue ;
		}
		result = true;
		break ;
	}
	return (result);
}

void			FileScanner::scanChildren(char *path) {
	DIR				*dir;

	std::cout << "Directory" << std::endl;
	if (access(path, R_OK | X_OK) == -1) {
		return ;
	}
	if ((dir = opendir(path)) != NULL) {
		struct dirent	*ent;

		while ((ent = readdir(dir)) != NULL) {
			if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, "..")) {
				continue ;
			}
			scan(&((std::string(path) + '/' + ent->d_name)[0]));
		}
	}
	closedir(dir);
}

void			FileScanner::scanFile(char *filename) {
	std::string			line;
	std::ifstream		ifs;
	char				*tmp;
	static sList		*last = &_files;
	sList				*testList;

	std::cout << "Scannable File" << std::endl;
	++_countFiles;
	ifs.open(filename);
	if (ifs.fail()) {
		return ;
	}
	/*tmp is used to save filenames in _files and not duplicate them*/
	tmp = strdup(filename);
	if ((testList = last->addLst(tmp)) != NULL) {
		last = testList;
	}
	while (std::getline(ifs, line)) {
		char				*pch;

		pch = strtok(&(line[0]), _separators);
		while (pch != NULL) {
			_t.addValue(pch, tmp);
			pch = strtok (NULL, _separators);
		}
		line.clear();
	}
	ifs.close();
}

void			FileScanner::scan(char *path) {
	struct stat		pathStat;

	if (!path) {
		return ;
	}
	std::cout << "Scanning:\t" << path << " ... ";
	lstat(path, &pathStat);
	if ((pathStat.st_mode & S_IRUSR) == 0) {
		std::cout << "Read access refused" << std::endl;
		return ;
	}
	if (S_ISDIR(pathStat.st_mode)) {
		scanChildren(path);
	} else if (S_ISREG(pathStat.st_mode) && isScannableFile(path)) {
		scanFile(path);
	} else {
		std::cout << "Not scannable file or dir" << std::endl;
	}
}

/*
**Ask for search
*/
void			FileScanner::ask(void) {
	std::string	input;

	/*
	**If you're searching for qq;, you're screwed
	*/
	std::cout << "\t\033[36m" << _countFiles << "\t\033[0m" << " files found." << std::endl;
	while (true) {
		std::cout << "Search(qq; for quit):";
		std::cin >> input;
		if (std::cin.eof() == 1) {
			std::cin.clear();
			std::cin.ignore();
			continue;
		}
		if (strcmp(input.c_str(), "qq;") == 0) {
			break ;
		} else {
			_t.searchValue(input);
		}
	}
}

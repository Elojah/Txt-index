#ifndef LIST_H
# define LIST_H

# include <stdlib.h>
# include <string.h>
# include <iostream>

/*
**Basic struct list to register filenames
*/
struct			sList {
	char			*value;
	sList			*next;
	unsigned int	count;

	void		create(char *valueSet) {
		value = valueSet;
		next = NULL;
		count = 1;
	}
	sList		*addLst(char *valueSet) {
		if (value != NULL && strcmp(value, valueSet) == 0) {
			count++;
			return (NULL);
		} else if (next != NULL) {
			return (next->addLst(valueSet));
		} else {
			next = new sList;
			next->create(valueSet);
			return (next);
		}
	}
	void		display(void) {
		std::cout << "\t" << value << "\t\033[36m" << count << "\033[0m" << std::endl;
		if (next != NULL) {
			next->display();
		}
	}
	/*
	**freeValues must be used once (FileScanner.files)
	*/
	void		freeValues(void) {
		if (next != NULL) {
			next->freeValues();
		}
		if (value != NULL) {
			free(value);
			value = NULL;
		}
	}
	void		remove(void) {
		if (next != NULL) {
			next->remove();
			delete next;
			next = NULL;
		}
	}
};

#endif

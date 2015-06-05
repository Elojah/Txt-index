#include "FileScanner.hpp"
#include <unistd.h>

static void		exec(char *path) {
	FileScanner		fs;

	write(1, "Scan:\tStarting ...\n", 19);
	fs.scan(path);
	write(1, "Scan:\tDONE\n", 11);
	fs.ask();
}

int				main(int ac, char **av) {
	if (ac != 2) {
		write(2, "Usage: <filename>\n", 18);
	} else {
		exec(av[1]);
	}
	write(1, "Thanks for using me, see ya !\n", 30);
	return (0);
}

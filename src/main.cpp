#include <cmath>
#include <fstream>
#include <iomanip>

#include "binary_tree.h"
#include "node.h"

/* Main
   Assert that the number of command line arguments is correct
   open the input file
   initialize variables
   Read in values
   Write values to file
   */
int main(int argc, char **argv) {
	// Assert that the number of command line arguments is correct
	if (argc != 3) {
		throw std::runtime_error(
				"\nYou must provide two command line args. The input file name and "
				"the output file name");
	}
	// open the input file
	std::ifstream is(argv[1]);
	if (!is.is_open()) {
		throw std::runtime_error("\nThe input file could not be opened");
	}

	// initialize variables
	BinaryTree<int> tree;
	int val;
	char instruction;

	// Read in values
	while (is >> instruction >> val) {
		if (instruction == 'a') {
			tree.a(val);
		} else if (instruction == 'd') {
			tree.d(val);
		}
	}

	// Write values to file
	tree.write(argv[2]);
}

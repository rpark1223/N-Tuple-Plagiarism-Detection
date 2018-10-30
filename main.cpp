/*
 * main.cpp
 *
 * Author:  Robin Park, Tufts University, Fall 2018
 *
 * A program to detect plagiarism between two files based on an N-tuple
 * comparison algorithm
 *
 * Invoke the program like this:
 *
 *      ./plag_det synonym_filename file_1 target_file tuple_number
 *
 * and it will calculate the percent of n-tuples in file_1 that occur in
 * the target file
 */

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "Detector.h"
using namespace std;

void usage_abort(string program_name);
int set_tuple(int argc, char *argv[]);

int main(int argc, char *argv[])
{
		Detector d;
		string   syn_file, file1, file2;
		ifstream input;

		if ((argc < 4) || (argc > 5)) {
				usage_abort(argv[0]);
		} else {
				for (int i = 1; i < 4; i++) {
				        input.open(argv[i]);
				        if (not input.is_open()) {
				                cerr << "Unable to open " << argv[i] << endl;
				                input.close();
				                exit(1);
				        }
				        input.close();
			    }
				syn_file = argv[1];
				file1 = argv[2];
				file2 = argv[3];
		}

		d.run(syn_file, file1, file2, set_tuple(argc, argv));
		return 0;
}

/*
 * Abort the program with an error message describing correct program
 * usage.
 */
void usage_abort(string program_name)
{
        cerr << "Usage: " << program_name
			 << " syn_file file1 file2 (tuple size)" << endl;
        exit(1);
}

/*
 * Sets tuple based on whether the user provided it as an argument
 */
int set_tuple(int argc, char *argv[])
{
		if (argc == 5) {
				return stoi(argv[4]);
		} else {
				return 3;
		}
}
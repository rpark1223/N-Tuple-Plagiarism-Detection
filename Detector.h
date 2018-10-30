/*
 * Robin Park
 * Header File for the Detector class
 */

#ifndef DETECTOR_H
#define DETECTOR_H
#include <string>
#include <vector>
#include "HashTable.h"
using namespace std;

class Detector {

	public:

		Detector();
		~Detector();

		void run(string syn_file, string file1, string file2, int tuple);

	private:

			HashTable synonym_table;
			HashTable tuple_table; /* contains all tuples in first file */
			vector<string> tuple_vector;

			int tuple;
			float number_tuple_matches;
			float percent_matches;

			void init_syn_table(string syn_file);
			void init_tuple_vector(string file);
			void init_tuple_table();

			void calculate_plagiarism();
			void output_plagiarism();

};

#endif
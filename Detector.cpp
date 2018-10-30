/*
 * Robin Park
 * Implementation File for the Detector class
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Detector.h"
#include "HashTable.h"
using namespace std;

// purpose: initializes instance of Detector class
// parameters: none
// return: none
Detector::Detector()
{
		tuple = 3;
		number_tuple_matches = 0;
		percent_matches = 0;
}

// purpose: destroys any heap-allocated data used in Detector
// parameters: 
// return: 
Detector::~Detector()
{
		// not needed
}

// purpose: launches process to detect percentage of plagiarism betwwen files
// parameters: string, string, string, int
// return: void
void Detector::run(string syn_file, string file1, string file2, int n)
{
		tuple = n;
		init_syn_table(syn_file);
		init_tuple_vector(file1);
		init_tuple_table();
		init_tuple_vector(file2);

		calculate_plagiarism();
		output_plagiarism();

}

// purpose: initializes the synonym hash table
// parameters: string
// return: void
void Detector::init_syn_table(string syn_file)
{
		ifstream input;
		input.open(syn_file);

		string line;

		while(getline(input, line)) {
				string first_word, word;
				stringstream ss(line);
				ss >> first_word;
				synonym_table.insert(first_word, first_word);

				// sets value of every synonym key as the first-appearing
				// synonym on its respective line in the synonym file
				while (ss >> word) {
						synonym_table.insert(word, first_word);
				}
		}

		input.close();
}

// purpose: initializes a vector of n-tuples using a file
// parameters: string
// return: void
void Detector::init_tuple_vector(string file)
{
		tuple_vector.clear();

		string word;
		vector<string> v;
		ifstream infile;
		infile.open(file);

		while (infile >> word)
				v.push_back(word);

		infile.close();

		for (size_t i = 0; i < v.size() - (tuple - 1); i++) {
				stringstream ss;
				for (int j = 0; j < tuple; j++) {
						string current = v.at(i + j);

						// replaces every synonym with the first synonym in its
						// respective line in the synonym file
						if (synonym_table.contains(current)) {
							current = synonym_table.get_value(current);
						}

						ss << current;
				}
				tuple_vector.push_back(ss.str());
		}
}

// purpose: initializes a hash table with all the n-tuples from the first file
// parameters: none
// return: void
void Detector::init_tuple_table()
{
		for (size_t i = 0; i < tuple_vector.size(); i++)
				tuple_table.insert(tuple_vector.at(i), "");		
}

// purpose: calculates the percentage of n-tuples in the first file that appear
//			in the target file (aka the number of tuples in the second file
//			that exist in the tuple table)
// parameters: none
// return: void
void Detector::calculate_plagiarism()
{
		float number_tuples = static_cast<float>(tuple_vector.size());
		for (float i = 0; i < number_tuples; i++) {
				if (tuple_table.contains(tuple_vector.at(i)))
						number_tuple_matches++;
		}

		percent_matches = (number_tuple_matches / number_tuples) * 100;
}

// purpose: outputs the percentage of n-tuple matches
// parameters: none
// return: void
void Detector::output_plagiarism()
{
		cout << percent_matches << "%\n";
}
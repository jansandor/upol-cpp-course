#include <iostream>
#include <exception>
#include <stdexcept>
#include <string>
#include <fstream>
#include <set>
#include <cstring>
#include <algorithm>
#include <cctype>

#ifdef _WIN32
#define NEWLINE_CHAR '\n'
#elif defined __unix
#define NEWLINE_CHAR '\r'
#endif

using namespace std;

void to_lowercase_str(string& str)
{
	transform(str.begin(), str.end(), str.begin(), [](int c) { return tolower(c); });
}

int main(int argc, char const* argv[])
{
	if (argc != 4)
	{
		throw runtime_error("Invalid input arguments count.");
	}
	string fpath_input_txt = argv[1];
	string fpath_input_dict = argv[2];
	string fpath_output_txt = argv[3];
	const int buff_size = 64;
	char buffer[buff_size];       // cteci buffer pro ifstream
	string word;                  // prectene slovo ze slovniku nebo textu
	set<string> words;            // mnozina (unikatnich) slov ze slovniku
	set<string> words_notin_dict; // obsahuje nalezena slova ze vstupniho textu, ktera nejsou ve slovniku
	// pro overeni, jestli jiz byla nalezena a zapsana do vystupniho souboru
	try
	{
		// load dict from txt file to memory
		ifstream fsi_dict(fpath_input_dict);
		if (fsi_dict.is_open() == false)
			throw string("Cannot open " + fpath_input_dict + " for reading.");
		cout << "Loading words from " << fpath_input_dict << " to the dictionary." << endl;
		while (fsi_dict.eof() == false)
		{
			fsi_dict.getline(buffer, buff_size, NEWLINE_CHAR);
			word = buffer;
			if (word == "")
				continue;
			to_lowercase_str(word);
			size_t erase_start = word.find_first_of(' ', 0);
			if (erase_start != string::npos) { // za slovem jsou mezery
				word.erase(word.begin() + erase_start, word.end()); // smaze libovolny pocet mezer za slovem
			}
			auto ret = words.insert(word);
			if (ret.second == false)
			{
				cout << "\"" << word << "\" already exists in the set of words." << endl;
			}
#ifdef __unix
			fsi_dict.getline(buffer, buff_size); // precteni \n za \r
#endif
		}
		fsi_dict.close();
		cout << "Done!" << endl;
	}
	catch (const string& errmsg)
	{
		cout << errmsg << endl;
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
	// cteni slov ze vstupniho textu a overovani, zdali je slovo ve slovniku    
	try
	{
		int written = 0; // pocet zapsanych slov do vystupniho souboru
		word = "";
		ifstream fsi_text(fpath_input_txt);
		ofstream fso_output(fpath_output_txt);
		if (fsi_text.is_open() == false)
			throw string("Cannot open " + fpath_input_txt + " for reading.");
		if (fso_output.is_open() == false)
			throw string("Cannot open " + fpath_output_txt + " for writing.");
		while (fsi_text.eof() == false)
		{
			int c = fsi_text.get();
			if (isalpha(c))
			{
				word += c;
			}
			else if (isspace(c))
			{
				if (word == "")
					continue;
				to_lowercase_str(word);
				if (words.find(word) == words.end()) // slovo nebylo ve slovniku nalezeno
				{
					if (words_notin_dict.find(word) == words_notin_dict.end())
					{
						words_notin_dict.insert(word); // slovo pridano do mnoziny nalezenych slov, ktera nejsou ve slovniku                        
						fso_output.write(word.c_str(), word.length()); // a zapsano do vystupniho souboru
						written++;
						if (written > 0 && written % 5 == 0) {
							fso_output.write("\n", 1); // zalomeni radku za 5. zapsanym slovem
						}
						else {
							fso_output.write(" ", 1); // vlozeni mezery za slovo, ktere neni posledni na radku
						}
					}
				}
				word = "";
			}
			else if (ispunct(c))
			{
				continue;
			}
		}
		fso_output.close();
		fsi_text.close();
	}
	catch (const string& errmsg)
	{
		cout << errmsg << endl;
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}
	return EXIT_SUCCESS;
}

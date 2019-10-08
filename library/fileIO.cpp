#include <fstream>
#include <sstream>
#include "../includes_usr/constants.h"
#include "../includes_usr/fileIO.h"
using namespace std;

const char DIVIDER = ',';
const std::string EMPTY_LINE = "";

bool isEmpty(std::fstream &file) {
	return file.peek() == std::ifstream::traits_type::eof();
}

/*
 * clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 */
int loadBooks(std::vector<book> &books, const char *filename) {
	std::fstream file;
	file.open(filename, std::ios_base::in);
	if (!file.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	if (isEmpty(file)) {
		return NO_BOOKS_IN_LIBRARY;
	}

	books.clear();

	std::string line;

	std::string id;
	std::string bookName;
	std::string author;
	std::string bookCheckOutState;
	std::string patronID;

	while (!file.eof()) {
		getline(file, line);

		if (line == EMPTY_LINE) {
			break;
		}

		std::stringstream ss(line);

		getline(ss, id, DIVIDER);
		getline(ss, bookName, DIVIDER);
		getline(ss, author, DIVIDER);
		getline(ss, bookCheckOutState, DIVIDER);
		getline(ss, patronID, DIVIDER);

		book newBook;
		newBook.book_id = stoi(id);
		newBook.title = bookName;
		newBook.author = author;
		newBook.state = book_checkout_state(stoi(bookCheckOutState));
		newBook.loaned_to_patron_id = stoi(patronID);

		books.push_back(newBook);
	}

	return SUCCESS;
}

/*
 * serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 */
int saveBooks(std::vector<book> &books, const char *filename) {
	std::fstream file;
	file.open(filename, std::ios_base::out);
	if (!file.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	if (books.empty()) {
		return NO_BOOKS_IN_LIBRARY;
	}

	for (std::vector<book>::iterator it = books.begin(); it != books.end();
			++it) {
		file << it->book_id << DIVIDER << it->title << DIVIDER << it->author << DIVIDER
				<< it->state << DIVIDER << it->loaned_to_patron_id << std::endl;
	}

	return SUCCESS;
}

/*
 * clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 */
int loadPatrons(std::vector<patron> &patrons, const char *filename) {
	std::fstream file;
	file.open(filename, std::ios_base::in);
	if (!file.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	if (isEmpty(file)) {
		return NO_PATRONS_IN_LIBRARY;
	}

	patrons.clear();

	std::string line;

	std::string patron_id;
	std::string patron_name;
	std::string booksCheckedOut;

	while (!file.eof()) {
		getline(file, line);
		std::stringstream ss(line);

		if (line == EMPTY_LINE) {
			break;
		}

		getline(ss, patron_id, DIVIDER);
		getline(ss, patron_name, DIVIDER);
		getline(ss, booksCheckedOut, DIVIDER);

		patron newPatron;
		newPatron.patron_id = stoi(patron_id);
		newPatron.name = patron_name;
		newPatron.number_books_checked_out = stoi(booksCheckedOut);

		patrons.push_back(newPatron);
	}

	return SUCCESS;
}

/*
 * serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 */
int savePatrons(std::vector<patron> &patrons, const char *filename) {
	std::ofstream file;
	file.open(filename, std::ios_base::out);
	if (!file.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	if (patrons.empty()) {
		return NO_PATRONS_IN_LIBRARY;
	}

	for (std::vector<patron>::iterator it = patrons.begin();
			it != patrons.end(); ++it) {
		file << it->patron_id << DIVIDER << it->name << DIVIDER
				<< it->number_books_checked_out << std::endl;
	}

	return SUCCESS;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Sneakers.h"

// For Input.cpp
int checking_size(char word[10]);
int checking_price(char word[10]);
void input_table_in_console(int* count_sneakers, struct Sneakers sneakers[100]);
void input_table_from_file(int* count_sneakers, struct Sneakers sneakers[100], int* flag);
void select_type_of_input(int* count_sneakers, struct Sneakers sneakers[100], int* flag);
// END

// For Output.cpp
void select_type_of_output(int* count_sneakers, struct Sneakers sneakers[100]);
void output_table_in_console(int* count_sneakers, struct Sneakers sneakers[100]);
void output_table_in_file(int* count_sneakers, struct Sneakers sneakers[100]);
void output_names();
void output_start();
void output_middle();
void output_end();
// END

// For Add_data.cpp
void add_sneakers(int* count_sneakers, struct Sneakers sneakers[100]);
// END

// For Delete.cpp
void delete_sneakers(int* count_sneakers, struct Sneakers sneakers[100]);
// END

// For Find_data.cpp
void find_sneakers(int* count_sneakers, struct Sneakers sneakers[100]);
void output_selected_elements(int count_selected_elements, struct Sneakers array_of_selected_elements[100]);
// END

// For Sorting.cpp
void sorting(int* count_sneakers, struct Sneakers sneakers[100]);
// END

void menu(struct Sneakers sneakers[100]);

// Functions for Input.cpp

int checking_size(char word[10]) {
	int len, index;

	len = strlen(word);

	for (index = 0; index < len; ++index) {
		if (!(isdigit(word[index])) && word[index] != '.') return 0;
	}

	return 1;
}

int checking_price(char word[10]) {
	int len, index;

	len = strlen(word);

	for (index = 0; index < len; ++index) {
		if (!(isdigit(word[index]))) return 0;
	}

	return 1;
}

void select_type_of_input(int* count_sneakers, struct Sneakers sneakers[100], int* flag) {
	int command;

again:

	printf(
		"How you wanna input data?\n"
		"\t1: In console\n"
		"\t2: From file\n"
	);

	scanf_s("%d", &command);

	switch (command) {
	case 1: {
		input_table_in_console(count_sneakers, sneakers);
		break;
	}
	case 2: {
		input_table_from_file(count_sneakers, sneakers, flag);
		break;
	}
	default: {
		printf("You inputed wrond command. Please, try again\n");
		goto again;
	}
	}
}

void input_table_from_file(int* count_sneakers, struct Sneakers sneakers[100], int* flag) {
	FILE* file;
	char letter, word_for_size[10], word_for_price[10];
	int index_for_struct, index_for_word;

	fopen_s(&file, "File_for_data.txt", "r");

	index_for_struct = 0;

	letter = fgetc(file);

	while (letter != EOF) {
		index_for_word = 0;
		while (letter != ' ') {
			sneakers[index_for_struct].title[index_for_word] = letter;
			letter = fgetc(file);
			++index_for_word;
		}
		sneakers[index_for_struct].title[index_for_word] = '\0';
		letter = fgetc(file);
		index_for_word = 0;

		while (letter != ' ') {
			sneakers[index_for_struct].firm[index_for_word] = letter;
			letter = fgetc(file);
			++index_for_word;
		}
		sneakers[index_for_struct].firm[index_for_word] = '\0';
		letter = fgetc(file);
		index_for_word = 0;

		while (letter != ' ') {
			word_for_size[index_for_word] = letter;
			letter = fgetc(file);
			++index_for_word;
		}
		letter = fgetc(file);
		word_for_size[index_for_word] = '\0';
		if (!(checking_size(word_for_size))) {
			printf("Data is wrong. Please, try input in console");
			*flag = 1;
			break;
		}
		index_for_word = 0;
		sneakers[index_for_struct].size = atof(word_for_size);

		while (letter != '\n' && letter != EOF) {
			word_for_price[index_for_word] = letter;
			letter = fgetc(file);
			++index_for_word;
		}
		word_for_price[index_for_word] = '\0';
		if (!(checking_price(word_for_price))) {
			printf("Data is wrong. Please, try input in console");
			*flag = 1;
			break;
		}
		sneakers[index_for_struct].price = atoi(word_for_price);
		letter = fgetc(file);

		++index_for_struct;
		++(*count_sneakers);
	}

	fclose(file);
}

void input_table_in_console(int* count_sneakers, struct Sneakers sneakers[100]) {
	int index, cnt;
	char word[10];

again:

	index = 0;
	printf("Input count of strings in your table\n");
	scanf_s("%d", &cnt);
	// printf("Input your table by columns: title firm size price\n");

	for (index = 0; index < cnt; ++index) {
		printf("Input title and firm of your sneakers\n");
		scanf_s(
			"%s %s",
			&sneakers[index].title, 30,
			&sneakers[index].firm, 10
		);

		printf("Input size of your sneakers\n");
		scanf_s("%s", word, 10);
		if (checking_size(word)) sneakers[index].size = atof(word);
		else {
			printf("You inputed wrong data. Please, try again\n");
			goto again;
		}

		printf("Input price of your sneakers\n");
		scanf_s("%s", &word, 10);
		if (checking_price(word)) sneakers[index].price = atoi(word);
		else {
			printf("You inputed wrong data. Please? try again\n");
			goto again;
		}
	}

	*count_sneakers += cnt;
}


// END


// Functions for Output.cpp

void select_type_of_output(int* count_sneakers, struct Sneakers sneakers[100]) {
	int command;

again:

	printf(
		"How you wanna input data?\n"
		"\t1: In console\n"
		"\t2: In file\n"
	);

	scanf_s("%d", &command);

	while (true) {
		switch (command) {
		case 1: {
			output_table_in_console(count_sneakers, sneakers);
			break;
		}
		case 2: {
			output_table_in_file(count_sneakers, sneakers);
			break;
		}
		default: {
			printf("You inputed wrond command. Please, try again\n");
		}
		}

		if (command == 1 || command == 2) break;
	}
}

void output_names() {
	int i;

	// number
	printf("%c%c  %c", 179, 252, 179);

	// title
	printf("Title");
	for (i = 0; i < 25; ++i) {
		printf(" ");
	}

	// firm
	printf("%cFirm", 179);
	for (i = 0; i < 7; ++i) {
		printf(" ");
	}

	// size
	printf("%cSize", 179);
	for (i = 0; i < 7; ++i) {
		printf(" ");
	}

	// price
	printf("%cPrice  %c\n", 179, 179);
}

void output_start() {
	int i;

	//number
	printf("%c", 218);
	for (i = 0; i < 3; ++i) {
		printf("%c", 196);
	}
	printf("%c", 194);

	//title
	for (i = 0; i < 30; ++i) {
		printf("%c", 196);
	}
	printf("%c", 194);

	//firm
	for (i = 0; i < 11; ++i) {
		printf("%c", 196);
	}
	printf("%c", 194);

	//size
	for (i = 0; i < 11; ++i) {
		printf("%c", 196);
	}
	printf("%c", 194);

	//price
	for (i = 0; i < 7; ++i) {
		printf("%c", 196);
	}
	printf("%c\n", 191);
}

void output_middle() {
	int i;

	//number
	printf("%c", 195);
	for (i = 0; i < 3; ++i) {
		printf("%c", 196);
	}
	printf("%c", 197);

	//title
	for (i = 0; i < 30; ++i) {
		printf("%c", 196);
	}
	printf("%c", 197);

	//firm
	for (i = 0; i < 11; ++i) {
		printf("%c", 196);
	}
	printf("%c", 197);

	//size
	for (i = 0; i < 11; ++i) {
		printf("%c", 196);
	}
	printf("%c", 197);

	//price
	for (i = 0; i < 7; ++i) {
		printf("%c", 196);
	}
	printf("%c\n", 180);
}

void output_end() {
	int i;

	//number
	printf("%c", 192);
	for (i = 0; i < 3; ++i) {
		printf("%c", 196);
	}
	printf("%c", 193);

	//title
	for (i = 0; i < 30; ++i) {
		printf("%c", 196);
	}
	printf("%c", 193);

	//firm
	for (i = 0; i < 11; ++i) {
		printf("%c", 196);
	}
	printf("%c", 193);

	//size
	for (i = 0; i < 11; ++i) {
		printf("%c", 196);
	}
	printf("%c", 193);

	//price
	for (i = 0; i < 7; ++i) {
		printf("%c", 196);
	}
	printf("%c\n", 217);
}

void output_table_in_console(int* count_sneakers, struct Sneakers sneakers[100]) {
	int index, number, remain_of_len, copy_element, cnt, i;

	number = 1;

	output_start();
	output_names();
	output_middle();

	for (index = 0; index < *count_sneakers; ++index) {
		// For column of numbers
		copy_element = number;
		remain_of_len = 2;
		while (copy_element / 10 > 0) {
			--remain_of_len;
			copy_element /= 10;
		}
		printf("%c%d", 179, number);
		for (i = 0; i < remain_of_len; ++i) {
			printf(" ");
		}

		// For column of titles
		remain_of_len = 30 - strlen(sneakers[index].title);
		printf("%c%s", 179, sneakers[index].title);
		for (i = 0; i < remain_of_len; ++i) {
			printf(" ");
		}

		// For column of firms
		remain_of_len = 11 - strlen(sneakers[index].firm);
		printf("%c%s", 179, sneakers[index].firm);
		for (i = 0; i < remain_of_len; ++i) {
			printf(" ");
		}

		// For column of sizes
		copy_element = sneakers[index].size;
		remain_of_len = 3;
		while (copy_element / 10 > 0) {
			--remain_of_len;
			copy_element /= 10;
		}
		printf("%c%f", 179, sneakers[index].size);
		for (i = 0; i < remain_of_len; ++i) {
			printf(" ");
		}

		// For column of prices
		copy_element = sneakers[index].price;
		remain_of_len = 6;
		while (copy_element / 10 > 0) {
			--remain_of_len;
			copy_element /= 10;
		}
		printf("%c%d", 179, sneakers[index].price);
		for (i = 0; i < remain_of_len; ++i) {
			printf(" ");
		}
		printf("%c\n", 179);

		++number;

		if (index == *count_sneakers - 1) {
			output_end();
		}
		else {
			output_middle();
		}
	}
}

void output_table_in_file(int* count_sneakers, struct Sneakers sneakers[100]) {
	int len, index_for_struct, index_for_word;
	char word_for_size[10], word_for_price[10];
	FILE* file;

	fopen_s(&file, "File_for_data.txt", "w");

	for (index_for_struct = 0; index_for_struct < *count_sneakers; ++index_for_struct) {
		len = strlen(sneakers[index_for_struct].title);
		for (index_for_word = 0; index_for_word < len; ++index_for_word) {
			fputc(sneakers[index_for_struct].title[index_for_word], file);
		}
		fputc(' ', file);

		len = strlen(sneakers[index_for_struct].firm);
		for (index_for_word = 0; index_for_word < len; ++index_for_word) {
			fputc(sneakers[index_for_struct].firm[index_for_word], file);
		}
		fputc(' ', file);

		sprintf_s(word_for_size, "%f", sneakers[index_for_struct].size);
		len = strlen(word_for_size);
		for (index_for_word = 0; index_for_word < len; ++index_for_word) {
			fputc(word_for_size[index_for_word], file);
		}
		fputc(' ', file);

		sprintf_s(word_for_price, "%d", sneakers[index_for_struct].price);
		len = strlen(word_for_price);
		for (index_for_word = 0; index_for_word < len; ++index_for_word) {
			fputc(word_for_price[index_for_word], file);
		}
		fputc('\n', file);
	}

	fclose(file);
}

// END

// Functions for Add_data.cpp

void add_sneakers(int* count_sneakers, struct Sneakers sneakers[100]) {
	int count, index;

	printf("Input count of your sneakers which you wanna add\n");
	scanf_s("%d", &count);
	printf("Input information about your sneakers by columns: title firm size price\n");

	for (index = 0; index < count; ++index) {
		scanf_s(
			"%s %s %f %d",
			&sneakers[*count_sneakers + index].title, 30,
			&sneakers[*count_sneakers + index].firm, 10,
			&sneakers[*count_sneakers + index].size,
			&sneakers[*count_sneakers + index].price
		);
	}

	*count_sneakers += count;
}

// END

// Functions for Find_data.cpp

void output_selected_elements(int count_selected_elements, struct Sneakers array_of_selected_elements[100]) {
	int i, index, number, copy_element, remain_of_len;

	number = 1;

	output_start();
	output_names();
	output_middle();

	for (index = 0; index < count_selected_elements; ++index) {
		// For column of numbers
		copy_element = number;
		remain_of_len = 2;
		while (copy_element / 10 > 0) {
			--remain_of_len;
			copy_element /= 10;
		}
		printf("%c%d", 179, number);
		for (i = 0; i < remain_of_len; ++i) {
			printf(" ");
		}

		// For column of titles
		remain_of_len = 30 - strlen(array_of_selected_elements[index].title);
		printf("%c%s", 179, array_of_selected_elements[index].title);
		for (i = 0; i < remain_of_len; ++i) {
			printf(" ");
		}

		// For column of firms
		remain_of_len = 11 - strlen(array_of_selected_elements[index].firm);
		printf("%c%s", 179, array_of_selected_elements[index].firm);
		for (i = 0; i < remain_of_len; ++i) {
			printf(" ");
		}

		// For column of sizes
		copy_element = array_of_selected_elements[index].size;
		remain_of_len = 3;
		while (copy_element / 10 > 0) {
			--remain_of_len;
			copy_element /= 10;
		}
		printf("%c%f", 179, array_of_selected_elements[index].size);
		for (i = 0; i < remain_of_len; ++i) {
			printf(" ");
		}

		// For column of prices
		copy_element = array_of_selected_elements[index].price;
		remain_of_len = 6;
		while (copy_element / 10 > 0) {
			--remain_of_len;
			copy_element /= 10;
		}
		printf("%c%d", 179, array_of_selected_elements[index].price);
		for (i = 0; i < remain_of_len; ++i) {
			printf(" ");
		}
		printf("%c\n", 179);

		++number;

		if (index == count_selected_elements - 1) {
			output_end();
		}
		else {
			output_middle();
		}
	}
}

void find_sneakers(int* count_sneakers, struct Sneakers sneakers[100]) {
	int number_of_column, index_for_find, index_for_array, command, number_of_string;
	struct Sneakers array_of_selected_elements[100];

	index_for_array = 0;

again:

	printf(
		"How you wanna find elements?\n"
		"\t1: By string\n"
		"\t2: By conumn\n"
	);
	scanf_s("%d", &command);

	if (command == 1) {
		printf("Input number of string from which you wanna select element\n");
		scanf_s("%d", &number_of_string);
		array_of_selected_elements[0] = sneakers[number_of_string - 1];
		output_selected_elements(1, array_of_selected_elements);
	}
	else if (command == 2) {
		printf(
			"Input number of column from which you wanna find elements\n"
			"\t0: Back to menu\n"
			"\t1: Title\n"
			"\t2: Firm\n"
			"\t3: Size\n"
			"\t4: Price\n"
		);

		scanf_s("%d", &number_of_column);

		if (number_of_column != 0) {
			printf("Input element which you wanna find\n");
		}

		switch (number_of_column) {
		case 0: break;
		case 1: {
			char element[30];

			scanf_s("%s", element, 30);

			for (index_for_find = 0; index_for_find < *count_sneakers; ++index_for_find) {
				if (!(_stricmp(sneakers[index_for_find].title, element))) {
					array_of_selected_elements[index_for_array] = sneakers[index_for_find];
					++index_for_array;
				}
			}

			break;
		}
		case 2: {
			char element[10];

			scanf_s("%s", element, 10);

			for (index_for_find = 0; index_for_find < *count_sneakers; ++index_for_find) {
				if (!(_stricmp(sneakers[index_for_find].firm, element))) {
					array_of_selected_elements[index_for_array] = sneakers[index_for_find];
					++index_for_array;
				}
			}

			break;
		}
		case 3: {
			int element;

			scanf_s("%f", &element);

			for (index_for_find = 0; index_for_find < *count_sneakers; ++index_for_find) {
				if (sneakers[index_for_find].size == element) {
					array_of_selected_elements[index_for_array] = sneakers[index_for_find];
					++index_for_array;
				}
			}

			break;
		}
		case 4: {
			int element;

			scanf_s("%d", &element);

			for (index_for_find = 0; index_for_find < *count_sneakers; ++index_for_find) {
				if (sneakers[index_for_find].price == element) {
					array_of_selected_elements[index_for_array] = sneakers[index_for_find];
					++index_for_array;
				}
			}

			break;
		}
		default: {
			printf("This column is noun. Please, try again:/\n");
			goto again;
		}
		}

		if (number_of_column != 0) {
			output_selected_elements(index_for_array, array_of_selected_elements);
		}
	}
}

// END

// Functions for Delete.cpp

void delete_sneakers(int* count_sneakers, struct Sneakers sneakers[100]) {
	int index, number_of_column, command, number_of_string;

again:

	printf(
		"Input how you wanna do remove?\n"
		"\t1: By string\n"
		"\t2: By column\n"
	);
	scanf_s("%d", &command);

	if (command == 1) {
		printf("Input number of string\n");
		scanf_s("%d", &number_of_string);

		for (index = number_of_string - 1; index < *count_sneakers; ++index) {
			sneakers[index] = sneakers[index + 1];
		}

		--(*count_sneakers);
		output_table_in_console(count_sneakers, sneakers);
	}
	else if (command == 2) {
		printf(
			"Input number of columns from which you wanna delete elements:\n"
			"\t0: Back to menu\n"
			"\t1: Title\n"
			"\t2: Firm\n"
			"\t3: Size\n"
			"\t4: Price\n"
		);
		scanf_s("%d", &number_of_column);

		if (number_of_column != 0) {
			printf("Input element which you wanna delete by\n");
		}

		switch (number_of_column)
		{
		case 0: break;
		case 1: {
			char element[30];
			scanf_s("%s", &element, 30);
			index = 0;

			while (index < *count_sneakers) {
				if (!(_stricmp(element, sneakers[index].title))) {
					for (int i = index; i < *count_sneakers; ++i) {
						sneakers[i] = sneakers[i + 1];
					}
					--(*count_sneakers);
					continue;
				}
				++index;
			}

			break;
		}
		case 2: {
			char element[10];
			scanf_s("%s", &element, 10);
			index = 0;

			while (index < *count_sneakers) {
				if (!(_stricmp(element, sneakers[index].firm))) {
					for (int i = index; i < *count_sneakers; ++i) {
						sneakers[i] = sneakers[i + 1];
					}
					--(*count_sneakers);
					continue;
				}
				++index;
			}

			break;
		}
		case 3: {
			int element;
			scanf_s("%d", &element);
			index = 0;

			while (index < *count_sneakers) {
				if (element == sneakers[index].size) {
					for (int i = index; i < *count_sneakers; ++i) {
						sneakers[i] = sneakers[i + 1];
					}
					--(*count_sneakers);
					continue;
				}
				++index;
			}

			break;
		}
		case 4: {
			int element;
			scanf_s("%d", &element);
			index = 0;

			while (index < *count_sneakers) {
				if (element == sneakers[index].price) {
					for (int i = index; i < *count_sneakers; ++i) {
						sneakers[i] = sneakers[i + 1];
					}
					--(*count_sneakers);
					continue;
				}
				++index;
			}

			break;
		}
		default: {
			printf("This column is noun. Please, try again\n");
			goto again;
		}
		}

		if (number_of_column != 0) {
			output_table_in_console(count_sneakers, sneakers);
		}
	}
	else {
		goto again;
	}
}

// END

//Functions for Sorting.cpp

void sorting(int* count_sneakers, struct Sneakers sneakers[100]) {
	int number_of_column, first_index, second_index, command;
	struct Sneakers element_for_swap;

again:

	printf(
		"Input number of columns by which you wanna sort:\n"
		"\t0: Back to menu\n"
		"\t1: Title\n"
		"\t2: Firm\n"
		"\t3: Size\n"
		"\t4: Price\n"
	);
	scanf_s("%d", &number_of_column);

	printf("How you wanna sorting table?\n"
		"\t1: In ascending\n\t2: In descending\n"
	);
	scanf_s("%d", &command);

	switch (number_of_column) {
	case 0: break;

	case 1: {
		for (first_index = 0; first_index < *count_sneakers; ++first_index) {
			for (second_index = first_index + 1; second_index < *count_sneakers; ++second_index) {
				if (command == 1) {
					if (strcmp(sneakers[first_index].title, sneakers[second_index].title) > 0) {
						element_for_swap = sneakers[first_index];
						sneakers[first_index] = sneakers[second_index];
						sneakers[second_index] = element_for_swap;
					}
				}
				else if (command == 2) {
					if (strcmp(sneakers[first_index].title, sneakers[second_index].title) < 0) {
						element_for_swap = sneakers[first_index];
						sneakers[first_index] = sneakers[second_index];
						sneakers[second_index] = element_for_swap;
					}
				}
			}
		}

		break;
	}

	case 2: {
		for (first_index = 0; first_index < *count_sneakers; ++first_index) {
			for (second_index = first_index + 1; second_index < *count_sneakers; ++second_index) {
				if (command == 1) {
					if (strcmp(sneakers[first_index].firm, sneakers[second_index].firm) > 0) {
						element_for_swap = sneakers[first_index];
						sneakers[first_index] = sneakers[second_index];
						sneakers[second_index] = element_for_swap;
					}
				}
				else if (command == 2) {
					if (strcmp(sneakers[first_index].firm, sneakers[second_index].firm) < 0) {
						element_for_swap = sneakers[first_index];
						sneakers[first_index] = sneakers[second_index];
						sneakers[second_index] = element_for_swap;
					}
				}
			}
		}

		break;
	}

	case 3: {
		for (first_index = 0; first_index < *count_sneakers; ++first_index) {
			for (second_index = first_index + 1; second_index < *count_sneakers; ++second_index) {
				if (command == 1) {
					if (sneakers[first_index].size > sneakers[second_index].size) {
						element_for_swap = sneakers[first_index];
						sneakers[first_index] = sneakers[second_index];
						sneakers[second_index] = element_for_swap;
					}
				}
				else if (command == 2) {
					if (sneakers[first_index].size < sneakers[second_index].size) {
						element_for_swap = sneakers[first_index];
						sneakers[first_index] = sneakers[second_index];
						sneakers[second_index] = element_for_swap;
					}
				}
			}
		}

		break;
	}

	case 4: {
		for (first_index = 0; first_index < *count_sneakers; ++first_index) {
			for (second_index = first_index + 1; second_index < *count_sneakers; ++second_index) {
				if (command == 1) {
					if (sneakers[first_index].price > sneakers[second_index].price) {
						element_for_swap = sneakers[first_index];
						sneakers[first_index] = sneakers[second_index];
						sneakers[second_index] = element_for_swap;
					}
				}
				else if (command == 2) {
					if (sneakers[first_index].price < sneakers[second_index].price) {
						element_for_swap = sneakers[first_index];
						sneakers[first_index] = sneakers[second_index];
						sneakers[second_index] = element_for_swap;
					}
				}
			}
		}

		break;
	}

	default: {
		printf("This column is noun. Please, try again\n");
		goto again;
	}
	}
}

// END

void menu(struct Sneakers sneakers[100]) {
	int command, count_sneakers, flag;
	char char_command[10];

	count_sneakers = 0;
	flag = 0;

	while (true) {
		printf(
			"Input command's number:\n"
			"\t1: Input table\n"
			"\t2: Output table\n"
			"\t3: Add sneakers\n"
			"\t4: Find sneakers\n"
			"\t5: Delete sneakers\n"
			"\t6: Sort table by..\n"
			"\t7: Exit\n"
		);

		scanf_s("%s", &char_command, 10);

		if (!(checking_price(char_command))) {
			printf("You inputed a wrong command. Please, try again");
			continue;
		}
		command = atoi(char_command);

		switch (command) {
		case 1: {
			count_sneakers = 0;
			select_type_of_input(&count_sneakers, sneakers, &flag);
			if (!flag) output_table_in_console(&count_sneakers, sneakers);
			break;
		}
		case 2: {
			select_type_of_output(&count_sneakers, sneakers);
			break;
		}
		case 3: {
			add_sneakers(&count_sneakers, sneakers);
			output_table_in_console(&count_sneakers, sneakers);
			break;
		}
		case 4: {
			find_sneakers(&count_sneakers, sneakers);
			break;
		}
		case 5: {
			delete_sneakers(&count_sneakers, sneakers);
			break;
		}
		case 6: {
			sorting(&count_sneakers, sneakers);
			output_table_in_console(&count_sneakers, sneakers);
			break;
		}
		case 7: {
			printf("You exited from my CRUD. See u;)");
			break;
		}
		default: {
			printf("We don't have these command.\nPlease, try again\n");
		}
		}

		if (command == 7) break;
	}
}

int main() {
	struct Sneakers sneakers[100];

	menu(sneakers);

	return 0;
}

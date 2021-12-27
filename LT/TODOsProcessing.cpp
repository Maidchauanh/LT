#include "TODOsProcessing.hpp"

// TODO: try to make a better countOs function 
int countOs(const char *line) {
	int i = 0;
	int count = 0; 
	while (line[i] != ':') {
		i++;
		if(line[i] == 'O') 
			count++;
	}
	return count - 1;
}

// TODO: normal swap not working so i have to use iter_swap, check this for more info: https://stackoverflow.com/questions/6224830/c-trying-to-swap-values-in-a-vector
static void swap(std::vector<TODO> &v, int position, int next_position) {
	// assuming your vector is called v
	std::iter_swap(v.begin() + position, v.begin() + next_position);
	// position, next_position are the indices of the elements you want to swap
}

static int partition(std::vector<TODO> &arr, int low, int high) {
	TODO pivot = arr[high];
	int left = low;
	int right = high - 1;
	while (true){
		while (left <= right && arr[left].OsLen < pivot.OsLen) left++;
		while (right >= left && arr[right].OsLen > pivot.OsLen) right--;
		if (left >= right) break;
		swap(arr, left, right);
		left++;
		right--;
	}
	swap(arr, left, high);
	return left;
}

// TODO: convert this to use std::ector 
void quickSortByOsLen(std::vector<TODO> &arr, int low, int high) {
	if (low < high)
	{
		int pi = partition(arr, low, high);

		quickSortByOsLen(arr, low, pi - 1);
		quickSortByOsLen(arr, pi + 1, high);
	}
}
void TODOsOutput(std::vector<TODO> &TODOs, void(*func)(std::vector<TODO> &TODOs, int i)) {
	for (int i = TODOs.size() - 1; i >= 0; i--) {
		func(TODOs, i);
	}
}

void TODOsOutput(std::vector<TODO> &TODOs, std::ostream &myfile, void(*func)(std::vector<TODO> &TODOs, int i, std::ostream &myfile)) {
	for (int i = TODOs.size() - 1; i >= 0; i--) {
		func(TODOs, i, myfile);
	}
}

void outputTODOs(std::vector<TODO> &TODOs) {
	quickSortByOsLen(TODOs, 0, TODOs.size() - 1);

	// TODOOOOOOO: change this to an enum 

	if (TODOs.size() == 0) std::cout << "No TODOs, looks like you have done all of your tasks :))\n";
	else {
		enum CHOICES
		{
			TERMINAL_OUTPUT,
			FILE_OUTPUT
		};

		int choice = TERMINAL_OUTPUT;

		switch (choice) {
		case TERMINAL_OUTPUT:  {
		   TODOsOutput(TODOs, [](std::vector<TODO> &TODOs, int i){
			   std::cout << TODOs.at(i).line << '\n';
		   });

		} break;

		case FILE_OUTPUT: {
			  std::string outputFileName = "TODOsList.txt";
			  std::ofstream myfile;
			  myfile.open(outputFileName);
			  if (myfile.is_open()) {
				  TODOsOutput(TODOs, myfile, [](std::vector<TODO> &TODOs, int i, std::ostream &myfile){
					  myfile << TODOs.at(i).line;
				  });
			  }
			  else std::cout << "Can not openfile to write\n";
			  myfile.close();
		} break;

		default:{

		} break;
		}
	}
}
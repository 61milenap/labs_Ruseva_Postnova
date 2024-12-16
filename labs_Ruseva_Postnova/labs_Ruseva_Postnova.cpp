#include <iostream>
#include <unordered_map>
#include <limits>
#include "utils.h"
#include "Pipe.h"
#include "Compr_station.h"
#include <chrono>
#include <format>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
using namespace chrono;


void show_commands();


int main()
{
	redirect_output_wrapper cerr_out(cerr);
	string time = std::format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now());
	ofstream logfile("log_" + time + ".txt");
	if (logfile)
		cerr_out.redirect(logfile);
	std::unordered_map<int, Pipe> pipes;
	std::unordered_map<int, Compr_station> compr_stations;
	int choice;

	while (true) {
		show_commands();
		std::cout << "\nEnter your choice: ";
		choice = get_num_value(0, 12);
		switch (choice) {
		case 1:
		{
			Pipe Pp;
			std::cin >> Pp;
			pipes[Pp.get_max_id()] = Pp;
			break;
		}
		case 2:
		{
			Compr_station Cs;
			std::cin >> Cs;
			compr_stations[Cs.get_max_id()] = Cs;
			break;
		}
		case 3:
		{
			std::cout << "Pipes:\n";
			show(pipes);
			std::cout << "Compresor stations:\n";
			show(compr_stations);
			break;
		}
		case 4:
		{
			if (show(pipes)) {
				int id;
				std::cout << "Select the pipe id: ";
				id = get_num_value(0, std::numeric_limits<int>::max());
				if (del_pipe(id, pipes)) std::cout << "Pipe was deleted\n";
				else std::cout << "There is no pipe with that id\n";
			}
			break;
		}
		case 5:
		{
			if (show(compr_stations)) {
				int id;
				std::cout << "Input the CS id: ";
				id = get_num_value(0, std::numeric_limits<int>::max());
				//INPUT_LINE(in, id);
				if (del_compr_station(id, compr_stations)) std::cout << "CS was deleted\n";
				else std::cout << "There is no CS with that id\n";
			}
			break;
		}
		case 6:
		{
			if (show(pipes)) {
				int id;
				std::cout << "Input pipe id: \n";
				id = get_num_value(0, std::numeric_limits<int>::max());
				if (edit_pipe(id, pipes)) std::cout << "Pipe was edited\n";
				else std::cout << "There is no pipe with that id\n";
			}
			break;
		}
		case 7:
		{
			if (show(compr_stations)) {
				int id;
				std::cout << "Input CS id: \n";
				id = get_num_value(0, std::numeric_limits<int>::max());
				edit_compr_station(id, compr_stations);
			}
			break;
		}
		case 8:
		{
			if (pipes.size() != 0) filter_pipes(pipes);
			else std::cout << "There are no Pipes\n";
			break;
		}
		case 9:
		{
			if (compr_stations.size() != 0) filter_compr_stations(compr_stations);
			else std::cout << "There are no CS\n";
			break;
		}
		case 10:
		{
			std::string name;
			std::cout << "Input name of file for saving: ";
			INPUT_LINE(std::cin, name);
			if (save_data(name, pipes, compr_stations)) std::cout << "Data was saved\n";
			else std::cout << "Data was not saved\n";
			break;
		}
		case 11:
		{
			std::string name;
			std::cout << "Input name of file for loading: ";
			INPUT_LINE(std::cin, name);
			if (read_data(name, pipes, compr_stations)) std::cout << "Data was loaded\n";
			else std::cout << "There is no file with that name\n";
			break;
		}
		case 0:
		{
			std::cout << "Goodbye\n";
			return 0;
		}
		default:
		{
			std::cout << "Invalid choice\n";
			break;
		}
		}
	}
}

void show_commands() {
	std::cout << "1. Add a pipe\n";
	std::cout << "2. Add a CS\n";
	std::cout << "3. View all objects\n";
	std::cout << "4. Delete single pipe\n";
	std::cout << "5. Delete single CS\n";
	std::cout << "6. Edit single pipe\n";
	std::cout << "7. Edit single CS\n";
	std::cout << "8. Filter pipes\n";
	std::cout << "9. Filter CS\n";
	std::cout << "10. Save\n";
	std::cout << "11. Load\n";
	std::cout << "0. Exit\n";
}
// Workshop 9 - Multi-Threading, Thread Class
// process_data.cpp
// 2021/1/5 - Jeevan Pant


#include "process_data.h"

namespace sdds_ws9
{

	void computeAvgFactor(const int* arr, int size, int divisor, double& avg) {
		avg = 0;
		for (int i = 0; i < size; i++) {
			avg += arr[i];
		}
		avg /= divisor;
	}

	void computeVarFactor(const int* arr, int size, int divisor, double avg, double& var) {
		var = 0;
		for (int i = 0; i < size; i++) {
			var += (arr[i] - avg) * (arr[i] - avg);
		}
		var /= divisor;
	}
	ProcessData::operator bool() const {
		return total_items > 0 && data && num_threads > 0 && averages && variances && p_indices;
	}

	ProcessData::ProcessData(std::string filename, int n_threads) {
		// TODO: Open the file whose name was received as parameter and read the content
		//         into variables "total_items" and "data". Don't forget to allocate
		//         memory for "data".
		//       The file is binary and has the format described in the specs.

		std::fstream fp(filename, std::ios::in | std::ios::binary);
		if (!fp)
		{
			throw std::string("The File cannot be opened");
		}
		fp.read(reinterpret_cast<char*>(&total_items), 4);
		data = new int[total_items];
		fp.read(reinterpret_cast<char*>(data), total_items * sizeof(total_items));
		fp.close();
		std::cout << "Item's count in file '" << filename << "': " << total_items << std::endl;
		std::cout << "  [" << data[0] << ", " << data[1] << ", " << data[2] << ", ... , "
			<< data[total_items - 3] << ", " << data[total_items - 2] << ", "
			<< data[total_items - 1] << "]\n";

		// Following statements initialize the variables added for multi-threaded 
		//   computation
		num_threads = n_threads;
		averages = new double[num_threads] {};
		variances = new double[num_threads] {};
		p_indices = new int[num_threads + 1]{};
		for (int i = 0; i < num_threads + 1; i++)
			p_indices[i] = i * (total_items / num_threads);
	}
	ProcessData::~ProcessData() {
		delete[] data;
		delete[] averages;
		delete[] variances;
		delete[] p_indices;
	}

	// TODO Improve operator() function from part-1 for multi-threaded operation. Enhance the  
	//   function logic for the computation of average and variance by running the 
	//   function computeAvgFactor and computeVarFactor in multile threads. 
	// The function divides the data into a number of parts, where the number of parts is 
	//   equal to the number of threads. Use multi-threading to compute average-factor for 
	//   each part of the data by calling the function computeAvgFactor. Add the obtained 
	//   average-factors to compute total average. Use the resulting total average as the 
	//   average value argument for the function computeVarFactor, to compute variance-factors 
	//   for each part of the data. Use multi-threading to compute variance-factor for each 
	//   part of the data. Add computed variance-factors to obtain total variance.
	// Save the data into a file with filename held by the argument fname_target. 
	// Also, read the workshop instruction.

	int ProcessData::operator()(std::string filename, double& avg, double& var)
	{
		if (total_items > 0)
		{
			int i;
			auto avg_Factor = std::bind(computeAvgFactor, std::placeholders::_1, std::placeholders::_2, total_items, std::placeholders::_3);
			computeAvgFactor(data, total_items, total_items, avg);
			std::vector<std::thread>threads;
			for (i = 0; i < num_threads; i++)
			{
				threads.push_back(std::thread(avg_Factor,&data[p_indices[i]],p_indices[i+1]-p_indices[i],std::ref(averages[i])));
			}
			avg = 0;
			for (i = 0; i < num_threads; i++)
			{
				threads[i].join();
				avg += averages[i];
			}
			auto var_Factor = std::bind(computeVarFactor, std::placeholders::_1, std::placeholders::_2, total_items,avg,std::placeholders::_3);
			computeVarFactor(data, total_items, total_items, avg, var);
			std::vector<std::thread>threads2;
			for (i = 0; i < num_threads; i++)
			{
				threads2.push_back(std::thread(var_Factor, &data[p_indices[i]], p_indices[i + 1] - p_indices[i], std::ref(variances[i])));
			}
			var = 0;
			for (i = 0; i < num_threads; i++)
			{
				threads2[i].join();
				var += variances[i];
			}
			std::fstream file(filename, std::ios::out | std::ios::binary);
			file.write(reinterpret_cast<char*>(&total_items), 4);
			for (auto i = 0; i < total_items; i++)
			{
				file.write(reinterpret_cast<char*>(&data[i]), 4);
			}
			file.close();
			return 0;
		}
		return -1;
	}
}
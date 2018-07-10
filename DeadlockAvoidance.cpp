
/*
By:
Abdullah Ibrahim Ahmad Abdou		
Hussien Mohamed Elsayed Ibrahim		
*/

#include <iostream>     /*		cin , cout		*/

using namespace std;

bool all_done(int *done_arr, int pnum){
	for (int i = 0; i < pnum; i++)
		if (done_arr[i] == 0) return false;
	return true;
}

int main()
{
	//INITIALIZE VARIABLES
	int process_num, res_num, **allocation_arr, **max_arr, **need_arr, *avilable_res_arr, *done_process_arr, *seq_arr;
	cout << "Enter Number of processes" << endl;
	cin >> process_num;
	cout << "Enter Number of Resources" << endl;
	cin >> res_num;
	avilable_res_arr = new int[res_num];
	seq_arr = new int[process_num];
	done_process_arr = new int[process_num];

	//DECLARE DYNAMIC 2D ARRAYS (MATRICES)
	allocation_arr = new int*[process_num];
	max_arr = new int*[process_num];
	need_arr = new int*[process_num];
	for (int i = 0; i < process_num; i++)
	{
		allocation_arr[i] = new int[res_num];
		max_arr[i] = new int[res_num];
		need_arr[i] = new int[res_num];
	}

	//FILL ALL MATRICES WITH INPUT DATA
	for (int i = 0; i < process_num; i++)
	{
		cout << "Enter All Allocation Resources for P" << i << endl;
		for (int j = 0; j < res_num; j++)
			cin >> allocation_arr[i][j];
		cout << "Enter All Maximum needed Resources for P" << i << endl;
		for (int j = 0; j < res_num; j++)
			cin >> max_arr[i][j];
	}

	// CALCULATE NEED MATRIX
	for (int i = 0; i < process_num; i++)
		for (int j = 0; j < res_num; j++)
			need_arr[i][j] = max_arr[i][j] - allocation_arr[i][j];

	// get input from user (available processes)
	cout << "Enter Current Available instances for each of the " << res_num << " resources" << endl;
	for (int j = 0; j < res_num; j++)
	{
		cin >> avilable_res_arr[j];
	}

	// take one request if the user wants
	char req;
	cout << "Do you want to enter a request? (y/n) --> ";
	cin >> req;
	if (req == 'y' || req == 'Y') {
		int process, *request_res_arr = new int[res_num];;
		cout << "Enter process number followed by the request resources" << endl;
		cin >> process;
		for (int j = 0; j < res_num; j++)
		{
			cin >> request_res_arr[j];
			allocation_arr[process][j] += request_res_arr[j];
			need_arr[process][j] -= request_res_arr[j];
			avilable_res_arr[j] -= request_res_arr[j];
		}
	}

	// initialize done array and sequence array with suitable values
	for (int j = 0; j < res_num; j++)
	{
		done_process_arr[j] = 0;  seq_arr[j] = -1;
	}

	// APPLY THE BANKER ALGORITHM
	int trials = 0, i = 0, last_seq_index = 0;      bool flag;
	int max_no_of_iter = process_num * process_num, zero_flag_counter = 0;
	while (trials++ <= max_no_of_iter &&		// number of trials should not exceed this number *can be removed*
		last_seq_index < process_num &&			// if seq_arr is full then we are done here
		zero_flag_counter <= process_num) {		// if no process found suitable after one full loop then break

		if (done_process_arr[i] == 1) {			//already taken
			i = (i + 1) % process_num; zero_flag_counter++; continue;
		}

		// Check if suitable
		flag = true;
		for (int j = 0; j < res_num; j++)
			if (need_arr[i][j] > avilable_res_arr[j]) { flag = false; break; }

		if (flag) {  // TRUE WHEN SUITABLE PROCESS CAN ASSIGN RESOURCES
			zero_flag_counter = 0;
			seq_arr[last_seq_index] = i;
			//			cout << "P" << i << "\t" << "last_seq_index" << last_seq_index << endl; //testing
			//			for(int k=0; k<process_num; k++) cout<<done_process_arr[k] << "\t";  //testing
			for (int j = 0; j < res_num; j++)   //UPDATE AVAILABLE RESOURCES
				avilable_res_arr[j] += allocation_arr[i][j];
			done_process_arr[i] = 1;       //MARK AS DONE
			last_seq_index++;
		}
		else zero_flag_counter++;

		i = (i + 1) % process_num;       //PREPARE NEXT PROCESS FOR THE ALGORITHM
	}

	if (all_done(done_process_arr, process_num)){
		cout << "\n\n*** THE SYSTEM IS SAFE ***\nTHE SAFE SEQUENCE IS:" << endl;
		for (int j = 0; j < process_num; j++)
			cout << "P" << seq_arr[j] << "\t";
		cout << endl;
	}
	else {
		cout << "\n\n* THE SYSTEM IS NOT SAFE SO NO VALID SEQUENCE *" << endl;
	}

	return 0;
}

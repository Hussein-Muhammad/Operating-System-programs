
/*
By:
	Abdullah Ibrahim Ahmad Abdou		
	Hussien Mohamed Elsayed Ibrahim		
*/

#include <iostream>     /*		cin , cout		*/
#include <stdlib.h>     /*		srand, rand		*/

using namespace std;
void FIFO(int* sequence, int seq_len, int frames);
void LRU(int* sequence, int seq_len, int frames);
void MRU(int* sequence, int seq_len, int frames);
void LFU(int* sequence, int seq_len, int frames, int pages);
void MFU(int* sequence, int seq_len, int frames, int pages);
void OPT(int* sequence, int seq_len, int frames);
void SC(int* sequence, int seq_len, int frames);

class myqueue
{
private:
	int *arr;
	int front, rear;
	int size, counter;

public:
	myqueue(int alt_size, int* parr = NULL) {
		size = alt_size;
		if (parr == NULL){
			arr = new int[size];
			front = rear = 0;
			counter = 0;
		}
		else{
			arr = parr;
			front = rear = 0;
			counter = alt_size;
		}
	}
	void enque(int item) {
		arr[rear] = item;
		rear = (rear + 1) % size;
		counter++;
	}
	int deque() {
		counter--;
		int temp = arr[front];
		front = (front + 1) % size;
		return temp;
	}
	bool is_empty(void) { return(counter == 0); }
	bool is_full(void) { return(counter == size); }
	int get(int index) { return arr[index]; }
	void set(int index, int data) { arr[index] = data; }
	void print_circular(void) {
		for (int i = 0; i < counter; i++) cout << "\t" << arr[(i + front) % size];
		cout << endl;
	}
	void print(void) {
		for (int i = 0; i < counter; i++) cout << "\t" << arr[i];
		cout << endl;
	}
	bool HasItem(int item) {
		for (int i = 0; i < counter; i++) if (arr[(i + front) % size] == item)  return true;
		return false;
	}
	int indexOf(int item){
		for (int i = 0; i < counter; i++) if (arr[(i + front) % size] == item) return i;
		return -1;
	}
};

class mystack{
private:
	int *arr, size, top;

public:
	mystack(int a_size)
	{
		size = a_size;
		arr = new int[size];
		top = 0;
	}
	void push(int n) { arr[top++] = n; }
	int pop(void) { return arr[--top]; }
	int rev_pop(void) { return pop_at(0); }
	bool isfull(void)  { return top == size; }
	bool isempty(void) { return top == 0; }
	int get_actual_size(void) { return top; }
	int get(int index) { return arr[index]; }
	void set(int index, int data) { arr[index] = data; }
	bool HasItem(int item) {
		for (int i = 0; i < top; i++) if (arr[i] == item) return true;
		return false;
	}
	int indexOf(int item){
		for (int i = 0; i < top; i++) if (item == arr[i]) return i;
		return -1;
	}
	int pop_at(int index){
		int temp = get(index);
		top--;
		for (int i = index; i < top; i++) arr[i] = arr[i + 1];
		return temp;
	}
};

int main()
{
	int SEQ_LEN, SRAND, PAGES, FRAMES;
	int choice;
	cout << "Enter the following:\nSequence length, No. of pages, No. of frames, Seed number\n";
	cin >> SEQ_LEN >> PAGES >> FRAMES >> SRAND;
	cout << "\nChoose the method you want to use:\n1. First In First Out (FIFO)\n2. Least Recently Used (LRU)\n"
		"3. Most Recently Used (MRU)\n4. Least Frequently Used (LFU)\n5. Most Frequently Used (MFU)\n6. Second-chance\n"
		"7. Optimal\n8. All\nYour choice: ";
	cin >> choice;
	
	int* Seq = new int[SEQ_LEN];
	cout << "\nThe random sequence is:";
	srand(SRAND);
	for (int i = 0; i < SEQ_LEN; i++){
		Seq[i] = rand() % PAGES;
		cout << " " << Seq[i];
	}
	cout << endl;

	switch (choice){
	case 1:
		FIFO(Seq, SEQ_LEN, FRAMES);
		break;
	case 2:
		LRU(Seq, SEQ_LEN, FRAMES);
		break;
	case 3:
		MRU(Seq, SEQ_LEN, FRAMES);
		break;
	case 4:
		LFU(Seq, SEQ_LEN, FRAMES, PAGES);
		break;
	case 5:
		MFU(Seq, SEQ_LEN, FRAMES, PAGES);
		break;
	case 6:
		SC(Seq, SEQ_LEN, FRAMES);
		break;
	case 7:
		OPT(Seq, SEQ_LEN, FRAMES);
		break;
	case 8:
		FIFO(Seq, SEQ_LEN, FRAMES);
		LRU(Seq, SEQ_LEN, FRAMES);
		MRU(Seq, SEQ_LEN, FRAMES);
		LFU(Seq, SEQ_LEN, FRAMES, PAGES);
		MFU(Seq, SEQ_LEN, FRAMES, PAGES);
		SC(Seq, SEQ_LEN, FRAMES);
		OPT(Seq, SEQ_LEN, FRAMES);
		break;
	}

	return 0;
}

void FIFO(int* sequence, int seq_len, int frames){
	myqueue seq_q(seq_len, sequence);
	myqueue frame_q(frames);
	int movements = 0; int temp;
	cout << "\n================== FIFO ==================\n";
	while (!seq_q.is_empty()){
		temp = seq_q.deque();
		cout << " " << temp << ":";
		if (frame_q.HasItem(temp)){
			cout << endl;
		}
		else if (!frame_q.is_full()){
			frame_q.enque(temp);
			frame_q.print();
			movements++;
		}
		else {
			frame_q.deque();
			frame_q.enque(temp);
			frame_q.print();
			movements++;
		}
	}
	cout << "Total miss = " << movements << endl;
}

void LRU(int* sequence, int seq_len, int frames){
	myqueue seq_q(seq_len, sequence);
	myqueue frame_q(frames);
	mystack recent_st(frames);
	int movements = 0; int temp;
	cout << "\n================== LRU ==================\n";
	while (!seq_q.is_empty()){
		temp = seq_q.deque();
		cout << " " << temp << ":";
		if (frame_q.HasItem(temp)){
			cout << endl;
		}
		else if (!frame_q.is_full()){
			frame_q.enque(temp);
			frame_q.print();
			movements++;
		}
		else {
			frame_q.set(frame_q.indexOf(recent_st.rev_pop()), temp);
			frame_q.print();
			movements++;
		}

		if (!recent_st.HasItem(temp)) recent_st.push(temp);
		else { recent_st.pop_at(recent_st.indexOf(temp)); recent_st.push(temp); }
	}
	cout << "Total miss = " << movements << endl;
}

void MRU(int* sequence, int seq_len, int frames){
	myqueue seq_q(seq_len, sequence);
	myqueue frame_q(frames);
	int most_recent;
	int movements = 0; int temp;
	cout << "\n================== MRU ==================\n";
	while (!seq_q.is_empty()){
		temp = seq_q.deque();
		cout << " " << temp << ":";
		if (frame_q.HasItem(temp)){
			cout << endl;
		}
		else if (!frame_q.is_full()){
			frame_q.enque(temp);
			frame_q.print();
			movements++;
		}
		else {
			frame_q.set(frame_q.indexOf(most_recent), temp);
			frame_q.print();
			movements++;
		}
		most_recent = temp;
	}
	cout << "Total miss = " << movements << endl;
}

void LFU(int* sequence, int seq_len, int frames, int pages){
	myqueue seq_q(seq_len, sequence);
	myqueue frame_q(frames);
	mystack recent_st(pages);
	mystack counter(pages);
	int movements = 0; int temp;
	cout << "\n================== LFU ==================\n";
	while (!seq_q.is_empty()){
		temp = seq_q.deque();
		cout << " " << temp << ":";
		if (frame_q.HasItem(temp)){
			cout << endl;
		}
		else if (!frame_q.is_full()){
			frame_q.enque(temp);
			frame_q.print();
			movements++;
		}
		else {
			int minIndex = -1, minCount = seq_len, recent_st_actual_size = recent_st.get_actual_size();
			for (int i = 0; i < recent_st_actual_size; i++)
				if (frame_q.HasItem(recent_st.get(i)) && counter.get(i) < minCount) { minIndex = i; minCount = counter.get(i); }
			frame_q.set(frame_q.indexOf(recent_st.get(minIndex)), temp);
			frame_q.print();
			movements++;
		}

		if (!recent_st.HasItem(temp)) { recent_st.push(temp); counter.push(1); }
		else {
			int index = recent_st.indexOf(temp);
			recent_st.push(recent_st.pop_at(index)); counter.push(counter.pop_at(index) + 1);
		}
	}
	cout << "Total miss = " << movements << endl;
}

void MFU(int* sequence, int seq_len, int frames, int pages){
	myqueue seq_q(seq_len, sequence);
	myqueue frame_q(frames);
	mystack recent_st(pages);
	mystack counter(pages);
	int movements = 0; int temp;
	cout << "\n================== MFU ==================\n";
	while (!seq_q.is_empty()){
		temp = seq_q.deque();
		cout << " " << temp << ":";
		if (frame_q.HasItem(temp)){
			cout << endl;
		}
		else if (!frame_q.is_full()){
			frame_q.enque(temp);
			frame_q.print();
			movements++;
		}
		else {
			int maxIndex = -1, maxCount = -1, recent_st_actual_size = recent_st.get_actual_size();
			for (int i = 0; i < recent_st_actual_size; i++)
				if (frame_q.HasItem(recent_st.get(i)) && counter.get(i) > maxIndex) { maxIndex = i; maxCount = counter.get(i); }
			frame_q.set(frame_q.indexOf(recent_st.get(maxIndex)), temp);
			frame_q.print();
			movements++;
		}

		if (!recent_st.HasItem(temp)) { recent_st.push(temp); counter.push(1); }
		else {
			int index = recent_st.indexOf(temp);
			recent_st.push(recent_st.pop_at(index)); counter.push(counter.pop_at(index) + 1);
		}
	}
	cout << "Total miss = " << movements << endl;
}

void SC(int* sequence, int seq_len, int frames){
	myqueue seq_q(seq_len, sequence);
	myqueue frame_q(frames);
	mystack fifo_st(frames);
	mystack ref_bit(frames);
	int movements = 0; int temp;
	cout << "\n================== SC ==================\n";
	while (!seq_q.is_empty()){
		temp = seq_q.deque();
		cout << " " << temp << ":";
		if (frame_q.HasItem(temp)){
			ref_bit.set(fifo_st.indexOf(temp), 1);
			cout << endl;
		}
		else if (!frame_q.is_full()){
			frame_q.enque(temp);
			fifo_st.push(temp); ref_bit.push(0);
			frame_q.print();
			movements++;
		}
		else {
			int i;
			for (i = 0; i < frames; i++) if (ref_bit.get(i)) ref_bit.set(i, 0); else break;
			frame_q.set(frame_q.indexOf(fifo_st.pop_at(i)), temp); ref_bit.pop_at(i);
			fifo_st.push(temp); ref_bit.push(0);
			frame_q.print();
			movements++;
		}
	}
	cout << "Total miss = " << movements << endl;
}

void OPT(int* sequence, int seq_len, int frames){
	myqueue seq_q(seq_len, sequence);
	myqueue frame_q(frames);
	int movements = 0; int temp;
	cout << "\n================== OPT ==================\n";
	while (!seq_q.is_empty()){
		temp = seq_q.deque();
		cout << " " << temp << ":";
		if (frame_q.HasItem(temp)){
			cout << endl;
		}
		else if (!frame_q.is_full()){
			frame_q.enque(temp);
			frame_q.print();
			movements++;
		}
		else {
			int index, maxFrameIndex = -1, maxSeqIndex = -1;
			bool flag = true;
			for (int i = 0; i < frames; i++){
				index = seq_q.indexOf(frame_q.get(i));
				if (index == -1) { frame_q.set(i, temp); flag = false; break; }
				else if (index > maxSeqIndex) { maxFrameIndex = i; maxSeqIndex = index; }
			}
			if (flag) frame_q.set(maxFrameIndex, temp);
			frame_q.print();
			movements++;
		}
	}
	cout << "Total miss = " << movements << endl;
}
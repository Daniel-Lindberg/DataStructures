#include <iostream>
#include <string>
#include <cmath>
//Authors:Daniel Lindberg, Bao Do, Alex Davis
using namespace std;

int Comparisons = 0;
void print_array(int array[], int size){

	cout<< endl;
	int j;
	for (j=0; j<size;j++)
		for (j=0; j<size;j++)
			cout <<" "<< array[j];
	cout << endl;
}//end of print_array


void mySwap(int& num1, int& num2){
	int temp = num1;
	num1 = num2;
	num2 = temp;
}


void insertion_sort(int arr[], int min,int max) {
	int i, j ,tmp;
	int length = max - min;
	for (i = min; i < length+min; i++) {
		j = i;
		Comparisons++;
		while (j > 0 && arr[j - 1] > arr[j]) {
			tmp = arr[j];
			Comparisons++;
			arr[j] = arr[j - 1];
			arr[j - 1] = tmp;
			j--;
		}//end of while loop
	}//end of for loop
}//end of insertion_sort.


void BubbleSort(int arr[],int min, int max)
{
	int numLength = max-min;
	int i, j, flag = 1;
	int temp;
	for(i = 1; (i <= numLength) && flag; i++)
	{
		flag = 0;
		for (j=min; j < (numLength -1+min); j++)
		{
			Comparisons++;
			if (arr[j+1] < arr[j])
			{
				temp = arr[j];             // swap elements
				arr[j] = arr[j+1];
				arr[j+1] = temp;
				flag = 1;
			}
		}
	}

}

void merge(int* input, int p, int r)
{
	int mid = floor((p + r) / 2);
	int i1 = 0;
	int i2 = p;
	int i3 = mid + 1;

	// Temp array
	int temp[r-p+1];
	// Merge in sorted form the 2 arrays
	while ( i2 <= mid && i3 <= r ){
		Comparisons++;
		if ( input[i2] < input[i3] )
		{

			temp[i1++] = input[i2++];
		}
		else
		{
			temp[i1++] = input[i3++];
		}
	}
	// Merge the remaining elements in left array
	while ( i2 <= mid ){
		temp[i1++] = input[i2++];
	}
	// Merge the remaining elements in right array
	while ( i3 <= r ){
		temp[i1++] = input[i3++];
	}
	// Move from temp array to master array
	for ( int i = p; i <= r; i++ ){
		input[i] = temp[i-p];
	}
}

void merge_sort(int* input, int p, int r)
{

	if ( p < r )
	{
		int mid = floor((p + r) / 2);
		merge_sort(input, p, mid);
		merge_sort(input, mid + 1, r);
		merge(input, p, r);
	}
}





void QuickSort(int myArray[], int min, int max){
	int pivot = myArray[(min + max) / 2];

	int left = min, right = max;
	while (left < right) {
		while (myArray[left] < pivot) {
			Comparisons++;
			left++;
		}
		while (myArray[right] > pivot) {
			Comparisons++;
			right--;
		}
		if (left <= right) {
			mySwap(myArray[left], myArray[right]);
			left++;
			right--;
		}
	}
	if (min < right) {
		QuickSort(myArray, min, right);
	}
	if (left < max) {
		QuickSort(myArray, left, max);
	}
}


void HybridSort(int myArray[], string large, string small, int t, int min, int max){
	bool Bubble = false;
	bool quick = false;
	if (small.find("bb") != std::string::npos){
		Bubble = true;
	}
	if (large.find("uic") != std::string::npos){
		quick = true;
	}
	if (quick){   //quickSort section
		if ((max - min) > t){

			int pivot = myArray[(min + max) / 2];

			int left = min, right = max;

			while (left < right) {
				while (myArray[left] < pivot) {
					Comparisons++;
					left++;
				}
				while (myArray[right] > pivot) {
					right--;
					Comparisons++;
				}

				if (left <= right) {
					mySwap(myArray[left], myArray[right]);
					left++;
					right--;
				}
			}

			if (min < right) {
				HybridSort(myArray,large,small,t, min, right);
			}
			if (left < max) {
				HybridSort(myArray,large,small,t, left, max);
			}
		} else {
			if (Bubble){
				BubbleSort(myArray,min,max);
				//cout<< "quickBub";
			}else {
				insertion_sort(myArray,min,max);
				//cout << "quickInsert";
			}

		}
	} else { //hybrid merge sort section
		if ( (max-min) > t)
		{
			int mid = floor((min + max) / 2);
			HybridSort(myArray,large,small,t, min, mid);
			HybridSort(myArray,large,small,t, mid + 1, max);
			merge(myArray, min, max);
		}
		else
		{
			if(Bubble)
			{
				BubbleSort(myArray,min,max+1);
				//cout<< "MergeBub" ;
			}
			else
			{
				insertion_sort(myArray,min,max+1);
				///cout << "MergeInsert";
			}
		}
	}
}


int main()
{


	//Commented out so we could test and produce results for write up
	//     This is the part that asks user for information
	//	int Threshold;
	//	int size;
	//	int random;
	//	int display;
	//	string large;
	//	string small;
	//
	//	cout << "Please enter the Threshold value:" << endl;
	//	cin >> Threshold;
	//	cout << "Please enter the size of your list" << endl;
	//	cin >> size;
	//	int b[size];
	//	if (size > 100){
	//		srand((unsigned)time(NULL));
	//		for (int i = 0; i < size; i++) {
	//			b[i] = 1+ rand() % 1000;
	//		}
	//		display = 0;
	//	} else {
	//		cout <<"please enter 0 if you would like to enter the list or 1 to randomly generate one" << endl;
	//				cin >> random;
	//		if(random == 1){
	//			srand((unsigned)time(NULL));
	//			for (int i = 0; i < size; i++) {
	//				b[i] = 1+ rand() % 1000;
	//			}
	//		} else {
	//			for(int i = 0; i < size; i++){
	//				cout << "Please enter value number " << i+1 <<":" << endl;
	//			    cin>> b[i];
	//			}
	//		}
	//		cout << "Please enter a 1 if you would like the list displayed and 0 if not" << endl;
	//		cin >> display;
	//	}
	//	while(large != "MergeSort" || large!= "QuickSort"){
	//		cout << "What sort would you like to use when the size of the array is larger then the threshold? Please enter Exactly (MergeSort or QuickSort)" << endl;
	//		cin >> large;
	//	}
	//	while(small != "BubbleSort" || small!= "Insertion")
	//	cout << "What sort would you like to use when the size of the array is smaller then the threshold? (BubbleSort or InsertionSort)" << endl;
	//	cin >> small;
	//
	//	HybridSort(b,large,small,Threshold);
	//
	//
	//
	//	if(display) {
	//		print_array(b,size);
	//	}
	//
	//
	int size = 50;
	int b[size];
	for (int z = 8; z < 17; z++) {

		cout<< "Threashold set at: " << z << endl;
		for (int i = 0; i < size; i++) {
			b[i] = 1+ rand() % 1000;
		}


		HybridSort(b,"Quick Sort","Bubble Sort", z, 0, size);
		for (int i = 0; i < size; i++) {
			b[i] = 1+ rand() % 1000;
		}
		cout << "Comparsions of quick and bubble: " << Comparisons << endl;


		Comparisons=0;
		HybridSort(b,"Merge Sort","Insertion Sort", z, 0, size);
		for (int i = 0; i < size; i++) {
			b[i] = 1+ rand() % 1000;
		}

		cout << "Comparsions of merge and insertion: " << Comparisons << endl;


		Comparisons=0;
		HybridSort(b,"Quick Sort","Insertion Sort", z, 0, size);
		for (int i = 0; i < size; i++) {
			b[i] = 1+ rand() % 1000;
		}

		cout << "Comparsions of quick and Insertion: " << Comparisons << endl;
		Comparisons=0;
		HybridSort(b,"Merge Sort","Bubble Sort", z, 0, size);
		cout << "Comparsions of merge and bubble: " << Comparisons << endl;

	 }

	return 0;
}

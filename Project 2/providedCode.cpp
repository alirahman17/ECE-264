// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2018

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
  unsigned int val1;
  unsigned int val2;
  char val3;
  string val4;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename.c_str());
  if (!input) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->val1 >> pData->val2 >> pData->val3 >> pData->val4;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename.c_str());
  if (!output) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << endl;

  // Write the data
  for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
    output << (*ipD)->val1 << " "
	   << (*ipD)->val2 << " "
	   << (*ipD)->val3 << " "
	   << (*ipD)->val4 << endl;
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &, int field);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  cout << "Data loaded.  Executing sort..." << endl;

  int field = 0;
  cout << "Enter an integer from 1 - 4, representing field to sort: ";
  try {
    cin >> field;
    if (field < 1 || field > 4) {
      cerr << "Error: invalid field" << endl;
      exit(1);
    }
  }
  catch (...) {
    cerr << "Error: invalid field" << endl;
    exit(1);
  }

  clock_t t1 = clock();
  sortDataList(theList, field);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

list<Data *>::iterator i, notsorted, lastsorted, next_sort, later_sorted;

const int RUN = 32;

void insertionSort(list<Data *> &l){
  i = l.begin();
  for (i++; i != l.end(); i++){
    notsorted = i;
    lastsorted = i; lastsorted--;
    while ((*notsorted)->val1 < (*lastsorted) ->val1  && notsorted != l.begin()){
      iter_swap(notsorted--, lastsorted--);
    }
  }
}


int getMax(list<Data *> &l){
    i = l.begin();
    int mx = (*i)->val3;
    for (i = l.begin(); i != l.end(); i++){
      if ((*i)->val3 > mx)
          mx = (*i)->val3;
    }
    return mx;
}

void countSort(list<Data *> &l, int exp){
  vector<Data *> vi(l.size());
  int count[10] = {0};
  for (i = l.begin(); i != l.end(); i++){
    count[(((*i)->val3)/exp)%10]++;
  }
  for (int k = 1; k < 10; k++){
    count[k] += count[k - 1];
  }
  int n = 1;
  i = l.end();
  i--;
  while (n){
    vi[count[(((*i)->val3)/ exp) % 10] - 1] = (*i);
    count[ (((*i)->val3)/exp)%10 ]--;
    if(i == l.begin()){
      break;
    }
    i--;
  }
  list<Data *> new_list(vi.begin(), vi.end());
  l.swap(new_list);
}

void RadixSort(list<Data *> &l){
  int m  = getMax(l);
  for (int exp = 1; m/exp > 0; exp *= 10)
      countSort(l, exp);
}

void merge(vector<Data *> &v, int start, int m, int r){
  int x, y, z;
  int n1 = m - start + 1;
  int n2 = r - m;
  vector<Data *> Left(n1);
  vector<Data *> Right(n2);
  for(x = 0; x < n1; x++){
    Left[x] = v[start + x];
  }
  for(y = 0; y < n2; y++){
    Right[y] = v[m + 1 + y];
  }
  x = 0;
  y = 0;
  z = start;
  while(x < n1 && y < n2){
    if(Left[x]->val1 <= Right[y]->val1){
      v[z] = Left[x];
      x++;
    } else{
      v[z] = Right[y];
      y++;
    }
    z++;
  }
  while(x < n1){
    v[z] = Left[x];
    x++;
    z++;
  }
  while(y < n2){
    v[z] = Right[y];
    y++;
    z++;
  }
}

void mergeSort(vector<Data *> &v, int start, int r){
  if (start < r){
      int m = start+(r-start)/2;
      mergeSort(v, start, m);
      mergeSort(v, m+1, r);
      merge(v, start, m, r);
    }
}

void timSort(list<Data *> &l){
  int nt = l.size() - 1;
}

bool cmp2(const Data* a1, const Data* a2){
  return(a1->val2 < a2->val2);
}


bool cmp4(const Data* a1, const Data* a2){
  return(a1->val4 < a2->val4);
}

void sortDataList(list<Data *> &l, int field) {
  // Fill in this function
  if(field == 1){
    vector<Data *> v{ make_move_iterator(begin(l)), make_move_iterator(end(l)) };
    int vsize = v.size();
    /*mergeSort(v, 0, vsize - 1);
    list<Data *> newList(v.begin(), v.end());
    l.swap(newList);*/
    insertionSort(l);
  } else if(field == 2){
    vector<Data *> v{ make_move_iterator(begin(l)), make_move_iterator(end(l)) };
    stable_sort(v.begin(), v.end(), cmp2);
    list<Data *> newList(v.begin(), v.end());
    l.swap(newList);
  } else if(field == 3){
    RadixSort(l);
  } else if(field == 4){
    vector<Data *> v{ make_move_iterator(begin(l)), make_move_iterator(end(l)) };
    stable_sort(v.begin(), v.end(), cmp4);
    list<Data *> newList(v.begin(), v.end());
    l.swap(newList);
  }
}

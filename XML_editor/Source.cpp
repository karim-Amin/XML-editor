#include<iostream>
#include<stack>
#include<queue>
#include<fstream>
#include<iterator>
#include<string>
#include<vector>
using namespace std;
// Global varaibles
queue<string> correct_tag_same;// to overwrite the wrong data by the correct one in the same line
queue <int> line_num_same;//to know the location of the error
queue<int> modif_index_same;// to specify the modification index in the same line
//--------------------------------------------------------------------------------------
queue<string> correct_tag_outline;
queue <int> line_num_outline;
//--------------------------------------------------------------------------------------
// Functions
vector <string> read_xml_file() {
	fstream  file;
	vector <string> v;
	string s;
	file.open("test.xml", ios::in);
	if (file.is_open()) {
		cout << "the file is opened"<<endl;
		while (getline(file, s)) {
			v.push_back(s);
		}
		file.close();
		return v;
		
	}
	else {
		cout << "error when opening the file";
		exit(1);
	}
	
}
vector<string> fix_outline(vector<string> xml_data) {
	while (!line_num_outline.empty()) {
		string old;
		old = xml_data[line_num_outline.front()-1];
		xml_data[line_num_outline.front()-1] = old+"</" + correct_tag_outline.front() + ">";
		correct_tag_outline.pop(); line_num_outline.pop();
	}
	return xml_data;
}
vector<string> fix_inline(vector <string> xml_data) {
	
	while (!line_num_same.empty()) {
		int length = 0;// to know the length of the wrong tag to erase it
		int lineNum = line_num_same.front();
		int wrong_index = modif_index_same.front();
		modif_index_same.pop();
		line_num_same.pop();
		string wrong_line = xml_data[lineNum];
		// finding the length of the wrong tag
		for (int i = wrong_index; i < wrong_line.size(); i++) {
			if (wrong_line[i] != ' ' && wrong_line[i] != '>')
				length++;
		}
		// erase the wrong tag
		xml_data[lineNum].erase(wrong_index,length+1);
		// write the correct one 
		xml_data[lineNum] += correct_tag_same.front() + '>';
		correct_tag_same.pop();
	}
	return xml_data;
}
vector<string> fix_expersion_error(vector<string> xml_data) {
	stack<char> exp;
	int start_index;
	int length = 0;
	for (int i = 0; i < xml_data.size(); i++) {
		string xml_line = xml_data[i];
		int line_size = xml_line.size();
		if (xml_line[line_size - 1] != '>'&& xml_line[line_size - 1] != '\t') {
			cout << "there is experssion error in line " << i<<endl;
			int count = line_size - 1;
			while (xml_line[count] != '>') {
				length++;
				exp.push(xml_line[count]);
				count--;
			}
			start_index = count+1;
			// erase the expersion
			xml_data[i].erase(start_index, length);
		}
	}
	return xml_data;
}
void detect_syn_error(vector<string> xml_data) {
	stack <string>  tag_stack;
	stack <int> line_index;
	//vector<string> xml_data = data;//make a copy to be able to fix the error in the source code
	int index = 0;// to know the number of the line where you are
	string xml_line;// get line by line
	
	for(int k=0;k < xml_data.size();k++) {
		xml_line = xml_data[k]; 
		for (int i = 0; i < xml_line.size(); i++) {
			// pushing in the stack
			if (xml_line[i] == '<' && xml_line[i + 1] != '!' && xml_line[i + 1] != '?' && xml_line[i + 1] != '/') {
				string tag;
				int j = i+1;// to cut the chars of the tag;
				while (xml_line[j] != ' '&& xml_line[j] != '>') {
					tag += xml_line[j];
					j++;
				}
				tag_stack.push(tag);
				line_index.push(index);
			}
			//poping from the stack
			else if (xml_line[i] == '<' && xml_line[i + 1] == '/') {
				string tag;
				int j = i + 2;
				while (xml_line[j] != ' ' && xml_line[j] != '>') {
					tag += xml_line[j];
					j++;
				}
				if (tag_stack.top() == tag) {
					tag_stack.pop();
					line_index.pop();
				}
				//if you are in the same line
				else if(line_index.top()==index) {
					cout << "there is wrong closing tag in the line : " << index << endl;
					cout << "the correction is </" << tag_stack.top()<<">"<< endl;
					correct_tag_same.push(tag_stack.top());
					line_num_same.push(index);
					tag_stack.pop();
					line_index.pop();
					modif_index_same.push(i + 2);//save the start address of the wrong tag
				}
			}

		}
		//check if the string is empty
		// missing closing tag case
		int line_size = xml_line.size();
		if (line_size != 0) {
			if ( xml_line[line_size - 1] == '\t'&& !tag_stack.empty()) {
				correct_tag_outline.push(tag_stack.top());
				tag_stack.pop();
				line_num_outline.push(index);
				cout << "there is missing closed tag at line :" << index ;
				cout <<" the correction is :</" <<correct_tag_outline.front() <<">"<< endl;
				
			}
		}
		else if (index == xml_data.size() - 1) {
			correct_tag_outline.push(tag_stack.top());
			tag_stack.pop();
			line_num_outline.push(index);
			cout << correct_tag_outline.front();
			cout << index;
		}
		index++;
		
	}
}
void Create_correct_xml_file(vector<string> xml_data) {
	fstream file;
	file.open("corrected_structure.xml", ios::out);

	// If no file is created, then
	// show the error message.
	if (file)
	{
		cout << "File created successfully.";
		for (int i = 0; i < xml_data.size(); ++i) {

			file<< xml_data[i] << endl; 
		}
	}
	else {
		cout << "Error in creating file!!!";
	}
	file.close();
}
int main() {

	vector<string> xml_data;
	xml_data = read_xml_file();
	detect_syn_error(xml_data);
	xml_data=fix_expersion_error(xml_data);
	xml_data = fix_outline(xml_data);
	xml_data = fix_inline(xml_data);
	//Create_correct_xml_file(xml_data);
	for (int i = 0; i < xml_data.size(); i++) {
		cout << xml_data[i] << endl;
	}
	return 0;
	return 0;
}

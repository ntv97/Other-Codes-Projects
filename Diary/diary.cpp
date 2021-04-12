// Nhi Vo
#include <chrono> 
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <thread> 
#include <vector>

#define MAX_PAGES 250
#define MAX_LINES 49

using namespace std;

ifstream in_diary;
ofstream out_diary;
string username, password, filename;
int page_num, line_num;

class Page {
public:
	Page() {
		string page = to_string(page_num);
                if (page_num < 10) page += " ";
                lines[0] = "                   +-------------------------------------------------------------------------------------------------+\n\0";
                lines[48] = "                   +-------------------------------------------------------------------------------------------------+            N.) Next page\n\0";
                lines[10] = "                10 |                                                                                                 |            A.) Go to line: \n\0";
                lines[11] = "                11 |                                                                                                 |            B.) Edit -- 1.) Word  2.) Line\n\0"; // max char = 97 
                lines[12] = "                12 |                                                                                                 |                                  * 97 max chars/line *\n\0";
                lines[13] = "                13 |                                                                                                 |            C.) Go to page: \n\0";
                lines[14] = "                14 |                                                                                                 |            D.) Save \n\0";
                lines[15] = "                15 |                                                                                                 |            E.) Exit -- 1.) Main Page  2.) Exit Program\n\0";

                int i;
                for (i = 1; i < 10; i++)
                        lines[i] = "                 " + to_string(i) + " |                                                                                                 |\n\0";
                for (i = 16; i < 47; i++)
                        lines[i] = "                " + to_string(i) + " |                                                                                                 |\n\0";
                if (page_num < 99) lines[47] = "                47 |                                                                                              " + page + " |\n\0";
                else lines[47] = "                47 |                                                                                             " + page + " |\n\0";
	}
	Page(int random) {
		string buffer;
                for (int i = 0; i < 49; i++) {
                        getline(in_diary, buffer);
                        if (buffer == "*") {
				i--;
				continue;
			}
                        lines[i] = buffer + '\n';
                }	
	}
	virtual ~Page(void) {}
	string& get_line(int num) {
		return lines[num];
	}
	void print() {
		for (int i = 0; i < MAX_LINES; i++)
			cout << lines[i];
	}
	void add(int page_num);
	void TOC() {
		
	}
	void edit_line() {
		cout << "                What do you want to write on line " << line_num << "?\n                ";
		string& line = lines[line_num];
		string message;
		cout << "    ";
		std::cin.ignore(INT_MAX, '\n');
		getline(cin, message);
		int message_len = message.length();
		int j;
		for (int i = 20, j = 0; i < 117 && j < message_len; i++, j++) {
			if (message[j] == '\t') { 
				int k = 8;
				while (k>=0) {
					if ( i > 116 ) break;
					line[i++] = ' ';
					k--;
				}
			} else { line[i] = message[j]; }
		}
		this->print();
		if (j < message_len - 1) cout << "                Message overflowed\n";
	}
	bool edit_word() {
		int choice, index = 20;
		string word, end, temp;
		string& line = lines[line_num];
		temp = lines[line_num];
		cout << "                Enter word or phrase to edit: ";
		std::cin.ignore(INT_MAX, '\n');
		getline(cin, word); 
		int idx = line.find(word);
		if (idx == string::npos) {
			cout << "                Line does not contain \"" << word << "\"." << endl;
			return false;
		}
		string new_word;
		cout << "                What do you want to change " << word << " to? ";
		getline(cin, new_word);
		int upper_idx = idx + new_word.length();
		int i, j;
		if (117 - upper_idx < 0) //upper_idx = 117;
			cout << "                Not enough space on the line to make change. Maximum number of characters is 97.\n";
		else
			for (i = idx, j = 0; i < upper_idx; i++, j++) {
				if (new_word[j] == '\t') {
					int k = 8;
					while (k>=0) {
						cout << "message " << j << " " << new_word[j] << endl;
						cout << "line " << i << " " << line[i] << endl;
						if ( i >= upper_idx ) break;
						line[i++] = ' ';
						k--;
					}
				} else { line[i] = new_word[j]; }
			}
		cout << "line[line_num]: " << lines[line_num] << endl;
		this->print();
		 if (j < new_word.length() - 1) cout << "                Message overflowed\n";
		return true;
	}
	void write() {
		for (int i = 0; i < 49; i++) {
			out_diary << lines[i];
		}
		out_diary << "*\n\0";
		
	}
	void parse() {
		string buffer;
		int i;
		for (i = 0; i < 49; i++) {
			getline(in_diary, buffer);
			if (buffer == "*") return;
			lines[i] = buffer + '\n';
		}
			
	}

protected:
	string lines[MAX_LINES]; // 119 chars
};

class Menu : public Page {
public:
	Menu(string title) {
                lines[0] = "                   +-------------------------------------------------------------------------------------------------+\n\0";
                lines[1] = "                   |                                           " + title + "                                              |\n\0";
                lines[2] = "                   |                                          -----------                                            |\n\0";
                lines[15] = "                   |                                         A.) Login                                               |\n\0";
                lines[16] = "                   |                                     B.) Create a New Diary                                      |\n\0";
                lines[48] = lines[0];
                int i;
                for (i = 3; i < 10; i++) 
                        lines[i] = "                   |                                                                                                 |\n\0";
                for (i = 10; i < 15; i++)
                        lines[i] = "                   |                                                                                                 |\n\0";
                for (i = 17; i < 48; i++) 
                        lines[i] = "                   |                                                                                                 |\n\0";
        }
	virtual ~Menu(void) {}
	char display_options() {
		char choice;
		this->print();
		while (true) {
        	        cout << "                   Enter A or B: ";
                	cin >> choice;
                	choice = toupper(choice);
                	if (choice == 'A' || choice == 'B') break;
        	}
        	cout << "               ";
        	if (choice == 'A') cout << "\n                    ...Trying to log in..." << endl << endl;
		else cout << "               ...Create a new diary..." << endl << endl;
		return choice;
	}
	void create(string& username, string& password) {
		cout << "\n                     **MAX CHAR LENGTH FOR USER AND PASS == 10 CHARS**\n" << endl;
		cout << "                 ~ Enter desired username\n";
		cout << "                   Username: ";
        	cin >> username;
        	while (username.length() > 10) {
               		cout << "                              Username must be 10 characters or less.\n";
                	cout << "                   Username: ";
                	cin >> username;
        	}
		cout << "\n                 ~ Enter desired password\n";
        	cout << "                   Password: ";
        	cin >> password;
        	while (password.length() > 10) {
                	cout << "                              Password must be 10 characters or less.\n";
                	cout << "                   Password: ";
                	cin >> password;
        	}
		ofstream new_diary(username+password+".txt");
		cout << "\n                    ... Diary created with username: " << username << "... " << endl; 
		std::this_thread::sleep_for (std::chrono::seconds(2));
	}
	bool login() {
		do {
			cout << "\n                   Username: ";
			cin >> username;
			if (username == "q") 
				return false;
			while (username.length() > 10) {
				cout << "                              Wrong username, try again..\n";
				cout << "\n                   Username: ";
				cin >> username;
			}
			if (username == "q") return false;
			cout << "\n                   Password: ";
			cin >> password;
			while (password.length() > 10) {
				cout << "                              Wrong password, try again..\n";
				cout << "\n                   Password: ";
				cin >> password;
			}
			filename = username+password+".txt";
			in_diary.open(filename);
			if (!in_diary) cout << "\n                   Login does not exist, try again. Press q to go back to home page. \n";
		} while (!in_diary);
		cout << "\n                    ... Logging in ..." << endl;
                std::this_thread::sleep_for (std::chrono::seconds(2));
		in_diary.close();
		return true;
	}
	void Menu_A() {
		while(true) {
                        if (!this->login())
                                if (this->display_options() == 'A')
                                        continue;
				else
					Menu_B();
			else 
				break;
                }
		// after loggin in show table of contents
	}
	void Menu_B() {
		this->create(username, password);
                //this->display_options();
                cout << endl;
	}
};

class CoverPage : public Page {
	CoverPage() : Page() {
		int i;
		lines[0] = "                   +-------------------------------------------------------------------------------------------------+\n";
                //lines[1] = "                 1 |                                                                                                 |\n";
                lines[48] = "                   +-------------------------------------------------------------------------------------------------+            N.) Next page\n";
		lines[47] = "                   |                                                                                                |\n";
                lines[10] = "                   |                                                                                                 |            A.) Go to line \n";
                lines[11] = "                   |                                                                                                 |            B.) Edit \n"; // max char = 97 
                for (i = 2; i < 10; i++)
			lines[i] = lines[47];
                for (i = 12; i < 47; i++)
			lines[i] = lines[47];
                lines[19] = "                   |                                            M y                                                  |\n";
                lines[20] = "                   |                                         D i a r y                                               |\n";
	}
	

};

class Diary {
public:
	Diary(string diary_file) {
		in_diary.open(diary_file);
		if (in_diary.peek() == std::ifstream::traits_type::eof()) {
			for (page_num = 0; page_num < MAX_PAGES; page_num++)
				pages.push_back(Page());

		} else {
			for (page_num = 0; page_num < MAX_PAGES; page_num++)
				pages.push_back(Page(1));

		}
		pages[0].print();
		page_num = 0;
		in_diary.close();
	}
	char get_command() {
		//cout << "                Enter A, B, C, D, E or N: " ;
                char choice;
		string s_choice;
//		std::cin.ignore(INT_MAX, '\n');
                int option;
		while (true) {
			cout << "                Enter A, B, C, D, E or N: " ;
			cin >> choice;
			choice = toupper(choice);
			if (choice != 'A' && choice != 'B' && choice != 'C' && 
				choice != 'D' && choice != 'E' && choice != 'N') {
                                //cout << "                Invalid line number, try again." << endl;
                                cin.clear();
                                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                continue;
                        } else {
                                        break;
                        }

		}
                //cin >> choice;
		//choice = toupper(choice);
		//while (choice != 'A' && choice != 'B' && choice != 'C' && 
	//		choice != 'D' && choice != 'E' && choice != 'N') {
/*		do {
			cout << "                Enter A, B, C, D, E or N: " ;
			getline(cin, s_choice);
			//choice = toupper(choice);
			s_choice. erase(remove(s_choice.begin(), s_choice.end(), ' '), s_choice.end());
			choice = toupper(s_choice[0]);
		} while ((choice != 'A' && choice != 'B' && choice != 'C' && 
                      choice != 'D' && choice != 'E' && choice != 'N') || (s_choice.length() > 1));
*/
		return choice;
	}
	void current_page(int num);
	void save() {
		cout << "                Saved.\n";
	}
	void change_page(int num) {
		pages[num].print();
	}
	void exit() { 
		char response;
		cout << "                Would you like to save?\n"; 
		cout << "                Enter 'Y' to save, otherwise enter any key to exit without saving: ";
		cin >> response;
		response = toupper(response);
		if (response == 'Y') this->choice_d();
		cout << "                Bye. \n"; 
	}// reset all the lines
	void choice_a(string& line) {
		Page& current_page = this->pages[page_num];
		string str_num;
		//cin.ignore(1,'\n');
		while(true) {
			cout << "                Only select lines in [1, 46]." << endl;
			cout << "                Which line # ? ";
			cin >> line_num;
			if (!cin || line_num < 1 || line_num > 46) {
				cout << "                Invalid line number, try again." << endl;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			} else {
					break;	
			}
		}
		line = current_page.get_line(line_num);
		cout << line.substr(0, 118) << endl;
	} // go to line
	int choice_b(string& line) {
		int option;
		cout << "                To edit: " << endl;
		choice_a(line);
		while(true) {
			cout << "                Select 1 to edit a word, or 2 to rewrite the whole line: ";
			cin >> option;
			if (!cin || (option != 1 && option != 2)) {
                                cout << "                Invalid option, try again." << endl;
				cin.clear(); // reset failbit
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                continue;
                        }
                        break;
                        
                }
		return option;
	}
	void choice_c() {
		string s_num;
		std::cin.ignore(INT_MAX, '\n');
		cout << "                Which page? ";
		getline(cin, s_num);
		s_num.erase(remove(s_num.begin(), s_num.end(), ' '), s_num.end());
		try {
			page_num = stoi(s_num);
		} catch(const std::invalid_argument&) {
			cout << "                Sorry, page does not exist.\n";
			return;
		}
		if (page_num < 0 || page_num > 249) {
			cout << "                Sorry, page does not exist.\n";
			return;
		}
		pages[page_num].print();
	}
	void choice_d() {   // save
		out_diary.open(filename);
		for (page_num = 0; page_num < MAX_PAGES; page_num++) {
			pages[page_num].write();
		}
		out_diary.close();
		cout << "                Saved.\n";
		
	}
	int choice_e() {
		int choice;
		cout << "                Press 1 to go main page, or 2 to exit program: ";
		cin >> choice;
		if (!cin || (choice != 1 && choice != 2)) {
			cout << "                Invalid option.\n";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return -1;
		}
		return choice;
	}
	void choice_n() { 
		if (page_num > 249) {
			cout << "No more pages.\n";
			return;
		}
		page_num++;
		pages[page_num].print();
	}	
	Page& get_page() {
		return pages[page_num];
	}
	~Diary(void); 

private:
	CoverPage coverpage();
	//std::vector<Page> toc;
	std::vector<Page> pages; 
};

void open_diary(Menu& menu) {
	while (menu.display_options() == 'B')
                menu.Menu_B();
	menu.Menu_A();
}

Diary *diary;
int main() {
	char choice;
	Menu menu("My Diary");
	menu.print();
	string username, password;
	open_diary(menu);
	//Diary *diary = new Diary(filename);
	diary = new Diary(filename);
	char command;
	//command = diary->get_command();
	string current_line;
	 do {
		command = diary->get_command();
		switch (command) {
			case 'A':
				diary->choice_a(current_line); // replace line number
				break;
			case 'B':
			{
				ofstream file(filename);
				Page& page =  diary->get_page();
				//int option =  diary->choice_b(current_line);
				//cout << option << endl;
				if (diary->choice_b(current_line) == 2) {
					page.edit_line();
				} else {
					page.edit_word();
				}
				break;
			}
			case 'C':
				diary->choice_c();
				break;
			case 'D':
				diary->choice_d();
				break;
			case 'E':
			{
				int option = diary->choice_e();
				if (option == 1) {
					menu.print();
					//open_diary(menu);
					
				} else if (option == 2) { 
					diary->exit();
					return 0;
				}
			}
				break;
			case 'N':
				diary->choice_n();
				break;
			//default:
		};
	} while (command != 'q');


	return 0;
}

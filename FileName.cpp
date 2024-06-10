#include<iostream>
#include<conio.h>
#include<string>
#include<string.h>
#include<cstring>
#include<cstdio>    // used for the rename function we have used 
#include<iomanip>
#include<fstream>
#include<algorithm> // For shuffle
#include<random>    // For random device and default_random_engine
#include<chrono>  // For the timer 
#include<Windows.h>




#define RESET   "\033[0m" // Resets the previous colour 
#define RED     "\033[31m"      // Red 
#define GREEN   "\033[32m"      // Green 
#define YELLOW  "\033[33m"      // Yellow 
#define BLUE    "\033[34m"      // Blue 
#define MAGENTA "\033[35m"      // Magenta 
#define CYAN    "\033[36m"      // Cyan 
#define WHITE   "\033[37m"      // White 


using namespace std;
const int MAX_STUDENTS = 100;
const int MAX_QUESTIONS = 100;
const int MAX_CHOICES = 4;

struct StudentCredential {
	string id;
	string password;
};
struct Question {
	string text;
	string choices[MAX_CHOICES];
	int correctAnswer;
};

// Structure For the quiz. It is a nested Structure 
struct Quiz {
	string name; // Name of the quiz or subject 
	int numQuestions; // We have specified the value to 100 but it 
	Question questions[MAX_QUESTIONS];
};
void storeadminCredentials(string username, string password);
void deleteStudentCredentials(string student_id);
bool authenticateAdmin(string auth_username, string auth_pass) {
	ifstream file;
	file.open("admin_credentials.txt", ios::in);

	if (file.is_open()) 
	{
		string username, password;
		while (file >> username >> password)
		{
			if (username == auth_username && password == auth_pass) 
			{
				file.close();
				return true; // authenticated successfully
			}
		}
		file.close();
		return false; // authentication failed
	}
	else 
	{
		cout << "Unable to open file." << endl;
		return false; // authentication failed
	}
}
bool authenticate(StudentCredential credentials[], int numStudents, string auth_username, string auth_pass) {
	bool authenticated = false;

		for (int i = 0; i < numStudents; i++) 
		{
			if (credentials[i].id == auth_username && credentials[i].password == auth_pass) 
			{
				authenticated = true;
				break;
			}
		}
		if (authenticated) 
		{
			cout << GREEN << "\t\t\t\t\t\t\t\t\t-----------  Authentication successful.  ----------" << RESET << endl;
			return true ;
		}
		else 
		{
			return false ;
		}
	


	
}
void storestudentCredentials(const StudentCredential* credentials, int numStudents);
void readCredentials(StudentCredential credentials[], int& numStudents);
string get_password() {
	string password;
	char ch;


	while ((ch = _getch()) != '\r') 
	{ // Enter key pressed
		if (ch == '\b')  // Backspace key pressed 
		{ 
			if (!password.empty()) 
			{
				cout << "\b \b";  //  prints a backspace, space, and another backspace to effectively erase the last character on the screen. Basically This is to erase the last character on screen not from the string
				password.pop_back();  //  removes the last character from the password string.

			}
		}
		else 
		{
			password.push_back(ch);  // adds the character to the password string. IT appends .
			cout << '*';
		}
	}

	
	cout << endl;
	return password;
}
void createQuiz();
// Function to Delete a quiz File and its name from the file that contains all quizzes names 
void deleteQuiz(string deletequiz);
// Function to shuffle questions
void shuffleQuestions(Quiz& quiz);
// Function to list available quizzes
void listQuizzes();
// Function to take a quiz
void takeQuiz();
// Function to view scores
void viewScores(); 



int main()
{
	int user;
	int user1;
	int user2;
	int attempts = 0;
	int count = 0;
	int numStudents = 0;
	string line;
	string username; // for student
	string password; // for student
	string auth_username; // for admin
	string auth_password; // for admin 
	string student_id;
	string student_pass;
	string delete_student_id;
	StudentCredential credentials[100];

adminmenu:

	cout << GREEN << "\t\t\t\t\t\t\t\t\t==============================================" << RESET <<  endl;
	cout << GREEN << "\t\t\t\t\t\t\t\t\t       Welcome to Examination System      " << RESET << endl;
	cout << GREEN << "\t\t\t\t\t\t\t\t\t==============================================" << RESET << endl;

cout << "\t\t\t\t\t\t\t\t\t----------------- Main Menu -----------------" << endl;
cout << "\t\t\t\t\t\t\t\t\t1. Admin" << endl;
cout << endl;
cout << "\t\t\t\t\t\t\t\t\t2. Student" << endl;
cout << endl;
cout << "\t\t\t\t\t\t\t\t\t0. Exit" << endl;
cout << endl;

cout << "\t\t\t\t\t\t\t\t\t----------------------------------------------" << endl;
cout << endl;
cout << endl;
cout << YELLOW  << "\t\t\t\t\t\t\t\t\tProceed by selecting an option number ->>> " << RESET ;
cin >> user;
if (user == 0)
{
	exit(0);
}

if (user != 1 && user != 2)
{
	system("CLS");
	cout <<RED << "\t\t\t\t\t\t\t\t\t---------- Invalid entry Try again ----------" <<RESET << endl;

	goto adminmenu;
}

switch (user)
{
case 1:
	count = 3;
adminauthenticatemenu:
	cout << endl;
	cout << CYAN << "\t\t\t\t\t\t\t\t\tEnter admin username: " << RESET ;
	cout << GREEN;
	cin >> auth_username;
	cout << RESET;
	cout << endl;
	cout << CYAN <<  "\t\t\t\t\t\t\t\t\tEnter admin password: " << RESET  ;
	auth_password = get_password(); 

	if (authenticateAdmin(auth_username, auth_password))
	{
		system("cls");
		cout << GREEN  << "\t\t\t\t\t\t\t\t\t               Authentication successful.        "  << RESET << endl;

	}
	else
	{
		cout << endl;
		cout << RED  << "\t\t\t\t\t\t\t\t\tAuthentication failed.You Have " << count << " ateempts left !!!" << RESET << endl;

		count--;

		if (count < 0 )
		{
			cout << "\t\t\t\t\t\t\t\t\tProgram will exit ";
			_getch();
			exit(0);
		}
		else
			goto adminauthenticatemenu;



	}
menu:
	cout << "\t\t\t\t\t\t\t\t\t----------------" << BLUE << "   Admin Menu   " << RESET  << "----------------- "  << endl;
	cout << endl;
	cout << "\t\t\t\t\t\t\t\t\t 1 : Register New Admin " << endl;
	cout << "\t\t\t\t\t\t\t\t\t 2 : Register a student   " << endl;
	cout << "\t\t\t\t\t\t\t\t\t 3 : View All students enrolled" << endl;
	cout << "\t\t\t\t\t\t\t\t\t 4 : Delete a student entry " << endl;
	cout << "\t\t\t\t\t\t\t\t\t 5 : Make a quiz " << endl;
	cout << "\t\t\t\t\t\t\t\t\t 6 : View Scores of students ." << endl;
	cout << "\t\t\t\t\t\t\t\t\t 7 : Delete A Quiz ." << endl;
	cout << "\t\t\t\t\t\t\t\t\t 0 : TO GO BACK  " << endl;
input:
	cout << endl; 
	cout << YELLOW << "\n\t\t\t\t\t\t\t\t\tSelect A Valid option : " << RESET;
	do {
		
		cin >> user1;
		if (user1 < 0 || user1 >8)
		{
			cout << RED << "\t\t\t\t\t\t\t\t\tInvalid option selected . Try again " << RESET << endl;
			
				goto input;


		}
		if (user1 == 1)
		{
			do
			{
				cout << endl;
				cout << GREEN << "\t\t\t\t\t\t\t\t\tEnter username: "<< RESET ;
				cin >> username;
				cout <<GREEN << "\t\t\t\t\t\t\t\t\tEnter password: " << RESET ;
				cin >> password;
				cout << GREEN << "\t\t\t\t\t\t\t\t\tIf You Want To Stop Press '0' OR Press any other key to Continue :" << RESET;
				cin >> user1;
				storeadminCredentials(username, password);
			} while (user1 != 0);
		label:
			cout << endl;
			cout << YELLOW << "\t\t\t\t\t\t\t\t\tEnter 0 to exit or 1 to go back  " << RESET;
			cin >> user1;
			if (user1 == 0)
			{
				exit(0);
			}
			if (user1 == 1)
			{
				system("CLS");
				goto menu;
			}
			else
				cout << RED << " \t\t\t\t\t\t\t\t\tInvalid Entry Try Again " << RESET;
			goto label;
		}


		if (user1 == 2)
		{
			StudentCredential credentials[MAX_STUDENTS];
			while (true)
			{
				cout << GREEN << "\t\t\t\t\t\t\t\t\tEnter student ID (or 'e' to finish): " << RESET ;
				cin >> student_id;

				if (student_id == "e")
				{
					break;
				}

				cout << GREEN << "\t\t\t\t\t\t\t\t\tEnter password: " << RESET ;
				cin >> student_pass;

				credentials[numStudents].id = student_id;
				credentials[numStudents].password = student_pass;
				numStudents++;

			}
			storestudentCredentials(credentials, numStudents);
		

		label2:
			cout << endl;
			cout << YELLOW << "\t\t\t\t\t\t\t\t\tEnter 0 to exit or 1 to go back  " << RESET;
			cin >> user1;
			if (user1 == 0)
			{
				exit(0);
			}
			if (user1 == 1)
			{
				system("CLS");
				goto menu;
			}
			else
				cout << RED << "\t\t\t\t\t\t\t\t\tInvalid Entry Try Again " << RESET ;
				goto label2;


		}
		if (user1 == 3)
		{
			cout << endl; 
			cout << endl;
			readCredentials(credentials, numStudents);
			for (int i = 0; i < numStudents; i++)
			{
				cout << GREEN << "\t\t\t\t\t\t\t\t\tSTUDENT NO. " << YELLOW << i + 1 << GREEN << "  ID  : " << RESET << credentials[i].id << endl;
				cout <<GREEN  <<"\t\t\t\t\t\t\t\t\tSTUDENT PASSWORD   : " << RESET << credentials[i].password << endl;
			}
			label3: 
			cout << endl;
			cout << YELLOW << "\t\t\t\t\t\t\t\t\tEnter 0 to exit or 1 to go back  " << RESET;
			cin >> user1;
			if (user1 == 0)
			{
				exit(0);
			}
			if (user1 == 1)
			{
				system("CLS");
				goto menu;
			}
			else
				cout << RED << "\t\t\t\t\t\t\t\t\tInvalid Entry Try Again " << RESET;
				goto label3;

		}

		if (user1 == 4)
		{

			cout << YELLOW  << "\t\t\t\t\t\t\t\t\tEnter student ID to delete: " <<  RESET ;
			cin >> delete_student_id;
			deleteStudentCredentials(delete_student_id);

		label4:
			cout << endl;
			cout << YELLOW << "\t\t\t\t\t\t\t\t\tEnter 0 to exit or 1 to go back  " << RESET;
			cin >> user1;
			if (user1 == 0)
			{
				exit(0);
			}
			if (user1 == 1)
			{
				system("CLS");
				goto menu;
			}
			else
				cout << RED << "\t\t\t\t\t\t\t\t\tInvalid Entry Try Again " << RESET;
				goto label4;

		}
		if (user1 == 5)
		{
			createQuiz();

		label5:
			cout << endl;
			cout << YELLOW << "\t\t\t\t\t\t\t\t\tEnter 0 to exit or 1 to go back  " << RESET;
			cin >> user1;
			if (user1 == 0)
			{
				exit(0);
			}
			if (user1 == 1)
			{
				system("CLS");
				goto menu;
			}
			else
				cout << RED << "\t\t\t\t\t\t\t\t\tInvalid Entry Try Again " << RESET;
				goto label5;

		}
		if (user1 == 6)
		{
			viewScores();
		label6:
			cout << endl;
			cout << YELLOW << "\t\t\t\t\t\t\t\t\tEnter 0 to exit or 1 to go back  " << RESET;
			cin >> user1;
			if (user1 == 0)
			{
				exit(0);
			}
			if (user1 == 1)
			{
				system("CLS");
				goto menu;
			}
			else
				cout << RED << "\t\t\t\t\t\t\t\t\tInvalid Entry Try Again " << RESET;
			goto label6;

		}
		if (user1 == 7)
		{
			listQuizzes();
			string  delete_quiz;
			cout << YELLOW << "\t\t\t\t\t\t\t\t\tEnter Name of Quiz you want to delete : " << RESET ;
			cin >> delete_quiz   ;
			deleteQuiz(delete_quiz);
		label7:
			cout << endl;
			cout << YELLOW << "\t\t\t\t\t\t\t\t\tEnter 0 to exit or 1 to go back  " << RESET;
			cin >> user1;
			if (user1 == 0)
			{
				exit(0);
			}
			if (user1 == 1)
			{
				system("CLS");
				goto menu;
			}
			else
				cout << RED << "\t\t\t\t\t\t\t\t\tInvalid Entry Try Again " << RESET;
			goto label7;

		}



		if (user1 == 0)
		{
			system("CLS ");
			goto adminmenu;
		}
		
	} while (user1 != 0);
case 2:
	count = 3; 
	label1 : 
	cout << GREEN << "\t\t\t\t\t\t\t\t\tEnter student username provided : " << RESET ;
	cin >> username;
	cout << GREEN <<"\t\t\t\t\t\t\t\t\tEnter student password provided : " << RESET ;
	password = get_password();
	readCredentials(credentials, numStudents);
	system("CLS"); 
	bool check = authenticate(credentials, numStudents, username, password);
	if(check )
	{
		while (true)
		{
			studentmenu : 
			cout << "\t\t\t\t\t\t\t\t\t----------------" << MAGENTA  << "   Student Menu   " << RESET  << "----------------- " << endl;
			cout << endl;
			cout << YELLOW << "\t\t\t\t\t\t\t\t\tSelect any option :\n";
			cout << endl; 
			cout << "\t\t\t\t\t\t\t\t\t1 : Take Test " << endl;
			cout << endl;
			cout << "\t\t\t\t\t\t\t\t\t2 : View Score Board  " << endl;
			cout << endl;
			cout << "\t\t\t\t\t\t\t\t\t0 : Back " << endl;
		input1:
			cout << endl;
			cout << endl;
			cout << YELLOW << "\t\t\t\t\t\t\t\t\tSELECT A VALID OPTION :    " << RESET;
			
			cin >> user2;
			if (user2 < 0 || user2 >2)
			{
				
				cout << RED << "\t\t\t\t\t\t\t\t\tInvalid option selected . Try again " << RESET << endl;

				goto input1;


			}
			
			switch (user2)
			{
			case 1:
			{
				cout << "\t\t\t\t\t\t\t\t\tBEST OF LUCK " << endl;
				{
					for (int i = 0; i < numStudents; i++)
					{
						if (credentials[i].id == username)
						{
							takeQuiz();


						}
					}
					break;
				}
			label8:
				cout << endl;
				cout << YELLOW << "\t\t\t\t\t\t\t\t\tEnter 0 to exit or 1 to go back  " << RESET;
				cin >> user2;
				if (user2 == 0)
				{
					exit(0);
				}
				if (user2 == 1)
				{
					system("CLS");
					goto studentmenu ;
				}
				else
					cout << RED << "\t\t\t\t\t\t\t\t\tInvalid Entry Try Again " << RESET;
				goto label8;


			}
			case 2:
			{
				viewScores();
			label9:
				cout << endl;
				cout << YELLOW << "\t\t\t\t\t\t\t\t\tEnter 0 to exit or 1 to go back  " << RESET;
				cin >> user1;
				if (user1 == 0)
				{
					exit(0);
				}
				if (user1 == 1)
				{
					system("CLS");
					goto studentmenu;
				}
				else
					cout << RED << "\t\t\t\t\t\t\t\t\tInvalid Entry Try Again " << RESET;
				goto label9;

			}
			case 0:
			{
				system("CLS");
				goto adminmenu;
			}

			}

		}
	}
	else
	{
		cout << RED << "\t\t\t\t\t\t\t\t\t--------Invalid username or password. You Have " << count << " attempts left. --------" << RESET << endl;
		count--;
		if (count < 0)
		{
			exit(0);
		}
		if (count >= 0 && count <= 3)
		{
			goto label1;
		}
		
	}
}

}


void storeadminCredentials(string username, string password) {
	ofstream file;
	file.open("admin_credentials.txt", ios ::app);

	if (file.is_open())
	{
		file << username << endl;
		file << password << endl;
		file.close();
		cout << "\t\t\t\t\t\t\t\t\tCredentials stored successfully." << endl;
	}
	else
	{
		cout << "\t\t\t\t\t\t\t\t\tUnable to open file." << endl;
	}
}


void storestudentCredentials(const StudentCredential* credentials, int numStudents) {
	ofstream file;
	file.open("student_credentials.txt", ios::app);

	if (file.is_open()) 
	{
		for (int i = 0; i < numStudents; i++)
		{
			file << credentials[i].id << "\n";
			file << credentials[i].password << "\n";
		}
		file.close();
		cout << "\t\t\t\t\t\t\t\t\tCredentials stored successfully." << endl;
	}
	else 
	{
		cout << "\t\t\t\t\t\t\t\t\tUnable to open file." << endl;
	}
}





void readCredentials(StudentCredential credentials[], int& numStudents) {
	ifstream finput("student_credentials.txt");
	string id, password;
	numStudents = 0;

	while (finput >> id >> password)
	{
		credentials[numStudents].id = id;
		credentials[numStudents].password = password;

		numStudents++;
	}
}
void deleteStudentCredentials(string student_id) 
{
	fstream input_file("student_credentials.txt", ios::in);
	fstream temp_file("temp_file.txt", ios::out); 

	if (input_file.is_open() && temp_file.is_open()) 
	{
		string line;
		bool skip_next_line = false;
		while (getline(input_file, line)) 
		{
			if (line == student_id) 
			{
				skip_next_line = true;
			}
			else if (!skip_next_line) 
			{
				temp_file << line << endl;
			}
			else 
			{
				skip_next_line = false;
			}
		}
		input_file.close();
		temp_file.close();

		remove("student_credentials.txt");
		rename("temp_file.txt", "student_credentials.txt");
		cout << "Student credentials deleted successfully." << endl;
	}
	else 
	{
		cout << "Error opening files." << endl;
	}
}
void createQuiz() {
	Quiz quiz;
	cout << GREEN << "\t\t\t\t\t\t\t\t\tEnter the name of the quiz: " << RESET;
	cin >> quiz.name;
	cout << endl;
	cout << GREEN << "\t\t\t\t\t\t\t\t\tEnter the number of questions: " << RESET;
	cin >> quiz.numQuestions;
	cin.ignore(); // To ignore the newline character after entering the number

	for (int i = 0; i < quiz.numQuestions; ++i)
	{
		cout << GREEN << "Enter the text of question " << RESET << YELLOW << i + 1 << ": " << RESET;
		getline(cin, quiz.questions[i].text);
		cout << endl;
		for (int j = 0; j < MAX_CHOICES; ++j) 
		{
			cout << "Enter choice " << j + 1 << " for question " << i + 1 << ": ";
			getline(cin, quiz.questions[i].choices[j]);
		}

		cout << "Enter the correct answer (1-" << MAX_CHOICES << ") for question " << i + 1 << ": ";
		cin >> quiz.questions[i].correctAnswer;
		cin.ignore(); // To ignore the newline character after entering the number
	}

	// Save quiz to a file
	ofstream outFile(quiz.name + ".txt");
	outFile << quiz.name << endl;
	outFile << quiz.numQuestions << endl;
	for (int i = 0; i < quiz.numQuestions; ++i) 
	{
		outFile << quiz.questions[i].text << endl;
		for (int j = 0; j < MAX_CHOICES; ++j) {
			outFile << quiz.questions[i].choices[j] << endl;
		}
		outFile << quiz.questions[i].correctAnswer << endl;
	}
	outFile.close();

	// Update the list of quizzes
	ofstream quizzesFile("quizzes.txt", ios::app);
	quizzesFile << quiz.name << ".txt" << endl;
	quizzesFile.close();

	cout << GREEN << "Quiz saved successfully!" << RESET << endl;
}
void takeQuiz() 
{
	// List available quizzes first
	listQuizzes();

	string quizName;  // user entered name / his selection
	cout << YELLOW << "\t\t\t\t\t\t\t\t\tEnter the exact name of the quiz to load: " << RESET ;
	cin >> quizName;

	ifstream inFile(quizName + ".txt");
	if (!inFile)
	{
		cout << "\t\t\t\t\t\t\t\t\tQuiz file not found!" << endl;
		return;
	}

	Quiz quiz;
	inFile >> quiz.name;
	inFile >> quiz.numQuestions;
	inFile.ignore(); // To ignore the newline character after entering the number

	for (int i = 0; i < quiz.numQuestions; ++i)
	{
		getline(inFile, quiz.questions[i].text);
		for (int j = 0; j < MAX_CHOICES; ++j)
		{
			getline(inFile, quiz.questions[i].choices[j]);
		}
		inFile >> quiz.questions[i].correctAnswer;
		inFile.ignore(); // To ignore the newline character after entering the number
	}
	inFile.close();

	shuffleQuestions(quiz);

	cout << "\t\t\t\t\t\t\t\t\tQuiz loaded  successfully!" << endl;
	cout << "\t\t\t\t\t\t\t\t\tQuiz: " << quiz.name << endl;
	auto start_time = std::chrono::high_resolution_clock::now();
	int answer;
	string userName;
	cout << GREEN << "\t\t\t\t\t\t\t\t\tEnter your name: " <<  RESET ;
	cin >> userName;
	cin.ignore();
	int score = 0;
	for (int i = 0; i < quiz.numQuestions; ++i)
	{
		cout << YELLOW << "\t\t\t\t\t\t\t\t\tQ" << i + 1 << ": " << quiz.questions[i].text <<  RESET  << endl;
		for (int j = 0; j < MAX_CHOICES; ++j)
		{
			cout <<"\t\t\t\t\t\t\t\t\t" << j + 1 << ") " << quiz.questions[i].choices[j] << endl;
		}
		cin.ignore();
		do
		{
			
			cout << endl;
			cout << GREEN << "\t\t\t\t\t\t\t\t\tSelect your choice from  (1-" << MAX_CHOICES << "): " << RESET;

			cin >> answer;
			
			if (answer < 1 || answer > 4)
			{
				cout << RED << "\t\t\t\t\t\t\t\t\tInvalid Option Selected Try Again " << RESET << endl;
			}
			if (answer == quiz.questions[i].correctAnswer)
			{
				score++;
			}
			cout << endl;
		} while (answer < 1 || answer > 4);
	}
	auto end_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed_time = end_time - start_time;

	cout << "\t\t\t\t\t\t\t\t\tQuiz completed in " << GREEN << elapsed_time.count() << RESET << " seconds." << endl;
	cout << "\t\t\t\t\t\t\t\t\tYour score: " << YELLOW << score << RESET << " out of "  << GREEN << quiz.numQuestions << RESET << endl;

	// Save the scores to the file
	ofstream scoreFile("scores.txt", ios::app);
	if (scoreFile.is_open()) {
		scoreFile << userName << " " << quiz.name << " " << score << endl;
		scoreFile.close();
	}
	else {
		cout << "Unable to open scores file." << endl;
	}
	// Save the score
	
}
void viewScores() 
{
	ifstream scoreFile("scores.txt");
	if (!scoreFile)
	{
		cout << "\t\t\t\t\t\t\t\t\tNo scores recorded yet!" << endl;
		return;
	}

	string userName, quizName;
	int score;
	cout << GREEN << "\t\t\t\t\t\t\t\t\tRecorded Scores:" << RESET << endl;
	while (scoreFile >> userName >> quizName >> score)
	{
		cout << YELLOW << "\t\t\t\t\t\t\t\t\tUser: " << RESET << userName << YELLOW << ", Quiz: " << RESET << quizName << YELLOW << ", Score: " << RESET << score << endl;
	}
	scoreFile.close();
}
void listQuizzes()
{
	ifstream quizzesFile("quizzes.txt");
	if (!quizzesFile)
	{
		cout << "\t\t\t\t\t\t\t\t\tNo quizzes available!" << endl;
		return;
	}

	string quizName;
	cout << "\t\t\t\t\t\t\t\t\tAvailable Quizzes:" << endl;
	while (getline(quizzesFile, quizName))
	{
		cout <<"\t\t\t\t\t\t\t\t\t" << quizName.substr(0, quizName.find('.')) << endl; // Here substr means subtract string . For Example I have a quiz file named computer.txt So it will subtract computer from this and display it to the user .
	}
	quizzesFile.close();
}
void shuffleQuestions(Quiz& quiz)
{
	random_device rd;
	mt19937 g(rd());
	shuffle(quiz.questions, quiz.questions + quiz.numQuestions, g);
}
void deleteQuiz(string deletequiz)
{
	string appended_name;
	fstream quizFile("quizzes.txt", ios::in);
	fstream tempFile("temp_quiz.txt", ios::out);

	if (quizFile.is_open() && tempFile.is_open())
	{
		string quiz;
		bool found = false;
		while (getline(quizFile, quiz))
		{
			appended_name = deletequiz + ".txt";
			if (quiz == appended_name)
			{
				cout << "Quiz Deleted Successfully\n";
				found = true;
				continue;
			}
			else
			{
				tempFile << quiz << endl; // W
			}
		}
		if (!found)
		{
			cout << "Quiz not found.\n";
		}
	}
	else
	{
		cout << "Unable to open file\n";
		return;
	}


	quizFile.close();
	tempFile.close();

	// Remove the original quizzes file
	if (remove("quizzes.txt") != 0)
	{
		cout << "Error deleting original file";
	}
	else
	{
		// Rename the temp file to quizzes.txt
		if (rename("temp_quiz.txt", "quizzes.txt") != 0)
		{
			cout << "Error renaming temp file";
		}
	}

	// Remove the associated quiz file
	if (remove(appended_name.c_str()) != 0)
	{
		cout << "Error deleting appended quiz file";
	}
}
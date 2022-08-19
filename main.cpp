#include<iostream>
#include<string.h>
#include<vector>
using namespace std;
const string TEMPLATE_PATH = "./Templates";
const string PROJECT_PATH = "./Projects";

int run_command(string command){
	return system(command.c_str());
}

class Manager;
class Template;
class Project;

// ---------------------------------- Class Definitions ---------------------------------------------
class Manager{
private:
	string MAIN_PATH;
	vector<Project*> PROJECTS;
	vector<Template*> TEMPLATES;
	bool IS_RUNNING;
	int choice;
	enum{
		VIEW_PROJECTS,
		OPEN_PROJECT,
		CREATE_PROJECT,
		VIEW_TEMPLATES,
		OPEN_TEMPLATE,
		EXIT
	};
public:
	Manager();
	bool init();
	void ListProjects();
	void ListProjectTemplates();
	void OpenProject();
	void OpenProjectTemplate();
	void CreateNewProject();
	bool is_running();
	void run();
	void Exit();
};

class Template{
	private:
		string name;
		// the name of the project
		string path;
		// the location of the project
	public:
		Template(string template_name);
		// loads template with name "name" in the TEMPLATE_PATH folder
		void open();
		// opens the template
		string getName();
		// returns the name of the template
		string getPath();
		// returns the path of the temlate
};
class Project{
	private:
		string path;
		// the location of the project
		string name;
		// the name of the project
		Template* projectTemplate;
		// the template used for creating this project
	public:
		Project(string projectName);
		// Initialzes a project with name projectName and creates a folder in the current directory
		Project(string projectName, Template* projectTemplate);
		// Initialzes a project with name projectName and creates a folder in the current directory using the template useTemplate
		string getPath();
		// Returns the location of the project
		string getName();
		// Returns the name of the project
		void loadTemplate(Template* projectTemplate);
		// Copies all the files in the template useTemplate to the project
		void deleteProject();
		// Deletes the project completely, also removing the corresponding directory.

		void open();
		// Opens the project
};



// -------------------------------------- End of Class Deifinitions -----------------------------

// -------------------------------------- Class Method Definitions -----------------------------
Manager::Manager(){
	IS_RUNNING = 1;
}

bool Manager::is_running(){
	return IS_RUNNING;
}

bool Manager::init(){
	freopen("error.log", "w", stderr);
	cout << "************************ WELCOME TO PROJECT MANAGEER ************************" << endl;
	choice = 0;
	return 1;
}
void Manager::ListProjects(){
	cout << "--------------------------------\n";
	run_command("ls " + PROJECT_PATH);
	cout << "---------------------------------\n";
}
void Manager::ListProjectTemplates(){
	cout << "--------------------------------\n";
	run_command("ls " + TEMPLATE_PATH);
	cout << "---------------------------------\n";
}
void Manager::OpenProject(){
	cout << "Enter the name of project to open : " << endl;
	string name;
	cin >> name;
	Project p(name);
	p.open();
	return ;
}
void Manager::OpenProjectTemplate(){
	cout << "Enter the name of template to open : " << endl;
	string name;
	cin >> name;
	Template cur_template(name);
	cur_template.open();
}
void Manager::CreateNewProject(){
	cout << "Enter the name of the new project : " << endl;
	string name;
	cin >> name;
	cout << endl;
	cout << "Do you wish to use a template ? (Y / N) : " << endl;
	char flag;
	cin >> flag;
	if(flag == 'Y' || flag == 'y'){
		cout << "Enter the name of the template : " << endl;
		string template_name;
		cin >> template_name;
		PROJECTS.push_back(new Project(name, new Template(template_name)));
	}else if(flag == 'N' || flag == 'n'){
		PROJECTS.push_back(new Project(name));
	}else{
		cout << "Unknown Command : " << flag << endl;
		return ;
	}
	cout << "Project created : " << name << endl;
}
void Manager::run(){
	fflush(stdout);
	cout << "\n\n\n\n\n" << endl;
	cout << "Please select one of the below actions : " << endl;
	cout << "0. View Projects " << endl;
	cout << "1. Open project " << endl;
	cout << "2. Create new project " << endl;
	cout << "3. View project templates " << endl;
	cout << "4. Open project template " << endl;
	cout << "5. Exit" << endl;
	cin >> choice;
	switch(choice){
		case VIEW_PROJECTS:
			ListProjects();
			break;
		case OPEN_PROJECT:
			ListProjects();
			OpenProject();
			break ;
		case CREATE_PROJECT:
			CreateNewProject();
			break ;
		case VIEW_TEMPLATES:
			ListProjectTemplates();
			break ;
		case OPEN_TEMPLATE:
			ListProjectTemplates();
			OpenProjectTemplate();
			break ;
		case EXIT:
			Exit();
			break ;
		default:
			cout << "Unknown option : " << choice << endl;
	}
}
void Manager::Exit(){
	IS_RUNNING = false;
}

//-------------------------------------------------------------------------------------------------------------
Template::Template(string template_name)
{
	// loads the template at path
	name = template_name;
	path = TEMPLATE_PATH + "/" + name;
}

void Template::open(){
	// opens the template
	run_command("code " + path);
}
string Template::getName(){
	// returns the name of the template
	return name;
}
string Template::getPath(){
	// returns the path of the temlate
	return path;
}

//------------------------------------------------------------------------------------

Project::Project(string projectName){
	// Initialzes a project with name projectName and creates a folder in the current directory
	name = projectName;
	path = PROJECT_PATH + "/" + name;
	run_command("mkdir " + path);
}

Project::Project(string projectName, Template* projectTemplate){
	// Initialzes a project with name projectName and creates a folder in the current directory using the template useTemplate
	name = projectName;
	path = PROJECT_PATH + "/" + name;
	run_command("mkdir " + path);
	run_command("cp -r " + projectTemplate -> getPath() + "/*" + " " + path);
}
string Project::getPath(){
	// Returns the location of the project
	return path;
}
string Project::getName(){
	// Returns the name of the project
	return name;
}
void Project::loadTemplate(Template* projectTemplate){
	// Copies all the files in the template useTemplate to the project
	string command = "cp -r " + (projectTemplate -> getPath()) + " " + path;
	system(command.c_str());
}
void Project::deleteProject(){
	// Deletes the project completely, also removing the corresponding directory.
	string command = "rm " + path;
	system(command.c_str());
}

void Project::open(){
	// Opens the project
	run_command("code " + path);
	return ;
}


// ------------------------------------- End of Class Deifinitions ----------------------------------



// ---------------------- Main Code Begins From Here ---------------------------------------------------

void clear_screen(){
	system("clear");
}
int main(int argc, char* argv[]){
	Manager M;
	if(!M.init()){
		cout << "Something Went Wrong" << endl;
		return 0;
	}

	while(M.is_running()){
		M.run();
	}
	return 0;
}
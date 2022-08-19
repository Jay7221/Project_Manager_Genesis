#include<iostream>
#include<string.h>
#include<vector>
const std::string TEMPLATE_PATH = "./Templates";
const std::string PROJECT_PATH = "./Projects";

int run_command(std::string command){
	return system(command.c_str());
}

class Manager;
class Template;
class Project;

// ---------------------------------- Class Definitions ---------------------------------------------
class Manager{
private:
	std::string MAIN_PATH;
	std::vector<Project*> PROJECTS;
	std::vector<Template*> TEMPLATES;
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
		std::string name;
		// the name of the project
		std::string path;
		// the location of the project
	public:
		Template(std::string template_name);
		// loads template with name "name" in the TEMPLATE_PATH folder
		void open();
		// opens the template
		std::string getName();
		// returns the name of the template
		std::string getPath();
		// returns the path of the temlate
};
class Project{
	private:
		std::string path;
		// the location of the project
		std::string name;
		// the name of the project
		Template* projectTemplate;
		// the template used for creating this project
	public:
		Project(std::string projectName);
		// Initialzes a project with name projectName and creates a folder in the current directory
		Project(std::string projectName, Template* projectTemplate);
		// Initialzes a project with name projectName and creates a folder in the current directory using the template useTemplate
		std::string getPath();
		// Returns the location of the project
		std::string getName();
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
	std::cout << "************************ WELCOME TO PROJECT MANAGEER ************************\n";
	choice = 0;
	return 1;
}
void Manager::ListProjects(){
	run_command("ls " + PROJECT_PATH);
}
void Manager::ListProjectTemplates(){
	run_command("ls " + TEMPLATE_PATH);
}
void Manager::OpenProject(){
	std::cout << "Enter the name of project to open : " << std::endl;
	std::string name;
	std::cin >> name;
	Project p(name);
	p.open();
	return ;
}
void Manager::OpenProjectTemplate(){
	std::cout << "Enter the name of template to open : " << std::endl;
	std::string name;
	std::cin >> name;
	Template cur_template(name);
	cur_template.open();
}
void Manager::CreateNewProject(){
	std::cout << "Enter the name of the new project : " << std::endl;
	std::string name;
	std::cin >> name;
	std::cout << std::endl;
	std::cout << "Do you wish to use a template ? (Y / N) : " << std::endl;
	char flag;
	std::cin >> flag;
	if(flag == 'Y' || flag == 'y'){
		std::cout << "Enter the name of the template : " << std::endl;
		std::string template_name;
		std::cin >> template_name;
		PROJECTS.push_back(new Project(name, new Template(template_name)));
	}else if(flag == 'N' || flag == 'n'){
		PROJECTS.push_back(new Project(name));
	}else{
		std::cout << "Unknown Command : " << flag << std::endl;
		return ;
	}
	std::cout << "Project created with index : " << PROJECTS.size() - 1 << std::endl;
	std::cout << name << std::endl;
}
void Manager::run(){
	while(choice != EXIT){
		std::cout << "\n\n\n\n\n" << std::endl;
		std::cout << "Please select one of the below actions : " << std::endl;
		std::cout << "0. View Projects " << std::endl;
		std::cout << "1. Open existing project " << std::endl;
		std::cout << "2. Create new project " << std::endl;
		std::cout << "3. View project templates " << std::endl;
		std::cout << "4. Open project template " << std::endl;
		std::cout << "5. Exit" << std::endl;
		std::cin >> choice;
		switch(choice){
			case VIEW_PROJECTS:
				ListProjects();
				break;
			case OPEN_PROJECT:
				ListProjects();
				OpenProject();
				Exit();
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
				std::cout << "Unknown option : " << choice << std::endl;
		}
	}
}
void Manager::Exit(){
	IS_RUNNING = false;
}

//-------------------------------------------------------------------------------------------------------------
Template::Template(std::string template_name)
{
	// loads the template at path
	name = template_name;
	path = TEMPLATE_PATH + "/" + name;
}

void Template::open(){
	// opens the template
	run_command("code " + path);
}
std::string Template::getName(){
	// returns the name of the template
	return name;
}
std::string Template::getPath(){
	// returns the path of the temlate
	return path;
}

//------------------------------------------------------------------------------------

Project::Project(std::string projectName){
	// Initialzes a project with name projectName and creates a folder in the current directory
	name = projectName;
	path = PROJECT_PATH + "/" + name;
	run_command("mkdir " + path);
}

Project::Project(std::string projectName, Template* projectTemplate){
	// Initialzes a project with name projectName and creates a folder in the current directory using the template useTemplate
	name = projectName;
	path = PROJECT_PATH + "/" + name;
	run_command("mkdir " + path);
	run_command("cp -r " + projectTemplate -> getPath() + "/*" + " " + path);
}
std::string Project::getPath(){
	// Returns the location of the project
	return path;
}
std::string Project::getName(){
	// Returns the name of the project
	return name;
}
void Project::loadTemplate(Template* projectTemplate){
	// Copies all the files in the template useTemplate to the project
	std::string command = "cp -r " + (projectTemplate -> getPath()) + " " + path;
	system(command.c_str());
}
void Project::deleteProject(){
	// Deletes the project completely, also removing the corresponding directory.
	std::string command = "rm " + path;
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
		std::cout << "Something Went Wrong" << std::endl;
		return 0;
	}

	while(M.is_running()){
		M.run();
	}
	return 0;
}
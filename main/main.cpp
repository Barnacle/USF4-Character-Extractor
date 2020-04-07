#include "main.h"

using namespace usf4_ce; //the project name in your header file

[STAThreadAttribute]
int main(array<String ^> ^args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Application::Run(gcnew MainForm());
	return 0;
}

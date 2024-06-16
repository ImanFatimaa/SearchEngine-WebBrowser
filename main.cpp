//including header file for my form class that conatins design and logic
#include "MyForm.h"

using namespace System;
//use windows naespace std for windows form type
using namespace System::Windows::Forms;
//threading model for the application is single-threaded apartment
[STAThreadAttribute]

void main(array<String^>^ args) {
    //enable visual style for application
    Application::EnableVisualStyles();
    //to draw letters or words smoothly on windows
    Application::SetCompatibleTextRenderingDefault(false);
    //create an instance of my form defined in gui
    gui::MyForm form;
    //run application and display the window
    Application::Run(% form);
}

#include "Window.h"

using namespace System;

using namespace System::Windows::Forms;

[STAThread]

void main()

{

    Application::EnableVisualStyles();

    Application::SetCompatibleTextRenderingDefault(false);

    NAGGui::Window window;

    Application::Run(% window);

}

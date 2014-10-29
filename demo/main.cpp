#include "MainWindow.h"

#include <QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    
    MainWindow window;
    window.show();
    return app.exec();
}

#if defined(_WIN32) && defined(POCO_WIN32_UTF8) && !defined(POCO_NO_WSTRING)
	#ifdef UNICODE
			#error Cannot use unicode version
	#endif
	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nShowCmd)
	{
		return main(__argc, __argv);
	}

#endif

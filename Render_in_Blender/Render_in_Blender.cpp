// Render_in_Blender.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <fstream>

bool BatTest();
void MakeBat();
std::wstring GetFilePath();
void render_blend_file(const std::string& file_path);
void render_multiple_files(const std::vector<std::string>& file_list);
void errorHandle();



int main() {
    std::vector<std::string> file_list;

    errorHandle();
    // Prompt the user to select files
    while (true) {
        std::wstring file_path_wide = GetFilePath();
        if (file_path_wide.empty()) {
            break;
        }
        std::string file_path(file_path_wide.begin(), file_path_wide.end());
        file_list.push_back(file_path);
    }

    if (file_list.empty()) {
        std::cout << "No files selected." << std::endl;
        return 0;
    }

    render_multiple_files(file_list);

    return 0;
}

void errorHandle() {
    if (BatTest() == 0) {
        MakeBat();
        system("blender_path.bat");
    }
    
    
}

bool BatTest() {
    std::ifstream batFile("blender_path.bat");
    if (batFile.is_open())
    {
        std::cout << "Batch file found." << std::endl;
        batFile.close();
        return 1;
    }
    std::cout << "Batch file not found." << std::endl;
    return 0;

}

void MakeBat() {
    std::ofstream batFile("blender_path.bat");
    if (batFile.is_open())
    {

        
            
        

        
        batFile << "@echo off" << std::endl;
        batFile << "set /p blenderpath=Enter the path to the Blender executable:" << std::endl;
        batFile << "setx PATH \"%blenderpath%;%PATH%\"" << std::endl;
        //batFile << "echo." << std::endl;
        //batFile << "echo The Blender executable has been added to the system's path." << std::endl;
        batFile.close();
    }
    else
    {
        std::cout << "Unable to create batch file." << std::endl;
    }
}


//Open file explorer and return the path of the selected file
std::wstring GetFilePath()
{
    OPENFILENAMEW ofn;
    wchar_t szFileName[MAX_PATH] = L"";

    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = L"Blender Files (*.blend)\0*.blend\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = szFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

    if (GetOpenFileNameW(&ofn) == TRUE)
    {
        std::wcout << "Selected file: " << ofn.lpstrFile << std::endl;
        return std::wstring(ofn.lpstrFile);
    }
    else
    {
        return std::wstring();
    }
}

//Use blender to render the file
void render_blend_file(const std::string& file_path) {
    std::string cmd = "blender -b " + file_path + " -o //render_output -a ";
    int result = system(cmd.c_str());
    if (result != 0) {
        std::cerr << "Error rendering file: " << file_path << std::endl;
       
    }
}

//Render all the files in the list
void render_multiple_files(const std::vector<std::string>& file_list) {
    for (const auto& file_path : file_list) {
        render_blend_file(file_path);
    }
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

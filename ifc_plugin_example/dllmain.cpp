#include "../../sdk/ifc_plugin_api.h"

#include <vector>
#include <string>


using namespace std;

using viewer::ApiVersion;
using viewer::PluginInfo;
using viewer::PLUGIN_ID;

//---------------------------------------------------------------------------
// helper functions
//---------------------------------------------------------------------------

wstring get_dll_path(HMODULE dll)
{
    wstring     path;
    wchar_t     buf[MAX_PATH];

    GetModuleFileName(dll, buf, MAX_PATH);
    path = buf;

    const size_t    pos = path.rfind(L'\\');

    if(std::string::npos != pos)
        path = path.substr(0, pos);
    return path;
}


//---------------------------------------------------------------------------
// plugin code
//---------------------------------------------------------------------------

HMODULE     dll;    // handle to plugin dll
PLUGIN_ID   pid;
HWND        viewer_hwnd;


void CALL button_click()
{
    MessageBoxW(viewer_hwnd, L"Hello world!", L"Plugin", MB_OK);
}


//--------------------------------------------------------------------------
// plugin exports
//--------------------------------------------------------------------------

extern "C" //
{

PLUGINDECL void CALL get_api_verion(const ApiVersion *viewer, ApiVersion *plugin)
{
    plugin->major = API_VERSION_MAJOR;
    plugin->minor = API_VERSION_MINOR;

    if(viewer->major != API_VERSION_MAJOR || viewer->minor < API_VERSION_MINOR)
    {
        //plugin will be not loaded
    }
}


PLUGINDECL void CALL get_plugin_info(PluginInfo *info)
{
    info->name = L"template VS 2012";
    info->producer = L"Datacomp IT";
    info->www = L"bimvision.com.pl";
    info->email = L"contact@bimvision.com.pl";
    info->description = L"plugin template for Visual Studio 2012";
}


PLUGINDECL void CALL on_plugin_load(PLUGIN_ID pid, bool registered, HWND viewer_hwnd)
{
    ::pid = pid;
    ::viewer_hwnd = viewer_hwnd;

    wstring     data_path;
    wstring     file;

    // get path of plugin data
    data_path = get_dll_path(dll);
    data_path += L"\\ifc_plugin_example_data\\";


    // create buttom
    int button_id = viewer::create_button(pid, 0, button_click);

    viewer::set_button_text(pid, button_id, L"Test demo", L"Plugin example");

    file = data_path;
    file += L"icon.png";
    viewer::set_button_image(pid, button_id, file.c_str());
}


PLUGINDECL void CALL on_call_limit()
{
}


PLUGINDECL void CALL on_plugin_unload()
{
}


PLUGINDECL void CALL on_gui_colors_change()
{
}


PLUGINDECL int CALL on_drag_enter(const char *text, int x, int y)
{
    return DROP_EFFECT_NONE;
}


PLUGINDECL int CALL on_drag_over(int x, int y, int effect)
{
    return DROP_EFFECT_NONE;
}


PLUGINDECL int CALL on_drop(const char *text, int x, int y, int effect)
{
    return DROP_EFFECT_NONE;
}


PLUGINDECL bool CALL on_model_load_v2(bool is_bvf_file)
{
// place for reading *.bvf file api ver. 2
    return false;
}


PLUGINDECL void CALL on_model_save_v2()
{
// place for writing *.bvf file api ver. 2
}

PLUGINDECL void CALL on_undo_redo_action(unsigned int action_id, int undo_redo_reset)
{
}


//---keys and plugin activation-------------------------------------------------


char    plugin_key[292] =
{
};


PLUGINDECL const char* CALL get_plugin_key()
{
    return NULL;
    //return plugin_key;
}


}

//---------------------------------------------------------------------------
// dll main
//---------------------------------------------------------------------------


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch(ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        {
            load_viewer_functions();
            dll = hModule;
			break;
        }
        case DLL_THREAD_ATTACH:
			break;
        case DLL_THREAD_DETACH:
			break;
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}



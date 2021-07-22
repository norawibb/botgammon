#include "Functions.hpp"
using namespace std;

int GetInt(string line)
{
    stringstream ssline;
    int result = 0;
    ssline << line;
    ssline >> result;
    ssline.str("");
    ssline.clear();
    return result;
}

Preferences ReadPreferences()
{
    Preferences preferences{ false, 800, 600 }; // Default preferences
    string line;
    int dim;
    stringstream ssline;
    ifstream preftxt("preferences.txt");
    if (preftxt.is_open())
    {
        while (getline(preftxt, line))
        {
            if (line.find("fullscreen") != string::npos)
            {
                if (line.find("true") != string::npos)
                {
                    preferences.fullscreen = true;
                }
                else {
                    preferences.fullscreen = false;
                }
            }
            if (line.find("resolution_x") != string::npos)
            {
                if ((dim = GetInt(line)) > 0)
                {
                    preferences.resolution_x = dim;
                }
            }
            if (line.find("resolution_y") != string::npos)
            {
                if ((dim = GetInt(line)) > 0)
                {
                    preferences.resolution_y = dim;
                }
            }
        }
        preftxt.close();
    }

    else std::cout << "Unable to open preferences" << endl;

    return preferences;
}
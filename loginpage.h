#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

struct LoginData
{
    char id[50];
    char password[20];
    bool success = false;
};

LoginData showLoginPage(string role);
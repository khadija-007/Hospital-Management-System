#include <iostream>
#include "Admin.h"
#include "Storage.h"
#include "FileHandler.h"
#include "Doctor.h"
#include "Patient.h"
#include "Appointment.h"
#include "Bills.h"
#include "Prescription.h"
#include "Authentication.h"
#include <SFML/Graphics.hpp>
#include "loginpage.h"
#include "menus.h"
#include "errorpage.h"
#include <string>
#include "text.h"
using namespace std;

enum State
{
    MAIN_MENU,
    PATIENT_MENU,
    DOCTOR_MENU,
    ADMIN_MENU,
    EXIT
};

void showMainMenu(sf::RenderWindow& window, State& state,
    sf::RectangleShape& patientBtn,
    sf::RectangleShape& doctorBtn,
    sf::RectangleShape& adminBtn,
    sf::RectangleShape& exitBtn,
    sf::Text& patientTxt,
    sf::Text& doctorTxt,
    sf::Text& adminTxt,
    sf::Text& exitTxt,
    sf::Font& font,
    sf::Sprite& bg)
{
    sf::Text text;

    text.setFont(font);
    text.setFillColor(sf::Color::White);

    text.setString(
        "MEDICORE HOSPITAL\n Management System"
    );

    text.setCharacterSize(34);
    text.setStyle(sf::Text::Bold);

    sf::FloatRect textBounds = text.getLocalBounds();

    text.setOrigin(
        textBounds.left + textBounds.width / 2.f,
        textBounds.top + textBounds.height / 2.f
    );
    sf::RectangleShape panel;

    text.setPosition(
        (window.getSize().x - panel.getSize().x) / 2.f, 300);
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            state = EXIT;

        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f pos(event.mouseButton.x, event.mouseButton.y);

            if (patientBtn.getGlobalBounds().contains(pos))
                state = PATIENT_MENU;

            if (doctorBtn.getGlobalBounds().contains(pos))
                state = DOCTOR_MENU;

            if (adminBtn.getGlobalBounds().contains(pos))
                state = ADMIN_MENU;

            if (exitBtn.getGlobalBounds().contains(pos))
                state = EXIT;
        }
    }
    panel.setSize(sf::Vector2f(500, 650)); 

    panel.setPosition(
        (window.getSize().x - panel.getSize().x) / 2.f,
        200
    );

    panel.setFillColor(sf::Color(20, 20, 20, 160));

    panel.setOutlineThickness(2);
    panel.setOutlineColor(sf::Color(255, 255, 255, 50));

    sf::Vector2f mouse(sf::Mouse::getPosition(window));

    auto hover = [&](sf::RectangleShape& b)
        {
            if (b.getGlobalBounds().contains(mouse))
                b.setFillColor(sf::Color(60, 120, 255));
            else
                b.setFillColor(sf::Color(30, 80, 200, 220));
        };

    hover(patientBtn);
    hover(doctorBtn);
    hover(adminBtn);

    if (exitBtn.getGlobalBounds().contains(mouse))
        exitBtn.setFillColor(sf::Color(255, 80, 80));
    else
        exitBtn.setFillColor(sf::Color(220, 50, 50, 220));

    window.clear();

    window.draw(bg);
    window.draw(panel);
    window.draw(text);
    window.draw(patientBtn); window.draw(patientTxt);
    window.draw(doctorBtn); window.draw(doctorTxt);
    window.draw(adminBtn); window.draw(adminTxt);
    window.draw(exitBtn); window.draw(exitTxt);

    window.display();
}

Storage<Doctor> doctorStorage;
Storage<Patient> patientStorage;
Storage<Appointment> appointmentStorage;
Storage<Prescription> prescriptionStorage;
Storage<Bills> billStorage;

int main()
{
    FileHandler::loadDoctors(doctorStorage);
    FileHandler::loadPatients(patientStorage);
    FileHandler::loadAppointments(appointmentStorage);
    FileHandler::loadPrescriptions(prescriptionStorage);
    FileHandler::loadBills(billStorage);

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(),
        "Medicore Hospital",
        sf::Style::Fullscreen);

    State state = MAIN_MENU;

    sf::Font font;
    font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

    sf::Texture bgTexture;
    bgTexture.loadFromFile("image.jpeg");

    sf::Sprite bgSprite;
    bgSprite.setTexture(bgTexture);

    bgSprite.setScale(
        (float)window.getSize().x / bgTexture.getSize().x,
        (float)window.getSize().y / bgTexture.getSize().y
    );

    float buttonWidth = 250;
    float x = (window.getSize().x - buttonWidth) / 2.f;

    sf::RectangleShape patientBtn(sf::Vector2f(buttonWidth, 70));
    sf::RectangleShape doctorBtn(sf::Vector2f(buttonWidth, 70));
    sf::RectangleShape adminBtn(sf::Vector2f(buttonWidth, 70));
    sf::RectangleShape exitBtn(sf::Vector2f(buttonWidth, 70));

    patientBtn.setPosition(x, 400);
    doctorBtn.setPosition(x, 500);
    adminBtn.setPosition(x, 600);
    exitBtn.setPosition(x, 700);

   

    sf::Text patientTxt, doctorTxt, adminTxt, exitTxt;

    auto setupText = [&](sf::Text& t, string s, sf::RectangleShape& b)
        {
            t.setFont(font);
            t.setString(s);
            t.setCharacterSize(22);
            t.setFillColor(sf::Color::White);

            sf::FloatRect bounds = t.getLocalBounds();

            t.setOrigin(
                bounds.left + bounds.width / 2.f,
                bounds.top + bounds.height / 2.f
            );

            t.setPosition(
                b.getPosition().x + b.getSize().x / 2.f,
                b.getPosition().y + b.getSize().y / 2.f
            );
        };

    setupText(patientTxt, "Patient Login", patientBtn);
    setupText(doctorTxt, "Doctor Login", doctorBtn);
    setupText(adminTxt, "Admin Login", adminBtn);
    setupText(exitTxt, "Exit", exitBtn);

    while (window.isOpen())
    {
        switch (state)
        {
        case MAIN_MENU:
            showMainMenu(window, state,
                patientBtn, doctorBtn, adminBtn, exitBtn,
                patientTxt, doctorTxt, adminTxt, exitTxt,
                font, bgSprite);
            break;

        case PATIENT_MENU:
        {
            Patient* p = nullptr;

            int attempts = 0;

            int lastID = 0;

            while (attempts < 3)
            {
                LoginData patientLogin =
                    showLoginPage("Patient");
                if (!patientLogin.success)
                {
                    state = MAIN_MENU;
                    break;
                }

                // STORE LAST ENTERED ID
                lastID = atoi(patientLogin.id);

                p = Authentication::loginPatient(
                    patientStorage,
                    patientLogin
                );

                // SUCCESS
                if (p != nullptr)
                {
                    p->setStorages(&doctorStorage, &appointmentStorage, &patientStorage, &prescriptionStorage, &billStorage);
                    showPatientMenu(*p,
                        p->getName(),
                        p->getBalance()
                    );
                    break;
                }

                // FAILED
                attempts++;

                if (attempts < 3)
                {
                    showErrorWindow(
                        "Invalid ID or Password"
                    );
                }
            }

            if (attempts == 3)
            {
                FileHandler::logEvent(
                    "Patient",
                    lastID,
                    "Locked"
                );

                showErrorWindow(
                    "Too many wrong attempts.\nAccount locked."
                );
            }

            state = MAIN_MENU;

            break;
        }
        case DOCTOR_MENU:
        {
            Doctor* d = nullptr;
            bool success = false;
            int lastId = -1;

            for (int i = 0; i < 3; i++)
            {
                LoginData doctorLogin = showLoginPage("Doctor");
                if (!doctorLogin.success)
                {
                    state = MAIN_MENU;
                    break;
                }

                lastId = atoi(doctorLogin.id);

                d = Authentication::loginDoctor(doctorStorage, doctorLogin);

                if (d != nullptr)
                {
                    d->setStorages(&doctorStorage, &appointmentStorage, &patientStorage, &prescriptionStorage, &billStorage);
                    success = true;
                    break;
                }

                showErrorWindow("Invalid credentials. Attempts left: " + to_string(2 - i));
            }

            if (success)
            {
                showDoctorMenu(*d);
            }
            else
            {
                FileHandler::logEvent("Doctor", lastId, "Locked");
                showErrorWindow("Account locked after 3 failed attempts.");
            }

            state = MAIN_MENU;
            break;
        }
        case ADMIN_MENU:
        {
            Admin admin;
            bool success = false;
            int lastId = -1;

            for (int i = 0; i < 3; i++)
            {
                LoginData d = showLoginPage("Admin");
                if (!d.success)
                {
                    state = MAIN_MENU;
                    break;
                }

                lastId = atoi(d.id);

                if (Authentication::loginAdmin(d))
                {
                    success = true;
                    break;
                }

                showErrorWindow("Wrong credentials. Attempts left: " + to_string(2 - i));
            }
            if (success)
            {
                admin.setStorages(&doctorStorage, &appointmentStorage, &patientStorage, &prescriptionStorage, &billStorage);
                showAdminMenu(admin);
            }
            else
            {
                FileHandler::logEvent("Admin", lastId, "Locked");
                showErrorWindow("Account locked after 3 failed attempts.");
            }
            state = MAIN_MENU;
            break;
       
        }

        case EXIT:
            window.close();
            break;
        }
    }

    return 0;
}


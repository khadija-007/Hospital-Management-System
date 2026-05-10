
#include <SFML/Graphics.hpp>
#include <iostream>
#include "menus.h"
#include <string>
using namespace std;

void showPatientMenu(Patient& p,string name, float balance)
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Patient Menu", sf::Style::Fullscreen);

    sf::Texture blurr;
    blurr.loadFromFile("imageblurr.png");

    sf::Sprite bgSprite;
    bgSprite.setTexture(blurr);

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::Vector2u texSize = blurr.getSize();

    bgSprite.setScale(
        (float)desktop.width / texSize.x,
        (float)desktop.height / texSize.y
    );

    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");

    float centerX = desktop.width / 2.0f;

    sf::Text welcome;
    welcome.setFont(font);
    welcome.setString("Welcome Patient: " + name);
    welcome.setCharacterSize(34);
    welcome.setPosition((centerX - welcome.getGlobalBounds().width / 2)-20, 150);
    welcome.setStyle(sf::Text::Bold);

    sf::Text bal;
    bal.setFont(font);
    bal.setString("Balance: PKR " + to_string(balance));
    bal.setCharacterSize(24);
    bal.setPosition((centerX - bal.getGlobalBounds().width / 2)-15, 200);
    bal.setStyle(sf::Text::Bold);


    string options[8] =
    {
        "Book Appointment",
        "Cancel Appointment",
        "View My Appointments",
        "View My Medical Records",
        "View My Bills",
        "Pay Bill",
        "Top Up Balance",
        "Logout"
    };

    sf::RectangleShape boxes[8];
    sf::Text texts[8];

    float boxWidth = 500;
    float boxHeight = 55;
    float spacing = 70;

    float startY = desktop.height / 2.0f - 250;

    for (int i = 0; i < 8; i++)
    {
        float x = centerX - boxWidth / 2;

        boxes[i].setSize(sf::Vector2f(boxWidth, boxHeight));
        boxes[i].setPosition(x, startY + i * spacing);
        boxes[i].setFillColor(sf::Color(70, 70, 70));

        texts[i].setFont(font);
        texts[i].setString(options[i]);
        texts[i].setCharacterSize(22);
        texts[i].setPosition(x + 20, startY + i * spacing + 12);
    }

    sf::Cursor arrow, hand;
    arrow.loadFromSystem(sf::Cursor::Arrow);
    hand.loadFromSystem(sf::Cursor::Hand);

    while (window.isOpen())
    {
        sf::Event event;

        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        sf::Vector2f m(mouse.x, mouse.y);

        bool hovering = false;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                for (int i = 0; i < 8; i++)
                {
                    if (boxes[i].getGlobalBounds().contains(m))
                    {
                  
                        if (options[i] == "Logout")
                        {
                            window.close();
                        }
                        else if (options[i] == "Book Appointment")
                        {
                            window.close();                    
                            p.bookAppointment();               
                            showPatientMenu(p, p.getName(), p.getBalance()); 
                            return;
                        }
                        else if (options[i] == "Cancel Appointment")
                        {
                            window.close();                    
                            p.cancelAppointment();             
                            showPatientMenu(p, p.getName(), p.getBalance());
                            return;
                        }
                        else if (options[i] == "View My Appointments")
                        {
                            window.close();                    
                            p.displayAppointments();              
                            showPatientMenu(p, p.getName(), p.getBalance()); 
                            return;
                        }
                        else if (options[i] == "View My Medical Records")
                        {
                            window.close();                   
                            p.displayMedicalRecords();              
                            showPatientMenu(p, p.getName(), p.getBalance()); 
                            return;
                        }
                        else if (options[i] == "View My Bills")
                        {
                            window.close();                    
                            p.displayBills();              
                            showPatientMenu(p, p.getName(), p.getBalance()); 
                            return;
                        }
                        else if (options[i] == "Pay Bill")
                        {
                            window.close();                    
                            p.payBill();              
                            showPatientMenu(p, p.getName(), p.getBalance()); 
                            return;
                        }
                        else if (options[i] == "Top Up Balance")
                        {
                            window.close();
                            p.topUpBalance();
                            showPatientMenu(p, p.getName(), p.getBalance());
                            return;
                        }
                        else
                        {
                            cout << options[i] << " clicked\n";
                        }
                    }
                }
            }
        }

        for (int i = 0; i < 8; i++)
        {
            if (boxes[i].getGlobalBounds().contains(m))
            {
                boxes[i].setFillColor(sf::Color(100, 100, 100));
                hovering = true;
            }
            else
            {
                boxes[i].setFillColor(sf::Color(70, 70, 70));
            }
        }

        window.setMouseCursor(hovering ? hand : arrow);

        window.clear(sf::Color(20, 20, 20));
        window.draw(bgSprite);

        window.draw(welcome);
        window.draw(bal);

        for (int i = 0; i < 8; i++)
        {
            window.draw(boxes[i]);
            window.draw(texts[i]);
        }

        window.display();
    }
}


void showDoctorMenu(Doctor & d)
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Doctor Menu", sf::Style::Fullscreen);

    sf::Texture blurr;
    blurr.loadFromFile("imageblurr.png");

    sf::Sprite bgSprite;
    bgSprite.setTexture(blurr);

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::Vector2u texSize = blurr.getSize();

    bgSprite.setScale(
        (float)desktop.width / texSize.x,
        (float)desktop.height / texSize.y
    );

    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");

    float centerX = desktop.width / 2.0f;

    sf::Text welcome;
    welcome.setFont(font);
    welcome.setString("Welcome Doctor: " + std::string(d.getName()));
    welcome.setCharacterSize(34);
    welcome.setPosition((centerX - welcome.getGlobalBounds().width / 2) - 20, 150);
    welcome.setStyle(sf::Text::Bold);

    string options[6] =
    {
        "View Today's Appointments",
        "Mark Appointment Complete",
        "Mark Appointment No-Show",
        "Write Prescription",
        "View Patient Medical History",
        "Logout"
    };

    sf::RectangleShape boxes[6];
    sf::Text texts[6];

    float boxWidth = 500;
    float boxHeight = 55;
    float spacing = 70;

    float startY = desktop.height / 2.0f - 200;

    for (int i = 0; i < 6; i++)
    {
        float x = centerX - boxWidth / 2;

        boxes[i].setSize(sf::Vector2f(boxWidth, boxHeight));
        boxes[i].setPosition(x, startY + i * spacing);
        boxes[i].setFillColor(sf::Color(70, 70, 70));

        texts[i].setFont(font);
        texts[i].setString(options[i]);
        texts[i].setCharacterSize(22);
        texts[i].setPosition(x + 20, startY + i * spacing + 12);
    }

    sf::Cursor arrow, hand;
    arrow.loadFromSystem(sf::Cursor::Arrow);
    hand.loadFromSystem(sf::Cursor::Hand);

    while (window.isOpen())
    {
        sf::Event event;

        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        sf::Vector2f m(mouse.x, mouse.y);

        bool hovering = false;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                for (int i = 0; i < 6; i++)
                {
                    if (boxes[i].getGlobalBounds().contains(m))
                    {
                        
                        if (options[i] == "Logout")
                        {
                            window.close();
                        }
                        else if (options[i] == "View Today's Appointments")
                        {
                            window.close();
                            d.displayTodayAppointment();
                            showDoctorMenu(d);
                            return;
                        }
                        else if (options[i] == "Mark Appointment Complete")
                        {
                            window.close();
                            d.markAppointmentComplete();
                            showDoctorMenu(d);
                            return;
                        }
                        else if (options[i] == "Mark Appointment No-Show")
                        {
                            window.close();
                            d.markAppointmentNoshow();
                            showDoctorMenu(d);
                            return;
                        }
                        else if (options[i] == "Write Prescription")
                        {
                            window.close();
                            d.writePrescription();
                            showDoctorMenu(d);
                            return;
                        }
                        else if (options[i] == "View Patient Medical History")
                        {
                            window.close();
                            d.displayPatientHistory();
                            showDoctorMenu(d);
                            return;
                        }
                        else
                        {
                            cout << options[i] << " clicked\n";
                        }
                    }
                }
            }
        }

        for (int i = 0; i < 6; i++)
        {
            if (boxes[i].getGlobalBounds().contains(m))
            {
                boxes[i].setFillColor(sf::Color(100, 100, 100));
                hovering = true;
            }
            else
            {
                boxes[i].setFillColor(sf::Color(70, 70, 70));
            }
        }

        window.setMouseCursor(hovering ? hand : arrow);

        window.clear(sf::Color(20, 20, 20));
        window.draw(bgSprite);

        window.draw(welcome);

        for (int i = 0; i < 6; i++)
        {
            window.draw(boxes[i]);
            window.draw(texts[i]);
        }

        window.display();
    }
}


void showAdminMenu(Admin& admin)
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Admin Menu", sf::Style::Fullscreen);

    sf::Texture blurr;
    blurr.loadFromFile("imageblurr.png");

    sf::Sprite bgSprite;
    bgSprite.setTexture(blurr);

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::Vector2u texSize = blurr.getSize();

    bgSprite.setScale(
        (float)desktop.width / texSize.x,
        (float)desktop.height / texSize.y
    );

    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");

    float centerX = desktop.width / 2.0f;

    sf::Text welcome;
    welcome.setFont(font);
    welcome.setString("Welcome Admin");
    welcome.setCharacterSize(34);
    welcome.setPosition((centerX - welcome.getGlobalBounds().width / 2) - 20, 150);
    welcome.setStyle(sf::Text::Bold);

    string options[11] =
    {
        "Add Doctor",
        "Remove Doctor",
        "Add Patient",
        "View All Patients",
        "View All Doctors",
        "View All Appointments",
        "View Unpaid Bills",
        "Discharge Patient",
        "View Security Log",
        "Generate Daily Report",
        "Logout"
    };

    sf::RectangleShape boxes[11];
    sf::Text texts[11];

    float boxWidth = 500;
    float boxHeight = 55;
    float spacing = 65;

    float startY = desktop.height / 2.0f - 280;

    for (int i = 0; i < 11; i++)
    {
        float x = centerX - boxWidth / 2;

        boxes[i].setSize(sf::Vector2f(boxWidth, boxHeight));
        boxes[i].setPosition(x, startY + i * spacing);
        boxes[i].setFillColor(sf::Color(70, 70, 70));

        texts[i].setFont(font);
        texts[i].setString(options[i]);
        texts[i].setCharacterSize(20);
        texts[i].setPosition(x + 20, startY + i * spacing + 12);
    }

    sf::Cursor arrow, hand;
    arrow.loadFromSystem(sf::Cursor::Arrow);
    hand.loadFromSystem(sf::Cursor::Hand);

    while (window.isOpen())
    {
        sf::Event event;

        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        sf::Vector2f m(mouse.x, mouse.y);

        bool hovering = false;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                for (int i = 0; i < 11; i++)
                {
                    if (boxes[i].getGlobalBounds().contains(m))
                    {
                        if (options[i] == "Logout")
                        {
                            window.close();
                        }
                        else if (options[i] == "Add Doctor")
                        {
                            window.close();
                            admin.AddDoctor();
                            showAdminMenu(admin);
                            return;
                        }
                        else if (options[i] == "Remove Doctor")
                        {
                            window.close();
                            admin.RemoveDoctor();
                            showAdminMenu(admin);
                            return;
                        }
                        else if (options[i] == "Add Patient")
                        {
                            window.close();
                            admin.AddPatient();
                            showAdminMenu(admin);
                            return;
                        }
                        else if (options[i] == "View All Patients")
                        {
                            window.close();
                            admin.ViewAllPatients();
                            showAdminMenu(admin);
                            return;
                        }
                        else if (options[i] == "View All Doctors")
                        {
                            window.close();
                            admin.ViewAllDoctors();
                            showAdminMenu(admin);
                            return;
                        }
                        else if (options[i] == "View All Appointments")
                        {
                            window.close();
                            admin.ViewAllAppointments();
                            showAdminMenu(admin);
                            return;
                        }
                        else if (options[i] == "View Unpaid Bills")
                        {
                            window.close();
                            admin.ViewUnpaidBills();
                            showAdminMenu(admin);
                            return;
                        }
                        else if (options[i] == "Discharge Patient")
                        {
                            window.close();
                            admin.DischargePatient();
                            showAdminMenu(admin);
                            return;
                        }
                        else if (options[i] == "View Security Log")
                        {
                            window.close();
                            admin.viewSecurityLog();
                            showAdminMenu(admin);
                            return;
                        }
                        else if (options[i] == "Generate Daily Report")
                        {
                            window.close();
                            admin.GenerateDailyReport();
                            showAdminMenu(admin);
                            return;
                        }
                        else
                        {
                            cout << options[i] << " clicked\n";
                        }
                    }
                }
            }
        }

        for (int i = 0; i < 11; i++)
        {
            if (boxes[i].getGlobalBounds().contains(m))
            {
                boxes[i].setFillColor(sf::Color(100, 100, 100));
                hovering = true;
            }
            else
            {
                boxes[i].setFillColor(sf::Color(70, 70, 70));
            }
        }

        window.setMouseCursor(hovering ? hand : arrow);

        window.clear(sf::Color(20, 20, 20));
        window.draw(bgSprite);

        window.draw(welcome);

        for (int i = 0; i < 11; i++)
        {
            window.draw(boxes[i]);
            window.draw(texts[i]);
        }

        window.display();
    }
}



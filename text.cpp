#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Patient.h"
#include "Doctor.h"
#include "Bills.h"
#include "Appointment.h"
#include "Prescription.h"
#include "storage.h"
#include "Person.h"
#include "text.h"
using namespace std;

void showDoctors(sf::RenderWindow& window,
    sf::Font& font,
    Doctor doctors[],
    int count)
{
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
    sf::Text header;
    header.setFont(font);
    header.setString("Doctors List");
    header.setCharacterSize(32);
    header.setPosition(100, 60);
    header.setStyle(sf::Text::Bold);
    header.setFillColor(sf::Color::White);

    sf::Text text[100];

    for (int i = 0; i < count; i++)
    {
        std::string line =
            "ID: " + std::to_string(doctors[i].getID()) +
            " | Name: " + doctors[i].getName() +
            " | Spec: " + doctors[i].getSpecialization() +
            " | No: " + doctors[i].getNumber() +
            " | Fee: " + std::to_string(doctors[i].getFee());

        text[i].setFont(font);
        text[i].setString(line);
        text[i].setCharacterSize(22);
        text[i].setPosition(100, 140 + i * 40);
        text[i].setFillColor(sf::Color::White);
    }

    sf::Text hint;
    hint.setFont(font);
    hint.setString("Press ENTER to continue");
    hint.setCharacterSize(18);
    hint.setPosition(100, 520);
    hint.setFillColor(sf::Color(180, 180, 180));

    bool running = true;

    while (window.isOpen() && running)
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return;
            }

            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Enter)
            {
                running = false;
            }
        }

        window.clear(sf::Color(25, 25, 25));
        window.draw(bgSprite);
        window.draw(header);

        for (int i = 0; i < count; i++)
            window.draw(text[i]);

        window.draw(hint);

        window.display();

    }
}

void showPatients(sf::RenderWindow& window, sf::Font& font, Patient patients[], int count)
{
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
    sf::Text header;
    header.setFont(font);
    header.setString("Patients List");
    header.setCharacterSize(32);
    header.setPosition(100, 60);
    header.setStyle(sf::Text::Bold);
    header.setFillColor(sf::Color::White);

    sf::Text text[100];

    for (int i = 0; i < count; i++)
    {
        std::string line = patients[i].getName();
        line += " | ID: ";
        line += std::to_string(patients[i].getID());

        text[i].setFont(font);
        text[i].setString(line);
        text[i].setCharacterSize(24);
        text[i].setPosition(100, 140 + i * 40);
        text[i].setFillColor(sf::Color::White);
    }

    sf::Text hint;
    hint.setFont(font);
    hint.setString("Press ENTER to go back");
    hint.setCharacterSize(18);
    hint.setPosition(100, 520);
    hint.setFillColor(sf::Color(180, 180, 180));

    bool running = true;

    while (window.isOpen() && running)
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Enter)
                running = false;
        }

        window.clear(sf::Color(25, 25, 25));
        window.draw(bgSprite);
        window.draw(header);

        for (int i = 0; i < count; i++)
            window.draw(text[i]);

        window.draw(hint);

        window.display();
    }
}
void showBills(sf::RenderWindow& window, sf::Font& font, Bills bills[], int count)
{
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
    sf::Text header;
    header.setFont(font);
    header.setString("Bills List");
    header.setCharacterSize(32);
    header.setPosition(100, 60);
    header.setStyle(sf::Text::Bold);
    header.setFillColor(sf::Color::White);

    sf::Text text[100];

    for (int i = 0; i < count; i++)
    {
        std::string line =
            "Bill ID: " + std::to_string(bills[i].getID());

        line += " | Appointment ID: ";
        line += std::to_string(bills[i].getAppointmentID());

        line += " | Patient ID: ";
        line += std::to_string(bills[i].getPatientID());

        line += " | Amount: ";
        line += std::to_string(bills[i].getAmount());

        line += " | Date: ";
        line += bills[i].getDate();

        line += " | Status: ";
        line += bills[i].getStatus();

        text[i].setFont(font);
        text[i].setString(line);
        text[i].setCharacterSize(24);
        text[i].setPosition(100, 140 + i * 40);
        text[i].setFillColor(sf::Color::White);
    }

    sf::Text hint;
    hint.setFont(font);
    hint.setString("Press ENTER to go back");
    hint.setCharacterSize(18);
    hint.setPosition(100, 520);
    hint.setFillColor(sf::Color(180, 180, 180));

    bool running = true;

    while (window.isOpen() && running)
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Enter)
                running = false;
        }

        window.clear(sf::Color(25, 25, 25));
        window.draw(bgSprite);
        window.draw(header);

        for (int i = 0; i < count; i++)
            window.draw(text[i]);

        window.draw(hint);

        window.display();
    }
}
void showPrescriptions(sf::RenderWindow& window, sf::Font& font, Prescription p[], int count)
{
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
    sf::Text header;
    header.setFont(font);
    header.setString("Prescriptions");
    header.setCharacterSize(32);
    header.setPosition(100, 60);
    header.setFillColor(sf::Color::White);

    sf::Text text[1000];
    int textIndex = 0;

    int y = 140;

    for (int i = 0; i < count; i++)
    {
        bool alreadyPrinted = false;

        for (int k = 0; k < i; k++)
        {
            if (p[k].getAppointmentId() == p[i].getAppointmentId())
            {
                alreadyPrinted = true;
                break;
            }
        }

        if (!alreadyPrinted)
        {
          
            std::string line =
                "Appointment ID: " + std::to_string(p[i].getAppointmentId());

            line += " | Date: ";
            line += p[i].getDate();

            line += " | Doctor: ";
            line += p[i].getDrname();

            text[textIndex].setFont(font);
            text[textIndex].setString(line);
            text[textIndex].setCharacterSize(24);
            text[textIndex].setPosition(100, y);
            text[textIndex].setFillColor(sf::Color::White);

            textIndex++;
            y += 40;

            for (int j = 0; j < count; j++)
            {
                if (p[j].getAppointmentId() == p[i].getAppointmentId())
                {
                    std::string medLine =
                        "Medicines: " + std::string(p[j].getMedicines());

                    medLine += " | Notes: ";
                    medLine += std::string(p[j].getNotes());

                    text[textIndex].setFont(font);
                    text[textIndex].setString(medLine);
                    text[textIndex].setCharacterSize(20);
                    text[textIndex].setPosition(140, y);
                    text[textIndex].setFillColor(sf::Color::Cyan);

                    textIndex++;
                    y += 30;
                }
            }

            y += 20; 
        }
    }

    sf::Text hint;
    hint.setFont(font);
    hint.setString("Press ENTER to go back");
    hint.setCharacterSize(18);
    hint.setPosition(100, 520);
    hint.setFillColor(sf::Color(180, 180, 180));

    bool running = true;

    while (window.isOpen() && running)
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Enter)
                running = false;
        }

        window.clear(sf::Color(25, 25, 25));

        window.draw(bgSprite);
        window.draw(header);

        for (int i = 0; i < textIndex; i++)
            window.draw(text[i]);

        window.draw(hint);

        window.display();
    }
}
void showAppointments(sf::RenderWindow& window, sf::Font& font, Appointment a[], int count, Storage<Doctor>& doctorStorage,Storage<Patient>& patientStorage)
{
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
    sf::Text header;
    header.setFont(font);
    header.setString("Appointments");
    header.setCharacterSize(32);
    header.setPosition(100, 60);
    header.setStyle(sf::Text::Bold);
    header.setFillColor(sf::Color::White);

    sf::Text text[100];

    for (int i = 0; i < count; i++)
    {
        Doctor* d = doctorStorage.findbyID(a->getDoctorID());
        Patient* p = patientStorage.findbyID(a->getPatientID());
        std::string line =
            "Appointment ID: " + std::to_string(a[i].getID()) +
            " | Patient ID: " + std::to_string(p->getID()) +
            " | Patient Name: " + p->getName() +
            " | Doctor ID: " + std::to_string(d->getID()) +
            " | Doctor Name: " + d->getName() +
            " | Date: " + a[i].getDate() +
            " | Slot: " + a[i].getTimeSlot() +
            " | Status: " + a[i].getStatus();


        text[i].setFont(font);
        text[i].setString(line);
        text[i].setCharacterSize(24);
        text[i].setPosition(100, 140 + i * 40);
        text[i].setFillColor(sf::Color::White);
    }

    sf::Text hint;
    hint.setFont(font);
    hint.setString("Press ENTER to go back");
    hint.setCharacterSize(18);
    hint.setPosition(100, 520);
    hint.setFillColor(sf::Color(180, 180, 180));

    bool running = true;

    while (window.isOpen() && running)
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Enter)
                running = false;
        }

        window.clear(sf::Color(25, 25, 25));
        window.draw(bgSprite);
        window.draw(bgSprite);
        window.draw(header);

        for (int i = 0; i < count; i++)
            window.draw(text[i]);

        window.draw(hint);

        window.display();
    }
}
void showDailyReportUI(sf::RenderWindow& window, sf::Font& font,
    const char today[],
    int total,
    int pending,
    int completed,
    int noshow,
    int cancelled,
    float revenue,
    char unpaidText[][200],
    int unpaidCount,
    char doctorSummary[][200],
    int doctorCount
)
{
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

    sf::Color primary(230, 240, 255);      
    sf::Color heading(120, 220, 255);      
    sf::Color accent(0, 255, 180);         
    sf::Color warning(255, 190, 120);      
    sf::Color panel(15, 25, 40, 180);      

    sf::RectangleShape topPanel(sf::Vector2f(1200, 180));
    topPanel.setPosition(160, 30);
    topPanel.setFillColor(panel);
    topPanel.setOutlineThickness(1.5);
    topPanel.setOutlineColor(sf::Color(255, 255, 255, 40));

    sf::RectangleShape leftPanel(sf::Vector2f(550, 420));
    leftPanel.setPosition(120, 260);
    leftPanel.setFillColor(panel);
    leftPanel.setOutlineThickness(1.5);
    leftPanel.setOutlineColor(sf::Color(255, 255, 255, 40));

    sf::RectangleShape rightPanel(sf::Vector2f(650, 420));
    rightPanel.setPosition(760, 260);
    rightPanel.setFillColor(panel);
    rightPanel.setOutlineThickness(1.5);
    rightPanel.setOutlineColor(sf::Color(255, 255, 255, 40));

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Enter)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
            

        }

        window.clear();
        window.draw(bgSprite);

        window.draw(topPanel);
        window.draw(leftPanel);
        window.draw(rightPanel);

        sf::Text title;
        title.setFont(font);
        title.setString("DAILY HOSPITAL REPORT");
        title.setCharacterSize(42);
        title.setStyle(sf::Text::Bold);
        title.setFillColor(heading);
        title.setPosition(470, 45);
        window.draw(title);

        sf::Text dateText;
        dateText.setFont(font);
        dateText.setString(today);
        dateText.setCharacterSize(24);
        dateText.setFillColor(primary);
        dateText.setPosition(655, 105);
        window.draw(dateText);

        char report[300];

        sprintf_s(report,
            "Total: %d     Pending: %d     Completed: %d     No-show: %d     Cancelled: %d",
            total, pending, completed, noshow, cancelled);

        sf::Text appText;
        appText.setFont(font);
        appText.setString(report);
        appText.setCharacterSize(26);
        appText.setStyle(sf::Text::Bold);
        appText.setFillColor(accent);
        appText.setPosition(240, 155);
        window.draw(appText);

        char revText[100];

        sprintf_s(revText,
            "Revenue Today: %.2f PKR",
            revenue);

        sf::Text revenueText;
        revenueText.setFont(font);
        revenueText.setString(revText);
        revenueText.setCharacterSize(28);
        revenueText.setStyle(sf::Text::Bold);
        revenueText.setFillColor(sf::Color::Black);
        revenueText.setPosition(520, 205);
        window.draw(revenueText);

        sf::Text unpaidTitle;
        unpaidTitle.setFont(font);
        unpaidTitle.setString("UNPAID BILLS");
        unpaidTitle.setCharacterSize(30);
        unpaidTitle.setStyle(sf::Text::Bold);
        unpaidTitle.setFillColor(heading);
        unpaidTitle.setPosition(290, 290);
        window.draw(unpaidTitle);

        float y = 355;

        for (int i = 0; i < unpaidCount; i++)
        {
            sf::Text t;

            t.setFont(font);
            t.setString(unpaidText[i]);
            t.setCharacterSize(23);
            t.setFillColor(primary);
            t.setPosition(155, y);

            y += 38;

            window.draw(t);
        }

        sf::Text docTitle;

        docTitle.setFont(font);
        docTitle.setString("DOCTOR-WISE SUMMARY");
        docTitle.setCharacterSize(30);
        docTitle.setStyle(sf::Text::Bold);
        docTitle.setFillColor(heading);
        docTitle.setPosition(930, 290);

        window.draw(docTitle);

        float y2 = 355;

        for (int i = 0; i < doctorCount; i++)
        {
            sf::Text t;

            t.setFont(font);
            t.setString(doctorSummary[i]);
            t.setCharacterSize(23);
            t.setFillColor(primary);
            t.setPosition(805, y2);

            y2 += 38;

            window.draw(t);
        }

        window.display();
    }
}
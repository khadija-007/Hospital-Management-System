# Hospital Management System

This is a Hospital Management System built in C++ using SFML for the graphical interface. It simulates how a basic hospital system works, where different users (Admin, Doctor, and Patient) can log in and perform their specific tasks.

The whole project is based on a role system and uses file handling to save data so that everything is still available when the program is reopened.

---

## What the System Does

The system is basically split into a few main parts that work together:

- A login system to check users (Admin, Doctor, Patient)
- File handling to store and load all data
- Input validation to make sure wrong data doesn’t break the system
- Exception handling to manage errors properly
- A GUI built with SFML for menus and interaction
- Separate functionalities for each role

---

## Features

### Login / Authentication
- Users log in as Admin, Doctor, or Patient
- The system checks ID and password before letting anyone in
- If login details are wrong, access is denied
- Failed login attempts are recorded in a security log after multiple tries

---

### Patient Features
- Book appointments with doctors  
- Cancel appointments  
- View medical history  
- Check their appointments  
- Pay bills and manage balance  

---

### Doctor Features
- View daily appointments  
- Write prescriptions for patients  
- Mark appointments as completed or no-show  
- Access patient medical history  

---

### Admin Features
- Add or remove doctors and patients  
- View all appointments, bills, doctors, and patients  
- Generate daily reports  
- Check security logs  
- Discharge patients from the system  

---

### Reports
The admin can generate a daily report that includes:
- Total revenue for the day  
- Number of bills generated  
- Appointment summary (pending, completed, canceled, no-show)  

---

### GUI (SFML)
- Fully graphical interface using SFML  
- Separate menus for each user role  
- Success screens when actions are completed  
- Error screens when something goes wrong  
- Sound feedback for success and errors  

---

### File Handling / Storage
- All data is saved using file handling  
- Data is loaded again when the program starts  
- Stores:
  - Patients  
  - Doctors  
  - Appointments  
  - Bills  
  - Prescriptions  
  - Security logs  

---

### Validation & Exception Handling
- Input validation is used throughout the system  
- Custom exceptions handle errors where needed  
- Prevents invalid input from crashing the program  

---

## Technologies Used
- C++
- SFML
- Object-Oriented Programming
- File Handling
- Templates
- Exception Handling

---

## User Roles

- **Admin** → full control of the system  
- **Doctor** → manages appointments and patients  
- **Patient** → books appointments and manages health info  

---

## Summary

Overall, this project is a complete hospital management system with login security, role-based access, file storage, and a working GUI. It was built to simulate real-world hospital operations in a simple but structured way.

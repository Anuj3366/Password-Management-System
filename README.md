# Password Management System

## Overview

The Password Management System is a command-line tool that allows users to securely manage their website passwords. It provides the following features:

- **Saving Passwords:** Users can save passwords associated with specific websites and usernames.
- **Viewing Passwords:** Users can retrieve and view stored passwords for their websites.
- **Generating Strong Passwords:** The system can generate strong passwords for users to use.

## Getting Started

### Prerequisites

To run the Password Management System, you'll need:

- C Compiler (e.g., GCC)
- Standard C Libraries
- Unix-like environment (Linux, macOS, or Windows Subsystem for Linux)

### Installation

1. Clone this repository to your local machine:

   ```bash
   git clone https://github.com/your-username/password-management-system.git
   ```

2. Compile the program using your C compiler:
   (You can skip this step in most cases)

   ```bash
   gcc main.c -o password_management_system
   ```

### Usage

To use the Password Management System, follow these steps:

1. Run the program:

   ```bash
   ./password_management_system
   ```

2. You'll be presented with a menu:

   ```
   Please select an option:
   To exit, type Anything or 0. You can also type "exit" at any time to return to this menu.
   1. Save a new password (Press 1).
   2. View an existing stored password (Press 2).
   3. Generate a new strong password (Press 3).
   ```

3. Choose an option by entering the corresponding number and following the prompts.
   
4. Next there will be various prompts according to the choice you made or value you entered, but I warn you to first read instructions only and then continue forward.

## Features

### Saving a New Password

- Enter the website's URL.
- Enter the username.
- Enter the password (8-10 characters with letters, digits, and special characters).

### Viewing an Existing Password

- Enter the website's URL.
- Enter the username.
- The system will display the stored password for the given website and username.

### Generating a Strong Password

- Enter the website's URL.
- Enter the username.
- The system will generate a strong password and display it.

## Security

- Passwords are stored in a file (`passwords.xls`) on your local machine.
- Passwords, URLs, and usernames are case-sensitive.
- The system checks for password strength and ensures uniqueness.

## License

This project is solely made and designed by Anuj Garg

---

### Remaining Task

#### Add privacy while writing passwords, no one can see what you wrote (Will try it later because Windows and Linux require different libraries to be imported and not touched those yet)

#### Add encryption and decryption to the saved password and give the option to make its key to the user

#### Add a feature where it can work with HTML and looks good

#### Add an encrypted password to the Excel file instead of text and provide an option to import it to the browser


# Password Management System

## Overview

The Password Management System is a command-line tool that allows users to securely manage their website passwords. Please note that this program is intended for demonstration purposes only and is not suitable for production use. It provides the following features:

- **User Account Management:** Users can create new accounts or log in to existing ones.
- **Password Storage:** Store passwords securely using encryption.
- **Password Retrieval:** Retrieve stored passwords for websites.
- **Strong Password Generation:** Generate strong passwords for use.

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
   To exit, type 'exit' at any time to return to this menu.
   1. Create a new account (Press 1).
   2. Log in to an existing account (Press 2).
   ```

3. Choose an option by entering the corresponding number and following the prompts.

4. For new accounts, you'll be prompted to create a username and a password. Please note that your password should consist only of positive numbers and should not be shared, as it is used to encrypt and decrypt your passwords.

5. Once logged in, you can choose to save new passwords, view existing stored passwords, or generate strong passwords.

## Features

### User Account Management

- Create a new account with a unique username and password.
- Log in to an existing account.

### Password Storage

- Store passwords securely using encryption.

### Password Retrieval

- Retrieve stored passwords for websites.

### Strong Password Generation

- Generate strong passwords for use.

## Security

- Passwords are stored securely using encryption.
- Passwords, URLs, and usernames are case-sensitive.

## License

This project is solely made and designed by Anuj Garg.

---

### Remaining Tasks

- Enhance privacy measures while writing passwords.
- Implement further encryption and decryption options for saved passwords.
- Add HTML compatibility and improve the user interface.
- Provide an option to import encrypted passwords to a web browser.

Please note that the program currently works only on Linux-based systems.

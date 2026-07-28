# Clinic Management System

A command-line clinic management system written in **C**. The program uses CSV files to store and manage patient information, medical records, treatment costs, clinic revenue, disease statistics, and follow-up schedules.

## Features

### 1. Patient Data Management

* Add new patients.
* Edit patient information.
* Delete patient records.
* Search for patients by patient ID.
* Display all registered patients.

### 2. Patient Visit History Management

* Add new medical visit records.
* Edit existing medical records.
* Delete medical records.
* Search for records by patient ID and date.
* Calculate treatment costs.
* Save updated records to `RiwayatPasien.csv`.

### 3. Patient Information and Medical History

* Search for patient information by patient ID.
* Display the patient's diagnoses and treatments.
* Display medical history in chronological order.

### 4. Clinic Revenue Report

* Calculate monthly clinic revenue.
* Calculate yearly clinic revenue.
* Calculate average revenue for a selected year.

### 5. Disease Statistics

* Count disease cases by month.
* Count disease cases by year.
* Sort diseases from the highest to the lowest number of cases.

### 6. Patient Follow-Up Information

* Display patients who are scheduled for a follow-up visit on a selected date.

## Technologies and Concepts

This project uses:

* C programming language.
* Structures (`struct`).
* Arrays.
* Linked lists.
* CSV file reading and writing.
* Data searching.
* Bubble sort.
* Date parsing and normalization.

## Repository Structure

| File                | Description                                                   |
| ------------------- | ------------------------------------------------------------- |
| `fitur1.c`          | Manages patient data.                                         |
| `fitur2.c`          | Manages patient visit history and calculates treatment costs. |
| `fitur3dan6.c`      | Displays patient medical history and follow-up schedules.     |
| `fitur4.c`          | Generates monthly and yearly clinic revenue reports.          |
| `fitur5.c`          | Generates monthly and yearly disease statistics.              |
| `DataPasien.csv`    | Stores patient information.                                   |
| `RiwayatPasien.csv` | Stores patient medical records and follow-up dates.           |
| `BiayaTindakan.csv` | Stores registration, examination, and treatment costs.        |

## CSV Data Format

The CSV files in this repository do not contain header rows. The following sections describe the expected column order.

### `DataPasien.csv`

```text
No,Name,Address,City,Place of Birth,Date of Birth,Age,BPJS Number,Patient ID
```

Example:

```text
1,Aris Suwito,Jl. Satu No.14,Kota Bandung,Kab. Mojokerto,01-01-1980,44,1234567890,KX 1230123
```

### `RiwayatPasien.csv`

```text
No,Date,Patient ID,Diagnosis,Treatment,Follow-Up Date,Cost
```

Example:

```text
1,1 Januari 2022,KX 1230123,Dehidrasi,Pemasangan infus,4 Januari 2022,265000
```

The existing CSV data may still contain Indonesian diagnosis, treatment, and month names because they are part of the original dataset.

### `BiayaTindakan.csv`

```text
No,Cost or Treatment Name,Cost
```

Example:

```text
1,Pendaftaran,15000
2,Pemeriksaan,125000
3,Vaksinasi,100000
```

## Requirements

Before compiling the program, make sure the following software is installed:

* GCC or another compatible C compiler.
* A terminal or command prompt.
* Git, if you want to clone the repository.

Linux or Windows Subsystem for Linux is recommended because some parts of the program use POSIX functions such as `strcasecmp`.

## Installation

Clone the repository:

```bash
git clone https://github.com/FilbertGarciano/Clinic-Management-EL2008.git
```

Move into the project directory:

```bash
cd Clinic-Management-EL2008
```

Make sure the CSV files remain in the same directory as the compiled programs.

## Compiling and Running the Programs

Each feature is currently implemented as a separate C program.

### Feature 1 — Patient Data Management

Compile:

```bash
gcc -std=c11 fitur1.c -o fitur1
```

Run on Linux or macOS:

```bash
./fitur1
```

Run on Windows:

```bash
fitur1.exe
```

### Feature 2 — Patient Visit History

Compile:

```bash
gcc -std=c11 fitur2.c -o fitur2
```

Run on Linux or macOS:

```bash
./fitur2
```

Run on Windows:

```bash
fitur2.exe
```

### Feature 4 — Revenue Report

Compile:

```bash
gcc -std=c11 fitur4.c -o fitur4
```

Run on Linux or macOS:

```bash
./fitur4
```

Run on Windows:

```bash
fitur4.exe
```

### Feature 5 — Disease Statistics

Compile:

```bash
gcc -std=gnu11 fitur5.c -o fitur5
```

Run on Linux or macOS:

```bash
./fitur5
```

Run on Windows:

```bash
fitur5.exe
```

## Running Features 3 and 6

The `fitur3dan6.c` file provides the `menuFitur3()` and `menuFitur6()` functions, but it does not include a `main()` function.

Create a new file named `main.c` in the project directory:

```c
#include <stdio.h>

void menuFitur3(void);
void menuFitur6(void);

int main(void) {
    int choice;

    do {
        printf("\n=== CLINIC MANAGEMENT SYSTEM ===\n");
        printf("1. Patient information and medical history\n");
        printf("2. Patient follow-up information\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            return 1;
        }

        switch (choice) {
            case 1:
                menuFitur3();
                break;

            case 2:
                menuFitur6();
                break;

            case 0:
                printf("Program closed.\n");
                break;

            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}
```

Compile `main.c` together with `fitur3dan6.c`:

```bash
gcc -std=gnu11 main.c fitur3dan6.c -o fitur3dan6
```

Run on Linux or macOS:

```bash
./fitur3dan6
```

Run on Windows:

```bash
fitur3dan6.exe
```

## Usage Notes

* Run the programs from the repository's root directory so they can find the CSV files.
* Do not change the CSV column order unless the parsing logic in the C source code is also updated.
* Use a consistent patient ID format, such as `KX 1230123`.
* The programs support several date formats, including `DD-MM-YYYY`, `DD-Mon-YY`, and `DD Month YYYY`.
* Back up the CSV files before testing features that add, edit, or delete records.
* Some program output and dataset values may still be written in Indonesian.

## Possible Improvements

Future development could include:

* Combining all features into one main application.
* Moving shared declarations into header files.
* Adding stronger input validation.
* Improving file error handling.
* Replacing unsafe or unbounded string operations.
* Using a more appropriate data type for long identification numbers.
* Adding automated tests.
* Adding a `Makefile` to simplify compilation.
* Translating all menus and program output into English.
* Adding role-based access for clinic staff.

## Contributing

Contributions are welcome.

1. Fork the repository.
2. Create a new branch:

```bash
git checkout -b feature/your-feature-name
```

3. Commit your changes:

```bash
git add .
git commit -m "Add your feature description"
```

4. Push the branch:

```bash
git push origin feature/your-feature-name
```

5. Open a pull request.

## License

This repository does not currently include a license file. Contact the repository owner before reusing or distributing the source code outside its intended educational purpose.


# Curve Rate Calculator

## Overview
The **Curve Rate Calculator** is a C++ program designed to process interest rate curves, including spot, discount, and forward rate calculations. It parses input curve data, performs calculations for discrete and continuous rates, and outputs results in a user-friendly format. 

---

## Features
- **Parse Input Curves**: Reads input files containing curve data in a structured format.
- **Interest Rate Calculations**:
  - Spot to Discount Rate
  - Forward Rates (1-year and multi-year forward rates)
  - Discrete and Continuous Rate Conversions
- **Tabular Output**: Displays results in a columnar format for easy interpretation.

---

## Project Structure
```
CurveRateCalculator/
├── CMakeLists.txt       # Build system configuration
├── main.cpp             # Entry point of the program
├── CurveCalculator.cpp  # Implementation of rate calculations
├── CurveCalculator.h    # Header for rate calculations
├── CurveReader.cpp      # Implementation of file reading
├── CurveReader.h        # Header for file reading
```

---

## Prerequisites
Before building and running the program, ensure the following software is installed:
- A C++ compiler supporting **C++17** or later (e.g., GCC, Clang, or MSVC).
- **CMake** (version 3.10 or higher) to manage the build system.

---

## Build and Run Instructions

### **Building the Project**
1. Clone or extract the project to your local system.
2. Open a terminal in the project directory.
3. Run the following commands to build the project:

   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

### **Running the Program**
Once built, execute the program from the build directory:

```bash
./CurveRateCalculator
```

---

## Input File Format
The program accepts an input file with the following structure:

1. **First Line**: Specifies the type of curve (`spot`, `fwd`, or `disc`).
2. **Subsequent Lines**: Contain `year rate` pairs, where:
   - `year`: A positive integer indicating the year.
   - `rate`: A floating-point value representing the interest rate.

### **Example Input File**
```
spot
1 0.03
2 0.032
3 0.035
4 0.04
```

---

## Output
The program calculates and outputs:
- **Discrete and Continuous Forward Rates**:
  - 1-year forward rates.
  - Multi-year forward rates (e.g., 2-year forward, 3-year forward).
- **Spot and Discount Rates** (if applicable).

The results are displayed in a tabular format where each forward rate (e.g., `fwd1yr`, `fwd2yr`) is shown as a column, and years are displayed as rows.

### **Sample Output**

#### Discrete Forward Rates:
```
   Year       fwd1yr       fwd2yr       fwd3yr       fwd4yr
      1       0.02      0.0224      0.0228      0.0232
      2      0.025      0.0276      0.0282      0.0288
      3       0.03      0.0330      0.0336      -
      4      0.035      0.0386      -           -
      5       0.04      -           -           -
```

#### Continuous Forward Rates:
```
   Year       fwd1yr       fwd2yr       fwd3yr       fwd4yr
      1       0.02      0.0220      0.0240      0.0260
      2      0.024      0.0265      0.0285      0.0305
      3      0.028      0.0309      0.0329      -
      4      0.032      0.0353      -           -
      5      0.036      -           -           -
```

---

## Files Description

### **1. `main.cpp`**
- The main entry point of the application.
- Handles program initialization, input reading, and function calls for curve calculations.

### **2. `CurveCalculator.cpp` / `CurveCalculator.h`**
- Implements core logic for interest rate calculations, including:
  - Spot to Discount Rate Conversion
  - Forward Rate Calculations (Discrete and Continuous)
  - Multi-Year Forward Rates

### **3. `CurveReader.cpp` / `CurveReader.h`**
- Handles input file parsing.
- Reads and validates curve data for further processing.

---

## Example Workflow
1. Prepare an input file (`input.txt`) with the appropriate structure.
2. Build and run the program.
3. Provide the input file when prompted.
4. View the tabular results in the terminal.

---

## Known Limitations
- Assumes the input file is well-structured and contains valid data.
- Rates beyond the input range are not extrapolated.

---

## License
This project is distributed under the MIT License. See `LICENSE` for more information.

---

## Authors
Developed by Mackenzie Qu.


Automatic License Plate Recognition (OCR)
==============================

This Windows application allows users to select an image containing a vehicle license plate, run OCR using Tesseract, and verify whether the recognized number is a valid Romanian license plate. The interface also features an automatic day/night theme.

1. REQUIREMENTSTo run this program, you will need:Operating System: Windows (7, 10, or 11)
* A C compiler compatible with Windows API (e.g., MinGW or MSVC)
* Tesseract OCR installed with English language support
* Tesseract added to the system PATH variable (this is done automatically if you check the option during installation)



2. INSTALLATION
1. Download and install the Tesseract executable:
   * https://github.com/UB-Mannheim/tesseract/wiki
   or use the installer attached in the folder.

   Make sure to:
   * Check “Add to PATH” during installation
   * Install the English language pack (enabled by default)

2. Compile the .c file using MinGW.


3. USAGE
   1. Run rec.exe
   2. Select one of the sample images from the attached folder to test license plate recognition.
   3. The program will automatically display the recognized text and indicate whether the license plate is valid or not.

5. COMMON ISSUES
* Error opening OCR result  
  * Verify that tesseract.exe is correctly added to your system PATH.  
  * Make sure the selected image is sharp and the license plate text is clearly visible.



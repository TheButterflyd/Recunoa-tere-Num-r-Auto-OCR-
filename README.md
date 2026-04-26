==============================
Recunoaștere Număr Auto (OCR)
==============================

Acest program Windows permite utilizatorului să selecteze o imagine conținând un număr de înmatriculare auto, să ruleze OCR folosind Tesseract, și să verifice dacă numărul recunoscut este unul românesc valid. Interfața include și o temă automată zi/noapte.

--------------
1. CERINȚE
--------------

Pentru a rula acest program, ai nevoie de:

- Sistem de operare: Windows (7, 10, 11)
- Un compilator C compatibil cu Windows API (ex: MinGW sau MSVC)
- [Tesseract OCR](https://github.com/tesseract-ocr/tesseract) instalat cu limba engleză activată
- Tesseract adăugat în variabila de sistem PATH (se face automat dacă bifezi opțiunea la instalare)

--------------
2. INSTALARE
--------------

1. Descarcă și instalează EXECUTABILUL Tesseract:
   https://github.com/UB-Mannheim/tesseract/wiki ori de aici, ori executabilul cel atasat in folder.

   Asigură-te că:
   - bifezi „Add to PATH”
   - limba „eng” este instalată (implicită)
2. Compilează fișierul `.c` cu MinGW.

--------------
3. UTILIZARE
--------------

1.Ruleaza rec.exe
2.Selecteaza 1 poza din cele atasate din folder pentru a recunoaste numarul de inmatriculare daca e valid sau nu.
3.Programul iti va afisa automat textul citit si mesajul daca numarul este valid sau nu.

--------------
4. BUGURI COMUNE
--------------

 Dacă apare mesajul „Eroare la deschiderea rezultatului OCR”:
   - Verifică dacă `tesseract.exe` se află în PATH
   - Verifică dacă imaginea e clară și lizibilă


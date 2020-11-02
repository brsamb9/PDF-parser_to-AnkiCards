
# Purpose: 
## Automate generation of anki flash cards from a PDF's glossary section.
<br>
<br>
# IMPORTANT:
<br>
Since every book has different rules, you need to tailor this 'ruleset' (in main.cpp) to yours.
No guarentees this will work for your case. This was a quick project to parse the glossary of the book to import as anki cards.
<br>
<br>
# Requirements:
linux & 'pdftotext' tool in the popplers.utils package
<br>
Can extend in code.
<br>

Designed for soley text input.
<br>
<br>
To use:
<br>
g++ main.cpp flash_card.cpp parse_text_file.cpp 
<br>
./a.out *file.pdf*
<br>
<br>
This will output a Anki_to_import.txt file. Then go to the Anki app to import (should automatically import correctly).

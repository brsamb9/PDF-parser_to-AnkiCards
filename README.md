
# Purpose: 
## Automate generation of anki flash cards with glossary key words and their respective definitions.
<br>
## Requirements:
linux & 'pdftotext' tool in the popplers.utils package
<br>
Can extend in code.
<br>
# IMPORTANT:
<br>
Change the following ruleset class for your chosen pdf. No guarentees this will work for your case. This was a quick project to parse the glossary of the book to import as anki cards.
<br>
<br>
Designed for soley text input.
<br>
<br>
Used by:
<br>
g++ main.cpp flash_card.cpp parse_text_file.cpp 
./a.out *file.pdf*

This will output a Anki_to_import.txt file. Then go to the Anki app to import (should automatically import correctly).

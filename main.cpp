/*
Purpose: 
Automate generation of anki flash cards with glossary key words and their respective definitions.

Requirements:
linux tool 'pdftotext' in the popplers.utils package

IMPORTANT:
    Change the following ruleset class for your chosen pdf

*/
#include <bits/stdc++.h>
#include "flash_card.h"
#include "parse_text_file.h"

/////////////////////////////////////////////////////////////////////////////////////////
// Put this class at the top to stress importance of tailoring it to the chosen pdf
class Ruleset
{
public:
    std::string glossary_key_word = "Defined Terms";
    std::vector<std::string>
        breaks{"Chapter", "Part", "Appendix"};
    std::vector<std::string> filler{"C++ Primer"};

    Ruleset() = default;
    bool transition_rule(char c);
    bool rule_of_book(std::string curr, char following_char, std::string keyword);
    // #####################################################
};

bool Ruleset::transition_rule(char c)
{
    return (isupper(c) || (c == ',')) ? true : false;
};
// rule following key_word
bool Ruleset::rule_of_book(std::string curr, char following, std::string kw)
{
    // In book i'm using, the key words starts with lowercase. Bizare.
    return (curr == kw && islower(following)) ? true : false;
};
/////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Error: require a pdf input argument\n");
        return 1;
    }

    std::string pdf_name = argv[1];
    if (pdf_name.find(".pdf") == std::string::npos)
    {
        fprintf(stderr, "Error: not a pdf input\n");
        return 1;
    }

    // file name with text extension
    std::string text_name = pdf_name.substr(0, pdf_name.find('.')).append(".txt");

    // convert pdf to text file
#ifdef unix
    std::string cmd = "pdftotext ";
    cmd.append(pdf_name + ' ' + text_name);
    system(cmd.c_str());
#else
    fprintf(stderr, "Not designed for this operating system. Only linux so far\n");
    return 1;
#endif

    Ruleset ruleset = Ruleset();

    // Open up text file (tf)
    // removing fillers and empty lines

    parse_file(text_name.c_str(), ruleset.filler);

    // After removing the junk
    std::fstream tf;
    tf.open(text_name, std::ios::in);
    bool record = false;

    std::vector<FlashCard> cards;

    size_t chapter{1};

    std::string whole_card;
    std::string line;
    while (getline(tf, line))
    {
        // Start 'recording' the following lines
        if (!record && ruleset.rule_of_book(line, tf.peek(), ruleset.glossary_key_word))
            record = true;

        else if (record)
        {
            if (cmp_line(line, ruleset.breaks, 0))
            {
                record = false;
                ++chapter;
            }

            else
            {
                // End of line and card
                whole_card += " " + line;
                if (line.back() == '.' && (islower(tf.peek()) || !isalpha(tf.peek())))
                {
                    // cout << chapter << " " << whole_card << endl;

                    int i{0};
                    while (!ruleset.transition_rule(whole_card[i]))
                        ++i;

                    FlashCard new_card;
                    new_card.chapter = chapter;
                    // No 'catches' to transition from front to back card - given arbiturary three word
                    if (whole_card.length() < i)
                    {
                        // second word
                        int j{1};
                        while (!isspace(whole_card[j++]))
                        {
                        }
                        new_card.front = whole_card.substr(0, j);
                        new_card.back = whole_card.substr(j);
                    }
                    else
                    {
                        new_card.front = whole_card.substr(0, i);
                        new_card.back = whole_card.substr(i);
                    }

                    //Minor edge cases -> assumed end of card but have following back text
                    //https://stackoverflow.com/questions/10268872/c-fstream-function-that-reads-a-line-without-extracting

                    cards.push_back(new_card);

                    // reset whole_card
                    whole_card = "";
                }
            }
        }
    }
    // current state, not perfect. but good enough

    // closes and removes temp text file
    tf.close();
    remove(text_name.c_str());

    // output
    std::ofstream output;
    output.open("Anki_to_import.txt", std::ios::out);

    for (FlashCard c : cards)
    {
        output << "Chapter_" << c.chapter << ": " << c.front << "\t" << c.back
               << "\n";
    }

    output.close();

    return 0;
}


#include "parse_text_file.h"

// ############
void parse_file(const char *file_name, std::vector<std::string> &filler)
{
    /*
    Creates a temporary file 
    scans the input file that was converted to text, to remove the whitelines and filler lines
    Replaces text file with the corrected temp file
    */
    std::ifstream fin;
    fin.open(file_name, std::ios::in);

    std::ofstream fout;
    fout.open("temp.txt", std::ios::out);

    std::string line;
    while (fin)
    {
        std::getline(fin, line);
        if (!(cmp_line(line, filler) || line.empty()))
        {
            fout << line << std::endl;
        }
    }
    fin.close();
    fout.close();

    remove(file_name);
    rename("temp.txt", file_name);
}

bool cmp_line(const std::string &line, const std::vector<std::string> &vec, const size_t n)
{
    /*
    Creates an array to fill with positions.
    These positions correspond to the elements of vec, to see if they are in the line or not.
    Given n, a different behaviour - probably should've done two seperate functions!
    */
    std::vector<std::size_t> arr;
    // find elements of the given vector in the line. Push to vector
    for (std::string s : vec)
        arr.push_back(line.find(s));

    // want to know if any found substrings at n
    switch (n)
    {
    case std::string::npos:
        for (size_t e : arr)
            if (e != n)
                return true;
        return false;
        break;
    // else, want to know if there is a 'hit' at a certain position
    default:
        for (size_t e : arr)
            if (e == n)
                return true;
        return false;
        break;
    }
}
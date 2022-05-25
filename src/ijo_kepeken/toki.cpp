#include "toki.hpp"


namespace kepeken {
    /**
     * @brief nanpa sitelen ken lon sitelen 1 tan fmtPrintLine().
     */
    constexpr int suliLinja = 75;

    void fmtPrintLine(std::ostream &os, const std::string &s, const int indentTabs, int secondLineOffset) {
        const std::string splitChars(" ,|");
        int maxChars = suliLinja - indentTabs;
        std::string indentString(indentTabs, '\t');
        int from = 0;
        int to = 0;
        int end = s.length();
        for (;;) {
            if (end - from <= maxChars) {
                // Rest of string fits on line, just print the remainder
                os << indentString << s.substr(from) << std::endl;
                return;
            }

            // Find the next place where it is good to break the string
            // (to) by finding the place where it is too late (tooFar) and
            // taking the previous one.
            int tooFar = to;
            while (tooFar - from <= maxChars &&
                static_cast<std::size_t>(tooFar) != std::string::npos) {
                to = tooFar;
                tooFar = s.find_first_of(splitChars, to + 1);
            }

            if (to == from) {
                // In case there was no good place to break the string,
                // just break it in the middle of a word at line length.
                to = from + maxChars - 1;
            }

            if (s[to] != ' ') {
                // Include delimiter before line break, unless it's a space
                to++;
            }

            os << indentString << s.substr(from, to - from) << '\n';

            // Avoid printing extra white space at start of a line
            for (; s[to] == ' '; to++) {
            }
            from = to;

            if (secondLineOffset != 0) {
                // Adjust offset for following lines
                indentString.insert(indentString.end(), secondLineOffset, '\t');
                maxChars -= secondLineOffset;
                secondLineOffset = 0;
            }
        }
    }
}
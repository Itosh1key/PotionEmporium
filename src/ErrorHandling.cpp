#include <cstdlib>  // for std::exit
#include <iostream> // for std::cin -- ignore(), eof(), clear(), peek()
#include <limits>   // for std::numeric_limits

namespace ErrorHandling
{
    void ignoreLine()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // returns true if extraction failed, false otherwise
    bool clearFailedExtraction()
    {
        // Check for failed extraction
        if (!std::cin) // If the previous extraction failed
        {
            if (std::cin.eof()) // If the stream was closed
            {
                std::exit(0); // Shut down the program now
            }

            // Let's handle the failure
            std::cin.clear(); // Put us back in 'normal' operation mode
            ignoreLine();     // And remove the bad input

            return true;
        }

        return false;
    }

    // returns true if std::cin has unextracted input on the current line, false otherwise
    bool hasUnextractedInput()
    {
        return !std::cin.eof() && std::cin.peek() != '\n';
    }
} 
// namespace ErrorHandling


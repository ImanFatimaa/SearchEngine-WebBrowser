//as we used experimental/filesystem so to handle the warning   predefining it
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

//all libraries that we needed in the code

#include <string>
#include <vector>
#include <fstream>
#include <experimental/filesystem>
#include <sstream>
#include <algorithm> 
#include <msclr/marshal_cppstd.h>

// move the searchengine class definition outside of the MyForm class because standard class cannot bepartof managed class
class searchengine {
public:
    //basic parameterized constructor that initializes the directory path and query

    searchengine(const std::string& path, const std::string& q) {
        directorypath = path;

        if (isQuery(q)) {  //if a query is entered
            //remove symbols from query
            query = removesymbols(q);
            parsequery();
        }
        else { //if a path is entered
            query = q;

        }
    }
    //calling function 

    void search() {
        if (isQuery(query)) {
            //calling the function to get the file names related to user query

            getfilenames();
            //calling the function to search the files

            searchfiles();
        }
        else {
            getfile();
        }
    }
    bool isQuery(const std::string& input) {
        // check if the input contains any invalid characters for a path
        for (char c : "*?\"<>|") {
            if (input.find(c) != -1) {
                //consider it a query
                return true;
            }
        }

        // check if the input starts with a valid drive letter followed by a colon
        if (input.size() >= 2 && std::isalpha(input[0]) && input[1] == ':') {
            // consider it a path
            return false;
        }

        // consider it a query if it doesn't match any of the above conditions
        return true;
    }


    // the function returns a constant reference to the pairs where each pair consists of 
  // the file path and the count of query word count in that file
    const std::vector<std::pair<std::string, int>>& getmatchingfiles() const {
        return matchingfiles;
    }

    //return filenames
    const std::vector<std::string> getbackfilename() {
        return filenames11;
    }


    //to read the content and get the content in the files

    std::string getfilecontent(const std::string& filepath) {
        //creating input file stream to read the specficed file data

        std::ifstream file(filepath);
        //if file is not opened than printing that the specified fill cannot be opened

        if (!file.is_open()) {
            return "cannot open the file: " + filepath;
        }
        //create string stream object to store the data of file

        std::stringstream buffer;
        //read entire content of file into buffer 

        buffer << file.rdbuf();
        //close the file once it reached the end

        file.close();
        //return the content in buffer as a string

        return buffer.str();
    }
private:
    //private attributes for the engine class
    std::string directorypath; //path of directory
    std::string query; //query by user
    std::vector<std::string> filenames; //vector to stores all related files
    std::vector<std::string> queri; //vector to store queries after removing and or
    bool an = false; //boolean to check if user entered and, or
    bool or1 = false;
    //vector pair to return the file path and the count of query word count in that file
    std::vector<std::pair<std::string, int>> matchingfiles;
    std::vector<std::string> filenames11; //vector to stores all related files

    void getfilenames() {
        // iterate over all files and directories in the directory specified by path,including all subdirectories
        //using a recursive_directory_iterator from the experimental filesystem library to iterate overall

        for (const auto& p : std::experimental::filesystem::recursive_directory_iterator(directorypath)) {

            //checks that the path is regular file or directory if it is a regular file than its pushed into a vector
            if (std::experimental::filesystem::is_regular_file(p.path())) {

                //pushing path in vector after converting into string
                filenames.push_back(p.path().string());
            }
        }
    }
    void getfile() {
        // iterate over all files and directories in the directory specified by path,including all subdirectories
        //using a recursive_directory_iterator from the experimental filesystem library to iterate overall

        for (const auto& p : std::experimental::filesystem::recursive_directory_iterator(query)) {

            //checks that the path is regular file or directory if it is a regular file than its pushed into a vector
            if (std::experimental::filesystem::is_regular_file(p.path())) {

                //pushing path in vector after converting into string
                filenames11.push_back(p.path().string());
            }
        }
    }

    // function to remove symbols and punctuation from a string
    std::string removesymbols(const std::string& str) {
        std::string result;
        for (char c : str) {
            if (std::isalnum(c) || std::isspace(c)) {
                result.push_back(c);
            }
        }
         return result;
    }
    //make case insensitive
    std::string tolowercase(const std::string& str) {
        std::string lower;
        lower.reserve(str.size()); // reserve space for efficiency
        for (char c : str) {
            lower.push_back(std::tolower(c));
        }
        return lower;
    }

    //function to further process the queries
    void parsequery() {
        //to check if AND OR are found if found returns the position of accurance else returns the std::string::npos 

        an = query.find("AND") != -1;
        or1 = query.find("OR") != -1;

        //if and is found
        if (an) {
            // split the query string into parts using a space as the delimiter and store the parts in queri

            queri = split(query, ' ');

            //iterator to iterate till we find AND
            auto it = std::find(queri.begin(), queri.end(), "AND");

            //if AND isfound remove it from query vector

            if (it != queri.end()) {
                queri.erase(it);
            }
        }

        //if or is found

        else if (or1) {
            // split the query string into parts using a space as the delimiter and store the parts in queri

            queri = split(query, ' ');

            //iterator to iterate till we find OR
            auto it = std::find(queri.begin(), queri.end(), "OR");
            //if AND isfound remove it from query vector

            if (it != queri.end()) {
                queri.erase(it);
            }
        }
        else {
            //if there is no AND OR than push back whole query is a single element
            queri.push_back(query);
        }
    }

    //split function that is used in parsequery

    std::vector<std::string> split(const std::string& q, char d) {

        // create a vector to store the split word
        std::vector<std::string> word;

        std::string w;

        // iterate over each character in the input string q
        for (char c : q) {

            //if current character is not the delimiter than add it in the current word
            if (c != d) {
                w += c;
            }
            else {
                //if current chv aracter is delimiter
                if (!w.empty()) {
                    //if current word is not empty add it to vector

                    word.push_back(w);
                    //clear the word so it can store new word without adding to previous one
                    w.clear();
                }
            }
        }
        //if after complete iteration word is not empty add it to the vector
        if (!w.empty()) {
            word.push_back(w);
        }
        //return the vector array
        return word;
    }
    // function to count the occurrences of a query
    int countoccurrences(const std::string& content, const std::string& word) {
        int count = 0; //occurence varriable /frequency

        //varriable to intialize position to zero of string
        int pos = 0;

        // loop through the content and find occurrenc
        while ((pos = tolowercase(content).find(tolowercase(word), pos)) != -1) {
            //increment the count of occurence of word

            ++count;

            // move position to the end of the word to continue searching
            pos += word.length();
        }
        //return the occurence of word
        return count;
    }
    void searchfiles() {
        // iterate through all files
        for (const std::string& f : filenames) {
            int t_count = 0; // variable for count of occurrences of query  for the current file
            std::string content = tolowercase(getfilecontent(f)); // get the content of the current file

            // searching for all words
            if (an) {
                bool allfound = true; // initialize a flag indicating if all words are found
                for (const std::string& q : queri) {
                    int count = countoccurrences(content, tolowercase(q)); // count occurrences of each query word
                    if (count == 0) {
                        allfound = false; // if any query word is not found set the flag to false
                        break;
                    }
                    t_count += count; // accumulate the total count of occurrences for all query
                }
                if (allfound) {
                    matchingfiles.emplace_back(f, t_count); // all query words are found add the file to matchingfiles with its total count
                }
            }
            // searching for any words
            else if (or1) {
                bool anyfound = false; // initialize a flag indicating if any query word is found
                for (const std::string& q : queri) {
                    int count = countoccurrences(content, tolowercase(q)); // count occurrences of each query word
                    if (count > 0) {
                        anyfound = true; // any query word is found set the flag to true
                        t_count += count; // total count of occurrences for all found query words
                    }
                }
                if (anyfound) {
                    matchingfiles.emplace_back(f, t_count); // any query word is foun add the file to matchingfiles with its total count
                }
            }
            //searching for a single word
            else {
                t_count = countoccurrences(content, tolowercase(queri[0])); // count occurrences of the single query word in the content
                if (t_count > 0) {
                    matchingfiles.emplace_back(f, t_count); //query word is found add the file to matchingfiles with its total count

                   
                }
            }
        }
       
        //sorting of matching  fies in descending order
        std::sort(matchingfiles.begin(), matchingfiles.end(), [](const auto& a, const auto& b) { return a.second > b.second; });
    }
    
};


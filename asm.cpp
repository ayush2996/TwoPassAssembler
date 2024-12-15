//AYUSH KUMAR SINGH 2301AI45


#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <set>
#include <map>
#include <vector>   
#include <unordered_map>
#include <unordered_set>
#include <cstdlib>
#include <regex>
#include <bitset>
#include <cmath>
#include <stdexcept>
#include <utility>
#include <exception>
#include <stdexcept>



using namespace std;
int binaryToInt(const std::string &binaryStr)
{
    int result = 0;
    int length = binaryStr.length();

    for (int i = 0; i < length; ++i)
    {
        // Check if each character is '1' or '0'
        if (binaryStr[i] == '1')
        {
            result += std::pow(2, length - i - 1);
        }
        else if (binaryStr[i] != '0')
        {
            throw std::invalid_argument("Invalid binary string");
        }
    }
    return result;
}

// Removes leading and trailing whitespace from a string
string remove_whitespace(const string &s)
{
    auto left = find_if_not(s.begin(), s.end(), ::isspace);
    auto right = find_if_not(s.rbegin(), s.rend(), ::isspace).base();
    return (left < right) ? string(left, right) : "";
}

int hexToInt(const std::string &hexStr)
{
    int result;
    std::stringstream ss;

    // Set the stream to interpret the number as hexadecimal
    ss << std::hex << hexStr;
    ss >> result;

    return result;
}

// Strips comments and trims whitespace from code line

string remove_comments(const string &line)
{
    size_t comment_start = line.find(';');
    string code_part = (comment_start != string::npos) ? line.substr(0, comment_start) : line;
    return remove_whitespace(code_part);
}

// Checks if the file has a .asm extension

bool isAsmFile(const string &filename)
{
    string extension = ".asm";
    return (filename.size() >= extension.size() && filename.compare(filename.size() - extension.size(), extension.size(), extension) == 0);
}

// Validates the starting character of a label
bool check_init(char c)
{
    return isalpha(c) || c == '_';
}

// Validates subsequent characters in a label
bool check_else(char c)
{
    return isalnum(c) || c == '_';
}

// Checks if the label is valid
bool verify_label(string &label)
{
    if (label.empty() || !check_init(label[0]))
        return false;

    for (char ch : label)
    {
        if (!check_else(ch))
            return false;
    }
    return true;
}

// Checks if a string is a valid integer or hexadecimal number
bool isValidNumber(const string &operand)
{
    if (operand.empty())
        return false;

    size_t pos = (operand[0] == '-' || operand[0] == '+') ? 1 : 0;
    bool isHex = (operand.size() > pos + 1 && operand[pos] == '0' && (operand[pos + 1] == 'x' || operand[pos + 1] == 'X'));

    if (isHex)
        pos += 2;

    for (size_t i = pos; i < operand.size(); i++)
    {
        if ((isHex && !isxdigit(operand[i])) || (!isHex && !isdigit(operand[i])))
        {
            return false;
        }
    }
    return true;
}

int instruction_table(std::string s)
{
    std::map<std::string, int> instruction_table;
    instruction_table["data"] = 0;
    instruction_table["ldc"] = 1;
    instruction_table["adc"] = 2;
    instruction_table["ldl"] = 3;
    instruction_table["stl"] = 4;
    instruction_table["ldnl"] = 5;
    instruction_table["stnl"] = 6;
    instruction_table["add"] = 7;
    instruction_table["sub"] = 8;
    instruction_table["shl"] = 9;
    instruction_table["shr"] = 10;
    instruction_table["adj"] = 11;
    instruction_table["a2sp"] = 12;
    instruction_table["sp2a"] = 13;
    instruction_table["call"] = 14;
    instruction_table["return"] = 15;
    instruction_table["brz"] = 16;
    instruction_table["brlz"] = 17;
    instruction_table["br"] = 18;
    instruction_table["HALT"] = 19;
    if (instruction_table.find(s) != instruction_table.end())
    {
        return instruction_table[s];
    }
    return -1;
}

string int_to_hex(int a, int width = 8)
{
    if (a == -1)
        return "Error";
    stringstream ss;
    ss << uppercase << hex << setw(width) << setfill('0') << (a & 0xFF); // Mask to 8 bits
    return ss.str();
}

std::string binary_to_hex(const std::string &binary)
{
    if (binary == "-1")
        return "Error";
    static const std::unordered_map<std::string, char> bin_to_hex = {
        {"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'}, {"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'}, {"1000", '8'}, {"1001", '9'}, {"1010", 'A'}, {"1011", 'B'}, {"1100", 'C'}, {"1101", 'D'}, {"1110", 'E'}, {"1111", 'F'}};

    std::string hex;
    for (size_t i = 0; i < binary.size(); i += 4)
    {
        // Extract a 4-bit chunk
        std::string chunk = binary.substr(i, 4);

        // Map the 4-bit chunk to its hexadecimal equivalent
        hex += bin_to_hex.at(chunk);
    }

    return hex;
}

void write_to_file(ofstream &file, const string &content)
{
    file << content;
    if (!file)
    {
        throw runtime_error("Failed to write to file");
    }
}
std::string int_to_bin(int num)
{
    if (num == -1)
        return "Error";
    return std::bitset<8>(num).to_string();
}
struct error
{

    int iber;
    string message;
    error(int line, string msg) : iber(line), message(msg) {}
};

struct warning
{
    int iber;
    string message;
    warning(int line, string msg) : iber(line), message(msg) {}
};

bool require_oper(const string &token)
{
    return (token != "add" && token != "sub" && token != "shl" && token != "shr" && token != "a2sp" && token != "sp2a" && token != "return" && token != "HALT");
}
bool require_num(const string &token)
{
    return (token != "add" && token != "sub" && token != "shl" && token != "shr" && token != "a2sp" && token != "sp2a" && token != "return" && token != "HALT" && token != "brz" && token != "brlz" && token != "br" && token != "call");
}

void insert_error(vector<error> &error_list, int line_num, const string &message)
{

    error_list.push_back(error(line_num, message));
}



// function to implement first pass................
void perform_first_pass(vector<string> &lines, map<string, int> &symbols, vector<error> &error_list, vector<warning> &warning_list, vector<pair<int, string>> &forward_refs)
{
    int program_counter = 0;
    bool halt_found = false;
    set<string> referenced_labels;

    for (int line_num = 0; line_num < lines.size(); line_num++)
    {
        istringstream line_stream(lines[line_num]);
        string word;

        // Get the first word in the line
        line_stream >> word;
        if (word.empty())
            continue;

        // Process labels
        if (word.back() == ':')
        {
            string label_name = word.substr(0, word.length() - 1);

            // Validate and store label..........................
            if (!verify_label(label_name))
            {
                insert_error(error_list, line_num + 1, "Invalid label name '" + label_name + "'");
                continue;
            }

            // checking the presence of duplicates........................
            if (symbols.find(label_name) != symbols.end())
            {
                insert_error(error_list, line_num + 1, "Duplicate label definition '" + label_name + "'");
                continue;
            }

            // Store the current program counter value for the label...............................
            symbols[label_name] = program_counter;

            // Check for inline instruction
            if (!(line_stream >> word))
            {
                continue; // No instruction after label
            }
        }

        // Process inline labels (label:instruction format)...................eg(label:A)
        size_t colon_pos = word.find(':');
        if (colon_pos != string::npos)
        {
            string label_name = word.substr(0, colon_pos);
            string instruction = word.substr(colon_pos + 1);

            // Validate and store label
            if (!verify_label(label_name))
            {
                insert_error(error_list, line_num + 1, "Invalid label name '" + label_name + "'");
                continue;
            }

            if (symbols.find(label_name) != symbols.end())
            {
                insert_error(error_list, line_num + 1, "Duplicate label definition '" + label_name + "'");
                continue;
            }

            symbols[label_name] = program_counter;

            if (instruction.empty())
            {
                if (!(line_stream >> word))
                    continue;
            }
            else
            {
                word = instruction;
            }
        }

        // Only increment program counter for actual instructions (not empty lines or pure labels)
        if (instruction_table(word) != -1 && word != "SET")
        {
            program_counter++;
        }
    }
}




// function to implement 2nd pass..........................................
void second_pass(const vector<string> &lines_to_process, const vector<string> &original_lines, const map<string, int> &labels, vector<error> &error_log, vector<warning> &warning_log, ofstream &listing_out, vector<pair<int, string>> unresolved_labels, ofstream &binary_out)
{   
    int program_counter = 0;
    int code_index = 0;
    vector<string> binary_instructions;

    if (!listing_out.is_open() || !binary_out.is_open())
    {
        insert_error(error_log, -1, "Failed to open output files");
        return;
    }
    if (!error_log.empty())
        return;

    // Ensure unresolved labels can be resolved
    for (const auto &label_ref : unresolved_labels)
    {
        if (labels.find(label_ref.second) == labels.end())
        {
            insert_error(error_log, label_ref.first, "Undefined label '" + label_ref.second + "'");
            return;
        }
    }
    write_to_file(listing_out, "\nSymbol Table:\n");
    for (const auto &label : labels)
    {
        write_to_file(listing_out, "Label '" + label.first + "': 0x" + int_to_hex(label.second, 8) + "\n");
    }
    write_to_file(listing_out, "\n");

    write_to_file(listing_out, "PC (Hex) Machine Code Source Line\n");
    write_to_file(listing_out, "-------- ------------ ------------\n");

    for (size_t i = 0; i < original_lines.size(); ++i)
    {
        string line_without_comments = remove_comments(original_lines[i]);

        // Handle empty lines
        if (line_without_comments.empty())
        {
            write_to_file(listing_out, int_to_hex(program_counter, 8) + " N/A " + original_lines[i] + "\n");
            continue;
        }

        istringstream line_stream(line_without_comments);
        string word;
        line_stream >> word;

        // Handle labels d p:
        if (word.back() == ':')
        {
            string label = word.substr(0, word.length() - 1);
            if (!(line_stream >> word))
            { // No instruction after label
                write_to_file(listing_out, int_to_hex(program_counter, 8) + " N/A " + original_lines[i] + "\n");
                continue;
            }
        }

        // Handle label:instruction format
        size_t colon_pos = word.find(':');
        if (colon_pos != string::npos)
        {
            string instruction_part = word.substr(colon_pos + 1);
            if (!instruction_part.empty())
            {
                word = instruction_part;
            }
            else if (!(line_stream >> word))
            {
                write_to_file(listing_out, int_to_hex(program_counter, 8) + " N/A " + original_lines[i] + "\n");
                continue;
            }
        }

        // Get instruction opcode
        int opcode = instruction_table(word);
        if (opcode == -1)
        {
            continue; // Invalid instruction, should have been caught in first pass
        }

        string operand;
        line_stream >> operand;

        try
        {
            string machine_code;
            // if (word == "data")
            // {
            //     // Handle data instruction
            //     int value = (operand.substr(0, 2) == "0x" || operand.substr(0, 2) == "0X")
            //                     ? stoi(operand.substr(2), nullptr, 16)
            //                     : stoi(operand);
            //     machine_code = bitset<32>(value).to_string();
            // }
            if (word == "data")
            {
                // Handle data instruction
                int value = (operand.substr(0, 2) == "0x" || operand.substr(0, 2) == "0X")
                                ? stoi(operand.substr(2), nullptr, 16)
                                : stoi(operand);

                // Convert the value to binary and prepend 8 '1's
                string data_bits = bitset<24>(value).to_string(); // Remaining 24 bits for data
                machine_code = data_bits+"00000000";            // First 8 bits are all 1's
            }

            else if (word == "SET")
            {
                write_to_file(listing_out, int_to_hex(program_counter, 8) + " N/A " + original_lines[i] + "\n");
                continue;
            }
            else
            {
                // Handle regular instructions
                bitset<8> opcode_bits(opcode);
                string opcode_str = opcode_bits.to_string();

                if (require_oper(word))
                {
                    int value;
                    // In the second_pass function, modify the branch calculation:
                    if (labels.find(operand) != labels.end())
                    {//lable[opera d]
                        value = labels.at(operand);
                        if (word == "br" || word == "brz" || word == "brlz" || word == "call")
                        {
                            // Calculate relative offset
                            int target_address = value;
                            int current_address = program_counter;
                            value = target_address - (current_address );

                            // Write debug info to listing file
                            // write_to_file(listing_out, "\nDebug info for " + word + " " + operand + ":\n");
                            // write_to_file(listing_out, "Target address: 0x" + int_to_hex(target_address, 8) + "\n");
                            // write_to_file(listing_out, "Current address: 0x" + int_to_hex(current_address, 8) + "\n");
                            // write_to_file(listing_out, "Calculated offset: 0x" + int_to_hex(value, 8) + "\n\n");

                            // Handle negative values properly for 24-bit signed values
                            if (value < 0)
                            {
                                // Convert negative value to 24-bit two's complement
                                value = (value & 0x00FFFFFF);
                            }
                        }
                    }

                    else
                    {
                        value = (operand.substr(0, 2) == "0x" || operand.substr(0, 2) == "0X")
                                    ? stoi(operand.substr(2), nullptr, 16)
                                    : stoi(operand);
                    }
                    bitset<24> value_bits(value);
                    machine_code = value_bits.to_string() + opcode_str;
                }
                else
                {
                    machine_code = string(24, '0') + opcode_str;
                }
            }

            // Write machine code to files
            string hex_code = binary_to_hex(machine_code);
            write_to_file(listing_out, int_to_hex(program_counter, 8) + " " + hex_code + " " + original_lines[i] + "\n");

            uint32_t binary_value = bitset<32>(machine_code).to_ulong();
            binary_out.write(reinterpret_cast<const char *>(&binary_value), sizeof(binary_value));

            // Increment program counter for all instructions except SET
            if (word != "SET")
            {
                program_counter++;
            }
        }
        catch (const exception &e)
        {
            
            insert_error(error_log, i + 1, string("Error processing instruction: ") + e.what()+" "+word);
            return;
        }
    }
}
int main(int argc, char *argv[])
{
    // Ensure a single argument is passed
    if (argc != 2)
    {
        cout << "Please provide one .asm file to compile.\n";
        return 0;
    }

    string asm_filename = argv[1];
    if (!isAsmFile(asm_filename))
    {
        cout << "Error: Provided file does not have a .asm extension.\n";
        return 1;
    }

    ifstream asm_input(asm_filename);
    if (!asm_input)
    {
        cerr << "Error: Unable to open file " << asm_filename << "\n";
        return 1;
    }

    string current_line;
    vector<string> comments_collection, processed_lines, original_lines;

    while (getline(asm_input, current_line))
    {
        original_lines.push_back(current_line);

        size_t comment_start = current_line.find(';');
        string line_content = current_line.substr(0, comment_start);
        string comment = (comment_start != string::npos) ? current_line.substr(comment_start) : "";

        line_content.erase(line_content.find_last_not_of(" \t") + 1);
        if (!line_content.empty())
        {
            processed_lines.push_back(line_content);
        }

        comments_collection.push_back(comment); // Collect comments
    }
    string base_filename = asm_filename.substr(0, asm_filename.find_last_of('.'));
    vector<error> error_log;
    vector<warning> warning_log;
    map<string, int> label_lookup;
    vector<pair<int, string>> unresolved_labels;

    ofstream listing_output(base_filename + ".lst"), log_output(base_filename + ".log"), binary_output(base_filename + ".o", ios::binary);

    perform_first_pass(processed_lines, label_lookup, error_log, warning_log, unresolved_labels);

    if (!error_log.empty())
    {
        write_to_file(log_output, "\nErrors encountered during assembly:\n");
        // log_output << "\nErrors encountered during assembly:\n";
        cout << "\nErrors found. See log file for details.\n";
        for (const auto &err : error_log)
        {
            write_to_file(log_output, "Error" + (err.iber != -1 ? " at line " + to_string(err.iber) : "") + ": " + err.message + "\n");
        }
        write_to_file(log_output, "\nWarnings\n");
        // log_output << "\nWarnings:\n";
        for (const auto &warn : warning_log)
        {
            write_to_file(log_output, "Warning" + (warn.iber != -1 ? " at line " + to_string(warn.iber) : "") + ": " + warn.message + "\n");
        }
        return 1;
    }

    second_pass(processed_lines, original_lines, label_lookup, error_log, warning_log, listing_output, unresolved_labels, binary_output);
    // for (const auto &entry : label_lookup)
    // {

    //     cout << entry.first << " -> " << int_to_hex(entry.second, 2) << "\n";
    // }
    // Log warnings
    if (!warning_log.empty())
    {
        write_to_file(log_output, "\nWarnings:\n");
        // log_output << "\nWarnings:\n";
        for (const auto &warn : warning_log)
        {
            write_to_file(log_output, "Warning" + (warn.iber != -1 ? " at line " + to_string(warn.iber) : "") + ": " + warn.message + "\n");
        }
    }

    // Handle errors from second pass
    if (!error_log.empty())
    {
        cout << "\nErrors found; refer to the log file for details.\n";
        write_to_file(log_output, "\nErrors found during assembly:\n");

        for (const auto &err : error_log)
        {
            write_to_file(log_output, "Error" + (err.iber != -1 ? " at line " + to_string(err.iber) : "") + ": " + err.message + "\n");
        }
        return 1;
    }
    else
    {
        cout << "\nAssembly completed successfully!\n";
        if (!warning_log.empty())
        {
            cout << "\nWarnings:\n";
            for (const auto &warn : warning_log)
            {

                cout << "Warning" << (warn.iber != -1 ? " at line " + to_string(warn.iber) : "")
                     << ": " << warn.message << "\n";
            }
        }
    }

    asm_input.close();
    listing_output.close();
    log_output.close();
    binary_output.close();
    return 0;
}

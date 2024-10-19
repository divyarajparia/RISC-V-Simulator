#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<bitset>
#include<vector>
#include<cstdlib>
#include <algorithm>
#include <cctype>
#include<map>

using namespace std;

//In this function we check the name of the register against all the real, as well as
//alias names of the 32 registers. If it is an alias name, convert it to the real name.
//If it is neither the alias, nor the real name, we throw an error
string aliasRemover(string r, int line_number, string reg_name) {
    if (r == "zero" || r == "x0") {
        r = "x0";
    } else if (r == "ra" || r =="x1") {
        r = "x1";
    } else if (r == "sp" || r =="x2") {
        r = "x2";
    } else if (r == "gp" || r=="x3") {
        r = "x3";
    } else if (r == "tp" || r == "x4") {
        r = "x4";
    } else if (r == "t0" || r == "x5") {
        r = "x5";
    } else if (r == "t1" || r =="x6") {
        r = "x6";
    } else if (r == "t2" || r == "x7") {
        r = "x7";
    } else if (r == "s0" || r == "fp" || r =="x8") {
        r = "x8";
    } else if (r == "s1" || r == "x9") {
        r = "x9";
    } else if (r == "a0" || r =="x10") {
        r = "x10";
    } else if (r == "a1" || r =="x11"){
        r = "x11";
    } else if (r == "a2" || r =="x12"){
        r = "x12";
    } else if (r == "a3" || r =="x13"){
        r = "x13";
    } else if (r == "a4" || r =="x14"){
        r = "x14";
    } else if (r == "a5" || r =="x15"){
        r = "x15";
    } else if (r == "a6" || r =="x16"){
        r = "x16";
    } else if (r == "a7" || r =="x17"){
        r = "x17";
    } else if (r == "s2" || r =="x18"){
        r = "x18";
    } else if (r == "s3" || r =="x19"){
        r = "x19";
    } else if (r == "s4" || r =="x20"){
        r = "x20";
    } else if (r == "s5" || r =="x21"){
        r = "x21";
    } else if (r == "s6" || r =="x22"){
        r = "x22";
    } else if (r == "s7" || r =="x23"){
        r = "x23";
    } else if (r == "s8" || r =="x24"){
        r = "x24";
    } else if (r == "s9" || r =="x25"){
        r = "x25";
    } else if (r == "s10" || r =="x26"){
        r = "x26";
    } else if (r == "s11" || r =="x27"){
        r = "x27";
    } else if (r == "t3" || r =="x28"){
        r = "x28";
    } else if (r == "t4" || r =="x29"){
        r = "x29";
    } else if (r == "t5" || r =="x30"){
        r = "x30";
    } else if (r == "t6" || r =="x31"){
        r = "x31";
    } else {
        cerr<<"Error in line: "<<line_number<<": Incorrect Register name: "<<reg_name<<endl;
        exit(0);
    }
        
    return r;
}


string regToBinary(string r, int line_number, string reg_name)
{
    //Converting the register to its real name in case of alias
    r = aliasRemover(r, line_number, reg_name);
    //cout<<r<<" ";
    int flag = 1;
    //Checking if the register is in range
    for(int i = 0; i < 32; i++)
    {
        int regNum = stoi(r.substr(1));
        if(regNum == i)
        {
            flag = 0;
        }
    }
    if(flag == 1)
    {
        cerr<<"Error in line "<<line_number<<": Register out of range: "<<reg_name<<endl;
        exit(0);
    }
    
    int regNum = stoi(r.substr(1)); 
   //cout<<regNum<<" ";

    //Converting the register name to its 5 bit binary
   if(regNum >= 0 && regNum <= 31)
   {
    bitset<5> binary(regNum);
    return binary.to_string();
   }
   else
   {
    return "";
   }
}

//We remove any leading or trailing commas that are there with a word
string removeCommas(string word)
{   
    while (!word.empty() && word.front() == ',') {
        word.erase(word.begin());
    }

    while (!word.empty() && word.back() == ',') {
        word.pop_back();
    }

    return word;
}


void rformat(string line, int line_number, map<string,int>labels, ofstream& outfile)
{
    //create an input string stream for the line
    istringstream iss(line);
    string inst, rd, rs1, rs2;
    string word;
    vector<string> words;
    iss>>word;
    //Checking if the first word is a label
    if(labels.find(word) != labels.end()){
        //do nothing, this is just a label
    }
    else{
        words.push_back(word);
    }
      while (iss >> word) {
        words.push_back(word);
    }

    //We check if the number of operands is correct(4) or not
    if (words.size() != 4) {
        cerr << "Error in line "<<line_number<<": Incorrect number of operands" <<endl;
        exit(0);
    }

    //Remove commas from all the operands
    inst = removeCommas(words[0]);
    rd = removeCommas(words[1]);
    rs1 = removeCommas(words[2]);
    rs2 = removeCommas(words[3]);
    //cout<<rd<<rs1<<rs2;

    string fn7, fn3, opcode;
    opcode = "0110011";//Setting the opcode for R type instructions
    
    //We now set the funct3 and funct7 values according to the respective instructions
    if(inst == "add"){
        fn3 = "000";
        fn7 = "0000000";
    }
    else if (inst == "sub"){
        fn3 = "000";
        fn7 = "0100000";
    }
    else if(inst == "and"){   
        fn3 = "111";
        fn7 = "0000000";
    }
    else if(inst == "or"){
        fn3 = "110";
        fn7 = "0000000";
    }
    else if(inst == "xor"){
        fn3 = "100";
        fn7 = "0000000";

    }
    else if(inst == "sll"){
        fn3 = "001";
        fn7 = "0000000";
    }
    else if(inst == "srl"){
        fn3 = "101";
        fn7 = "0000000";
    }
    else if(inst == "sra"){
        fn3 = "101";
        fn7 = "0100000";
    }
    else{
        cerr << "Error in line "<<line_number<<": Invalid Instruction entered"<<endl;
        exit(0);
    }

    //We now convert the registers to binary
    string binInst;
    rd = regToBinary(rd, line_number, "rd");
    rs1 = regToBinary(rs1, line_number, "rs1");
    rs2 = regToBinary(rs2, line_number, "rs2");
    //cout<<rd<<" "<<rs1<<" "<<rs1<<" "<<endl;
    
    //We now put everything together, by concatenating the register names, funct values, and opcode
    binInst = fn7 + rs2 + rs1 + fn3 + rd + opcode;


    bitset<32> binarySet(binInst);
    unsigned int number = binarySet.to_ulong();

    //Converting the number to hexadecimal
    stringstream ss;
    ss << hex << number;
    string hexStr = ss.str();
    int len = hexStr.length();
    int n = 8 - len;
    while(n)
    {
        hexStr = "0"+hexStr;
        n--;
    }
    //hexStr="0x"+hexStr;

    //Printing it out to the outfile
    outfile<<hexStr<<endl;
}

void iformatshift(string line, int line_number, map<string,int>labels, ofstream& outfile)
{
    //create and input stream fo the line
    istringstream iss(line);
    string inst, rd, rs1, imm;
    string word;
    vector<string> words;
    iss>>word;

    //we now read all the words in the line
    if(labels.find(word) != labels.end())
    {
        //do nothing, this is just a label
    }
    else
    {
        words.push_back(word);
    }

      while (iss >> word) {
        words.push_back(word);
    }


    //If the numer of words/operands do not match, we throw an error
    if (words.size() != 4) {
        cerr << "Error in line "<<line_number<<": Incorrect number of operands" <<endl;
        exit(0);
    }

    //Assigning values to the operands
    inst = words[0];
    rd = words[1];
    rs1 = words[2];
    imm = words[3];

    inst = removeCommas(inst);
    rd = removeCommas(rd);r
    rs1 = removeCommas(rs1);
    imm = removeCommas(imm);    

    //Checking if the immediate value is non-numeric
if(imm[0] == '-') {
    // Check if the rest of the string (after the '-') consists only of digits
    if(!all_of(imm.begin() + 1, imm.end(), ::isdigit)) {
        cerr <<"Error in line "<<line_number<<": Incorrect (Non-Numeric) immediate value entered"<<endl;
        exit(0);
    }
} else {
    // We check if all the characters are numeric
    if(!all_of(imm.begin(), imm.end(), ::isdigit)) {
        cerr <<"Error in line "<<line_number<<": Incorrect (Non-Numeric) immediate value entered"<<endl;
        exit(0);
    }
}
    //Convert the string to an immediate valued integer

    int im = stoi(imm);
    //Checking if the immediate value is in its allowed range
    if(im < 0 || im > 63)
    {
        cerr<<"Error in line "<<line_number<<": Immediate value out of range"<<endl;
        exit(0);
    }

    //Assigning the opcode value for I format shift instructions
    string opcode="0010011";
    string fn3, fn6;
    //We now assign the funct3 and funct6 values for different instuctions in this format
    if(inst == "slli")
    {
        fn3 = "001";
        fn6 = "000000";
    }
    else if(inst == "srli")
    {
        fn3 = "101";
        fn6 = "000000";
    }
    else if(inst == "srai")
    {
        fn3 = "101";
        fn6 = "010000";
    }
    else
    {
        cerr << "Error in line "<<line_number<<": Invalid Instruction entered"<<endl;
        exit(0);
    }
    //Converting the register names to their 5 bit binary representations
    rd = regToBinary(rd, line_number, "rd");
    rs1 = regToBinary(rs1, line_number, "rs1");
    //Converting the immediate value to integer
    int imm_val = stoi(imm.substr(0)); 
   //cout<<regNum<<" ";
    //Immediate value to 6 bit binary string
    bitset<6> binary(imm_val);
    imm = binary.to_string();
    //Putting it all together, concatenating the opcode, funct values, immediate values, and register values
    string binInst = fn6+imm+rs1+fn3+rd+opcode;

    //Converting the 32 bit binary to hex representations
    bitset<32> binarySet(binInst);
    unsigned int number = binarySet.to_ulong();

    stringstream ss;
    ss << hex << number;
    string hexStr = ss.str();
    int len = hexStr.length();
    int n = 8 - len;
    while(n)
    {
        hexStr = "0"+hexStr;
        n--;
    }
    //Writing to the outfile
    outfile<<hexStr<<endl;
}

//This function is used for isntructions in which the immediate value and rs value occur as one word, like sd rs2, imm(rs1)
void splitImmAndRs(string& s, string& imm, string& rs) {
    //We locate the parenthesis in the code
    size_t openParenPos = s.find('(');
    size_t closeParenPos = s.find(')');
    //The immediate value is the part before the parenthesis
    imm = s.substr(0, openParenPos);
    //The register name is inside the parenthesis
    rs = s.substr(openParenPos + 1, closeParenPos - openParenPos - 1);
}
void iformat(string line, int line_number, map<string,int>labels, ofstream& outfile)
{
    //Creating an input stream for the line
    istringstream iss(line);
    string inst, rd, rs1, imm;
    string word;
    vector<string> words;
    iss>>word;
    //Creating a vector containing all the words of this line
    if(labels.find(word) != labels.end())
    {
        //do nothing, this is just a label
    }
    else
    {
        words.push_back(word);
    }

      while (iss >> word) {
        words.push_back(word);
    }
    //Special case for jalr, which contains only 3 words jalr rd, imm(rs1)
    if(words[0] != "jalr")
    {
    if (words.size() != 4) {
        cerr << "Error in line "<<line_number<<": Incorrect number of operands" <<endl;
        exit(0);
    }
    }
    else 
    {
        if (words.size() != 3) {
        cerr << "Error in line "<<line_number<<": Incorrect number of operands" <<endl;
        exit(0);
    }
    }
    //Assigning values of words, handling differently for jalr as it has imm value and rs concatenated
    if(words[0] != "jalr")
    {

    inst = words[0];
    rd = words[1];
    rs1 = words[2];
    imm = words[3];
    }
    else
    {
        inst = words[0];
        rd = words[1];
        string s = words[2];
        splitImmAndRs(s, imm, rs1);
    }
    //Removing commas
    inst = removeCommas(inst);
    rd = removeCommas(rd);
    rs1 = removeCommas(rs1);
    imm = removeCommas(imm);    
    //Checking id the immediate value is numeric
    if(imm[0] == '-') {
    // Check if the rest of the string (after the '-') consists only of digits
    if(!all_of(imm.begin() + 1, imm.end(), ::isdigit)) {
        cerr <<"Error in line "<<line_number<<": Incorrect (Non-Numeric) immediate value entered"<<endl;
        exit(0);
    }
} else {
    // Check if all characters are numeric
    if(!all_of(imm.begin(), imm.end(), ::isdigit)) {
        cerr <<"Error in line "<<line_number<<": Incorrect (Non-Numeric) immediate value entered"<<endl;
        exit(0);
    }
}
    //Checking the range of the immediate value
    int im = stoi(imm);
    if(im < -2048 || im > 2047)
    {
        cerr<<"Error in line "<<line_number<<": Immediate value out of range"<<endl;
        exit(0);
    }
    //Storing the opcode and funct3 values, as defined for risc v
    string opcode;
    string fn3;
    if(inst=="addi"||inst=="xori"||inst=="ori"||inst=="andi"||inst=="jalr")
    {
        opcode = "0010011";
        if(inst == "addi")
        {
            fn3 = "000";
        }
        else if(inst == "xori")
        {
            fn3 = "100";
        }
        else if(inst == "ori")
        {
            fn3 = "110";
        }
        else if(inst=="andi")
        {
            fn3 = "111";
        }
        else if(inst=="jalr")
        {   
            opcode = "1100111";
            fn3="000";
        }
    }
    else
    {
        cerr << "Error in line "<<line_number<<": Invalid Instruction entered"<<endl;
        exit(0);
    }

    //Converting the registers to their 5 bit binary representation
    rd = regToBinary(rd, line_number, "rd");
    rs1 = regToBinary(rs1, line_number, "rs1");
    //Converting the immediate value to an integer
    int imm_val = stoi(imm.substr(0)); 
   //cout<<regNum<<" ";
    //Converting the integer immediate value to binary string
    bitset<12> binary(imm_val);
    imm = binary.to_string();
    //Putting it all together, concatenating the immediate, register, funct3, and opcode values
    string binInst = imm+rs1+fn3+rd+opcode;

    bitset<32> binarySet(binInst);
    unsigned int number = binarySet.to_ulong();
    //Converting to hex representation
    stringstream ss;
    ss << hex << number;
    string hexStr = ss.str();
    int len = hexStr.length();
    int n = 8 - len;
    while(n)
    {
        hexStr = "0"+hexStr;
        n--;
    }
    //Writing to the outfile
    outfile<<hexStr<<endl;
}

void iformatload(string line, int line_number, map<string,int>labels, ofstream& outfile)
{
    //Creating an input stream for the line
    istringstream iss(line);
    string inst, rd, rs1, imm;
    string word;
    vector<string> words;
    iss>>word;
    if(labels.find(word) != labels.end())
    {
        //do nothing, this is just a label
    }
    else
    {
        words.push_back(word);
    }

      while (iss >> word) {
        words.push_back(word);
    }
    //Checking if the number of operands is indeed correct, throwring an error if not
    if (words.size() != 3) {
        cerr << "Error in line "<<line_number<<": Incorrect number of opperands" <<endl;
        exit(0);
    }

    //Assigning the words to relevant operand names
    inst = words[0];
    rd = words[1];
    string s = words[2];
    splitImmAndRs(s, imm, rs1);
    
    //Removing commas
    inst = removeCommas(inst);
    rd = removeCommas(rd);
    rs1 = removeCommas(rs1);
    imm = removeCommas(imm);

    //Checking if the immediate value is numeric
    if(imm[0] == '-') {
    // Check if the rest of the string (after the '-') consists only of digits
    if(!all_of(imm.begin() + 1, imm.end(), ::isdigit)) {
        cerr <<"Error in line "<<line_number<<": Incorrect (Non-Numeric) immediate value entered"<<endl;
        exit(0);
    }
} else {
    // Check if all characters are numeric
    if(!all_of(imm.begin(), imm.end(), ::isdigit)) {
        cerr <<"Error in line "<<line_number<<": Incorrect (Non-Numeric) immediate value entered"<<endl;
        exit(0);
    }
}
    //Converting the immediate value to integer
    int imm_val = stoi(imm);
    //Verifying if the immediate value is in its allowed range
    if(imm_val < -2048 || imm_val > 2047)
    {
        cerr<<"Error in line "<<line_number<<": Immediate value out of range"<<endl;
        exit(0);
    }
    //Allocating opcodes and funct3 values for each instruction in this type
    string opcode, fn3;

    if(inst=="lb" || inst=="lh" || inst=="lw" || inst=="ld" || inst=="lbu" || inst=="lhu" || inst=="lwu")
    {
        opcode="0000011";
        if(inst=="lb")
        {
            fn3 = "000";
        }
        else if(inst=="lh")
        {
            fn3 = "001";
        }
        else if(inst=="lw")
        {
            fn3 = "010";
        }
        else if(inst=="ld")
        {
            fn3 = "011";
        }
        else if(inst=="lbu")
        {
            fn3 = "100";
        }
        else if(inst=="lhu")
        {
            fn3 = "101";
        }
        else if(inst=="lwu")
        {
            fn3 = "110";
        }
    }
    //Converting the registers to 5 bit binary strings
    rd = regToBinary(rd, line_number, "rd");
    rs1 = regToBinary(rs1, line_number, "rs1");

    // int imm_val = stoi(imm.substr(0)); 
   //cout<<regNum<<" ";
    //Converting the immediate value to 12 bit binary strings
    bitset<12> binary(imm_val);
    imm = binary.to_string();
    //Putting it all together, concatenating everythign we have calculated
    string binInst = imm+rs1+fn3+rd+opcode;
    //Converting 32 bit binary representation to unsigned long
    bitset<32> binarySet(binInst);
    unsigned int number = binarySet.to_ulong();
    //Converting it to hex
    stringstream ss;
    ss << hex << number;
    string hexStr = ss.str();
    int len = hexStr.length();
    int n = 8 - len;
    while(n)
    {
        hexStr = "0"+hexStr;
        n--;
    }
    //Writing to the outfile
    outfile<<hexStr<<endl;
}

void sformat(string line, int line_number, map<string,int>labels, ofstream& outfile)
{   //Creatign an input stream for the line
    istringstream iss(line);
    string inst, rs2, rs1, imm;
    string word;
    vector<string> words;
    iss>>word;
    if(labels.find(word) != labels.end())
    {
        //do nothing, this is just a label
    }
    else
    {
        words.push_back(word);
    }

      while (iss >> word) {
        words.push_back(word);
    }
    //Checking if the number of operands are correct
    if (words.size() != 3) {
        cerr << "Error in line "<<line_number<<": Incorrect number of operands" <<endl;
        exit(0);
    }
    //Giving appropriate names to the operan words
    inst = words[0];
    rs2 = words[1];
    string s = words[2];
    splitImmAndRs(s, imm, rs1);//Splitting the immediate value and register name, which is a single word

    inst = removeCommas(inst);
    rs2 = removeCommas(rs2);
    rs1 = removeCommas(rs1);
    imm = removeCommas(imm);

    
    if(imm[0] == '-') {
    // Check if the rest of the string (after the '-') consists only of digits
    if(!all_of(imm.begin() + 1, imm.end(), ::isdigit)) {
        cerr <<"Error in line "<<line_number<<": Incorrect (Non-Numeric) immediate value entered"<<endl;
        exit(0);
    }
} else {
    // Check if all characters are digits (no minus sign)
    if(!all_of(imm.begin(), imm.end(), ::isdigit)) {
        cerr <<"Error in line "<<line_number<<": Incorrect (Non-Numeric) immediate value entered"<<endl;
        exit(0);
    }
}   //Converting the immediate value to integer, and checking if it is in its allowed range
    int imm_val = stoi(imm);
    if(imm_val < -2048 || imm_val > 2047)
    {
        cerr<<"Error in line "<<line_number<<": Immediate value out of range"<<endl;
        exit(0);
    }
    //Assigning the opcode and funct3 values for the instructions of this type
    string opcode, fn3;

    if(inst=="sd" || inst=="sw" || inst=="sh" || inst=="sb" || inst=="jalr")
    {
        opcode="0100011";
        if(inst=="sd")
        {
            fn3 = "011";
        }
        else if(inst=="sw")
        {
            fn3 = "010";
        }
        else if(inst=="sh")
        {
            fn3 = "001";
        }
        else if(inst=="sb")
        {
            fn3 = "000";
        }
        else if(inst=="jalr")
        {
            opcode = "1100111";
            fn3 = "000";
        }
    }
    //Converting the registers to 5 bit binary 
    rs2 = regToBinary(rs2, line_number, "rs2");
    rs1 = regToBinary(rs1, line_number, "rs1");

    // int imm_val = stoi(imm.substr(0)); 
   //cout<<regNum<<" ";

    bitset<12> binary(imm_val);
    imm = binary.to_string();
    //Putting it all together according to the s format
    string binInst = imm.substr(0, 7) + rs2 + rs1 + fn3 + imm.substr(7, 5) + opcode;
    //Converting 32 bit binary to unsigned int
    bitset<32> binarySet(binInst);
    unsigned int number = binarySet.to_ulong();
    //Converting it to hex
    stringstream ss;
    ss << hex << number;
    string hexStr = ss.str();
    int len = hexStr.length();
    int n = 8 - len;
    while(n)
    {
        hexStr = "0"+hexStr;
        n--;
    }
    //Writing to the outfile
    outfile<<hexStr<<endl;
}

void bformat(string line, int line_number, map<string, int>labels, ofstream& outfile)
{   //Creating an input stream for the line
    istringstream iss(line);
    string inst, rs1, rs2, label;
    string word;
    vector<string> words;
    iss>>word;
    if(labels.find(word) != labels.end()){
        //do nothing, this is just a label
    }
    else{
        words.push_back(word);
    }

      while (iss >> word) {
        words.push_back(word);
    }
    //cout<<words.size();
    //Verifying that the number of operands is valid
    if (words.size() != 4) {
        cerr << "Error in line "<<line_number<<": Incorrect number of operands" <<endl;
        exit(0);
    }
    //Assigning the words to their appropriate operands
    inst = removeCommas(words[0]);
    rs1 = removeCommas(words[1]);
    rs2 = removeCommas(words[2]);
    label = removeCommas(words[3] + ':');
    
    //Finding the difference(in number of lines) between the current line andthe destination line
    int destination_line;
    if(labels.find(label) != labels.end())
    {
        destination_line = labels[label];
    }
    else
    {   //If the label does not exist in our labels map, throw an error
        cerr<<"Error in line: "<<line_number<<" Incorrect label specified"<<endl;
        exit(0);
    }
    //Finding the jump offset as difference of lines
    int offset = destination_line - line_number;
    string imm;
    
    //Each line(instruction) is 4 bits, hence we mutiply by 4 to get the offset in bits
    offset = offset * 4;
    //cout<<offset;
    //Find if the offset is in range
    if(offset < -4096 || offset > 4094){
        cerr<<"Error in line "<<line_number<<": Jump offset out of range"<<endl;
        exit(0);
    }
    //Storing the opcode and fn3 values for all insructions
    string opcode, fn3;
    opcode="1100011";
        if(inst=="beq"){
            fn3 = "000";
            }
        else if(inst=="bne"){
            fn3 = "001";
            }
        else if(inst=="blt"){
            fn3 = "100";
            }
        else if(inst=="bge"){
            fn3 = "101";
            }
        else if(inst=="bltu"){
            fn3 = "110";
            }
        else if(inst == "bgeu")
        {
            fn3 = "111";
        }
    //Converting the registers to their 5 bit binary reprsentations
    rs2 = regToBinary(rs2, line_number, "rs2");
    rs1 = regToBinary(rs1, line_number, "rs1");

    bitset<13> binary(offset);
    imm = binary.to_string();
    //Concatenating everything according to the instruction format
    string binInst = imm.substr(0,1)+imm.substr(2, 6)+rs2+rs1+fn3+imm.substr(8, 4)+imm.substr(1,1)+opcode;
    bitset<32> binarySet(binInst);
    unsigned int number = binarySet.to_ulong();
    //Converting the 32 bit binary to hex
    stringstream ss;
    ss << hex << number;
    string hexStr = ss.str();
    int len = hexStr.length();
    int n = 8 - len;
    while(n){
        hexStr = "0"+hexStr;
        n--;
        }
    //Writing to the outfile
    outfile<<hexStr<<endl;
}

void jformat(string line, int line_number, map<string, int>labels, ofstream& outfile)
{   //Creating an input stream for the line
    istringstream iss(line);
    string inst, rd, label;
    string word;
    vector<string> words;
    iss>>word;
    if(labels.find(word) != labels.end()){
        //do nothing, this is just a label
    }
    else{
        words.push_back(word);
    }

      while (iss >> word) {
        words.push_back(word);
    }
    //Confirm that the number of operands are correct
    if (words.size() != 3) {
        cerr << "Error in line "<<line_number<<": Incorrect number of operands" <<endl;
        exit(0);
    }
    //Remove commas from the operands
    inst = removeCommas(words[0]);
    rd = removeCommas(words[1]);
    label = removeCommas(words[2] + ':');//Add a semicolon to the label, as it will be stored in the labels map in that format
    
    //Finding it the label is valid, and if yes - finding the destination line
    int destination_line;
    if(labels.find(label) != labels.end())
    {
        destination_line = labels[label];
    }
    else
    {
        cerr<<"Error in line: "<<line_number<<"Incorrect label specified"<<endl;
        exit(0);
    }
    //Get the offset as difference in number of lines
    int offset = destination_line - line_number;
    string imm;
    //Multiply it with 4 to get the offset in number of bits
    offset = offset * 4;
    //cout<<offset;
    //Check if the offset is in its alowed range. If not - error
    if(offset < -1048576 || offset > 1048574){
        cerr<<"Error in line "<<line_number<<": Jump offset out of range"<<endl;
        exit(0);
    }
    //Assign the opcode and funct3 values for jal instruction
    string opcode, fn3;
    opcode="1101111";
    fn3 = "000";
    //Convert rd to 5 bit binary
    rd = regToBinary(rd, line_number, "rd");
    bitset<21> binary(offset);
    imm = binary.to_string();
    //Get the 32 bit binary by concatenating everything
    string binInst = imm.substr(0,1)+imm.substr(10, 10)+imm.substr(9, 1)+imm.substr(1, 8)+rd+opcode;
    bitset<32> binarySet(binInst);
    unsigned int number = binarySet.to_ulong();
    //Converting it to hex
    stringstream ss;
    ss << hex << number;
    string hexStr = ss.str();
    int len = hexStr.length();
    int n = 8 - len;
    while(n){
        hexStr = "0"+hexStr;
        n--;
        }
    outfile<<hexStr<<endl;
}

void uformat(string line, int line_number, map<string, int>labels, ofstream& outfile)   
{   //Creating an input stream for the line
    istringstream iss(line);
    string inst, rd, imm;
    string word;
    vector<string> words;
    iss>>word;
    //Store all the words of that line in a vector
    if(labels.find(word) != labels.end()){
        //do nothing, this is just a label
    }
    else{
        words.push_back(word);
    }   

      while (iss >> word) {
        words.push_back(word);
    }
    //Checking if the number of operands are correct
    if (words.size() != 3) {
        cerr << "Error in line "<<line_number<<": Incorrect number of parameters in instruction" <<endl;
        exit(0);
    }
    //Remove commas
    inst = removeCommas(words[0]);
    rd = removeCommas(words[1]);
    imm = removeCommas(words[2]);
    int imm_val;
    stringstream ss;
    //Check if the immediate value is numeric
       if(imm[0] == '-') {
    // Check if the rest of the string (after the '-') contains only digits
    if(!all_of(imm.begin() + 1, imm.end(), ::isdigit)) {
        cerr <<"Error in line "<<line_number<<": Incorrect (Non-Numeric) immediate value entered"<<endl;
        exit(0);
    }
} else {
    // Check if all characters are numbers
    if(!all_of(imm.begin(), imm.end(), ::isdigit)) {
        cerr <<"Error in line "<<line_number<<": Incorrect (Non-Numeric) immediate value entered"<<endl;
        exit(0);
    }
}
    //Converting the immediate value to decimal
    imm_val = stoi(imm);
    //cout<<imm_val<<" ";

    ss.clear();
    ss.str("");
    //Verifying if the immediate value is in allowed range
   if(imm_val < -524288 || imm_val > 524287) {
    cerr << "Error in line " << line_number << ": Immediate value out of range" << endl;
    exit(0);
}   //Setting the opcode, converting the register to 5 bit binary
    string opcode;
    opcode="0110111";
    rd = regToBinary(rd, line_number, "rd");
    bitset<32> binary(imm_val);
    imm = binary.to_string();
    //cout<<imm<<" ";
    //Concatenating everything to get a 32 bit binary number
    string binInst = imm.substr(12,20)+rd+opcode;
    bitset<32> binarySet(binInst);
    unsigned int number = binarySet.to_ulong();

    //Converting to hex
    ss << hex << number;
    string hexStr = ss.str();
    int len = hexStr.length();
    int n = 8 - len;
    while(n){
        hexStr = "0"+hexStr;
        n--;
        }
    //Writing to the outfile
    outfile<<hexStr<<endl;
}


int main()
{
    //The first step here is to take the input from txt file

    ofstream outfile("output.hex"); // Open the output file
    if (!outfile.is_open()) {
        cerr << "Error opening output file!" << endl;
        return 1;
    }

    //Open the tescase file
    ifstream file("testcase-R.s");
    string line;
    if(!file.is_open()){
        cerr<<"Error opening file"<<endl;
        return 0;
    }    
    int line_ct = 0; //Counter to maintain line number
    map <string, int> labels; //Map to store labels and their locations
    
    //We now do the first pass, to locate all the labels in the assembly code
    while(getline(file, line)){
        line_ct++;
        //cout<<"Instruction: "<<line<<endl;
        istringstream iss(line);
        string word;
        if(iss>>word){
            //If the word is a label, add it to the labels map
            if(!word.empty() && word.back() == ':'){
                //word.pop_back();
                if(labels.find(word) != labels.end())
                {   //If this label already exists in the labels map, we throw and error
                    cout<<"Error in line: "<<line_ct<<"Same label found twice"<<endl;
                    exit(0);
                }
                labels[word] = line_ct;
            }
        }
        }
    file.clear();    
    file.seekg(0, std::ios::beg); //Going back to the start of the file, for the second pass
    line_ct = 0;
    //We now do the second pass, to actually convert the assembly instructions
     while(getline(file, line)){
        line_ct++;
        //cout<<"Instruction: "<<line<<endl;
        istringstream iss(line);
        string word;

        //We now check the first non-label word against the list of valid instructions
        //If it does not match any of the valid instruction, nor is it a label, we throw an error
        if(iss>>word){
            if(!word.empty() && word.back() == ':'){
                iss>>word;
            }
            if(word=="add" || word=="sub" || word=="and" || word=="or" || word=="xor" || word=="sll" || word=="srl" || word=="sra"){
                rformat(line, line_ct, labels, outfile);
            }
            else if(word=="slli" || word=="srai" || word=="srli"){
                iformatshift(line, line_ct, labels, outfile);
            }
            else if(word=="addi" || word=="xori" || word=="ori" || word=="andi" || word=="jalr"){
                iformat(line, line_ct, labels, outfile);
            }
            else if(word=="lh" || word=="lw" || word=="ld" || word=="lbu" || word=="lhu" || word=="lwu" || word=="lb"){
                iformatload(line, line_ct, labels, outfile);
            }
            else if(word=="sd" || word=="sw" || word=="sh" || word=="sb"){
                sformat(line, line_ct, labels, outfile);
            }
            else if(word=="beq" || word=="bne" || word=="blt" || word=="bge" || word=="bltu" || word=="bgeu"){
                bformat(line, line_ct, labels, outfile);
            }
            else if(word=="jal"){
                jformat(line, line_ct, labels, outfile);
            }
            else if(word=="lui"){
                uformat(line, line_ct, labels, outfile);
            }
            else{
                cerr<<"Error in line "<<line_ct<<": Incorrect instruction entered"<<endl;
                exit(0);
            }

        }
    }
    //Closing both the input and output files
    outfile.close();
    file.close();
    return 0;
}

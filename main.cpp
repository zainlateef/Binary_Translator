//
//  main.cpp
//  MIPSsim
//
//  Created by Zain Lateef on 11/19/16.
//  Copyright © 2016 Zain Lateef. All rights reserved.



#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>

//proj2smp.txt
struct node
{
    std::string binary,instruction;
    int PC=0,v1,v2,v3;
};


std::string brake="00111100000000000000000000001101";
std::vector<node> ot;
int z=0;
int cnt=64;


void vecset(std::string bin, std::string inst, int P,int uno, int dos,int tres);
void interpret(std::string line,std::ofstream &outputFile);
int interpret_num_unsigned(std::string line);
int interpret_num(std::string line);
std::string shift(std::string line,int steps);
void cat1(std::string line,std::ofstream &outputFile);
void cat2(std::string line,std::ofstream &outputFile);
void cat3(std::string line,std::ofstream &outputFile);
void NOP(std::string line,std::ofstream &outputFile);
void J(std::string line,std::ofstream &outputFile);
void BEQ(std::string line,std::ofstream &outputFile);
void BNE(std::string line,std::ofstream &outputFile);
void BGTZ(std::string line,std::ofstream &outputFile);
void SW(std::string line,std::ofstream &outputFile);
void LW(std::string line,std::ofstream &outputFile);
void XOR(std::string line,std::ofstream &outputFile);
void MUL(std::string line,std::ofstream &outputFile);
void ADD(std::string line,std::ofstream &outputFile);
void SUB(std::string line,std::ofstream &outputFile);
void AND(std::string line,std::ofstream &outputFile);
void OR(std::string line,std::ofstream &outputFile);
void ADDU(std::string line,std::ofstream &outputFile);
void SUBU(std::string line,std::ofstream &outputFile);
void ORI(std::string line,std::ofstream &outputFile);
void XORI(std::string line,std::ofstream &outputFile);
void ADDI(std::string line,std::ofstream &outputFile);
void SUBI(std::string line,std::ofstream &outputFile);
void ANDI(std::string line,std::ofstream &outputFile);
void SRL(std::string line,std::ofstream &outputFile);
void SRA(std::string line,std::ofstream &outputFile);
void SLL(std::string line,std::ofstream &outputFile);


std::string shift(std::string line, int steps, char direction)
{
    
    int i,j;
    int len=line.size();
    char temp;
    if(direction=='l')
    {
        for(j=0;j<steps;j++)
        {
            for(i=0;i<len;i++)
            {
                if(i==len-1)
                    line[i]='0';
                
                else
                {
                    temp=line[i];
                    line[i]=line[i+1];
                    line[i+1]=temp;
                }
            }
        }
    }
    
    if(direction=='r')
    {
        for(j=0;j<steps;j++)
        {
            for(i=len-1;i>=0;i--)
            {
                if(i==0)
                    line[i]='0';
                
                else
                {
                    temp=line[i];
                    line[i]=line[i-1];
                    line[i-1]=temp;
                }
            }
        }
        
        
        
        
    }
    return line;
    
}


void interpret (std::string line,std::ofstream &outputFile)
{
    std::string first_3=line.substr(0,3);
    
    if(first_3=="001")
        cat1(line,outputFile);
    
    
    if(first_3=="010")
        cat2(line,outputFile);
    
    if(first_3=="100")
        cat3(line,outputFile);
}


int interpret_num_unsigned(std::string line)
{
    bool negative=false;
    int i;
    int last_char=line.length()-1;
    
    int digit,power,decimal=0;
    last_char=line.length()-1;
    for(i=0;i<=last_char;i++)
    {
        digit=line[i]-'0';
        if(digit!=0)
        {
            power=last_char-i;
            decimal=decimal+pow(2,power);
        }
    }
    
    
    if(negative)
        decimal=decimal*-1;
    
    return decimal;
}






int interpret_num(std::string line)
{
    
    bool negative=false;
    int i;
    int last_char=line.length()-1;
    
   
    if(line[0]=='1')
    {
        negative=true;
        
        while(line[last_char]!='1')
        {
            last_char=last_char-1;
        }
        
        
        for(i=0;i<last_char;i++)
        {
            if(line[i]=='1')
            {
                line[i]='0';
            }
            
            else if(line[i]=='0')
            {
                line[i]='1';
            }
        }
        
    }
    int digit,power,decimal=0;
    last_char=line.length()-1;
    for(i=0;i<=last_char;i++)
    {
        digit=line[i]-'0';
        if(digit!=0)
        {
            power=last_char-i;
            decimal=decimal+pow(2,power);
        }
    }
    
    
    if(negative)
        decimal=decimal*-1;
    
    return decimal;
}




void cat1(std::string line,std::ofstream &outputFile)
{
    std:: string op_code=line.substr(3,3);
    if(op_code=="000")
        NOP(line,outputFile);
    else if (op_code=="001")
        J(line,outputFile);
    else if (op_code=="010")
        BEQ(line,outputFile);
    else if (op_code=="011")
        BNE(line,outputFile);
    else if (op_code=="100")
        BGTZ(line,outputFile);
    else if (op_code=="101")
        SW(line,outputFile);
    else if (op_code=="110")
        LW(line,outputFile);
}




void cat2(std::string line,std::ofstream &outputFile)
{
    std:: string op_code=line.substr(3,3);
    if(op_code=="000")
        XOR(line,outputFile);
    else if (op_code=="001")
        MUL(line,outputFile);
    else if (op_code=="010")
        ADD(line,outputFile);
    else if (op_code=="011")
        SUB(line,outputFile);
    else if (op_code=="100")
        AND(line,outputFile);
    else if (op_code=="101")
        OR(line,outputFile);
    else if (op_code=="110")
        ADDU(line,outputFile);
    else if (op_code=="111")
        SUBU(line,outputFile);
}




void cat3(std::string line,std::ofstream &outputFile)
{
    std:: string op_code=line.substr(3,3);
    if(op_code=="000")
        ORI(line,outputFile);
    else if (op_code=="001")
        XORI(line,outputFile);
    else if (op_code=="010")
        ADDI(line,outputFile);
    else if (op_code=="011")
        SUBI(line,outputFile);
    else if (op_code=="100")
        ANDI(line,outputFile);
    else if (op_code=="101")
        SRL(line,outputFile);
    else if (op_code=="110")
        SRA(line,outputFile);
    else if (op_code=="111")
        SLL(line,outputFile);
}


void vecset(std::string bin, std::string inst, int P,int uno, int dos,int tres)
{
    ot[z].binary=bin;
    ot[z].instruction=inst;
    ot[z].PC=P-4;
    ot[z].v1=uno;
    ot[z].v2=dos;
    ot[z].v3=tres;
    z++;
}




void NOP(std::string line,std::ofstream &outputFile)
{
    vecset(line, "NOP", cnt, 0, 0, 0);
    outputFile<<"NOP"<<"\n";
    
}
void J(std::string line,std::ofstream &outputFile)
{
    
    std::string minus_six=line.substr(6,26);
    std::string temp=shift(minus_six,2,'l');
    int number=interpret_num_unsigned(temp);
    
    vecset(line, "J", cnt, number, 0, 0);
    
    outputFile<<"J #"<<number<<"\n";
    
}
void BEQ(std::string line,std::ofstream &outputFile)
{
    std::string r1=line.substr(6,5);
    std::string r2=line.substr(11,5);
    std::string off=line.substr(16,16);
    
    int ar1=interpret_num_unsigned(r1);
    int ar2=interpret_num_unsigned(r2);
    int offs=interpret_num(off);
    
    vecset(line, "BEQ", cnt, ar1, ar2, offs);
    
    outputFile<<"BEQ R"<<ar1<<", R"<<ar2<<", #"<<offs<<"\n";
    
}
void BNE(std::string line,std::ofstream &outputFile)
{
    std::string r1=line.substr(6,5);
    std::string r2=line.substr(11,5);
    std::string off=line.substr(16,16);
    
    int ar1=interpret_num_unsigned(r1);
    int ar2=interpret_num_unsigned(r2);
    int offs=interpret_num(off);
    
    vecset(line, "BNE", cnt, ar1, ar2, offs);
    
    outputFile<<"BNE R"<<ar1<<", R"<<ar2<<", #"<<offs<<"\n";
    
}
void BGTZ(std::string line,std::ofstream &outputFile)
{
    std::string r1=line.substr(6,5);
    std::string r2=line.substr(11,5);
    std::string off=line.substr(16,16);
    
    int ar1=interpret_num_unsigned(r1);
    int ar2=interpret_num_unsigned(r2);
    int offs=interpret_num(off);
    
    vecset(line, "BGTZ", cnt, ar1, offs, 0);
    
    outputFile<<"BGTZ R"<<ar1<<", #"<<offs<<"\n";
    
}
void SW(std::string line,std::ofstream &outputFile)
{
    std::string r1=line.substr(6,5);
    std::string r2=line.substr(11,5);
    std::string off=line.substr(16,16);
    
    int ar1=interpret_num_unsigned(r1);
    int ar2=interpret_num_unsigned(r2);
    int offs=interpret_num(off);
    
    vecset(line, "SW", cnt, ar2, offs, ar1);
    
    outputFile<<"SW R"<<ar2<<", "<<offs<<"(R"<<ar1<<")\n";
    
}
void LW(std::string line,std::ofstream &outputFile)
{
    std::string r1=line.substr(6,5);
    std::string r2=line.substr(11,5);
    std::string off=line.substr(16,16);
    
    int ar1=interpret_num_unsigned(r1);
    int ar2=interpret_num_unsigned(r2);
    int offs=interpret_num(off);
    
    vecset(line, "LW", cnt, ar2, offs, ar1);
    
    outputFile<<"LW R"<<ar2<<", "<<offs<<"(R"<<ar1<<")\n";
    
}
void XOR(std::string line,std::ofstream &outputFile)
{
    std::string r1=line.substr(6,5);
    std::string r2=line.substr(11,5);
    std::string r3=line.substr(16,5);
    
    int ar1=interpret_num_unsigned(r1);
    int ar2=interpret_num_unsigned(r2);
    int ar3=interpret_num_unsigned(r3);
    
    vecset(line, "XOR", cnt, ar1, ar2, ar3);
    
    outputFile<<"XOR R"<<ar1<<", R"<<ar2<<", R"<<ar3<<"\n";
    
}
void MUL(std::string line,std::ofstream &outputFile)
{
    std::string r1=line.substr(6,5);
    std::string r2=line.substr(11,5);
    std::string r3=line.substr(16,5);
    
    int ar1=interpret_num_unsigned(r1);
    int ar2=interpret_num_unsigned(r2);
    int ar3=interpret_num_unsigned(r3);
    
    vecset(line, "MUL", cnt, ar1, ar2, ar3);
    
    outputFile<<"MUL R"<<ar1<<", R"<<ar2<<", R"<<ar3<<"\n";
    
}
void ADD(std::string line,std::ofstream &outputFile)
{
    std::string r1=line.substr(6,5);
    std::string r2=line.substr(11,5);
    std::string r3=line.substr(16,5);
    
    int ar1=interpret_num_unsigned(r1);
    int ar2=interpret_num_unsigned(r2);
    int ar3=interpret_num_unsigned(r3);
    
    vecset(line, "ADD", cnt, ar1, ar2, ar3);
    
    outputFile<<"ADD R"<<ar1<<", R"<<ar2<<", R"<<ar3<<"\n";
    
}
void SUB(std::string line,std::ofstream &outputFile)
{
    std::string r1=line.substr(6,5);
    std::string r2=line.substr(11,5);
    std::string r3=line.substr(16,5);
    
    int ar1=interpret_num_unsigned(r1);
    int ar2=interpret_num_unsigned(r2);
    int ar3=interpret_num_unsigned(r3);
    
    vecset(line, "SUB", cnt, ar1, ar2, ar3);
    
    outputFile<<"SUB R"<<ar1<<", R"<<ar2<<", R"<<ar3<<"\n";
    
}
void AND(std::string line,std::ofstream &outputFile)
{
    std::string r1=line.substr(6,5);
    std::string r2=line.substr(11,5);
    std::string r3=line.substr(16,5);
    
    int ar1=interpret_num_unsigned(r1);
    int ar2=interpret_num_unsigned(r2);
    int ar3=interpret_num_unsigned(r3);
    
    vecset(line, "AND", cnt, ar1, ar2, ar3);
    
    outputFile<<"AND R"<<ar1<<", R"<<ar2<<", R"<<ar3<<"\n";
    
}
void OR(std::string line,std::ofstream &outputFile)
{
    std::string r1=line.substr(6,5);
    std::string r2=line.substr(11,5);
    std::string r3=line.substr(16,5);
    
    int ar1=interpret_num_unsigned(r1);
    int ar2=interpret_num_unsigned(r2);
    int ar3=interpret_num_unsigned(r3);
    
    vecset(line, "OR", cnt, ar1, ar2, ar3);
    
    outputFile<<"OR R"<<ar1<<", R"<<ar2<<", R"<<ar3<<"\n";
    
}
void ADDU(std::string line,std::ofstream &outputFile)
{
    std::string r1=line.substr(6,5);
    std::string r2=line.substr(11,5);
    std::string r3=line.substr(16,5);
    
    int ar1=interpret_num_unsigned(r1);
    int ar2=interpret_num_unsigned(r2);
    int ar3=interpret_num_unsigned(r3);
    
    vecset(line, "ADDU", cnt, ar1, ar2, ar3);
    
    outputFile<<"ADDU R"<<ar1<<", R"<<ar2<<", R"<<ar3<<"\n";
    
}
void SUBU(std::string line,std::ofstream &outputFile)
{
    std::string r1=line.substr(6,5);
    std::string r2=line.substr(11,5);
    std::string r3=line.substr(16,5);
    
    int ar1=interpret_num_unsigned(r1);
    int ar2=interpret_num_unsigned(r2);
    int ar3=interpret_num_unsigned(r3);
    
    vecset(line, "SUBU", cnt, ar1, ar2, ar3);
    
    outputFile<<"SUBU R"<<ar1<<", R"<<ar2<<", R"<<ar3<<"\n";
    
}
void ORI(std::string line,std::ofstream &outputFile)
{
    std::string r1=line.substr(6,5);
    std::string r2=line.substr(11,5);
    std::string off=line.substr(16,16);
    
    int ar1=interpret_num_unsigned(r1);
    int ar2=interpret_num_unsigned(r2);
    int offs=interpret_num_unsigned(off);
    
    vecset(line, "ORI", cnt, ar1, ar2, offs);
    
    outputFile<<"ORI R"<<ar1<<", R"<<ar2<<", #"<<offs<<"\n";
    
    
    
}
void XORI(std::string line,std::ofstream &outputFile)
{
    std::string r1=line.substr(6,5);
    std::string r2=line.substr(11,5);
    std::string off=line.substr(16,16);
    
    int ar1=interpret_num_unsigned(r1);
    int ar2=interpret_num_unsigned(r2);
    int offs=interpret_num_unsigned(off);
    
    vecset(line, "XORI", cnt, ar1, ar2, offs);
    
    outputFile<<"XORI R"<<ar1<<", R"<<ar2<<", #"<<offs<<"\n";
    
}
void ADDI(std::string line,std::ofstream &outputFile)
{
    std::string r1=line.substr(6,5);
    std::string r2=line.substr(11,5);
    std::string off=line.substr(16,16);
    
    int ar1=interpret_num_unsigned(r1);
    int ar2=interpret_num_unsigned(r2);
    int offs=interpret_num(off);
    
    vecset(line, "ADDI", cnt, ar1, ar2, offs);
    
    outputFile<<"ADDI R"<<ar1<<", R"<<ar2<<", #"<<offs<<"\n";
    
}
void SUBI(std::string line,std::ofstream &outputFile)
{
    std::string r1=line.substr(6,5);
    std::string r2=line.substr(11,5);
    std::string off=line.substr(16,16);
    
    int ar1=interpret_num_unsigned(r1);
    int ar2=interpret_num_unsigned(r2);
    int offs=interpret_num(off);
    
    vecset(line, "SUBI", cnt, ar1, ar2, offs);
    
    outputFile<<"SUBI R"<<ar1<<", R"<<ar2<<", #"<<offs<<"\n";
    
}
void ANDI(std::string line,std::ofstream &outputFile)
{
    std::string r1=line.substr(6,5);
    std::string r2=line.substr(11,5);
    std::string off=line.substr(16,16);
    
    int ar1=interpret_num_unsigned(r1);
    int ar2=interpret_num_unsigned(r2);
    int offs=interpret_num(off);
    
    vecset(line, "ANDI", cnt, ar1, ar2, offs);
    
    outputFile<<"ANDI R"<<ar1<<", R"<<ar2<<", #"<<offs<<"\n";
    
    
}
void SRL(std::string line,std::ofstream &outputFile)
{
    
    std::string r1=line.substr(6,5);
    std::string r2=line.substr(11,5);
    std::string off=line.substr(27,5);
    
    int rtin=interpret_num_unsigned(r1);
    int rdin=interpret_num_unsigned(r2);
    int sain=interpret_num_unsigned(off);
    
    vecset(line, "SRL", cnt, rtin, rdin, sain);
    
    
    outputFile<<"SRL R"<<rtin<<", R"<<rdin<<", #"<<sain<<"\n";
    
}
void SRA(std::string line,std::ofstream &outputFile)
{
    std::string r1=line.substr(6,5);
    std::string r2=line.substr(11,5);
    std::string off=line.substr(27,5);
    
    int rtin=interpret_num_unsigned(r1);
    int rdin=interpret_num_unsigned(r2);
    int sain=interpret_num_unsigned(off);
    
    vecset(line, "SRA", cnt, rtin, rdin, sain);
    
    outputFile<<"SRA R"<<rtin<<", R"<<rdin<<", #"<<sain<<"\n";
}
void SLL(std::string line,std::ofstream &outputFile)
{
    std::string r1=line.substr(6,5);
    std::string r2=line.substr(11,5);
    std::string off=line.substr(27,5);
    
    int rtin=interpret_num_unsigned(r1);
    int rdin=interpret_num_unsigned(r2);
    int sain=interpret_num_unsigned(off);
    
    vecset(line, "SLL", cnt, rtin, rdin, sain);
    
    outputFile<<"SLL R"<<rtin<<", R"<<rdin<<", #"<<sain<<"\n";
    
    
}




int main(int argc, char *argv[])
{
  
    std:: string file_name=argv[1];
    
    std::string line;
    std::ifstream envelope (file_name);
    
    
    bool break_hit=false;
    int dat,row=0,col=0,columns;
    
    
    std::ofstream outputFile;
    outputFile.open("disassembler.txt");
    
    
    
    int size_of_array=0;
    int size_of_data=0;
    while (getline(envelope,line))
    {
		line.erase( std::remove(line.begin(), line.end(), '\r'), line.end() );
        if(line==brake)
            break_hit=true;
        if(break_hit==false)
            size_of_array++;
        else if(line!=brake)
            size_of_data++;
    }
    envelope.clear();
    envelope.seekg(0, std::ios::beg);
    
    ot.resize(size_of_array+100);
    
    columns=size_of_data/8;
    if((size_of_data%8)>0)
        columns++;
    
    int data_array[9][columns];
    
    break_hit=false;
    while (getline(envelope,line))
    {
		line.erase( std::remove(line.begin(), line.end(), '\r'), line.end() );
        outputFile<<line<<"\t"<<cnt<<"\t";
        cnt=cnt+4;
        
        if(line==brake)
        {
            break_hit=true;
            outputFile<<"BREAK\n";
            vecset(brake, "BREAK", cnt, 0, 0, 0);
        }
        else if(!break_hit)
            interpret(line,outputFile);
        else
        {
            dat=interpret_num(line);
            outputFile<<dat<<"\n";
            
            if(row==0)
            {
                data_array[row][col]=cnt-4;
                row++;
                data_array[row][col]=dat;
                row++;
            }
            else
            {
                data_array[row][col]=dat;
                row++;
            }
            if(row==9)
            {
                row=0;
                col++;
            }
            
        }
    }
    
    envelope.close();
    outputFile.close();
    
    int regarray[32]={0};
    
    
    std::ofstream writer;
    writer.open("simulation.txt");
    
    break_hit=false;
    int cycle_count=1;
    int pc_count=0;
    int i,j,t,zain,p,cooper;
    std::string tempor,aye;
    
    
    
    while(!break_hit)
    {
        if(ot[pc_count].binary==brake)
            break_hit=true;
        
        writer<<"--------------------\n";
        writer<<"Cycle "<<cycle_count<<":\t"<<ot[pc_count].PC<<"\t";
        cycle_count++;
        if(!break_hit)
            interpret(ot[pc_count].binary, writer);
        else
            writer<<"BREAK\n";
        writer<<"\nRegisters\n";
        
        tempor=ot[pc_count].instruction;
    
        if(tempor=="NOP")
        {
            pc_count++;
        }
        else if(tempor=="J")
        {
            cooper=ot[pc_count].v1;
            
            while(ot[pc_count].PC>cooper)
                pc_count--;
            while(ot[pc_count].PC<cooper)
                pc_count++;
        }
        else if(tempor=="BEQ")
        {
            if(regarray[ot[pc_count].v1]==regarray[ot[pc_count].v2])
            {
                t=4*ot[pc_count].v3;
                t=t+ot[pc_count+1].PC;
                
                while(ot[pc_count].PC>t)
                    pc_count--;
                while(ot[pc_count].PC<t)
                    pc_count++;
            }
            else
                pc_count++;
        }
        else if(tempor=="BNE")
        {
            if(regarray[ot[pc_count].v1]!=regarray[ot[pc_count].v2])
            {
                t=4*ot[pc_count].v3;
                t=t+ot[pc_count+1].PC;
                
                while(ot[pc_count].PC>t)
                    pc_count--;
                while(ot[pc_count].PC<t)
                    pc_count++;
            }
            else
                pc_count++;
        }
        else if(tempor=="BGTZ")
        {
            if(regarray[ot[pc_count].v1]>0)
            {
                
                t=4*ot[pc_count].v2;
                t=t+ot[pc_count+1].PC;
                
                while(ot[pc_count].PC>t)
                {
                    pc_count--;
                }
                while(ot[pc_count].PC<t)
                {
                    pc_count++;
                }
                
            }
            else
                pc_count++;
            
        }
        else if(tempor=="SW")
        {
            t=ot[pc_count].v2+regarray[ot[pc_count].v3];
            zain=data_array[0][0];
            for(j=0;j<columns;j++)
            {
                for(i=1;i<9;i++)
                {
                    
                    if(zain==t)
                        data_array[i][j]=regarray[ot[pc_count].v1];
                    zain=zain+4;
                }
            }
            pc_count++;
        }
        else if(tempor=="LW")
        {
            t=ot[pc_count].v2+regarray[ot[pc_count].v3];
            zain=data_array[0][0];
            for(j=0;j<columns;j++)
            {
                for(i=1;i<9;i++)
                {
                    
                    if(zain==t)
                        regarray[ot[pc_count].v1]=data_array[i][j];
                    zain=zain+4;
                }
            }
            pc_count++;
        }
        else if(break_hit)
        {}
        else if(tempor=="XOR")
        {
            t=regarray[ot[pc_count].v2];
            zain=regarray[ot[pc_count].v3];
            t=t^zain;
            regarray[ot[pc_count].v1]=t;
            pc_count++;
        }
        else if(tempor=="MUL")
        {
            t=regarray[ot[pc_count].v2];
            zain=regarray[ot[pc_count].v3];
            t=t*zain;
            regarray[ot[pc_count].v1]=t;
            pc_count++;
        }
        else if(tempor=="ADD")
        {
            t=regarray[ot[pc_count].v2];
            zain=regarray[ot[pc_count].v3];
            t=t+zain;
            regarray[ot[pc_count].v1]=t;
            pc_count++;
        }
        else if(tempor=="SUB")
        {
            t=regarray[ot[pc_count].v2];
            zain=regarray[ot[pc_count].v3];
            t=t-zain;
            regarray[ot[pc_count].v1]=t;
            pc_count++;
        }
        else if(tempor=="AND")
        {
            t=regarray[ot[pc_count].v2];
            zain=regarray[ot[pc_count].v3];
            t=t&zain;
            regarray[ot[pc_count].v1]=t;
            pc_count++;
        }
        else if(tempor=="OR")
        {
            t=regarray[ot[pc_count].v2];
            zain=regarray[ot[pc_count].v3];
            t=t|zain;
            regarray[ot[pc_count].v1]=t;
            pc_count++;
        }
        else if(tempor=="ADDU")
        {
            t=regarray[ot[pc_count].v2];
            zain=regarray[ot[pc_count].v3];
            t=t+zain;
            regarray[ot[pc_count].v1]=t;
            pc_count++;
        }
        else if(tempor=="SUBU")
        {
            t=regarray[ot[pc_count].v2];
            zain=regarray[ot[pc_count].v3];
            t=t-zain;
            regarray[ot[pc_count].v1]=t;
            pc_count++;
        }
        else if(tempor=="ORI")
        {
            t=regarray[ot[pc_count].v2];
            zain=ot[pc_count].v3;
            t=t|zain;
            regarray[ot[pc_count].v1]=t;
            pc_count++;
        }
        else if(tempor=="XORI")
        {
            t=regarray[ot[pc_count].v2];
            zain=ot[pc_count].v3;
            t=t^zain;
            regarray[ot[pc_count].v1]=t;
            pc_count++;
        }
        else if(tempor=="ADDI")
        {
            t=regarray[ot[pc_count].v2];
            zain=ot[pc_count].v3;
            t=t+zain;
            regarray[ot[pc_count].v1]=t;
            pc_count++;
        }
        else if(tempor=="SUBI")
        {
            t=regarray[ot[pc_count].v2];
            zain=ot[pc_count].v3;
            t=t-zain;
            regarray[ot[pc_count].v1]=t;
            pc_count++;
        }
        else if(tempor=="ANDI")
        {
            t=regarray[ot[pc_count].v2];
            zain=ot[pc_count].v3;
            t=t&zain;
            regarray[ot[pc_count].v1]=t;
            pc_count++;
        }
        else if(tempor=="SRL")
        {
            t=pow(2, ot[pc_count].v3);
            t=regarray[ot[pc_count].v2]/t;
            regarray[ot[pc_count].v1]=t;
            pc_count++;
        }
        else if(tempor=="SRA")
        {
            t=regarray[ot[pc_count].v2];
            t>>=ot[pc_count].v3;
            regarray[ot[pc_count].v1]=t;
            pc_count++;
        }
        else if(tempor=="SLL")
        {
            t=pow(2, ot[pc_count].v3);
            t=regarray[ot[pc_count].v2]*t;
            regarray[ot[pc_count].v1]=t;
            pc_count++;
        }
        writer<<"R00:";
        for(i=0;i<8;i++)
            writer<<"\t"<<regarray[i];
        writer<<"\nR08:";
        for(i=8;i<16;i++)
            writer<<"\t"<<regarray[i];
        writer<<"\nR16:";
        for(i=16;i<24;i++)
            writer<<"\t"<<regarray[i];
        writer<<"\nR24:";
        for(i=24;i<32;i++)
            writer<<"\t"<<regarray[i];
        
        writer<<"\n\nData\n";
        
        for(j=0;j<columns;j++)
        {
            for(i=0;i<9;i++)
            {
                writer<<data_array[i][j];
                if(i==0)
                    writer<<":";
                writer<<"\t";
            }
            writer<<"\n";
        }
        
        writer<<"\n";
        
    }
    
    writer.close();
    
    return 0;
}

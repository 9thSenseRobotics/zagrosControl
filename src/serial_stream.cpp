#include <iostream>
#include <string>
#include <sstream>
#include <SerialStream.h>

using namespace std;
using namespace LibSerial;

#define PORT "/dev/ttyACM0" //This is system-specific

SerialStream mySerial;


void sendSerial(string Data)
{
    cout << "sending string = " << Data << endl;
    mySerial << Data;
}
    
int getSerial(){
    int res;
    char str[16];
    mySerial.read(str,2);
    sscanf(str,"%d",&res);
    return res;
}


int main(int argc, char** argv)
{

    /*The mySerialino must be setup to use the same baud rate*/
    cout << "opening port" << endl;
    mySerial.Open(PORT);
    mySerial.SetBaudRate(SerialStreamBuf::BAUD_9600);
    mySerial.SetCharSize(SerialStreamBuf::CHAR_SIZE_8);
    cout << "port open" << endl;
    do
    {
        cout << "Press a command key, use q to quit: ";
        char val = cin.get();
        cout << "Key pressed was " << val << endl;
        cin.ignore();
        if (val == 'q') break;
        stringstream ss;
        string cmd;
        ss << val;
        ss >> cmd;
        cmd.append("#");
        sendSerial(cmd);
        
        if (val == 'b') 
        {
            cout << "value received = "  << getSerial() << endl;
        }            
     } while(1);   
}



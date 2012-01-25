#include <iostream>
#include <string>
//#include <sstream>
#include <SerialStream.h>

using namespace std;
using namespace LibSerial;

#define PORT "/dev/ttyACM0" //This is system-specific

SerialStream ardu;
    
int get(string out){
    int res;
    char str[16];
    string test = "m#";
    //char test[3];
    //test[0] = 'm';
    //test[1] = '#';
    //test[2] = 0;
    cout << "sending string" << endl;
    ardu << out;
    cout << "string sent, trying to recieve" << endl;
    //ardu << '#';
    ardu >> str;
    cout << "string received" << endl;
    sscanf(str,"%d",&res);
    return res;
}


int main(int argc, char** argv)
{

    /*The arduino must be setup to use the same baud rate*/
    cout << "opening port" << endl;
    ardu.Open(PORT);
    ardu.SetBaudRate(SerialStreamBuf::BAUD_9600);
    ardu.SetCharSize(SerialStreamBuf::CHAR_SIZE_8);
    cout << "port open" << endl;
    char batt = 'b';
    cout << "value = " << get("j#") << endl;
    
}



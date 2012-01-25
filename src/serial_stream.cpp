#include <iostream>
#include <string>
#include <sstream>
#include <SerialStream.h>

using namespace std;
using namespace LibSerial;

#define PORT "/dev/ttyACM0" //This is system-specific

SerialStream ardu;


void send(string Data)
{
    cout << "sending string = " << Data << endl;
    ardu << Data;
}
    
int get(string out){
    int res;
    char str[16];
    string test = "m#";

    cout << "string sent, trying to recieve, hit a key" << endl;
   for (int i =0; i < 3; i++)
   { cin.ignore();
     cout << "key hit, proceeding" << endl;
    //ardu >> str;
    //char next_byte ;
    //ardu.get(str,2) ;
    ardu.read(str,1);
    sscanf(str,"%d",&res);
    cout << "string received = "  << res << endl;
    }
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
        ardu << cmd;
        
        if (val == 'b') 
        {
            char str[16];
            cout << "string sent, trying to recieve, hit a key" << endl;
            //cin.ignore();
            cout << "key hit, proceeding" << endl;
            ardu.read(str,1);
            cout << "string received = "  << str[0] << endl;
        }            
     } while(1);   
}



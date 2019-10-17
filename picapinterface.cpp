#include <iostream>
#include <signal.h>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <vector>
#include <bits/stdc++.h>

//#include <wiringpi.h>
//#include <sys/socket.h>
//#include <sys/types.h>
//#include <netinet/in.h>
//#include <netdb.h>

bool volatile keepRunning=true;

using namespace std;

DIR *dir;
dirent *ent;
//string dir_sample = "./SAMPLES/";
vector<string> sample_list;
vector<string> loop_list;
vector<string> transfer_list;
vector<string> sd_list;
string sample;
string ls;
int no_samples;
int no_loops;
int counter;
int no_sd;
bool usb;
int sense;

void debug(string out)
{
  cout << out.c_str() <<endl;
}

bool mycomp(string a, string b){
	return a<b;
}

vector<string> alphabaticallySort(vector<string> a){
	//int n=a.size();
	sort(a.begin(),a.end(),mycomp);
	return a;
}

vector<string> load_wav(string location, bool sd, bool loops)
{
vector<string> a;
  
  if ((dir = opendir (location.c_str())) != NULL)
  {
    counter = 0;
    cout << "Open DIR "<< location.c_str() << endl;
    
     while((ent = readdir(dir)) != NULL)
     {
      sample = ent->d_name;
        if((sample.compare("..") > 0))
        {
        if(sd)
        {
          a.push_back(ent->d_name);
          no_sd++;
        }
        else
        { 
         a.push_back(ent->d_name);
         
         if(loops) no_loops++;
         else no_samples++;
         counter++;
        }
         //cout<<sample.c_str()<<endl;
        }
      }
      closedir(dir);
    }
  else  cout << "Error Opening DIR "<< location.c_str()<< endl;
      
  return a;
}

string GetStdoutFromCommand(string cmd, bool command)
{
  string data;
  FILE* stream;
  const int max_buffer = 256;
  char buffer[max_buffer];
  
  
  if(command)
  {
    cmd.append(" 2>&1");
    stream = popen(cmd.c_str(), "r");
  }
  else
  stream = fopen(cmd.c_str(), "r");
  
  if(stream)
  {
    while(!feof(stream))
      if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
    pclose(stream);
  }
  return data;
}


int main(void) {
  
  cout << "Hello World" << endl;
  
 
  sd_list = load_wav("/media/pi/", true, false);
  cout << "No. USBs: " << no_sd <<endl;
  for(int i = 0; i<no_sd; i++)
  {
    sample = "/media/pi/" + sd_list[i] + "/SAMPLES";
    transfer_list = load_wav(sample, false, false);
    transfer_list = alphabaticallySort(transfer_list);
    for(int j = 0; j<counter; j++)
    {
    sample_list.push_back(("/media/pi/"+sd_list[i]+"/"+transfer_list[j]));
    }
    transfer_list.clear();
    
    
    sample = "/media/pi/" + sd_list[i] + "/LOOPS";
    transfer_list = load_wav(sample, false, true);
    transfer_list = alphabaticallySort(transfer_list);
    for(int j = 0; j<counter; j++)
    {
    loop_list.push_back(("/media/pi/"+sd_list[i]+"/"+transfer_list[j]));
    }
    transfer_list.clear();
    
    
  }


  transfer_list.clear();
  transfer_list = load_wav("./SAMPLES", false, false);
  transfer_list = alphabaticallySort(transfer_list);
  for(int i = 0; i<counter; i++)
  {
    sample_list.push_back(("./SAMPLES/"+transfer_list[i]));
  }
  
  transfer_list.clear();
  transfer_list = load_wav("./LOOPS", false, true);
  transfer_list = alphabaticallySort(transfer_list);
  for(int i = 0; i<counter; i++)
  {
    loop_list.push_back(("./LOOPS/"+transfer_list[i]));
  }
  
  for(int i =0; i<no_samples; i++) cout<<sample_list[i]<<endl;
  for(int i =0; i<no_loops; i++) cout<<loop_list[i]<<endl;
  
  cout << "No Samples:" << no_samples <<endl;
  cout << "No Loops:" << no_loops <<endl;
  
  
  //find sensitivity
  if(no_sd>0)
  {
  sample = "/media/pi/" + sd_list[0] + "/CONF/sense.conf";
  ls = GetStdoutFromCommand(sample, false);
  }
  //else
  ls = GetStdoutFromCommand("./CONF/sense.conf", false);
  sense = stoi(ls);
  cout << "Sensitivity: " << sense << endl;
  
  /*ls = GetStdoutFromCommand("sudo raveloxmidi -c ./MIDI/raveloxmidi.conf", true);
  debug(ls);
  ls = GetStdoutFromCommand("./MIDI/note_send.py 144", true);
  debug(ls);*/
 
 /*
 int sockfd;
 //int portno;
 //int n;
 //int serverlen;
 struct sockaddr_in serveraddr;
 //char *hostname;
 //char buf[1024];
 
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if(sockfd < 0)debug("socket error");
  else debug("Socket OK");
 

 
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = htons(5006);
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr))<0) debug("Bind Error");
  else debug("Bind OK");
  
  //struct hostent *hp;
  */
  
 
 
 
  
  while (keepRunning) {
    sleep(100);
   
  }


  return 0;
}

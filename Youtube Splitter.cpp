#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cinttypes>
#include <sstream>
#include <unistd.h>
#include <cstdio>
#include <array>
using namespace std;

std::string youtube_dl_caller(std::string URL){
    FILE * stream = NULL;
    std::string youtube_dl_command, results;
    std::array<char, 5> buffer;
    
    youtube_dl_command = "youtube-dl -g " + URL ;
    char command[youtube_dl_command.size() + 1];
    strcpy(command, youtube_dl_command.c_str());

    stream = _popen(command,"r");
    while (fgets(buffer.data(), 5, stream) != nullptr){

        results += buffer.data();
    }
    auto returnCode = pclose(stream);

    return results;
}

int ffmpeg_caller(std::vector<std::string> streamURLs, std::string timeStart, std::string duration ){
    auto videoStream = streamURLs.at(0);
    auto audioStream = streamURLs.at(1);
    std::string command = "ffmpeg -ss " + timeStart + " -i \"" + videoStream + "\" -ss " + timeStart + " -i \"" + audioStream + "\" -t " + duration + " -map 0:v -map 1:a -c:v libx264 -c:a aac output.mkv";
    system(command.c_str());
    return 0;
}


int main(){
    int i;
    std::string youtubeURL,timeStart,durationToEnd,youtube_dl_command,results;
    std::vector<std::string> output;
    
    cout << "Enter the youtube URL:" << endl;
    cin >> youtubeURL;

    cout<< "Time for clip start (HH,MM,SS,MSMS): " << endl;
    cin >> timeStart;

    cout << "Duration of clip (HH,MM,SS,MSMS)" << endl;
    cin >> durationToEnd;

    std::string youtubeCaller = youtube_dl_caller(youtubeURL);
    std::vector<std::string> storage;
    stringstream ss(youtubeCaller);
    
    while(ss.good()){
        std::string SingleLine;
        getline(ss,SingleLine,'\n');
        output.push_back(SingleLine);
    }

    int a = ffmpeg_caller(output, timeStart, durationToEnd);
    cout << "Command has finished, press any key to leave";
    cin >> i;
}


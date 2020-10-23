#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cinttypes>
#include <sstream>
#include <cstdio>
#include <array>
#include <cstring>

std::string youtube_dl_caller(std::string URL){
    FILE* stream = NULL;
    std::string youtube_dl_command, results;
    std::array<char, 5> buffer;
    
    youtube_dl_command = "youtube-dl -g " + URL ;
    char command[youtube_dl_command.size() + 1];
    std::strcpy(command, youtube_dl_command.c_str());

    stream = _popen(command,"r");
    while (fgets(buffer.data(), 5, stream) != nullptr){

        results += buffer.data();
    }
    auto returnCode = pclose(stream);

    return results;
}

int ffmpeg_caller(std::vector<std::string> streamURLs, std::string time_start, std::string duration ){
    auto video_stream = streamURLs.at(0);
    auto audio_stream = streamURLs.at(1);
    std::string command = "ffmpeg -ss " + time_start + " -i \"" + video_stream + "\" -ss " + time_start + " -i \"" + audio_stream + "\" -t " + duration + " -map 0:v -map 1:a -c:v libx264 -c:a aac output.mkv";
    system(command.c_str());
    return 0;
}


int main(){
    int i;
    std::string youtubeURL,time_start,duration_to_end,youtube_dl_command,results;
    std::vector<std::string> output;
    
    std::cout << "Enter the youtube URL:" << std::endl;
    std::cin >> youtubeURL;

    std::cout<< "Time for clip start (HH:MM:SS.MSMS): " << std::endl;
    std::cin >> time_start;

    std::cout << "Duration of clip (HH:MM:SS.MSMS)" << std::endl;
    std::cin >> duration_to_end;

    std::string youtube_caller = youtube_dl_caller(youtubeURL);
    std::vector<std::string> storage;
    std::stringstream ss(youtube_caller);
    
    while(ss.good()){
        std::string single_line;
        getline(ss,single_line,'\n');
        output.push_back(single_line);
    }

    int a = ffmpeg_caller(output, time_start, duration_to_end);
    std::cout << "Command has finished, press any key to leave";
    std::cin >> i;
}

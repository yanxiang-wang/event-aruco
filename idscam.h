#ifndef IDSRECORDER_H
#define IDSRECORDER_H

#include <opencv2/core.hpp>
#include <ueye.h>
#include <atomic>
#include <thread>
#include "liveview.h"

class IDSCam
{
    std::vector <cv::Mat> frames;
    std::vector<INT> mem_ids;
    std::vector<int> mem_indices;
    std::vector<long long int> time_stamps;
    std::vector<INT> ts_memids;
    int num_frames;
    HIDS cam_handle;

    LiveView *liveWindow;

    static void grabber(std::vector<cv::Mat>* frames_p, std::atomic_bool *live_view, std::atomic_bool *recording, std::vector<long long int> *t_sts, HIDS *cam_handle, LiveView *lw);
    static void stamper(HIDS *cam_handle, std::atomic_bool *recording, std::atomic_int *buff_index, std::vector<long long int> *tsts);
    static void player(std::atomic_bool *playing, LiveView* window, std::string folder_path, std::vector<long long int> *time_stamps_p, std::vector<cv::Mat> *frames_p, long long int s);
    std::thread liveView_t,stamper_t,player_t;
    std::atomic_bool recording,live_view,playing;
    std::atomic_int buffer_index;

public:
    IDSCam(LiveView* lw,int nf=1800);//1800 frames = 30 seconds with 60 fps
    ~IDSCam();

    void openCam();
    void start();
    void stop();
    void record();
    void play(long long int s);
    void play(std::string folder_path, long long int s=1);
    void playAndLoad(std::string folder_path, long long int s=1);
    void saveFrames(std::string folder_path);
    void loadFrames(std::string folder_path);
};

#endif // IDSRECORDER_H

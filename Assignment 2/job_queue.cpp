#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Thread {
    int idx;
    long long time;
};


class JobQueue {
private:
    int num_workers_;
    vector<int> jobs_;
    vector<int> assigned_workers_;
    vector<long long> start_times_;
    vector<Thread> threads_;

    void WriteResponse() const {
        for (int i = 0; i < jobs_.size(); ++i) {
            cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
        }
    }

    void ReadData() {
        int m;
        cin >> num_workers_ >> m;
        jobs_.resize(m);
        for(int i = 0; i < m; ++i)
            cin >> jobs_[i];
    }

    void SiftDown(int i, int size){
        int min_idx = i;
        int l_idx = 2*i + 1;
        int r_idx = 2*i + 2;
        if(l_idx > (size-1) && r_idx > (size-1)){return;}
        if(l_idx <= (size-1) && threads_[l_idx].time <= threads_[min_idx].time){
            if(threads_[l_idx].time == threads_[min_idx].time){
                if(threads_[l_idx].idx < threads_[min_idx].idx){min_idx = l_idx;}
            }
            else{min_idx = l_idx;}
        }
        if(r_idx <= (size-1) && threads_[r_idx].time <= threads_[min_idx].time){
            if(threads_[l_idx].time == threads_[r_idx].time){
                if(threads_[l_idx].idx < threads_[r_idx].idx){min_idx = l_idx;}
                else if(threads_[l_idx].idx > threads_[r_idx].idx){min_idx = r_idx;}
            }
            else{min_idx = r_idx;}
        }
        if(i != min_idx){
            swap(threads_[i], threads_[min_idx]);
            SiftDown(min_idx, size);
        }

    }

    void AssignJobs() {
        assigned_workers_.resize(jobs_.size());
        start_times_.resize(jobs_.size());
        threads_.resize(num_workers_);

        for(int m = 0; m < num_workers_; ++m){
            threads_[m].idx = m;
            threads_[m].time = 0;
        }

        for(int i = 0; i < jobs_.size(); ++i) {
            assigned_workers_[i] = threads_[0].idx;
            start_times_[i] = threads_[0].time;
            threads_[0].time += jobs_[i];
            SiftDown(0, num_workers_);
        }
    }

public:
    void Solve() {
        ReadData();
        AssignJobs();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    JobQueue job_queue;
    job_queue.Solve();
    return 0;
}

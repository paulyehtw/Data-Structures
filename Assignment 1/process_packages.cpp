#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Request {
    Request(int arrival_time, int process_time):
            arrival_time(arrival_time),
            process_time(process_time)
    {}

    int arrival_time;
    int process_time;
};

struct Response {
    Response(bool dropped, int start_time):
            dropped(dropped),
            start_time(start_time)
    {}

    bool dropped;
    int start_time;
};

class Buffer {
public:
    Buffer(int size):
            size(size),
            finish_time()
    {}

    Response Process(const Request &request) {
        if(finish_time.empty()){
            finish_time.push(request.process_time);
            return Response( false, request.arrival_time );
        }
        if(finish_time.size() >= size){
            if(request.arrival_time < finish_time.front()){return Response( true, -1 );}
            else{
                int start_t = max(finish_time.back(), request.arrival_time);
                finish_time.pop();
                finish_time.push(request.process_time + start_t);
                return Response( false, start_t );
            }

        }
        else{
            int start_t = max(finish_time.back(), request.arrival_time);
            finish_time.push(request.process_time + start_t);
            return Response( false, start_t );
        }
    }
private:
    int size;
    std::queue <int> finish_time;
};

std::vector <Request> ReadRequests() {
    std::vector <Request> requests;
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
        int arrival_time, process_time;
        std::cin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }
    return requests;
}

std::vector <Response> ProcessRequests(const std::vector <Request> &requests, Buffer *buffer) {
    std::vector <Response> responses;
    for (int i = 0; i < requests.size(); ++i)
        responses.push_back(buffer->Process(requests[i]));
    return responses;
}

void PrintResponses(const std::vector <Response> &responses) {
    for (int i = 0; i < responses.size(); ++i)
        std::cout << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
}

int main() {
    int size;
    std::cin >> size;
    std::vector <Request> requests = ReadRequests();

    Buffer buffer(size);
    std::vector <Response> responses = ProcessRequests(requests, &buffer);

    PrintResponses(responses);
    return 0;
}

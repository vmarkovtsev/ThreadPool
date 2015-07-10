#include <iostream>
#include <vector>
#include <chrono>
#include <sstream>

#include "ThreadPool.hpp"

int main()
{
    
    ThreadPool pool;
    std::vector< std::future<int> > results;
    std::ostringstream buf;

    std::cout << "Workers: " << pool.size() << std::endl;

    for(int i = 0; i < 8; ++i) {
        results.emplace_back(
            pool.enqueue([i] {
                std::cout << "hello " << i << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << "world " << i << std::endl;
                return i*i;
            })
        );
    }

    buf << '<' << pool.pending() << '>';
    std::cout << buf.str();

    for(auto && result: results)
        std::cout << result.get() << ' ';
    std::cout << std::endl;
    
    return 0;
}

class Twitter {
private:
    int timer = 0;

    unordered_map<int, vector<pair<int, int>>> tweets;

    unordered_map<int, unordered_set<int>> following;

public:
    Twitter() {
        
    }

    void postTweet(int userId, int tweetId) {
        tweets[userId].push_back({timer++, tweetId});
    }

    vector<int> getNewsFeed(int userId) {
        priority_queue<tuple<int, int, int>> pq;

        unordered_set<int> users = following[userId];
        users.insert(userId);

        for (int id : users) {
            if (!tweets[id].empty()) {
                int index = tweets[id].size() - 1;
                auto [time, tweetId] = tweets[id][index];

                pq.push({time, id, index});
            }
        }

        vector<int> feed;

        while (!pq.empty() && feed.size() < 10) {
            auto [time, id, index] = pq.top();
            pq.pop();

            feed.push_back(tweets[id][index].second);

            if (index > 0) {
                index--;
                auto [prevTime, prevTweet] = tweets[id][index];

                pq.push({prevTime, id, index});
            }
        }

        return feed;
    }

    void follow(int followerId, int followeeId) {
        if (followerId != followeeId) {
            following[followerId].insert(followeeId);
        }
    }

    void unfollow(int followerId, int followeeId) {
        following[followerId].erase(followeeId);
    }
};

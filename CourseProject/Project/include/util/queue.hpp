#ifndef QUEUE_HPP
#define QUEUE_HPP

template<class T>
class queue {
    constexpr static int INF = -1;
    struct node {
        T value;
        node *next = nullptr;
        node *prev = nullptr;
    };
public:
    queue(int max_size = INF)
            : max_size_(max_size),
              size_(0),
              head_(nullptr),
              tail_(nullptr) {
    }

    void push_back(const T &t) {
        if (!head_) {
            head_ = new node();
            head_->value = t;
            tail_ = head_;
        } else {
            if (max_size_ != INF && size_ + 1 > max_size_)
                pop_front();
            node *prev = tail_;
            tail_ = new node();
            tail_->value = t;
            prev->next = tail_;
        }
        ++size_;
    }

    void pop_front() {
        if (head_) {
            if (head_->next) {
                node *tmp = head_;
                head_ = head_->next;
                head_->prev = nullptr;
                delete tmp;
            } else {
                delete head_;
            }
            --size_;
        }
    }

    node *begin() {
        return head_;
    }

    node *end() {
        return nullptr;
    }

    T &back() {
        return tail_->value;
    }

    int size() const {
        return size_;
    }

    int max_size() const {
        return max_size_;
    }

private:
    int max_size_;
    int size_;
    node *head_;
    node *tail_;
};

#endif // QUEUE_HPP

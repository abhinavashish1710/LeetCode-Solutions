class MinStack {
    stack<int> st,mn;

public:
    MinStack() {}
    
    void push(int value) {
        st.push(value);
        mn.push(mn.empty()?value:min(value,mn.top()));
    }
    
    void pop() {
        st.pop();
        mn.pop();
    }
    
    int top() {
        return st.top();
    }
    
    int getMin() {
        return mn.top();
    }
};

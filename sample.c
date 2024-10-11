class Solution {
  public:
    Node* addOne(Node* head) {
        // Your Code here
        // return head of list after adding one
        
        Node *newHead = reverse(head);
        Node *temp = newHead;
        int c = 1;
        while(newHead){
            newHead->data+=1;
            if(newHead->data<10){
                c = 0;
                break;
            }
            newHead->data = 0;
            c = 1;
            newHead=newHead->next;
        }
        if(c==1){
            
            temp = reverse(temp);
            Node *newData = new Node(1);
            newData->next = temp;
            temp = newData;
            return temp;
        }
        temp = reverse(temp);
        return temp;
        
        
    }
    
};
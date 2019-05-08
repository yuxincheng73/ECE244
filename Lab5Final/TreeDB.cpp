/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "TreeDB.h"
#include "TreeNode.h"

// the default constructor, creates an empty database.
TreeDB:: TreeDB() {
    root = NULL;
    probesCount = 0;
}

// the destructor, deletes all the entries in the database.
TreeDB:: ~TreeDB() {
    clear();
}

// inserts the entry pointed to by newEntry into the database. 
// If an entry with the same key as newEntry's exists 
// in the database, it returns false. Otherwise, it returns true.
bool TreeDB:: insert(DBentry* newEntry) {
    //if tree is empty
    if(root == NULL) {
        root = new TreeNode(newEntry);
        return true;
    }
    
    //check for duplicates
    if(find(newEntry->getName()) != NULL) {
        return false;
    }
    
    //create a new node for the insert to attach to 
    TreeNode* insertNode = traverseToNode(root, newEntry->getName());
    
    //insert the new node at insertNode
    if(newEntry->getName() < insertNode->getEntry()->getName()) {
        insertNode->setLeft(new TreeNode(newEntry));
    }
    
    else if(newEntry->getName() > insertNode->getEntry()->getName()) {
        insertNode->setRight(new TreeNode(newEntry));
    }
    
    return true;
}

   // searches the database for an entry with a key equal to name.
   // If the entry is found, a pointer to it is returned.
   // If the entry is not found, the NULL pointer is returned.
   // Also sets probesCount
   DBentry* TreeDB:: find(string name) {
       probesCount = 0;
       return findHelper(root, name);
   }

   // deletes the entry with the specified name (key)  from the database.
   // If the entry was indeed in the database, it returns true.
   // Returns false otherwise.
   // See section 6 of the lab handout for the *required* removal method.
   // If you do not use that removal method (replace deleted node by
   // maximum node in the left subtree when the deleted node has two children)
   // you will not match exercise's output.
   bool TreeDB:: remove(string name) {
       //if empty tree
       if(root == NULL) 
           return false;
       //if node doesn't exist 
       else if(find(name) == NULL)
           return false;
       
       TreeNode* newHead;
       TreeNode* deleteNode;
       bool isLeft = false;
       bool isHead = false;
       
       //if deleting the top node
       if(root->getEntry()->getName() == name) {
           isHead = true;
           isLeft = true;
           newHead = new TreeNode(new DBentry());
           deleteNode = root;
           newHead->setLeft(root);
       }
       //find where to delete the node that isn't the top node 
       else {
           newHead = traverseToNodeAbove(root, name);
           
           if(newHead->getLeft()->getEntry()->getName() == name) {
               deleteNode = newHead->getLeft();
               isLeft = true;
           }
           else {
               deleteNode = newHead->getRight();
               isLeft = false;
           }
       }
       //actually deleting the node by checking left, right, and subtrees of the node to be deleted
       if(deleteNode->getLeft() == NULL) {
           if(deleteNode->getRight() == NULL) {
               if(isLeft)
                   newHead->setLeft(NULL);
               else
                   newHead->setRight(NULL);
           }
           //the node only has one branched subtree to the right 
           else {
               if(isLeft)
                   newHead->setLeft(deleteNode->getRight());
               else 
                   newHead->setRight(deleteNode->getRight());
           }
           if(isHead) {
               root = deleteNode->getRight();
               delete newHead;
               newHead = NULL;
           }
           delete deleteNode;
       }
       //the node only has one branched subtree to the left
       else if(deleteNode->getRight() == NULL) {
           if(isLeft) 
               newHead->setLeft(deleteNode->getLeft());
           else 
               newHead->setRight(deleteNode->getLeft());
           if(isHead) {
               root = deleteNode->getLeft();
               delete newHead;
               newHead = NULL;
           }
           delete deleteNode;
       }
       //if the node to be deleted has a full subtree, left and right
       //according to the lab handout, we want to find the largest node in the left subtree
       else {
           if(deleteNode->getLeft()->getRight() == NULL) {
               if(isLeft)
                   newHead->setLeft(deleteNode->getLeft());
               else
                   newHead->setRight(deleteNode->getLeft());
               
               deleteNode->getLeft()->setRight(deleteNode->getRight());
               
               if(isHead) {
                   root = deleteNode->getLeft();
                   delete newHead;
                   newHead = NULL;
               }
               delete deleteNode;
           }
           else {
                TreeNode* temp = removeLargestSubtree(deleteNode->getLeft());

                if(isLeft) 
                    newHead->setLeft(temp);
                else
                    newHead->setRight(temp);

                if(isHead) {
                    root = temp;
                    delete newHead;
                    newHead = NULL;
                }

                //reattach the rest of the subtree to the position of deleteNode
                temp->setLeft(deleteNode->getLeft());
                temp->setRight(deleteNode->getRight());
                delete deleteNode;
           }
       }
       return true;
   }
	
   // deletes all the entries in the database.
   void TreeDB:: clear() {
       removeAll(root);
       root = NULL;
   }
    
   // prints the number of probes stored in probesCount
   void TreeDB:: printProbes() const {
       cout << probesCount << endl;
   }
   
   // computes and prints out the total number of active entries
   // in the database (i.e. entries with active==true).
   void TreeDB:: countActive () const {
       //traverse the entire tree
       cout << traverseBT(root) << endl;
   }

   // Prints the entire tree, in ascending order of key/name
   ostream& operator<< (ostream& out, const TreeDB& rhs) {
       rhs.printHelper(rhs.root);
       return out;
   }
   
   //returns the node that we want to insert at, traversing to the left and right
   TreeNode* TreeDB:: traverseToNode(TreeNode* current, string key) {
       //traverse to the left
       if(current->getEntry()->getName() > key) {
           if(current->getLeft() == NULL) 
               return current;
           else
               return traverseToNode(current->getLeft(), key);
       }
       
       //traverse to the right 
       else if(current->getEntry()->getName() < key) {
           if(current->getRight() == NULL) 
               return current;
           else 
               return traverseToNode(current->getRight(), key);
       }
       
       //return null 
       return NULL;
   }
   
   //helper function to find a node
   DBentry* TreeDB:: findHelper(TreeNode* findNode, string name) {
       if(root == NULL)
           return NULL;
       if(findNode == NULL) 
           return NULL;
       
       probesCount++;
       if(findNode->getEntry()->getName() == name) {
           return findNode->getEntry();
       }
       else if(findNode->getEntry()->getName() > name) {
           return findHelper(findNode->getLeft(), name);
       }
       else 
           return findHelper(findNode->getRight(), name);
   }
   
   //returns the node above the node we are at
   TreeNode* TreeDB:: traverseToNodeAbove(TreeNode* current, string key) {
       //traverse left
       if(current->getEntry()->getName() > key) {
           if(current->getLeft()->getEntry()->getName() == key)
               return current;
           else
               return traverseToNodeAbove(current->getLeft(), key);
       }
       
       //traverse to the right
       else if(current->getEntry()->getName() < key) {
           if(current->getRight()->getEntry()->getName() == key)
               return current;
           else
               return traverseToNodeAbove(current->getRight(), key);
       }
   }
   
   //finds the node that has the largest subtree and disconnects it
   TreeNode* TreeDB:: removeLargestSubtree(TreeNode* current) {
       if(current->getRight()->getRight() == NULL) {
           TreeNode* temp = current->getRight();
           
           if(temp->getLeft() != NULL)
               current->setRight(temp->getLeft());
           else
               current->setRight(NULL);
           
           temp->setLeft(NULL);
           temp->setRight(NULL);
           return temp;
       }
       else {
           removeLargestSubtree(current->getRight());
       }
       return NULL;
   }
   
   //deletes all the nodes in the tree
   void TreeDB:: removeAll(TreeNode* current) {
       //if empty tree
       if(current == NULL)
           return;
       
       //recursively move down the tree
       removeAll(current->getLeft());
       current->setLeft(NULL);
       removeAll(current->getRight());
       current->setRight(NULL);
       
       //delete node
       delete current;
       current = NULL;
       
       return;
   }
   
   //traverse the entire tree
   int TreeDB:: traverseBT(TreeNode* current) const {
       if(current == NULL)
           return 0;
       //add 1 if node is active
       else if(current->getEntry()->getActive())
           return (traverseBT(current->getLeft()) + traverseBT(current->getRight()) + 1);
       //else just keep it the same
       else
           return (traverseBT(current->getLeft()) + traverseBT(current->getRight()));
   }
   
   //traverses the entire tree and prints each node
   void TreeDB:: printHelper(TreeNode* current) const {
       //if tree is empty
       if(current == NULL)
           return;
       else {
           printHelper(current->getLeft());
           cout << *current->getEntry() << endl;
           printHelper(current->getRight());
           return;
       }
   }
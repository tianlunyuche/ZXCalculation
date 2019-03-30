//
//  main.cpp
//  ZXCalculation
//
//  Created by xinying on 2018/12/15.
//  Copyright © 2018年 habav. All rights reserved.
//

#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <string>
#include "CMyString.cpp"

using namespace std;


struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x):
    val(x), next(NULL) {
    }
};

struct RandomListNode {
    int label;
    struct RandomListNode *next , *radom;
    RandomListNode(int x):
    label(x), next(NULL), radom(NULL) {
        
    }
};

//树结点
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x) , left(NULL) , right(NULL) {}
};

class Shili {
    static int a;
    void m2() {
        
    }
    Shili() {
        
    }
    ~Shili() {
        
    }
};

class Solution1 {
    
public:
    
    //剑指Offer（三）：输入一个链表，输出一个反序的链表
    vector<int> printList(ListNode *head) {
        stack<int> nodes;
        vector<int> results;
        ListNode *node = head;
        
        while (node != NULL) {
            nodes.push(node->val);
            node = node->next;
        }
        
        while (!nodes.empty()) {
            results.push_back(nodes.top()); //将nodes栈顶值 加到 矢量数组results里
            nodes.pop();
        }
        
        return results;
    }
    //剑指Offer（十四）：返回链表中倒数第k个结点
    //用两个指针，指针a和b都指向第一个结点，当a遍历到 第k个结点，及a走了k-1步，
    //b和a开始同步遍历，直到a走到最后一个结点，b指向的刚好就是倒数第k个结点
    ListNode* findKth(ListNode *head , int k) {
        if (head == NULL || k == 0) {
            return NULL;
        }
        ListNode *a = head;
        ListNode *b = head;
        for (int i = 0; i < k-1; i++) {
            if (a->next != NULL) {
                a = a->next;
            } else {
                return NULL;
            }
        }
        
        while (a->next != NULL) {
            a = a->next;
            b = b->next;
        }
        return b;
    }
//    剑指Offer（十五）：反转链表： 1234， 变成4321
    //用到3个结点：前一个，当前和下一个结点，改变当前结点的nex指向 到前一个结点
    ListNode* ReverseList(ListNode* pHead) {
        ListNode* pReversedHead = NULL;
        ListNode* pNode = pHead;
        ListNode* pPrev = NULL;
        while(pNode != NULL){
            ListNode* pNext = pNode->next;
            if(pNext == NULL){
                pReversedHead = pNode;
            }
            //改变指向
            //a -> b 变成 a <- b
            pNode->next = pPrev;
            //准备下一次遍历用，当前结点作为 前一个结点，下一个结点作为 当前结点
            // 即 往后移动一步 以便下次遍历操作
            pPrev = pNode;
            pNode = pNext;
 
        }
        return pReversedHead;
    }
    
//    剑指Offer（十六）：合并两个排序的链表
    //创建一个合并后的新链表结点，判断取较小的结点 赋值给 新的结点mergeList ，mergeList 后移，继续递归 取较小的结点，直到任意一个链表到头
    ListNode* merge(ListNode *list1 , ListNode *list2) {
        ListNode *mergeList = NULL;
        if (list1 == NULL) {
            mergeList = list2;
        } else
            if (list2 == NULL) {
                mergeList = list1;
            }
            else {
                if (list1->val < list2->val) {
                    mergeList = list1;
                    mergeList->next = merge(list1->next, list2);
                } else {
                    mergeList = list2;
                    mergeList->next = merge(list1, list2->next);
                }
            }
        return mergeList;
    }
    
    
//    剑指Offer（二十五）：复杂链表的复制
    //复制后的结点跟原结点是前后关系，即在同一个链表上
    //（1）先复制label和next，(2)再复制radom，(3)最后拆分链表
    RandomListNode *clone(RandomListNode *head) {
        RandomListNode *pNode = head;
        while (pNode != NULL) {
            //1
            RandomListNode *pCloned = new RandomListNode(0);
            pCloned->label = pNode->label;
            pCloned->next = pNode->next;
            
            pNode->next = pCloned;
            
            pNode = pCloned->next;
        }
        
        
        //2
        pNode = head;
        while (pNode != NULL) {
            RandomListNode *pCloned = pNode->next;
            if (pNode->radom != NULL) {
                pCloned->radom = pNode->radom->next;
            }
            pNode = pCloned->next;
        }
        
        //3
        pNode = head;
        RandomListNode *pClonedHead = NULL; //最终要返回的头结点
        RandomListNode *pClonedNode = NULL;
        
        if (pNode != NULL) {
            pClonedHead = pClonedNode = pNode->next;
            pNode->next = pClonedNode->next;    //将原链表还原，原结点指向下一个原结点
            pNode = pNode->next;        //获取到 第二个原结点
        }
        
        while (pNode != NULL) {
            pClonedNode->next = pNode->next;
            pClonedNode = pClonedNode->next;
            pNode->next = pClonedNode->next; //将原链表还原，原结点指向下一个原结点
            pNode = pNode->next;
        }
        return pClonedHead;
    }
    
//    剑指Offer（三十六）：两个链表的第一个公共结点
    ListNode *findFirstCommonNode(ListNode *head1, ListNode *head2) {
        if (head1 == NULL || head2== NULL) {
            return NULL;
        }
        unsigned int len1 = GetListLength(head1);
        unsigned int len2 = GetListLength(head2);
        
        ListNode *longHead, *shortHead;
        int dif;
        if (len1 < len2) {
            longHead = head2;
            shortHead = head1;
            dif = len2 - len1;
        } else {
            longHead = head1;
            shortHead = head2;
            dif = len1 - len2;
        }
        
        for (int i = 0; i< dif; i++) {
            longHead = longHead->next;
        }
        
        while (longHead!= NULL && shortHead!=NULL && (longHead!= shortHead)) {
            longHead = longHead->next;
            shortHead = shortHead->next;
        }
        return longHead;
    }
    
//    剑指Offer(二)：替换空格
    //遍历计算字符串原始的长度，和空格数量， 计算替换后新字符串的 总长度：原长度+ 2*空格数量，
    //从后往前遍历，将后面的字符 赋值到。最终的位置，如果是空格，赋值为“%20”
    void replaceSpace(string str) {
        if (str.empty()) {
            return;
        }
        int originLen =0, blankNum = 0;
        int i = 0;
        while (str[i++] != '\0') {
            ++originLen;
            if (str[i] == ' ') {
                ++blankNum;
            }
        }
        
        int newLen = originLen + 2* blankNum;
        
        int originIndex = originLen;
        int newIndex= newLen;
        
//        for (int i = originLen; i < newLen; i++) {
//            str[originLen] = '0';
//        }
        
        while (originIndex >= 0 && newLen > originIndex) {
            if (str[originIndex] == ' ') {
                str[newIndex--] = '0';
                str[newIndex--] = '2';
                str[newIndex--] = '%';
            } else {
                str[newIndex--] = str[originIndex];         //有bug，没有开辟空间
            }
            --originIndex;
        }
    }
    
//    剑指Offer（五十五）：链表中环的入口结点
    //使用快慢指针（相差1步）找到环中的任意一个结点，环中的这个结点 再走一圈，计算出环的结点总数；
    //然后 取相差步数为 环结点总数的两个 指针，同步遍历，直到两个指针都指向 同一个结点，该结点则为
    //环入口结点
    ListNode *entryNodeOfLoop(ListNode *pHead) {
        if (pHead == NULL) {
            return NULL;
        }
        ListNode *meetingNode = MeetingNode(pHead);
        if (meetingNode == NULL) {
            return NULL;
        }
        
        //环中结点总数
        int nodesloop = 1;
        //
        ListNode *pNode1 = meetingNode;
        while (pNode1->next != meetingNode) {
            pNode1 = pNode1->next;
            nodesloop++;
        }
        pNode1 = pHead;
        //第一个指针向前移动 nodesloop步
        for (int i= 0; i< nodesloop; i++) {
            pNode1 = pNode1->next;
        }
        //两个指针同时移动，找到环入口
        ListNode *pNode2 = pHead;
        while (pNode1 != pNode2) {
            pNode1 = pNode1->next;
            pNode2 = pNode2->next;
        }
        return pNode1;
    }
    
//    剑指Offer（二十七）：字符串的排列
    // 如果字符相同 则不交换，不相同则位置交换；当第一位和最后一位 交换完成，递归结束，result添加字符串.
    //位置交换:后面的字符的第一个字符，以及这个字符之后的所有字符, 把第一个字符逐一和它后面的字符交换。
    vector<string> Permutation(string str) {
        if (str.length() == 0) {
            return result;
        }
        PermutiaonCore(str ,0);
        //对结果进行排序
//        sort(result.begin(), result.end());
        return result;
    }
    
    
    //剑指Offer（三十四）：返回字符串中 第一个只出现一次的字符 位置
    //建立一个哈希表，第一次扫描时 统计每个字符 出现次数；
    //第二次扫描时，如果出现次数为1，返回这个字符位置 ；
    int FirstNotRepeatingChar(string str) {
        int len = (int)str.size();
        if (len == 0) {
            return -1;
        }
        
        map<char, int> item;
        for (int i =0; i < len; i++) {
            item[str[i]]++;
        }
        
        for (int i = 0; i < len; i++) {
            if (item[str[i]] == 1) {
                return i;
            }
        }
        return -1;
    }
    
//    剑指Offer（四十三）：左旋转字符串
    //例如输入字符串"abcdefg"和数字2，该函数将返回左旋转2位得到的结果"cdefgab";
    //左旋转n位 的实现：先对前 n位翻转，然后 对len - n位翻转，最后对整个字符串 翻转
    string LeftRotateString(string str, int n) {
        string result = str;
        int len = (int)result.size();
        if (len < 0) {
            return NULL;
        }
        if (0 <= n <= len) {
            ReverseString(result, 0, n-1);
            ReverseString(result, n, len-1);
            ReverseString(result, 0, len-1);
        }
        return result;
    }
    
//    剑指Offer（四十四）：翻转单词顺序序列
    //一个句子： “student. am a I“,翻转成 “I am a student.“
    //扫描一遍，如果第i位 是空格，第一次是 翻转 0到i-1 ，标记 mark = i+1,
    //继续扫描，在遇到空格，翻转 mark 到i-1数字 ， 最后整个字符串翻转
    string ReverseSentence(string str) {
        string result = str;
        int len = (int)result.size();
        if (len == 0) {
            return "";
        }
        
        result += ' ';
        int mark = 0;
        //反转所有单词
        for (int i = 0; i < len +1; i++) {
            if (result[i] == ' ') {
                ReverseString(result, mark, i-1);
                mark = i+1;
            }
        }
        //去掉添加空格
        result = result.substr(0, len);
        //整体翻转
        ReverseString(result, 0, len - 1);
        return result;
    }
    
    //剑指Offer（四十九）：把字符串转换成整数
    //(1)判断 指针是否位空，字符串是否为空，
    //(2)字符串对于正负号的处理；
    //(3)输入值 是否为合法值，即大于等于‘0’,小于等于‘9’
    //(4)int为32位，需要判断是否 溢出；
    //（5)使用错误标志，区分合法值0和非法值0
    enum Status{
        kValid = 0,
        kInValid
    };
    int g_nStatus = kInValid;
    int StrToInt(string str) {
            long long num = 0;
            const char* cstr = str.c_str();
            //(1)
            if (cstr != NULL && *cstr != '\0') {
                //(2)正负号标志位，默认是加号
                bool minus = false;
                if (*cstr == '+') {
                    cstr++;
                } else if (*cstr == '-') {
                    minus = true;
                    cstr++;
                }
                
                //(3),(4)
                while (*cstr != '\0') {
                    //判断是否是 非法值
                    if (*cstr >= '0' && *cstr <= '9') {
                        int flag = minus ? -1 : 1;
                        num = num * 10 + flag * (*cstr - '0');
                        //判断是否溢出， 32位
                        if ((!minus && num > 0x7fffffff) ||
                            (minus && num < (signed int)0x80000000)) {
                            num = 0;
                            break;
                        }
                        cstr++;
                    }
                    else {
                        num = 0;
                        break;
                    }
                }
                //判断是否正常结束
                if (*cstr == '\0') {
                    g_nStatus = kValid;
                }
            }
            return (int)num;
    }
    
//    剑指Offer（五十二）：* . 正则表达式匹配
    //字符串和模式串都为空，返回false；
    //字符串和 模式串都到结尾，返回true；
    //字符串没到结尾，模式串到了，返回false，
    //如果模式串的下一个字符是'*'，进入状态机匹配：
    /**字符串和模式串相等，或者 模式串是‘.’且 字符串不等于‘0’，
     *  ‘*’匹配1个，进入到下一个状态，字符串后移1位，模式串后移2位
        或者 ‘*’匹配下一个字符，保持当前状态，字符串后移1位，,继续用 '*'去匹配
         跳过‘*’匹配0个，str不移动，模式串后移2位。
         如果字符串和模式串不相等，则跳过当前模式串的字符和'*'，进入新一轮的匹配。
         如果字符串和模式串相等，或者模式串是'.'，并且字符串没有到结尾，则继续匹配
     **/
    bool match(char *str, char *pattern) {
        if (str == NULL || pattern == NULL) {
            return false;
        }
        if (*str == '\0' && *pattern == '\0') {
            return true;
        }
        //字符串没有到结尾，模式串到了，则返回false
        if (*str != '\0' && *pattern == '\0') {
            return false;
        }
        //
        if (*(pattern + 1) == '*') {
            if (*str == *pattern || (*pattern == '.' && *str != '\0')) {
                return match(str + 1, pattern + 2) ||
                match(str + 1, pattern) ||
                match(str, pattern + 2);
            }
            else {
                return match(str, pattern + 2);
            }
        }
        
        if (*str == *pattern || (*pattern == '.' && *str != '\0')) {
            return match(str + 1, pattern + 1);
        }
        return false;
    }
    
//    剑指Offer（一）：二维数组中的查找：
//    在一个二维数组中，每一行按照从左到右 递增顺序，每一列从上到下递增顺序，
    //输入一个这样数组，和一个整数，在数组中查找是否有这个整数，时间复杂度要求为 O（n）
    //思路： 选取 数组中右上角的数，比较输入的整数，若相等，返回；
//            若大于输入整数值，剔除数字所在的列；
//            若小于输入整数值，剔除数字所在行；
//            直到查找到这个整数，或查找范围为空了
    bool  findVector(int target, vector<vector<int>> array) {
        int rows = (int)array.size();
        int cols = (int)array[0].size();
        
        if (!array.empty() && rows > 0 && cols > 0) {
            int row = 0;
            int col  = cols -1;
            
            while (row < rows && col >= 0) {
                if (array[row][col] == target) {
                    return true;
                } else
                    if (array[row][col] > target) {
                        --col;
                    } else {
                        ++row;
                    }
            }
        }
        return false;
    }
    
//    剑指Offer（四）：重建二叉树
    TreeNode* reConstructBinaryTree(vector<int> pre, vector<int>vin) {
        if (pre.size() == 0) {
            return NULL;
        }
        
        //前序遍历 左子树／右 ，中序遍历 左子树／右
        vector<int> left_pre, right_pre , left_vin , right_vin;
        
        TreeNode *head = new TreeNode(pre[0]);
        
        //找中序遍历中 的根结点pre[0]位置
        int vin_root_loc = 0;
        for (int i = 0; i < vin.size(); i++) {
            if (pre[0]  == vin[i]) {
                vin_root_loc = i;
                break;
            }
        }
        
//     利用中序遍历 的根结点 ，对二叉树结点进行归并，
//        即 分成两部分，放到 左子树的数组 和 右子树 数组中
        for (int i = 0; i < vin_root_loc; i++) {
            left_pre.push_back(pre[i + 1]);
            left_vin.push_back(vin[i]);
        }
        
        for (int i = vin_root_loc + 1; i < pre.size(); i++) {
            right_pre.push_back(pre[i]);
            right_vin.push_back(vin[i]);
        }
        
        //递归， 再进行上述步骤，区分子树的 左右子树，直到 叶子结点
        head->left = reConstructBinaryTree(left_pre, left_vin);
        head->right  = reConstructBinaryTree(right_pre, right_vin);
        
        return head;
    }

//    剑指Offer（十七）：树的子结构 -树1 是否含有 树2 作为子结构
    // 如果 树1 的根结点值 等于 树2 根结点值，则 遍历 两棵树的 左结点和右结点是否相同；
//      如果树1的根结点不等于 树2的根结点，则用递归 将树1的左结点作为根结点来遍历；
    //      如果树1的根结点不等于 树2的根结点，则用递归 将树1的右结点作为根结点来遍历；
    
    bool HasSubtree(TreeNode *p1 ,TreeNode *p2)
    {
        bool result = false;
        if (p1 != NULL && p2 != NULL) {
            if (p1->val == p2->val) {
                result = DoesTreeHasTree2(p1, p2);
            }
            
            if (!result) {
                result = HasSubtree(p1->left, p2);
            }
            if (!result) {
                result = HasSubtree(p1->right, p2);
            }
        }
        return result;
    }
    
//    剑指Offer（二十三）：二叉搜索树的后序遍历序列：
//    给定一个数组，判断它是否是 二叉搜索树的后序遍历序列
//    先判断数组的左子树和右子树的位置（右子树的第一个值的位置），
//    然后利用 递归 再判断左右子树是不是 二叉搜索树
    bool VerifySquenceOfBST(vector<int> sequece) {
        return bst(sequece, 0, sequece.size() - 1);
    }
    
    
//    剑指Offer（二十六）：二叉搜索树与双向链表
    //输入二叉搜索树的根指针，输出 中序遍历排序的 双向链表
    TreeNode *Convert(TreeNode *pRootOfTree) {
        //用来记录双向链表的尾结点
        TreeNode *pLastNodeInList = NULL;
        
        ConvertNode(pRootOfTree, &pLastNodeInList);
        //利用 pLastNodeInList双向链表的尾结点 来
//        获取链表的头结点
        TreeNode *pHeadOfList = pLastNodeInList;
        while (pHeadOfList != NULL &&
               pHeadOfList->left != NULL) {
            pHeadOfList = pHeadOfList->left;
        }
        return pHeadOfList;
    }
    
//    剑指Offer（六十五）：矩阵中的路径
    //给一个矩阵用字符串指针表示，和要匹配的字符串指针，返回是否匹配成功bool
    //如果输入矩阵为空；行数，列表小于1，要匹配的字符串为空，返回false
    //创建一个被访问的布尔数组，初始化为0；
    //pathLength为当前要匹配的字符位置，
    //取当前要匹配的字符，对矩阵遍历，如果当前的矩阵字符相等，且未被访问过，则
//    取下一个要匹配的字符，同时当前的矩阵字符位置设为已访问；
    //对 当前的矩阵字符相邻的4个字符进行 递归 比较，
    //如果 hasPath为false，重新去上一个 要匹配的字符，再进行 递归比较，
    //直到 str[pathLength] = '\0'
    bool hasPath(char *matrix, int rows, int cols, char *str) {
        if (matrix == NULL || rows < 1 || cols < 1
            || str == NULL) {
            return false;
        }
        
        bool *visited = new bool(rows * cols);
        memset(visited, 0, rows * cols);
        
        int pathLength = 0;
        //循环遍历获取到 匹配字符串的起始位置
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                //
                if (hasPathCore(matrix, rows, cols,
                                row, col, str, pathLength,
                                visited)) {
                   
                    delete[] visited;
                    return true;
                }
            }
        }
        delete[] visited;
        return false;
    }
    
    
private:
    bool hasPathCore(char *matrix, int rows, int cols,
                     int row, int col, char *str,
                     int pathLength, bool *visited) {
        if (str[pathLength] == '\0') {
            return true;
        }
        bool hasPath = false;
        if (row >= 0 && row < rows && col >= 0 && col < cols
            && matrix[row*cols + col] == str[pathLength]
            && !visited[row*cols + col]) {
            
            ++pathLength;
            visited[row * cols + col] = true;
            
            hasPath = hasPathCore(matrix, rows, cols, row - 1, col, str, pathLength, visited)
                   || hasPathCore(matrix, rows, cols, row + 1, col, str, pathLength, visited)
                   || hasPathCore(matrix, rows, cols, row   , col - 1, str, pathLength, visited)
            || hasPathCore(matrix, rows, cols, row   , col + 1, str, pathLength, visited);
            
            if (!hasPath) {
                --pathLength;
                visited[row * cols + col] = false;
            }
        }
        return hasPath;
    }
    
    void ConvertNode(TreeNode *pNode ,TreeNode **pLastNodeInList) {
        if (pNode == NULL) {
            return;
        }
        
        TreeNode *pCurrent = pNode;
        //(1) 递归左子树，获取最左结点;
//        (2) 给该结点 左指针和右指针赋值；
        //(3) 给pLastNodeInList 链表最后结点的指针赋值
        //然后获取 右子树的结点，
        if (pCurrent->left != NULL) {
            ConvertNode(pCurrent->left, pLastNodeInList);
        }
        
        //左指针
        pCurrent->left  = *pLastNodeInList;
        //
        if (*pLastNodeInList != NULL) {
            (*pLastNodeInList)->right = pCurrent;
        }
        
        //
        *pLastNodeInList = pCurrent;
        
        //
        if (pCurrent->right != NULL) {
            ConvertNode(pCurrent->right, pLastNodeInList);
        }
    }
    
    bool bst(vector<int> seq, int begin, unsigned long end) {
        if (seq.empty() || begin > end) {
            return false;
        }
        
        //根结点
        int root = seq[end];
        
        //二叉搜索树中左子树的结点 小于根结点
        int i = begin;
        for (; i < end; ++i) {
            if (seq[i] > root) {
                break;
            }
        }
        
        //二叉搜索树的右子树 所有结点 都是大于 根结点
        for (int j = i; j < end; ++i) {
            if (seq[j] < root) {
                return false;
            }
        }
        
        //判断左子树 是不是 二叉搜索树
        bool left  = true;
        if (i > begin) {
            left  = bst(seq, begin, i - 1);
        }
        
        bool right = true;
        if (i < end - 1) {
            right = bst(seq, i, end - 1);
        }
        
        return left && right;
    }
    
    bool DoesTreeHasTree2(TreeNode *p1, TreeNode *p2)
    {
        if (p2 == NULL) {
            return true;
        } else
            if (p1 == NULL) {
                return false;
            } else
                if (p1->val != p2->val) {
                    return false;
                } else
                {
                    return DoesTreeHasTree2(p1->left, p2->left) &&
                    DoesTreeHasTree2(p1->right, p2->right);
                }
    }
    
    void ReverseString(string &str ,int begin ,int end) {
        while (begin < end) {
            swap(str[begin++], str[end--]);
        }
    }
    
    vector<string> result;
    void PermutiaonCore(string str ,int begin) {
        //递归结束的条件： 第一位和最后一位 交换完成
        if (begin == str.length()) {
            result.push_back(str);
            return;
        }
        for (int i= begin; i < str.length(); i++) {
            //如果字符相同， 则不交换
            if (i != begin && str[i]  == str[begin]) {
                continue;
            }
            //位置交换
            swap(str[begin], str[i]);
            //递归调用，前面 begin+1 的位置不变，后面的字符串全排列
            PermutiaonCore(str ,begin + 1);
        }
    }
    
    unsigned int GetListLength(ListNode *pHead) {
        if (pHead == NULL) {
            return 0;
        }
        unsigned int length  = 1;
        while (pHead->next != NULL) {
            pHead = pHead->next;
            length++;
        }
        return length;
    }
    
    //使用快慢指针，找到环中 任意一个结点
    ListNode *MeetingNode(ListNode *pHead) {
        ListNode *pSlow = pHead->next;
        if (pSlow == NULL) {
            return NULL;
        }
        ListNode *pFast = pSlow->next;
        while (pFast != NULL && pSlow != NULL) {
            if (pFast == pSlow) {
                return pFast;
            }
            pSlow = pSlow->next;
            pFast = pFast->next;
            if (pFast != NULL) {
                pFast = pFast->next;
            }
        }
        return NULL;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    //剑指Offer（三）：输入一个链表，输出一个反序的链表
    Solution1 *so1 = new Solution1();
    
    ListNode *no1  = new ListNode(1);
    ListNode *no2  = new ListNode(2);
    ListNode *no3  = new ListNode(3);
    ListNode *no4  = new ListNode(4);
    no1->next = no2;
    no2->next = no3;
    no3->next = no4;
    
    vector<int> d = so1->printList(no1);
    //------------------------------------
    //剑指Offer（十四）：返回链表中倒数第k个结点
//    ListNode *so14 = so1->findKth(no1, 2);
//  //    剑指Offer（十五）：反转链表： 1234， 变成4321
//    ListNode *so3 = so1->ReverseList(no1);
    
    //    剑指Offer（十六）：合并两个排序的链表
    ListNode *no5  = new ListNode(5);
    ListNode *so4 = so1->merge(no1, no5);
    
//    剑指Offer（二十五）：复杂链表的复制
    RandomListNode *ro1  = new RandomListNode(1);
    RandomListNode *ro2  = new RandomListNode(2);
    RandomListNode *ro3  = new RandomListNode(3);
    ro1->next = ro2;
    ro2->next = ro3;
    ro1->radom = ro3;
    ro2->radom = ro1;
    
    RandomListNode *so5 = so1->clone(ro1);
    
    ListNode *so6 = so1->findFirstCommonNode(no1, no3);
    
    string ds = "we are happy.";
    so1->replaceSpace(ds);
    //全排列
    vector<string> so7 =  so1->Permutation("qba");
    
    int so8 = so1->FirstNotRepeatingChar("abbca");
    
    string so9 = so1->LeftRotateString("abcdef", 4);
    
    string so10 = so1->ReverseSentence("student. am a I");
    
    int so11 = so1->StrToInt("-13422342");
    
    char nzArr[100]="abcd";
//    memset(nzArr,'g',sizeof(nzArr));
    
    
    vector<int> pre = {1,2,4,7,3,5,6,8};
    vector<int> vin = {4,7,2,1,5,3,8,6};
    TreeNode *node = so1->reConstructBinaryTree(pre, vin);
    
    Shili *voidshili;
    cout << "value: " << sizeof(voidshili);
    
    
    return 0;
}



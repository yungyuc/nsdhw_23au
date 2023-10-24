# NSD project proposal: k-d tree

## Basic Information
> [Github Repo](https://github.com/adcf3016/kdtree)
- K-d(k-dimensional tree) tree is a Multidimensional BST.
It is a very useful data structure for those who need to store and access multi-key data.
It also supports searching data in a given range.

## Problem to Solve
- There are a few problems to be solved if we need to implement a k-d tree library:
    1. When we start to build the k-d tree, there is some way to choose the root among the multi-key data set
        - Choosing the median from each dimension.
        And then compare which dimension's median makes the number of left and right subtrees closer to each other, as better as possible.
        This will create balanced k-d tree.
        - We have the following parameters that allow us to determine the different options for choosing the root
            - cell
            - bounding rectangle
            - aspect ratio
            - spread

    2. Implement the basic operation of k-d tree such as `findNearest` and `rangeSearch`

## Prospective Users
- A simple library of k-d tree for those who need to store and access data with multiple key values, and also need to search for a specific range of data.

## API Description
- k-d tree class overview
    ```c++
    class KdTree {
        public:
            kdTree(vector<vector<double>> data_set, int dimension);
            void insert(vector<double> node);
            bool delete(vector<double> node);
            bool search(vector<double> node);
            vector<double> findNearest(vector<double> node);
            vector<vector<double>> rangeSearch(vector<double> lowerbound,
                                               vector<double> upperbound);
            vector<double> findMin(int dimension);
            vector<double> findMax(int dimension);

        private:
            KdTree *left;
            KdTree *right;
            vector<double> key;
    };
    ```
- class function usage
    - `kdTree`
        - Choosing the root node and recursive build subtree
    - `insert`
        - Insert new data into current k-d tree
    - `delete`
        - Delete the provided data in k-d tree.
        Return delete sucess or not.
    - `search`
        - Return if the data provided is in the tree or not
    - `findNearest`
        - Find the nearest node to the node provided
    - `rangeSearch`
        - Find all data with key value between lowerbound and upperbound
    - `findMin` & `findMax`
        - Find min/max value of the given dimension

## Engineering Infrastructure
1. Automatic build system: `Makefile`
2. Version control: `git`
3. Wrapping module: `pybind11`
4. Testing framework: `pytest`
5. Documentation: `README.md`

## Schedule
### Week 1 (10/30)
- Study different types of k-d tree splits and decide what type to implement.
- Implement `kdTree`
- Write the Makefile for this project

### Week 2 (11/6)
- Continue implement `kdTree`

### Week 3 (11/13)
- Implement `insert`, `delete`, `search`

### Week 4 (11/20)
- Implement `findMin`, `findMax`
- Write pytest to test `kdTree`, `insert`, `delete`, `findMin`, `findMax`

### Week 5 (11/27)
- Implement `findNearest`, `rangeSearch`

### Week 6 (12/4)
- Write pytest to test `findNearest`, `rangeSearch`

### Week 7 (12/11)
- Flextime

### Week 8 (12/18)
- Flextime

## References
- [Wikipedia](https://en.wikipedia.org/wiki/K-d_tree)
- [KD-tree Algorithm Note by YuCheng](https://blog.yucheng.me/post/kd-tree/)
- [KD Tree Learning Note by Chih-Hao Liu](https://tomohiroliu22.medium.com/%E6%A9%9F%E5%99%A8%E5%AD%B8%E7%BF%92-%E5%AD%B8%E7%BF%92%E7%AD%86%E8%A8%98%E7%B3%BB%E5%88%97-69-k%E7%B6%AD%E6%A8%B9-kd-tree-b3b8591c9245)
- To be added...

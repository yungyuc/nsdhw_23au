# NSD Project: Kernel K-means on Image

### Basic Information
This project is the implementation of Kernel K-means on image with c++ and python. I will also try to accelerate the computation on GPU by using CUDA if time is enough.

### Problem to Solve
I will do clustering on image data by using kernel kmeans, which "similar" pixels would be grouped together. 

Kernel k-means is well-known unsupervised clustering algorithm. It will find k cluster centers to represent each group, and assign each data point to its nearest center like traditional k-means. Different from traditional k-means using euclidean distance, kernel kmeans utilize kernel function to calculate distance:

$$\begin{aligned}
\min_{k} (||\phi(x_j) - \mu_{k}||) = \min_{k} (||\phi(x_j) - \sum_{n} {\alpha_{k}^{n} \phi(x_n)} ||)
\end{aligned}
$$

where $x$ represent data point which consists of pixel value (rgb) and posistion, $\phi$ means kernel function, $\mu$ means cluster center, and $alpha$ is assignment with the value 0 or 1. kernel kmeans would search the appropriate assignment that cause minimum distance.

### Prospective Users
Those who want to do segmentation task on image data useful in image processing and computer vision application.

### System Architecture
I will first take image as input and extract the pixel value (rgb) and position (i,j) as data features. Then, the algorithm group the image pixel according to these features. Finally, I will visualize the segmented result on image.

### API Description
The estimated API is below:
#### c++
```c++
class KernelKmeans{
    public:
        KernelKmeans(int k, int max_iter);
        void extract_features();
        vector<double> do_cluster(cv::Mat const & img);
        double calc_dist(vector<double> const & x, vector<double> const & y);
        //...
    private:
        vector<vector<double>> m_image_data;
        vector<int> m_alpha;
        cv::Mat m_img;
        int m_max_iter;
        int m_k;
        //....
};

```

#### python
Pybind11 is used to wrap c++ API, and the python API can accept the numpy format as input.

### Engineering Infrastructure
-   Build system: Makefile
-   Version control: Git
-   Testing framework: Pytest
-   Wrapping: Pybind11


## Schedule

Week 1 (10/31): Implement the naive c++ code without multithread.

Week 2 (11/7):  Finish the naive c++ code and search the way for accelerating the matrix operation (ex: multi-threading).

Week 3 (11/14): Implement the matrix operation with multithread.

Week 4 (11/21): Wrapping with pybind11

Week 5 (11/28): Search how to compute on GPU with CUDA.

Week 6 (12/5): Prepare for the project presentation.

Week 7 (12/12): Implement the cuda code.

Week 8 (12/19): Finish the oral slides..

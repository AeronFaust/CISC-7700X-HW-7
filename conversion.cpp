#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void convert(const string& imgf, const string& labelf, const string& outf, int n) 
{
    ifstream f(imgf, ios::binary);
    ofstream o(outf);
    ifstream l(labelf, ios::binary);

    f.seekg(16);
    l.seekg(8);

    vector<vector<int>> images;

    for (int i = 0; i < n; ++i) 
    {
        vector<int> image;
        char label;
        l.read(&label, 1);
        for (int j = 0; j < 28 * 28; ++j) 
        {
            char pixel;
            f.read(&pixel, 1);
            image.push_back(static_cast<int>(pixel));
        }
        image.push_back(static_cast<int>(label));

        images.push_back(image);
    }

    for (const auto& image : images) {
        for (size_t i = 0; i < image.size(); ++i) 
        {
            o << image[i];
            if (i != image.size() - 1)
                o << ",";
        }
        o << "\n";
    }

    f.close();
    o.close();
    l.close();
}

int main() 
{
    convert("train-images.idx3-ubyte", "train-labels.idx1-ubyte", "mnist_train.csv", 60000);
    convert("t10k-images.idx3-ubyte", "t10k-labels.idx1-ubyte", "mnist_test.csv", 10000);

    return 0;
}
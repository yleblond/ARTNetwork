#include <iostream>
#include "artsettings.hpp"
#include "prgsettings.hpp"
#include "image.hpp"
#include <fstream>
#include <string>

typedef unsigned char uchar;


ARTSettings* getNetworkSettings() {
    ARTSettings* s = new ARTSettings();
    s->nOutputs = 40;
    s->I_VIGILANCE = 0.8;
    return s;
}

ProcessSettings* getProcessSettings() {
    ProcessSettings* s = new ProcessSettings();
    s->LEARNING_MAXITEMS = -1;
    s->QUERY_MAXITEMS = -1;
    return s;
}



uchar** read_mnist_images(std::string full_path, int& number_of_images, int& image_size, int& image_width, int& image_height) {
    auto reverseInt = [](int i) {
        unsigned char c1, c2, c3, c4;
        c1 = i & 255, c2 = (i >> 8) & 255, c3 = (i >> 16) & 255, c4 = (i >> 24) & 255;
        return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
    };

    typedef unsigned char uchar;

    std::ifstream file(full_path, std::ios::binary);

    if(file.is_open()) {
        int magic_number = 0, n_rows = 0, n_cols = 0;

        file.read((char *)&magic_number, sizeof(magic_number));
        magic_number = reverseInt(magic_number);

        if(magic_number != 2051) throw std::runtime_error("Invalid MNIST image file!");

        file.read((char *)&number_of_images, sizeof(number_of_images)), number_of_images = reverseInt(number_of_images);
        file.read((char *)&n_rows, sizeof(n_rows)), n_rows = reverseInt(n_rows);
        file.read((char *)&n_cols, sizeof(n_cols)), n_cols = reverseInt(n_cols);

		image_width = n_cols;
		image_height = n_rows;
        image_size = n_rows * n_cols;

        uchar** _dataset = new uchar*[number_of_images];
        for(int i = 0; i < number_of_images; i++) {
            _dataset[i] = new uchar[image_size];
            file.read((char *)_dataset[i], image_size);
        }
        return _dataset;
    } else {
        throw std::runtime_error("Cannot open file `" + full_path + "`!");
    }
}

uchar* read_mnist_labels(std::string full_path, int& number_of_labels) {
    auto reverseInt = [](int i) {
        unsigned char c1, c2, c3, c4;
        c1 = i & 255, c2 = (i >> 8) & 255, c3 = (i >> 16) & 255, c4 = (i >> 24) & 255;
        return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
    };

    typedef unsigned char uchar;

    std::ifstream file(full_path, std::ios::binary);

    if(file.is_open()) {
        int magic_number = 0;
        file.read((char *)&magic_number, sizeof(magic_number));
        magic_number = reverseInt(magic_number);

        if(magic_number != 2049) throw std::runtime_error("Invalid MNIST label file!");

        file.read((char *)&number_of_labels, sizeof(number_of_labels)), number_of_labels = reverseInt(number_of_labels);

        uchar* _dataset = new uchar[number_of_labels];
        for(int i = 0; i < number_of_labels; i++) {
            file.read((char*)&_dataset[i], 1);
        }
        return _dataset;
    } else {
        throw std::runtime_error("Unable to open file `" + full_path + "`!");
    }
}

void printArrayAsHex(const unsigned char* array, size_t size, int imageWidth) {
    for (size_t i = 0; i < size; ++i) {
        // Print each byte in hexadecimal format
        // std::hex: Format number in hexadecimal
        // std::setw(2): Set width of the next integer to 2 characters
        // std::setfill('0'): Fill empty character spaces with '0'
        // static_cast<int>(array[i]): Cast uchar to int for proper stream handling
        
        std::cout << std::hex << std::setw(2) << std::setfill(' ') << static_cast<int>(array[i]) << " ";
        if (i%imageWidth) {
        } else {
	        std::cout << "\n";
        }
    }
    std::cout << std::dec << std::endl; // Switch back to decimal format
}


int test(void)
{
	//std::string labelFile = "./t10k-labels.idx1-ubyte";
	//std::string imageFile = "./t10k-images.idx3-ubyte";

	std::string labelFile = "./train-labels.idx1-ubyte";
	std::string imageFile = "./train-images.idx3-ubyte";
	
    printf("Load MNIST files !!!\n");
    
    int numberOfImages;
    int image_size;
    int image_width;
    int image_heigth;
    int numberOfLabels;

    uchar** images = read_mnist_images(imageFile, numberOfImages, image_size, image_width, image_heigth);
    uchar* labels = read_mnist_labels(labelFile, numberOfLabels);

    printf("numberOfImages %d\n", numberOfImages);
    printf("image_size %d\n", image_size);
    printf("numberOfLabels %d\n", numberOfLabels);

        
        for(int i = 0; i < numberOfLabels; i++) {
		    printf("label[%d] -> %d\n", i, labels[i]);
        }

       for(int j = 0; j < numberOfImages; j++) {
		    printf("image[%d] : %d\n", j, (j<numberOfLabels) ? labels[j] : -1);
		    printArrayAsHex(images[j], image_size, image_width);
        }
       
    return 0;
}


ImageSet* getMnistFiles(const char* labelFile, const char* imageFile)
{
    ImageSet* set = new ImageSet();


    printf("Load MNIST files !!!\n");
    
    int numberOfImages;
    int image_size;
    int image_width;
    int image_heigth;
    int numberOfLabels;

    uchar* labels = read_mnist_labels(labelFile, numberOfLabels);
    uchar** images = read_mnist_images(imageFile, numberOfImages, image_size, image_width, image_heigth);

    printf("numberOfImages %d\n", numberOfImages);
    printf("image_size %d\n", image_size);
    printf("image_width %d\n", image_width);
    printf("image_heigth %d\n", image_heigth);
    printf("numberOfLabels %d\n", numberOfLabels);
           
    set->nEntrees = image_size;
	set->nExemples = numberOfImages;
	set->imageSize = image_size;
	set->width = image_width;
    set->height = image_heigth;


	Image** figure = (Image**) calloc(numberOfImages+1,sizeof(Image*));

    for(int k = 0; k < numberOfImages; k++) {
    	// prepare image data
    	float* image= new float[image_size];
    	// assign pixel float values
    	for (int p=0; p<image_size; p++) {
    		uchar pixel = images[k][p];
    		image[p] = (float)pixel / 256.0;
    	}
    	// create image object
    	figure[k] = new Image();
    	figure[k]->setData(image);
    	figure[k]->setLabel(labels[k]);
        figure[k]->setDimensions(image_width, image_heigth);
    }
	figure[numberOfImages]=0;

    set->learningFigure = figure;
	return set;
}

ImageSet* getLearningPattern()
{
	return getMnistFiles("./train-labels.idx1-ubyte","./train-images.idx3-ubyte");
}

ImageSet* getReconnaissancePattern()
{
	return getMnistFiles("./t10k-labels.idx1-ubyte","./t10k-images.idx3-ubyte");
}

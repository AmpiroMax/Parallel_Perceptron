#include <fstream>
#include <vector>

/**
 * @brief Переводит число из big endian в little endian
 * @param i - число, которое будет обращаться
 * @return перевёрнытый int
 */
int reverseInt(int i)
{
    unsigned char c1, c2, c3, c4;
    c1 = i & 255, c2 = (i >> 8) & 255, c3 = (i >> 16) & 255, c4 = (i >> 24) & 255;
    return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
};

/**
 * @brief Чтение изображений MNIST из бинарного файла
 * @param full_path        - расположение файла для чтения
 * @param number_of_images - число изображений, которое считалось
 * @param image_size       - размер изображений, лежавших в файле
 * @return матрицу uchar   - считынне изображения
 *
 * Считывает изображения и созраняет их в матрицу uchar**. Каждое изображение
 * кодируется положительным целым числом от 0 до 255, представленное char.
 */
char **read_mnist_images(std::string full_path, int &number_of_images, int &image_size)
{
    std::ifstream file(full_path, std::ios::binary);

    if (file.is_open())
    {
        int magic_number = 0, n_rows = 0, n_cols = 0;

        file.read((char *)&magic_number, sizeof(magic_number));
        magic_number = reverseInt(magic_number);

        if (magic_number != 2051)
            throw std::runtime_error("Invalid MNIST image file!");

        file.read((char *)&number_of_images, sizeof(number_of_images)), number_of_images = reverseInt(number_of_images);
        file.read((char *)&n_rows, sizeof(n_rows)), n_rows = reverseInt(n_rows);
        file.read((char *)&n_cols, sizeof(n_cols)), n_cols = reverseInt(n_cols);

        image_size = n_rows * n_cols;

        char **_dataset = new char *[number_of_images];
        for (int i = 0; i < number_of_images; i++)
        {
            _dataset[i] = new char[image_size];
            file.read((char *)_dataset[i], image_size);
        }
        return _dataset;
    }
    else
    {
        throw std::runtime_error("Cannot open file `" + full_path + "`!");
    }
}

/**
 * @brief Чтение лейблов картинок MNIST из бинарного файла
 * @param full_path        - расположение файла для чтения
 * @param number_of_labels - число считанных label
 * @return массив uchar*   - массив из значений labels для
 *                           соответствующей картинки
 */
char *read_mnist_labels(std::string full_path, int &number_of_labels)
{
    std::ifstream file(full_path, std::ios::binary);

    if (file.is_open())
    {
        int magic_number = 0;
        file.read((char *)&magic_number, sizeof(magic_number));
        magic_number = reverseInt(magic_number);

        if (magic_number != 2049)
            throw std::runtime_error("Invalid MNIST label file!");

        file.read((char *)&number_of_labels, sizeof(number_of_labels)), number_of_labels = reverseInt(number_of_labels);

        char *_dataset = new char[number_of_labels];
        for (int i = 0; i < number_of_labels; i++)
        {
            file.read((char *)&_dataset[i], 1);
        }
        return _dataset;
    }
    else
    {
        throw std::runtime_error("Unable to open file `" + full_path + "`!");
    }
}

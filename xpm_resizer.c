#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to hold the image data
typedef struct {
    int width;
    int height;
    char** data;
}	Image;

// Function to read an XPM file into an Image structure
Image* read_xpm(const char* filename) {
    Image* img = NULL;
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        char buffer[1024];
        // Read the image dimensions from the file
        fgets(buffer, sizeof(buffer), file);
        int width, height;
        sscanf(buffer, "%d %d", &width, &height);
        // Allocate memory for the image data
        img = (Image*)malloc(sizeof(Image));
        img->width = width;
        img->height = height;
        img->data = (char**)malloc(sizeof(char*) * height);
        for (int i = 0; i < height; i++) {
            img->data[i] = (char*)malloc(sizeof(char) * (width + 1));
        }
        // Read the image data from the file
        for (int i = 0; i < height; i++) {
            fgets(buffer, sizeof(buffer), file);
            strncpy(img->data[i], buffer, width);
            img->data[i][width] = '\0';
        }
        fclose(file);
    }
    return img;
}

// Function to write an Image structure to an XPM file
void write_xpm(const char* filename, const Image* img) {
    FILE* file = fopen(filename, "w");
    if (file != NULL) {
        // Write the image dimensions to the file
        fprintf(file, "%d %d\n", img->width, img->height);
        // Write the image data to the file
        for (int i = 0; i < img->height; i++) {
            fprintf(file, "%s\n", img->data[i]);
        }
        fclose(file);
    }
}

// Function to resize an image using nearest-neighbor interpolation
Image* resize_image(const Image* src, int width, int height) {
    Image* dst = (Image*)malloc(sizeof(Image));
    dst->width = width;
    dst->height = height;
    dst->data = (char**)malloc(sizeof(char*) * height);
    for (int i = 0; i < height; i++) {
        dst->data[i] = (char*)malloc(sizeof(char) * (width + 1));
    }
    double dx = (double)src->width / width;
    double dy = (double)src->height / height;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int sx = (int)(x * dx + 0.5);
            int sy = (int)(y * dy + 0.5);
            dst->data[y][x] = src->data[sy][sx];
        }
        dst->data[y][width] = '\0';
    }
    return dst;
}

int main(int argc, char** argv)
{
	if (argc != 4) {
		printf("Usage: resize <original> <width> <height>\n");
		return (1);
	}
    // Read the original image from a file
    Image* src = read_xpm(argv[1]);
    if (src == NULL) {
        printf("Error reading XPM file.\n");
        return (1);
    }
    // Resize the image to a new size
    Image* dst = resize_image(src, atoi(argv[2]), atoi(argv[3]));
    if (dst == NULL) {
        printf("Error resizing image.\n");
		return (1);
	}
	// Write the resized image to a new file
	write_xpm("resized.xpm", dst);
	// Free the memory used by the images
	for (int i = 0; i < src->height; i++) {
		free(src->data[i]);
	}
	free(src->data);
	free(src);
	for (int i = 0; i < dst->height; i++) {
		free(dst->data[i]);
	}
	free(dst->data);
	free(dst);
	return (0);
}
